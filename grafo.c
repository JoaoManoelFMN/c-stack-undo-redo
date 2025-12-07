#include "grafo.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Estruturas auxiliares para BFS (Fila)

typedef struct NoFila {
    int dado;
    struct NoFila* prox;
} NoFila;

typedef struct {
    NoFila *inicio, *fim;
} FilaAux;

void enqueue(FilaAux* f, int v) {
    NoFila* n = (NoFila*) malloc(sizeof(NoFila));
    if (!n) return;
    n->dado = v;
    n->prox = NULL;
    if (f->fim) f->fim->prox = n;
    else f->inicio = n;
    f->fim = n;
}

int dequeue(FilaAux* f) {
    if (!f->inicio) return -1;
    NoFila* t = f->inicio;
    int v = t->dado;
    f->inicio = t->prox;
    if (!f->inicio) f->fim = NULL;
    free(t);
    return v;
}

int fila_vazia(FilaAux* f) { return f->inicio == NULL; }

// Funções do Grafo

Grafo* criar_grafo(int capacidade) {
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    if (g) {
        g->vertices = (Vertice*) calloc(capacidade, sizeof(Vertice));
        g->qtd_vertices = 0;
        g->capacidade = capacidade;
    }
    return g;
}

void liberar_grafo(Grafo* g) {
    if (!g) return;
    for (int i = 0; i < g->qtd_vertices; i++) {
        free(g->vertices[i].nome);
        Aresta* a = g->vertices[i].lista_adj;
        while (a) {
            Aresta* t = a;
            a = a->prox;
            free(t);
        }
    }
    free(g->vertices);
    free(g);
}

// Função auxiliar para adicionar uma aresta direcionada
void adicionar_aresta_direcionada(Grafo* g, int u, int v) {
    Aresta* nova = (Aresta*) malloc(sizeof(Aresta));
    if (!nova) return;
    nova->indice_destino = v;
    nova->prox = g->vertices[u].lista_adj;
    g->vertices[u].lista_adj = nova;
}

int obter_indice(Grafo* g, const char* nome) {
    // 1. Tenta encontrar o vértice existente
    for (int i = 0; i < g->qtd_vertices; i++) {
        if (strcmp(g->vertices[i].nome, nome) == 0) return i;
    }

    // 2. Se não encontrou, verifica se precisa redimensionar
    if (g->qtd_vertices >= g->capacidade) {
        g->capacidade *= 2;
        Vertice* novo_vertices = (Vertice*) realloc(g->vertices, g->capacidade * sizeof(Vertice));
        if (!novo_vertices) {
            fprintf(stderr, COR_VERMELHO "Erro de memória ao redimensionar o grafo.\n" COR_RESET);
            return -1; // Erro
        }
        g->vertices = novo_vertices;
        
        // Inicializa os novos espaços
        for(int i = g->qtd_vertices; i < g->capacidade; i++) {
            g->vertices[i].lista_adj = NULL;
            g->vertices[i].nome = NULL;
        }
    }

    // 3. Cria o novo vértice
    int idx = g->qtd_vertices++;
    g->vertices[idx].nome = strdup(nome);
    g->vertices[idx].lista_adj = NULL;
    return idx;
}

void adicionar_dependencia(Grafo* g, const char* origem, const char* destino) {
    int u = obter_indice(g, origem);
    int v = obter_indice(g, destino);

    if (u == -1 || v == -1) return; // Erro de memória

    // O grafo deve ser NÃO DIRECIONADO, então adicionamos arestas em ambas as direções
    adicionar_aresta_direcionada(g, u, v);
    adicionar_aresta_direcionada(g, v, u); // Aresta de volta

    printf(COR_VERDE "Dependencia (Nao-Direcionada): [%s] <-> [%s]\n" COR_RESET, origem, destino);
}

// DFS para encontrar o componente conexo
void dfs_rec(Grafo* g, int u, int* visitados, char** resultados, int* count) {
    visitados[u] = 1;
    resultados[*count] = strdup(g->vertices[u].nome);
    (*count)++;

    Aresta* a = g->vertices[u].lista_adj;
    while (a) {
        if (!visitados[a->indice_destino]) {
            dfs_rec(g, a->indice_destino, visitados, resultados, count);
        }
        a = a->prox;
    }
}

// Implementação da funcionalidade "Ver grupo de tarefas relacionadas"
char** ver_grupo_tarefas_relacionadas(Grafo* g, const char* inicio, int* num_tarefas) {
    int u = obter_indice(g, inicio);
    if (u == -1 || u >= g->qtd_vertices || strcmp(g->vertices[u].nome, inicio) != 0) {
        *num_tarefas = 0;
        return NULL; // Tarefa não existe
    }

    int* visitados = (int*) calloc(g->capacidade, sizeof(int));
    if (!visitados) {
        *num_tarefas = 0;
        return NULL;
    }

    // Aloca espaço máximo possível para os resultados (pode ser otimizado)
    char** resultados = (char**) malloc(g->qtd_vertices * sizeof(char*));
    if (!resultados) {
        free(visitados);
        *num_tarefas = 0;
        return NULL;
    }

    *num_tarefas = 0;
    dfs_rec(g, u, visitados, resultados, num_tarefas);

    free(visitados);
    
    // Redimensiona o array de resultados para o tamanho exato
    if (*num_tarefas > 0) {
        char** resultados_finais = (char**) realloc(resultados, (*num_tarefas) * sizeof(char*));
        if (resultados_finais) return resultados_finais;
    }
    
    // Se não encontrou nada ou realloc falhou, libera e retorna NULL
    for(int i = 0; i < *num_tarefas; i++) free(resultados[i]);
    free(resultados);
    *num_tarefas = 0;
    return NULL;
}

