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
// Protótipos das funções

/**
 * @brief Aloca memória e inicializa uma nova pilha.
 * @return Ponteiro para a nova pilha criada.
 */
Pilha* criar_pilha();

/**
 * @brief Adiciona um novo item (texto) ao topo da pilha.
 * @param pi Ponteiro para a pilha.
 * @param texto A string (tarefa) a ser adicionada.
 */
void push(Pilha* pi, const char* texto); 

/**
 * @brief Remove e retorna o item do topo da pilha.
 * @param pi Ponteiro para a pilha.
 * @return Ponteiro para a string removida (ou NULL se vazia).
 */
char* pop(Pilha* pi); 

/**
 * @brief Imprime todos os itens da pilha, do topo para a base.
 * @param pi Ponteiro para a pilha.
 */
void display(Pilha* pi); 

/**
 * @brief Remove todos os elementos da pilha, liberando a memória.
 * @param pi Ponteiro para a pilha.
 */
void limparPilha(Pilha* pi);

/**
 * @brief Limpa o buffer de entrada do teclado (stdin).
 */
void limpar_buffer();
