#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

#include "../include/modelos.h"
#include "../include/interval_scheduling.h"
#include "../include/knapsack.h"
#include "../include/dados.h"

using namespace std;

void limparBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void imprimirGrade(const vector<AulaFixa>& grade) {
    cout << "\n--- GRADE DE AULAS OTIMIZADA ---\n";
    int creditosTotais = 0;
    for (const auto& aula : grade) {
        cout << "[" << formatarTempo(aula.inicio) << " as " << formatarTempo(aula.fim) << "] " 
             << aula.nomeDisciplina << " (Creditos: " << aula.peso << ")\n";
        creditosTotais += aula.peso;
    }
    cout << "Total de creditos compativeis no dia: " << creditosTotais << "\n\n";
}

void imprimirTarefas(const vector<TarefaEstudo>& tarefas, int tempoLivre) {
    cout << "\n--- TAREFAS SELECIONADAS (JANELA DE " << formatarTempo(tempoLivre) << " HORAS) ---\n";
    int tempoGasto = 0;
    int prioridadeTotal = 0;
    for (const auto& t : tarefas) {
        cout << "- " << t.descricao << "\n  [" << t.disciplina << "] -> Tempo: " 
             << formatarTempo(t.tempoEstimado) << "h | Prioridade: " << t.prioridade << "\n";
        tempoGasto += t.tempoEstimado;
        prioridadeTotal += t.prioridade;
    }
    cout << "Tempo total utilizado: " << formatarTempo(tempoGasto) << "h\n";
    cout << "Prioridade total alcancada (maximizada): " << prioridadeTotal << "\n\n";
}

void gerenciarAulas(vector<AulaFixa>& aulas, vector<TarefaEstudo>& tarefas) {
    int opcao = 0;
    while (opcao != 4) {
        cout << "\n--- GERENCIAR GRADE FIXA ---\n";
        cout << "1. Adicionar nova aula\n2. Editar aula existente\n3. Excluir aula\n4. Voltar\nEscolha: ";
        cin >> opcao;

        if (opcao == 1) {
            AulaFixa novaAula;
            novaAula.id = aulas.empty() ? 1 : aulas.back().id + 1;
            limparBuffer();
            string horarioInicio, horarioFim;
            cout << "Nome da Disciplina: ";
            getline(cin, novaAula.nomeDisciplina);
            cout << "Inicio (formato HH:MM): ";
            cin >> horarioInicio;
            novaAula.inicio = converterParaMinutos(horarioInicio);
            cout << "Fim (formato HH:MM): ";
            cin >> horarioFim;
            novaAula.fim = converterParaMinutos(horarioFim);
            cout << "Peso/Creditos: ";
            cin >> novaAula.peso;
            aulas.push_back(novaAula);
            salvarDadosJSON(aulas, tarefas);
            cout << "Aula salva com sucesso no Banco de Dados!\n";
        } 
        else if (opcao == 2) {
            char continuar = 's';
            while (tolower(continuar) == 's') {
                if (aulas.empty()) break;
                cout << "\n--- AULAS CADASTRADAS ---\n";
                for (size_t i = 0; i < aulas.size(); i++) {
                    cout << i + 1 << ". " << aulas[i].nomeDisciplina << " (" << formatarTempo(aulas[i].inicio) << " - " << formatarTempo(aulas[i].fim) << ")\n";
                }
                
                int indexA;
                cout << "Numero da aula para editar: ";
                cin >> indexA; indexA--;

                if (indexA >= 0 && indexA < aulas.size()) {
                    int opcEdicao;
                    string novoHorario;
                    cout << "Editar:\n1. Nome\n2. Inicio (HH:MM)\n3. Fim (HH:MM)\n4. Creditos\nEscolha: ";
                    cin >> opcEdicao;
                    limparBuffer();

                    if (opcEdicao == 1) getline(cin, aulas[indexA].nomeDisciplina);
                    else if (opcEdicao == 2) { cin >> novoHorario; aulas[indexA].inicio = converterParaMinutos(novoHorario); }
                    else if (opcEdicao == 3) { cin >> novoHorario; aulas[indexA].fim = converterParaMinutos(novoHorario); }
                    else if (opcEdicao == 4) cin >> aulas[indexA].peso;
                    
                    salvarDadosJSON(aulas, tarefas);
                    cout << "Alteracao salva no Banco de Dados!\n";
                }
                cout << "\nDeseja editar outra aula? (s/n): ";
                cin >> continuar;
            }
        }
        else if (opcao == 3) {
            int index;
            cout << "Numero da aula para excluir: ";
            cin >> index;
            if (index > 0 && index <= aulas.size()) {
                aulas.erase(aulas.begin() + (index - 1));
                salvarDadosJSON(aulas, tarefas);
                cout << "Aula excluida do Banco de Dados!\n";
            }
        }
    }
}

