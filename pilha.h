#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define LIMPAR_TELA "cls"
#else
    #define LIMPAR_TELA "clear"
#endif

typedef struct No{
    char* texto;
    struct No* prox;
} No;

typedef struct Pilha{
    No* topo;
} Pilha;


// Protótipos das funções
Pilha* criar_pilha();

void push(Pilha* pi, const char* texto);   // Empilhar
char* pop(Pilha* pi);                      // Desempilhar
void display(Pilha* pi);                   // Imprime o conteúdo contido na pilha
void limparPilha(Pilha* pi);               // Esvazia a pilha
void limpar_buffer();

#endif