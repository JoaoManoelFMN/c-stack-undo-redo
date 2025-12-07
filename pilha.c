#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pilha* criar_pilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if (p) {
        p->topo = NULL;
        p->tamanho = 0;
    }
    return p;
}

void liberarPilha(Pilha* p) {
    if (!p) return;
    limparPilha(p);
    free(p);
}

void push(Pilha* p, const char* nome_tarefa) {
    if (!p) return;
    NoPilha* novo = (NoPilha*) malloc(sizeof(NoPilha));
    if (!novo) return;

    strncpy(novo->tarefa.nome, nome_tarefa, sizeof(novo->tarefa.nome) - 1);
    novo->tarefa.nome[sizeof(novo->tarefa.nome) - 1] = '\0';
    
    novo->prox = p->topo;
    p->topo = novo;
    p->tamanho++;
}

Tarefa* pop(Pilha* p) {
    if (estaVazia(p)) return NULL;
    NoPilha* temp = p->topo;
    Tarefa* tarefa = (Tarefa*) malloc(sizeof(Tarefa));
    if (!tarefa) return NULL;

    *tarefa = temp->tarefa;
    p->topo = temp->prox;
    p->tamanho--;
    free(temp);
    return tarefa;
}

Tarefa* verTopo(Pilha* p) {
    if (estaVazia(p)) return NULL;
    return &(p->topo->tarefa);
}

int estaVazia(Pilha* p) {
    return p == NULL || p->topo == NULL;
}

int contarItens(Pilha* p) {
    return p ? p->tamanho : 0;
}

void limparPilha(Pilha* p) {
    if (!p) return;
    NoPilha* atual = p->topo;
    while (atual) {
        NoPilha* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    p->topo = NULL;
    p->tamanho = 0;
}

// Funções de arquivo (simuladas para compilar)
void carregarPilhaDeArquivo(Pilha* p, const char* nome_arquivo) {
    // Simulação de carregamento
    printf(COR_AMARELO "Simulando carregamento de tarefas de %s...\n" COR_RESET, nome_arquivo);
    // Exemplo de dados iniciais para o grafo
    push(p, "Configurar ambiente");
    push(p, "Implementar funcionalidade X");
    push(p, "Testar funcionalidade X");
}

void salvarPilhaEmArquivo(Pilha* p, const char* nome_arquivo) {
    // Simulação de salvamento
    printf(COR_AMARELO "Simulando salvamento de tarefas em %s...\n" COR_RESET, nome_arquivo);
}

void exibirPilha(Pilha* p) {
    if (estaVazia(p)) {
        printf(COR_AMARELO "A lista de tarefas está vazia.\n" COR_RESET);
        return;
    }
    printf(COR_AZUL "--- Tarefas ---\n" COR_RESET);
    NoPilha* atual = p->topo;
    int i = 1;
    while (atual) {
        printf("%d. %s\n", i++, atual->tarefa.nome);
        atual = atual->prox;
    }
    printf(COR_AZUL "---------------\n" COR_RESET);
}