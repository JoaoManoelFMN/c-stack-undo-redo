#include "utils.h"
#include "pilha.h"
#include "grafo.h"

#define ARQUIVO_DB "tarefas.txt"

#ifdef _WIN32
#include <windows.h>
#endif

// Função auxiliar para obter o nome da tarefa
char* obter_nome_tarefa(Pilha* p, int indice) {
    if (indice <= 0 || indice > contarItens(p)) return NULL;
    
    NoPilha* atual = p->topo;
    for(int i = 1; i < indice; i++) {
        atual = atual->prox;
    }
    return atual->tarefa.nome;
}

// Função auxiliar para exibir o caminho
void exibir_caminho(char** caminho, int tamanho) {
    if (tamanho == 0) {
        printf(COR_AMARELO "Nenhum caminho encontrado.\n" COR_RESET);
        return;
    }
    printf(COR_VERDE "Caminho encontrado (%d passos): " COR_RESET, tamanho);
    for (int i = 0; i < tamanho; i++) {
        printf("%s", caminho[i]);
        if (i < tamanho - 1) {
            printf(" -> ");
        }
        free(caminho[i]); // Libera a string alocada
    }
    printf("\n");
    free(caminho); // Libera o array de ponteiros
}


int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif

    // Inicialização das Estruturas
    Pilha* todo_list = criar_pilha();
    Pilha* redo_list = criar_pilha();
    Grafo* grafo_deps = criar_grafo(20); // Capacidade inicial do grafo

    if (!todo_list || !redo_list || !grafo_deps) {
        printf(COR_VERMELHO "Erro fatal: Falha de memória.\n" COR_RESET);
        return 1;
    }

    // Carrega dados do arquivo
    carregarPilhaDeArquivo(todo_list, ARQUIVO_DB);
   
    int opcao = 0;
    char buffer[100];
    char buffer2[100]; // Auxiliar para segunda tarefa

    do {
        system(LIMPAR_TELA);
       
        int total_itens = contarItens(todo_list);
        int total_redo = contarItens(redo_list);

        printf("\n--- Lista de Tarefas (Itens: %d) | (Refazer: %d) ---\n", total_itens, total_redo);
        printf("----------------------------------\n");
        printf("1. Adicionar novo item\n");
        printf("2. Concluir/Desfazer último item (Undo)\n");
        printf("3. Refazer item desfeito (Redo)\n");
        printf("4. Ver próximo item (Topo)\n");
        printf("5. Mostrar todos os itens (Display)\n");
        printf("6. Sair\n");
        printf(COR_CYAN "--- Dependências (Grafos) ---\n" COR_RESET);
        printf("7. Adicionar Dependência\n");
        printf("8. Ver Grupo de Tarefas Relacionadas (DFS)\n"); // Novo nome
        printf("9. Verificar Conexão entre Tarefas (BFS)\n"); // Novo nome
        printf("----------------------------------\n");
        printf("Escolha uma opção: ");
       
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limpar_buffer();

        switch (opcao) {
            case 1:{
                system(LIMPAR_TELA);
                printf("--- Adicionar Novo Item ---\n");
                printf("Digite o item: ");

                buffer[0] = '\0';
                scanf("%99[^\n]", buffer); // Limita a leitura para evitar buffer overflow
                limpar_buffer();

                if (strlen(buffer) == 0 || buffer[0] == ' ') {
                    printf(COR_VERMELHO "\nErro: Tarefa vazia!\n" COR_RESET);
                }
                else {
                    push(todo_list, buffer);
                    if (!estaVazia(redo_list)) {
                        printf(COR_AMARELO "Histórico de Refazer limpo.\n" COR_RESET);
                        limparPilha(redo_list);
                    }
                }
                printf("\nEnter para voltar."); getchar();
                break;
            }
            case 2:{
                system(LIMPAR_TELA);
                printf("--- Concluir/Desfazer ---\n");
                Tarefa* t = pop(todo_list);
                if (t) {
                    printf(COR_VERDE "Tarefa concluída/desfeita: %s\n" COR_RESET, t->nome);
                    push(redo_list, t->nome);
                    free(t);
                } else {
                    printf(COR_AMARELO "A lista de tarefas está vazia.\n" COR_RESET);
                }
                printf("\nEnter para voltar."); getchar();
                break;
            }
            case 3:{
                system(LIMPAR_TELA);
                printf("--- Refazer ---\n");
                Tarefa* t = pop(redo_list);
                if (t) {
                    printf(COR_VERDE "Tarefa refeita: %s\n" COR_RESET, t->nome);
                    push(todo_list, t->nome);
                    free(t);
                } else {
                    printf(COR_AMARELO "Nenhuma tarefa para refazer.\n" COR_RESET);
                }
                printf("\nEnter para voltar."); getchar();
                break;
            }
            case 4:{
                system(LIMPAR_TELA);
                printf("--- Ver Próximo Item ---\n");
                Tarefa* t = verTopo(todo_list);
                if (t) {
                    printf(COR_VERDE "Próxima tarefa: %s\n" COR_RESET, t->nome);
                } else {
                    printf(COR_AMARELO "A lista de tarefas está vazia.\n" COR_RESET);
                }
                printf("\nEnter para voltar."); getchar();
                break;
            }
            case 5:{
                system(LIMPAR_TELA);
                exibirPilha(todo_list);
                printf("\nEnter para voltar."); getchar();
                break;
            }
            case 6:{
                salvarPilhaEmArquivo(todo_list, ARQUIVO_DB);
                printf(COR_VERDE "Saindo. Dados salvos.\n" COR_RESET);
                break;
            }
            case 7:{
                system(LIMPAR_TELA);
                printf("--- Adicionar Dependência ---\n");
                printf("Digite o nome da TAREFA DE ORIGEM: ");
                scanf("%99[^\n]", buffer);
                limpar_buffer();
                printf("Digite o nome da TAREFA DE DESTINO: ");
                scanf("%99[^\n]", buffer2);
                limpar_buffer();

                if (strlen(buffer) > 0 && strlen(buffer2) > 0) {
                    adicionar_dependencia(grafo_deps, buffer, buffer2);
                } else {
                    printf(COR_VERMELHO "Erro: Nomes de tarefas não podem ser vazios.\n" COR_RESET);
                }
                printf("\nEnter para voltar."); getchar();
                break;
            }
            case 8:{
                system(LIMPAR_TELA);
                printf("--- Ver Grupo de Tarefas Relacionadas (DFS) ---\n");
                printf("Digite o nome da TAREFA INICIAL: ");
                scanf("%99[^\n]", buffer);
                limpar_buffer();

                if (strlen(buffer) > 0) {
                    int num_tarefas = 0;
                    char** grupo = ver_grupo_tarefas_relacionadas(grafo_deps, buffer, &num_tarefas);
                    
                    if (grupo) {
                        printf(COR_CYAN "\n[GRUPO RELACIONADO] Componente Conexo a partir de '%s' (%d tarefas):\n" COR_RESET, buffer, num_tarefas);
                        for (int i = 0; i < num_tarefas; i++) {
                            printf(COR_AMARELO " - %s\n" COR_RESET, grupo[i]);
                            free(grupo[i]);
                        }
                        free(grupo);
                    } else {
                        printf(COR_AMARELO "Tarefa '%s' não encontrada ou não possui relações.\n" COR_RESET, buffer);
                    }
                } else {
                    printf(COR_VERMELHO "Erro: Nome da tarefa não pode ser vazio.\n" COR_RESET);
                }
                printf("\nEnter para voltar."); getchar();
                break;
            }
            case 9:{
                system(LIMPAR_TELA);
                printf("--- Verificar Conexão entre Tarefas (BFS) ---\n");
                printf("Digite o nome da TAREFA DE ORIGEM: ");
                scanf("%99[^\n]", buffer);
                limpar_buffer();
                printf("Digite o nome da TAREFA DE DESTINO: ");
                scanf("%99[^\n]", buffer2);
                limpar_buffer();

                if (strlen(buffer) > 0 && strlen(buffer2) > 0) {
                    char** caminho = NULL;
                    int tamanho_caminho = 0;
                    int conectado = verificar_conexao(grafo_deps, buffer, buffer2, &caminho, &tamanho_caminho);

                    if (conectado) {
                        printf(COR_VERDE "\nAs tarefas '%s' e '%s' ESTÃO CONECTADAS.\n" COR_RESET, buffer, buffer2);
                        exibir_caminho(caminho, tamanho_caminho);
                    } else {
                        printf(COR_AMARELO "\nAs tarefas '%s' e '%s' NÃO ESTÃO CONECTADAS.\n" COR_RESET, buffer, buffer2);
                    }
                } else {
                    printf(COR_VERMELHO "Erro: Nomes de tarefas não podem ser vazios.\n" COR_RESET);
                }
                printf("\nEnter para voltar."); getchar();
                break;
            }
            default:
                if (opcao != 6) {
                    printf(COR_VERMELHO "\nOpção inválida. Tente novamente.\n" COR_RESET);
                    printf("\nEnter para voltar."); getchar();
                }
                break;
        }
    } while (opcao != 6);

    // Liberação de memória
    liberarPilha(todo_list);
    liberarPilha(redo_list);
    liberar_grafo(grafo_deps);

    return 0;
}