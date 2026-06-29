#pragma once
#include <algorithm>
#include <vector>
#include "modelos.h"

bool compararTermino(const AulaFixa& a, const AulaFixa& b) {
    return a.fim < b.fim;
}

int encontrarUltimoCompativel(const vector<AulaFixa>& aulas, int indiceAtual) {
    int inicio = 0, fim = indiceAtual - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (aulas[meio].fim <= aulas[indiceAtual].inicio) {
            if (aulas[meio + 1].fim <= aulas[indiceAtual].inicio) {
                inicio = meio + 1;
            } else {
                return meio;
            }
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

vector<AulaFixa> otimizarGradeFixa(vector<AulaFixa>& aulas) {
    int n = aulas.size();
    if (n == 0) return {};

    sort(aulas.begin(), aulas.end(), compararTermino);

    vector<int> M(n);
    M[0] = aulas[0].peso;

    for (int i = 1; i < n; i++) {
        int pesoAtual = aulas[i].peso;
        int p_i = encontrarUltimoCompativel(aulas, i);
        if (p_i != -1) {
            pesoAtual += M[p_i];
        }
        M[i] = max(pesoAtual, M[i - 1]);
    }

    vector<AulaFixa> gradeOtimizada;
    int i = n - 1;
    while (i >= 0) {
        int p_i = encontrarUltimoCompativel(aulas, i);
        int valorComAulaAtual = aulas[i].peso + (p_i != -1 ? M[p_i] : 0);

        if (i == 0 || valorComAulaAtual > M[i - 1]) {
            gradeOtimizada.push_back(aulas[i]);
            i = p_i;
        } else {
            i--;
        }
    }

    reverse(gradeOtimizada.begin(), gradeOtimizada.end());
    
    return gradeOtimizada;
}