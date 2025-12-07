# 📝 To-Do List com Pilha e Grafo de Dependências em C

Um projeto simples em C que implementa uma "To-Do List" (Lista de Tarefas) básica, rodando no terminal. A aplicação utiliza a estrutura de dados **Pilha (Stack)** para gerenciar os itens da lista e a estrutura de **Grafo** para mapear as dependências entre as tarefas.

Este projeto foi criado como um exercício prático da faculdade para demonstrar o uso de pilhas, grafos, gerenciamento de memória (`malloc`/`free`) e manipulação de ponteiros em C.

Alunos: 
João Manoel Freire,
João Pedro Magalhães,
Rafael Maia,
Leonardo Freitas Barboza e
Bruno Braga Ramos.

## O Conceito da Pilha (LIFO)

A lógica da To-Do List para gerenciamento de tarefas é baseada em **LIFO (Last-In, First-Out)**, que é o princípio fundamental de uma Pilha. Isso significa que:

* O **último** item que você adiciona à lista é o **primeiro** que aparece para ser concluído.

## O Conceito do Grafo de Dependências (BFS/DFS)

Para adicionar uma camada de complexidade e utilidade, o projeto foi estendido para incluir um **Grafo Não Direcionado** que mapeia as relações de dependência ou associação entre as tarefas.

*   **Vértices:** Cada tarefa é um vértice no grafo.
*   **Arestas:** Uma aresta conecta duas tarefas que possuem uma relação de dependência mútua.

O uso de algoritmos de travessia de grafos (BFS e DFS) permite analisar a estrutura de dependências das tarefas.

## Funcionalidades

O programa tem um menu simples com as seguintes operações, divididas em gerenciamento de Pilha e gerenciamento de Grafo:

### Gerenciamento de Pilha (To-Do List)

1.  **Adicionar novo item:** Empilha (`push`) uma nova tarefa no topo da pilha.
2.  **Concluir/Desfazer último item (Undo):** Desempilha (`pop`) o item do topo da pilha (a tarefa mais recente) e o move para uma pilha de "Refazer".
3.  **Refazer item desfeito (Redo):** Move o item da pilha de "Refazer" de volta para a pilha principal.
4.  **Ver próximo item (Topo):** Apenas visualiza (`peek`) o item no topo da pilha, sem removê-lo.
5.  **Mostrar todos os itens (Display):** Exibe todas as tarefas na lista.
6.  **Sair:** Encerra o programa, salva o estado e libera toda a memória alocada (`free`) de forma segura.

### Gerenciamento de Grafo (Dependências)

7.  **Adicionar Dependência:** Cria uma aresta não direcionada entre duas tarefas, registrando uma relação mútua.
8.  **Ver Grupo de Tarefas Relacionadas (DFS):** Dado o nome de uma tarefa, utiliza a Busca em Profundidade (DFS) para encontrar e listar todas as tarefas que estão conectadas a ela (o componente conexo).
9.  **Verificar Conexão entre Tarefas (BFS):** Dado o nome de duas tarefas, utiliza a Busca em Largura (BFS) para verificar se existe um caminho entre elas e, se houver, exibe o caminho mais curto.

## 📁 Estrutura do Código

O código foi separado em múltiplos arquivos para melhor organização e modularidade:

*   **`pilha.h` / `pilha.c`**: Implementação da estrutura de dados Pilha para o gerenciamento básico da To-Do List.
*   **`grafo.h` / `grafo.c`**: Implementação da estrutura de dados Grafo (Lista de Adjacência) e dos algoritmos de travessia (BFS e DFS) para o gerenciamento de dependências.
*   **`utils.h` / `utils.c`**: Funções utilitárias, como a definição de cores para o terminal e a função para limpar o buffer de entrada (`limpar_buffer`).
*   **`main.c`**: O programa principal que contém o menu, a lógica do usuário e faz a chamada às funções das Pilhas e do Grafo.

## 🚀 Como Compilar e Executar

Para rodar este projeto, você precisa ter o git e um compilador C (como o `gcc`) instalados.

1. Clone o repositório:

    ```bash
    git clone https://github.com/JoaoManoelFMN/c-stack-undo-redo.git
    ```

2. Navegue até o diretório que você acabou de baixar:
    ```bash
    cd c-stack-undo-redo
    ```

3. Compile o programa, incluindo todos os arquivos de implementação:

    ```bash
    gcc -o task_manager main.c grafo.c pilha.c utils.c -Wall
    ```

4. Execute o programa:

    ```bash
    ./task_manager
    ```
