# G29_Programacao_dinamica_PA-26.1

**Número da lista:** 29

**Conteúdo da disciplina:** Programação Dinâmica

## Alunos

| Nome | Matrícula |
| --- | --- |
| Alan Farias Braga | 251005909 |
| Vilmar José Fagundes | 231026590 |

## Sobre

**Sistema de Gestão e Otimização de Cronogramas de Estudo**

Este projeto acadêmico foi desenvolvido com base no conteúdo de **Programação Dinâmica** para otimização de tempo e planejamento acadêmico. 

O software recebe uma grade de atividades fixas e uma lista de tarefas pendentes (como guias de estudo e listas de exercícios para os currículos) e calcula matematicamente a rotina diária mais eficiente, evitando sobreposição de horários e maximizando o aprendizado.

## Algoritmos

O motor lógico do sistema é dividido em duas abordagens clássicas de Programação Dinâmica:

1. **Agendamento de Intervalos Ponderados (Weighted Interval Scheduling):**
   - **Função:** Organizar a grade horária principal.
   - **Lógica:** Ordena aulas e compromissos fixos pelo tempo de término. Utiliza *Memoization* ou abordagem iterativa *Bottom-Up* para calcular o subconjunto de atividades mutuamente compatíveis que entrega o maior peso/valor total no dia.
   - **Complexidade:** O(n log n) para a ordenação inicial e O(n) para a resolução do subproblema estrutural.

2. **Problema da Mochila (Knapsack Problem):**
   - **Função:** Otimizar o "tempo livre" ou janelas entre as atividades principais.
   - **Lógica:** Trata as horas livres como a "capacidade da mochila" (W) e aloca tarefas secundárias baseadas em sua duração estimada (peso) e nível de prioridade para a aprovação escolar (valor).
   - **Complexidade:** O(n * W) em tempo.

## Como Compilar e Executar

O projeto foi construído em **C++** e homologado para rodar nativamente no Windows utilizando o compilador GCC (MinGW-w64).

### Pré-requisitos
- Ter o `g++` configurado no `PATH` (Variáveis de Ambiente) do Windows.

### Compilação
1. Clone este repositório para a sua máquina local:
   ```powershell
   git clone <url-do-repositorio-da-disciplina>
   ```
2. Pelo terminal (PowerShell ou CMD), navegue até o diretório do projeto:
   ```powershell
   cd caminho\para\o\repositorio
   ```
3. Compile o código-fonte (utilizando a flag de otimização O3):
   ```powershell
   g++ -O3 -o otimizador main.cpp
   ```

### Execução
Após a compilação bem-sucedida, inicie o sistema executando:
```powershell
.\otimizador.exe
```
## Gravação
A gravação pode ser acessada através do link [https://youtu.be/iqbmZo2gGdE](https://youtu.be/iqbmZo2gGdE)
