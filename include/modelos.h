#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct AulaFixa {
    int id;
    string nomeDisciplina;
    int inicio;
    int fim;
    int peso;
};

struct TarefaEstudo {
    int id;
    string descricao;
    string disciplina;
    int tempoEstimado;
    int prioridade;
};