# 📝 To-Do List com Pilha em C

Um projeto simples em C que implementa uma "To-Do List" (Lista de Tarefas) básica, rodando no terminal. A aplicação utiliza a estrutura de dados **Pilha (Stack)** para gerenciar os itens da lista.

Este projeto foi criado como um exercício prático da faculdade para demonstrar o uso de pilhas em C, gerenciamento de memória (`malloc`/`free`) e manipulação de ponteiros.

Alunos: 
João Manoel Freire,
João Pedro Magalhães,
Rafael Maia e
Leonardo Freitas Barboza.

## O Conceito da Pilha (LIFO)

A lógica da To-Do List é baseada em **LIFO (Last-In, First-Out)**, que é o princípio fundamental de uma Pilha. Isso significa que:

* O **último** item que você adiciona à lista é o **primeiro** que aparece para ser concluído.

## Funcionalidades

O programa tem um menu simples com as seguintes operações:

1.  **Adicionar novo item:** Empilha (`push`) uma nova tarefa no topo da pilha.
2.  **Concluir último item:** Desempilha (`pop`) o item do topo da pilha (a tarefa mais recente) e o remove.
3.  **Ver próximo item:** Apenas visualiza (`peek`) o item no topo da pilha, sem removê-lo.
4.  **Sair:** Encerra o programa e libera toda a memória alocada (`free`) de forma segura.

## 📁 Estrutura do Código

O código foi separado em três arquivos para melhor organização, demonstrando a separação entre interface (header) e implementação (código-fonte):

* **`pilha.h`**: O arquivo de cabeçalho (header) que define as `structs` (`No`, `Pilha`) e os protótipos de todas as funções da pilha.
* **`pilha.c`**: O arquivo de implementação que contém o código-fonte de todas as funções da pilha (ex: `criar_pilha`, `push`, `pop`, etc.).
* **`main.c`**: O programa principal que contém o menu, a lógica do usuário e faz a chamada às funções da pilha.

## 🚀 Como Compilar e Executar

Para rodar este projeto, você precisa ter o git e um compilador C (como o gcc) instalados.

1. Clone o repositório:

    ```bash
    git clone https://github.com/JoaoManoelFMN/c-stack-undo-redo.git
    ```

2. Navegue até o diretório que você acabou de baixar:
    ```bash
    cd c-stack-undo-redo
    ```

3. Compile o programa:

    ```bash
    gcc -o main main.c
    ```

4. Execute o programa:

    ```bash
    ./main
    ```
