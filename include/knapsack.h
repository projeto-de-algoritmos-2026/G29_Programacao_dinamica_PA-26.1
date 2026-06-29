#pragma once
#include <vector>
#include <algorithm>
#include "modelos.h"

using namespace std;

vector<TarefaEstudo> otimizarTempoLivre(int tempoLivre, vector<TarefaEstudo>& tarefas) {
    int n = tarefas.size();
    
    vector<vector<int>> M(n + 1, vector<int>(tempoLivre + 1, 0));

    for (int i = 1; i <= n; i++) {
        int tempoAtual = tarefas[i - 1].tempoEstimado;
        int prioridadeAtual = tarefas[i - 1].prioridade;

        for (int w = 1; w <= tempoLivre; w++) {
            if (tempoAtual > w) {
                M[i][w] = M[i - 1][w];
            } else {
                M[i][w] = max(M[i - 1][w], prioridadeAtual + M[i - 1][w - tempoAtual]);
            }
        }
    }

    vector<TarefaEstudo> tarefasEscolhidas;
    int wAtual = tempoLivre;
    
    for (int i = n; i > 0 && M[i][wAtual] > 0; i--) {
        if (M[i][wAtual] != M[i - 1][wAtual]) {
            tarefasEscolhidas.push_back(tarefas[i - 1]);
            wAtual -= tarefas[i - 1].tempoEstimado;
        }
    }

    reverse(tarefasEscolhidas.begin(), tarefasEscolhidas.end());

    return tarefasEscolhidas;
}