# 🚀 Simulador de Undo/Redo com Pilha em C

Um projeto simples em C que implementa a funcionalidade de "Desfazer" (Undo) e "Refazer" (Redo) usando duas Pilhas (Stacks).

Este projeto foi criado como um exercício prático para demonstrar o uso da estrutura de dados **Pilha (Stack)** em um cenário do mundo real, como a de um editor de texto.

## 🎯 Conceito Principal

A lógica é baseada em duas pilhas:

* **Pilha `undo` (Desfazer):** Armazena todas as ações que o usuário executa.
* **Pilha `redo` (Refazer):** Armazena as ações que foram desfeitas.

### Lógica da Aplicação

1.  **Nova Ação:** Quando o usuário executa uma nova ação (ex: "Digitou 'Olá'"), a ação é empilhada (`push`) na pilha `undo`. Ao mesmo tempo, a pilha `redo` é totalmente esvaziada.
2.  **Desfazer (Undo):** O item do topo da pilha `undo` é desempilhado (`pop`) e, em seguida, empilhado (`push`) na pilha `redo`.
3.  **Refazer (Redo):** O item do topo da pilha `redo` é desempilhado (`pop`) e, em seguida, empilhado (`push`) de volta na pilha `undo`.

## 🛠️ Estrutura de Dados

A Pilha foi implementada em C puro como uma **lista encadeada** (linked list) para gerenciar strings de tamanho variável de forma eficiente. A implementação está separada em:

* `pilha.h`: Arquivo de cabeçalho (header) com as definiTamanhocoes da `struct` e os protótipos das funções.
* `pilha.c`: A implementação das funções da pilha (ex: `push`, `pop`, `estaVazia`).
* `main.c`: O programa principal que contém a lógica do menu e o gerenciamento das pilhas de Undo/Redo.

## ⚙️ Como Compilar e Executar

1.  Clone o repositório:
    ```bash
    git clone [https://github.com/seu-usuario/seu-repositorio.git](https://github.com/seu-usuario/seu-repositorio.git)
    cd seu-repositorio
    ```
2.  Compile os arquivos:
    ```bash
    gcc main.c pilha.c -o editor
    ```
3.  Execute o programa:
    ```bash
    ./editor
    ```

---
