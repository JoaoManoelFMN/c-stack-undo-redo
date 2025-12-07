#ifndef PILHA_H
#define PILHA_H

#include "utils.h"

// Definição de uma estrutura de Tarefa (simplificada)
typedef struct {
    char nome[100];
    // Adicionar outros campos da tarefa se necessário
} Tarefa;

// Estrutura de Nó da Pilha
typedef struct NoPilha {
    Tarefa tarefa;
    struct NoPilha* prox;
} NoPilha;

// Estrutura da Pilha
typedef struct {
    NoPilha* topo;
    int tamanho;
} Pilha;

// Protótipos das funções da Pilha (para compilar main.c)
Pilha* criar_pilha();
void liberarPilha(Pilha* p);
void push(Pilha* p, const char* nome_tarefa);
Tarefa* pop(Pilha* p);
Tarefa* verTopo(Pilha* p);
int estaVazia(Pilha* p);
int contarItens(Pilha* p);
void limparPilha(Pilha* p);
void carregarPilhaDeArquivo(Pilha* p, const char* nome_arquivo);
void salvarPilhaEmArquivo(Pilha* p, const char* nome_arquivo);
void exibirPilha(Pilha* p); // Função auxiliar para exibir

#endif // PILHA_H