// Implementação da funcionalidade "Ver se duas tarefas estão conectadas" (BFS com caminho)
int verificar_conexao(Grafo* g, const char* origem, const char* destino, char*** caminho, int* tamanho_caminho) {
    int u = obter_indice(g, origem);
    int v = obter_indice(g, destino);

    if (u == -1 || v == -1 || u >= g->qtd_vertices || v >= g->qtd_vertices || strcmp(g->vertices[u].nome, origem) != 0 || strcmp(g->vertices[v].nome, destino) != 0) {
        *tamanho_caminho = 0;
        return 0; // Uma ou ambas as tarefas não existem
    }

    if (u == v) {
        *tamanho_caminho = 1;
        *caminho = (char**) malloc(sizeof(char*));
        (*caminho)[0] = strdup(origem);
        return 1;
    }

    int* visitados = (int*) calloc(g->capacidade, sizeof(int));
    int* pai = (int*) malloc(g->capacidade * sizeof(int));
    if (!visitados || !pai) {
        free(visitados); free(pai);
        *tamanho_caminho = 0;
        return 0;
    }
    for(int i = 0; i < g->capacidade; i++) pai[i] = -1;

    FilaAux f = {NULL, NULL};
    enqueue(&f, u);
    visitados[u] = 1;

    int encontrado = 0;
    while (!fila_vazia(&f)) {
        int atual = dequeue(&f);
        if (atual == v) {
            encontrado = 1;
            break;
        }

        Aresta* a = g->vertices[atual].lista_adj;
        while (a) {
            if (!visitados[a->indice_destino]) {
                visitados[a->indice_destino] = 1;
                pai[a->indice_destino] = atual;
                enqueue(&f, a->indice_destino);
            }
            a = a->prox;
        }
    }

    // Reconstruir o caminho se encontrado
    if (encontrado) {
        int temp_v = v;
        int count = 0;
        // Conta o tamanho do caminho
        while (temp_v != -1) {
            count++;
            temp_v = pai[temp_v];
        }

        *tamanho_caminho = count;
        *caminho = (char**) malloc(count * sizeof(char*));
        
        // Preenche o caminho de trás para frente
        temp_v = v;
        for (int i = count - 1; i >= 0; i--) {
            (*caminho)[i] = strdup(g->vertices[temp_v].nome);
            temp_v = pai[temp_v];
        }
    } else {
        *tamanho_caminho = 0;
        *caminho = NULL;
    }

    // Libera a memória auxiliar
    free(visitados);
    free(pai);
    
    // Libera a fila (deve estar vazia, mas por segurança)
    while(!fila_vazia(&f)) dequeue(&f);

    return encontrado;
}

// Funções originais de travessia (mantidas para o menu original)
void executar_dfs(Grafo* g, const char* inicio) {
    int u = obter_indice(g, inicio);
    if (u == -1 || u >= g->qtd_vertices || strcmp(g->vertices[u].nome, inicio) != 0) {
        printf(COR_VERMELHO "\nErro: Tarefa [%s] nao encontrada no grafo.\n" COR_RESET, inicio);
        return;
    }
    
    int* visitados = (int*) calloc(g->capacidade, sizeof(int));
   
    printf("\n[DFS] Cadeia a partir de %s:", inicio);
    dfs_rec(g, u, visitados, NULL, NULL); // Usando a versão recursiva, mas sem armazenar resultados
    printf("\n");
    free(visitados);
}

void executar_bfs(Grafo* g, const char* inicio) {
    int u = obter_indice(g, inicio);
    if (u == -1 || u >= g->qtd_vertices || strcmp(g->vertices[u].nome, inicio) != 0) {
        printf(COR_VERMELHO "\nErro: Tarefa [%s] nao encontrada no grafo.\n" COR_RESET, inicio);
        return;
    }
    
    int* visitados = (int*) calloc(g->capacidade, sizeof(int));
    FilaAux f = {NULL, NULL};

    printf("\n[BFS] Niveis a partir de %s: ", inicio);
    visitados[u] = 1;
    enqueue(&f, u);

    while (!fila_vazia(&f)) {
        int v = dequeue(&f);
        printf(COR_AMARELO "[%s] " COR_RESET, g->vertices[v].nome);

        Aresta* a = g->vertices[v].lista_adj;
        while (a) {
            if (!visitados[a->indice_destino]) {
                visitados[a->indice_destino] = 1;
                enqueue(&f, a->indice_destino);
            }
            a = a->prox;
        }
    }
    printf("\n");
    free(visitados);
}