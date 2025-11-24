#include "pilha.h"

Pilha* criar_pilha(){
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if (pi != NULL){
        pi->topo = NULL;
    }
    return pi;
}

void push(Pilha* pi, const char* texto){
    if (pi == NULL) return;

    No* novo_no = (No*) malloc(sizeof(No));

    if (novo_no == NULL) return;

    novo_no->texto = strdup(texto); 
    if (novo_no->texto == NULL) {
        perror(COR_VERMELHO "Erro ao duplicar string para a pilha" COR_RESET);
        free(novo_no);
        return;
    }

    
    novo_no->prox = pi->topo;
    
   
    pi->topo = novo_no;

    printf(COR_VERDE "Item adicionado com sucesso.\n" COR_RESET);
}

char* pop(Pilha* pi){
    if (estaVazia(pi)){ 
        printf(COR_VERMELHO "Erro: Pilha vazia.\n" COR_RESET);
        return NULL;
    }

    No* no_remover = pi->topo;
    char* texto_retornado = no_remover->texto;

    
    pi->topo = no_remover->prox;

    free(no_remover); 

    return texto_retornado;
}

void display(Pilha* pi){
    if (estaVazia(pi)){ 
        printf(COR_AMARELO "Pilha vazia.\n" COR_RESET);
        return;
    }

    printf(COR_CYAN "\n===== PILHA =====\n" COR_RESET);

    No* atual = pi->topo;
    while (atual != NULL) {
        printf(COR_CYAN " ┌───────────────┐\n" COR_RESET);
        printf(COR_CYAN " │ " COR_RESET "%-13s" COR_CYAN " │\n", atual->texto);
        printf(COR_CYAN " └───────────────┘\n" COR_RESET);

        if (atual->prox != NULL)
            printf("        ↑\n");

        atual = atual->prox;
    }

    printf(COR_CYAN "===== BASE =====\n" COR_RESET);
}

void limparPilha(Pilha* pi){
    if (pi == NULL) return;

    while (!estaVazia(pi)){ 
        char* texto = pop(pi);
        
        if (texto != NULL){
            free(texto);
        }
    }
}


void destruirPilha(Pilha* pi){
    if (pi == NULL) return;

    limparPilha(pi); 
    free(pi);        
}

int estaVazia(Pilha* pi) {
    if (pi == NULL) {
        return 1; 
    }
    return (pi->topo == NULL); 
}

void limpar_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int contarItens(Pilha* pi){
    if (estaVazia(pi)) {
        return 0;
    }
    
    int count = 0;
    No* atual = pi->topo;
    while (atual != NULL){
        count++;
        atual = atual->prox;
    }
    return count;
}