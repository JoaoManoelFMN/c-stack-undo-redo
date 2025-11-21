#ifndef PILHA_H
#define PILHA_H

#define COR_RESET    "\033[0m"
#define COR_VERDE    "\033[0;32m"
#define COR_VERMELHO "\033[0;31m"
#define COR_AMARELO  "\033[1;33m"
#define COR_CYAN     "\033[0;36m"

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

Pilha* criar_pilha();
void push(Pilha* pi, const char* texto); 
char* pop(Pilha* pi); 
void display(Pilha* pi); 
void limparPilha(Pilha* pi);
void destruirPilha(Pilha* pi); // Nova função solicitada
int estaVazia(Pilha* pi);
int contarItens(Pilha* pi);
void limpar_buffer();

#endif