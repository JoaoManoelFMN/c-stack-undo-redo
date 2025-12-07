#include "pilha.h"

// Caso o compilador reclame do strdup no Windows/ANSI estrito
char* duplicar_string(const char* s) {
    char* d = malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}

Pilha* criar_pilha(){
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if (pi != NULL){
        pi->topo = NULL;
        pi->base = NULL; 
    }
    return pi;
}

void push(Pilha* pi, const char* texto){
    if (pi == NULL) return;

    No* novo_no = (No*) malloc(sizeof(No));
    if (novo_no == NULL) return;

    novo_no->texto = duplicar_string(texto);
    if (novo_no->texto == NULL) {
        free(novo_no);
        return;
    }

    if (estaVazia(pi)) {
        // Se vazia: O novo é topo E base.
        pi->topo = novo_no;
        pi->base = novo_no;
        novo_no->prox = novo_no; // Aponta pra si mesmo
    } else {
        // Se já tem gente:
        novo_no->prox = pi->topo; // Novo aponta pro antigo topo
        pi->topo = novo_no;       // Novo vira topo
        
        // A MÁGICA CIRCULAR: A base aponta para o novo topo
        pi->base->prox = pi->topo; 
    }

    printf(COR_VERDE "Item empilhado (Circular).\n" COR_RESET);
}

char* pop(Pilha* pi){
    if (estaVazia(pi)) return NULL;

    No* no_remover = pi->topo;
    char* texto_retornado = no_remover->texto;

    // Se só tem 1 elemento (ele aponta pra ele mesmo)
    if (pi->topo == pi->base) {
        pi->topo = NULL;
        pi->base = NULL;
    } else {
        // Se tem mais de 1:
        pi->topo = no_remover->prox; // Topo desce
        pi->base->prox = pi->topo;   // Base atualiza pra apontar pro novo topo
    }

    free(no_remover);
    return texto_retornado;
}

void display(Pilha* pi){
    if (estaVazia(pi)){ 
        printf(COR_AMARELO "Pilha vazia.\n" COR_RESET);
        return;
    }

    printf(COR_CYAN "\n=== PILHA CIRCULAR ===\n" COR_RESET);
    
    No* atual = pi->topo;
    
    do {
        printf(COR_CYAN " ┌───────────────┐\n" COR_RESET);
        printf(COR_CYAN " │ " COR_RESET "%-13s" COR_CYAN " │\n", atual->texto);
        printf(COR_CYAN " └───────────────┘\n" COR_RESET);
        printf("        ↓\n"); // Seta indicando o ciclo

        atual = atual->prox;

    } while (atual != pi->topo); // Para quando der a volta completa

    printf(COR_CYAN "(Volta para o Topo: %s)\n" COR_RESET, pi->topo->texto);
}

void limparPilha(Pilha* pi){
    if (pi == NULL) return;
    while (!estaVazia(pi)){ 
        char* t = pop(pi);
        if (t) free(t);
    }
}

void destruirPilha(Pilha* pi){
    if (pi == NULL) return;
    limparPilha(pi); 
    free(pi);        
}

int estaVazia(Pilha* pi) {
    if (pi == NULL) return 1; 
    return (pi->topo == NULL); 
}

int contarItens(Pilha* pi){
    if (estaVazia(pi)) return 0;
    int count = 0;
    No* atual = pi->topo;
    do {
        count++;
        atual = atual->prox;
    } while (atual != pi->topo);
    return count;
}

void salvarPilhaEmArquivo(Pilha* pi, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "w");
    if (f == NULL) return;
    
    if (!estaVazia(pi)) {
        // Salvar do topo para a base
        No* atual = pi->topo;
        do {
            fprintf(f, "%s\n", atual->texto);
            atual = atual->prox;
        } while (atual != pi->topo);
    }
    fclose(f);
}

void carregarPilhaDeArquivo(Pilha* pi, const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (f == NULL) return; 

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) > 0) {
            push(pi, buffer);
        }
    }
    fclose(f);
}

void limpar_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}