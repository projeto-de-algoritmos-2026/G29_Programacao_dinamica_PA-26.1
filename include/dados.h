#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "modelos.h"

using namespace std;

int converterParaMinutos(string horario) {
    size_t pos = horario.find(':');
    if (pos != string::npos) {
        int h = stoi(horario.substr(0, pos));
        int m = stoi(horario.substr(pos + 1));
        return (h * 60) + m;
    }
    return stoi(horario) * 60;
}

string formatarTempo(int minutos) {
    int h = minutos / 60;
    int m = minutos % 60;
    string horaStr = (h < 10 ? "0" : "") + to_string(h);
    string minStr = (m < 10 ? "0" : "") + to_string(m);
    return horaStr + ":" + minStr;
}

void salvarDadosJSON(const vector<AulaFixa>& aulas, const vector<TarefaEstudo>& tarefas) {
    ofstream arquivo("data/dados.json");
    if (!arquivo.is_open()) return;

    arquivo << "{\n  \"aulas\": [\n";
    for (size_t i = 0; i < aulas.size(); i++) {
        arquivo << "    {\"id\": " << aulas[i].id << ", \"nome\": \"" << aulas[i].nomeDisciplina 
                << "\", \"inicio\": " << aulas[i].inicio << ", \"fim\": " << aulas[i].fim 
                << ", \"peso\": " << aulas[i].peso << "}";
        if (i < aulas.size() - 1) arquivo << ",";
        arquivo << "\n";
    }
    
    arquivo << "  ],\n  \"tarefas\": [\n";
    for (size_t i = 0; i < tarefas.size(); i++) {
        arquivo << "    {\"id\": " << tarefas[i].id << ", \"descricao\": \"" << tarefas[i].descricao 
                << "\", \"disciplina\": \"" << tarefas[i].disciplina 
                << "\", \"tempoEstimado\": " << tarefas[i].tempoEstimado 
                << ", \"prioridade\": " << tarefas[i].prioridade << "}";
        if (i < tarefas.size() - 1) arquivo << ",";
        arquivo << "\n";
    }
    arquivo << "  ]\n}\n";
    arquivo.close();
}

void carregarDadosJSON(vector<AulaFixa>& aulas, vector<TarefaEstudo>& tarefas) {
    ifstream arquivo("data/dados.json");
    if (!arquivo.is_open()) return;

    aulas.clear();
    tarefas.clear();
    string linha;
    int modo = 0;

    AulaFixa aulaTemp;
    TarefaEstudo tarefaTemp;

    while (getline(arquivo, linha)) {
        if (linha.find("\"aulas\":") != string::npos) modo = 1;
        else if (linha.find("\"tarefas\":") != string::npos) modo = 2;

        if (modo == 1 && linha.find("\"id\":") != string::npos) {
            aulaTemp.id = stoi(linha.substr(linha.find("\"id\":") + 5));
            
            int posNome = linha.find("\"nome\": \"") + 9;
            aulaTemp.nomeDisciplina = linha.substr(posNome, linha.find("\"", posNome) - posNome);
            
            aulaTemp.inicio = stoi(linha.substr(linha.find("\"inicio\":") + 9));
            aulaTemp.fim = stoi(linha.substr(linha.find("\"fim\":") + 6));
            aulaTemp.peso = stoi(linha.substr(linha.find("\"peso\":") + 7));
            
            aulas.push_back(aulaTemp);
        } 
        else if (modo == 2 && linha.find("\"id\":") != string::npos) {
            tarefaTemp.id = stoi(linha.substr(linha.find("\"id\":") + 5));
            
            int posDesc = linha.find("\"descricao\": \"") + 14;
            tarefaTemp.descricao = linha.substr(posDesc, linha.find("\"", posDesc) - posDesc);
            
            int posDisc = linha.find("\"disciplina\": \"") + 15;
            tarefaTemp.disciplina = linha.substr(posDisc, linha.find("\"", posDisc) - posDisc);
            
            tarefaTemp.tempoEstimado = stoi(linha.substr(linha.find("\"tempoEstimado\":") + 16));
            tarefaTemp.prioridade = stoi(linha.substr(linha.find("\"prioridade\":") + 13));
            
            tarefas.push_back(tarefaTemp);
        }
    }
    arquivo.close();
}