void gerenciarTarefas(vector<AulaFixa>& aulas, vector<TarefaEstudo>& tarefas) {
    int opcao = 0;
    while (opcao != 4) {
        cout << "\n--- GERENCIAR TAREFAS ---\n";
        cout << "1. Adicionar tarefa\n2. Editar tarefa\n3. Excluir tarefa\n4. Voltar\nEscolha: ";
        cin >> opcao;

        if (opcao == 1) {
            TarefaEstudo novaTarefa;
            novaTarefa.id = tarefas.empty() ? 1 : tarefas.back().id + 1;
            limparBuffer();
            string duracao;
            cout << "Descricao: ";
            getline(cin, novaTarefa.descricao);
            cout << "Disciplina: ";
            getline(cin, novaTarefa.disciplina);
            cout << "Tempo necessario (HH:MM, ex: 01:30): ";
            cin >> duracao;
            novaTarefa.tempoEstimado = converterParaMinutos(duracao);
            cout << "Prioridade (1 a 10): ";
            cin >> novaTarefa.prioridade;
            tarefas.push_back(novaTarefa);
            salvarDadosJSON(aulas, tarefas);
            cout << "Tarefa salva no Banco de Dados!\n";
        } 
        else if (opcao == 2) {
            char continuar = 's';
            while (tolower(continuar) == 's') {
                if (tarefas.empty()) break;
                for (size_t i = 0; i < tarefas.size(); i++) {
                    cout << i + 1 << ". " << tarefas[i].descricao << " (" << formatarTempo(tarefas[i].tempoEstimado) << "h)\n";
                }
                
                int indexT;
                cout << "Numero da tarefa para editar: ";
                cin >> indexT; indexT--;

                if (indexT >= 0 && indexT < tarefas.size()) {
                    int opcEdicao;
                    string novaDuracao;
                    cout << "Editar:\n1. Descricao\n2. Disciplina\n3. Tempo (HH:MM)\n4. Prioridade\nEscolha: ";
                    cin >> opcEdicao;
                    limparBuffer();

                    if (opcEdicao == 1) getline(cin, tarefas[indexT].descricao);
                    else if (opcEdicao == 2) getline(cin, tarefas[indexT].disciplina);
                    else if (opcEdicao == 3) { cin >> novaDuracao; tarefas[indexT].tempoEstimado = converterParaMinutos(novaDuracao); }
                    else if (opcEdicao == 4) cin >> tarefas[indexT].prioridade;
                    
                    salvarDadosJSON(aulas, tarefas);
                    cout << "Alteracao salva no Banco de Dados!\n";
                }
                cout << "\nDeseja editar outra tarefa? (s/n): ";
                cin >> continuar;
            }
        }
        else if (opcao == 3) {
            int index;
            cout << "Numero da tarefa para excluir: ";
            cin >> index;
            if (index > 0 && index <= tarefas.size()) {
                tarefas.erase(tarefas.begin() + (index - 1));
                salvarDadosJSON(aulas, tarefas);
                cout << "Tarefa excluida do Banco de Dados!\n";
            }
        }
    }
}

int main() {
    vector<AulaFixa> gradeAulas;
    vector<TarefaEstudo> tarefasPendentes;

    carregarDadosJSON(gradeAulas, tarefasPendentes);

    int opcao = 0;

    while (opcao != 5) {
        cout << "\n=========================================================\n";
        cout << " OTIMIZADOR DE ESTUDOS - ENG. DE SOFTWARE (FGA/UNB)\n";
        cout << "=========================================================\n";
        cout << "1. Gerar Grade de Aulas Otimizada (Interval Scheduling)\n";
        cout << "2. Otimizar Tempo Livre para Estudos (Knapsack)\n";
        cout << "3. Gerenciar Grade de Aulas\n";
        cout << "4. Gerenciar Tarefas Pendentes\n";
        cout << "5. Sair do Sistema\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (cin.fail()) {
            limparBuffer();
            cout << "Entrada invalida.\n";
            continue;
        }

        if (opcao == 1) {
            vector<AulaFixa> melhorGrade = otimizarGradeFixa(gradeAulas);
            imprimirGrade(melhorGrade);
        } 
        else if (opcao == 2) {
            string janelaTempo;
            cout << "\nTempo livre disponivel agora (HH:MM): ";
            cin >> janelaTempo;
            int tempoDisponivelMinutos = converterParaMinutos(janelaTempo);
            vector<TarefaEstudo> melhoresTarefas = otimizarTempoLivre(tempoDisponivelMinutos, tarefasPendentes);
            imprimirTarefas(melhoresTarefas, tempoDisponivelMinutos);
        } 
        else if (opcao == 3) {
            gerenciarAulas(gradeAulas, tarefasPendentes);
        }
        else if (opcao == 4) {
            gerenciarTarefas(gradeAulas, tarefasPendentes);
        }
    }

    return 0;
}