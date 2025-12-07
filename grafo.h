#ifndef GRAFO_H
#define GRAFO_H
#include "utils.h"

typedef struct Aresta {
    int indice_destino;
    struct Aresta* prox;
} Aresta;

typedef struct {
    char* nome;
    Aresta* lista_adj;
} Vertice;

typedef struct {
    Vertice* vertices;
    int qtd_vertices;
    int capacidade;
} Grafo;

Grafo* criar_grafo(int capacidade_inicial);
void liberar_grafo(Grafo* g);
void adicionar_dependencia(Grafo* g, const char* origem, const char* destino);
void executar_dfs(Grafo* g, const char* inicio);
void executar_bfs(Grafo* g, const char* inicio);
// Novas funções para o requisito
char** ver_grupo_tarefas_relacionadas(Grafo* g, const char* inicio, int* num_tarefas);
int verificar_conexao(Grafo* g, const char* origem, const char* destino, char*** caminho, int* tamanho_caminho);

#endif