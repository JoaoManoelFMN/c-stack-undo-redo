#include "pilha.c"

int main() {
    Pilha* todo_list = criar_pilha(); 
    
    int opcao = 0;
    char buffer[100];

    do {
        system(LIMPAR_TELA);
        printf("\n--- Lista de tarefas (Pilha) ---\n");
        printf("----------------------------------\n");
        printf("1. Adicionar novo item\n");
        printf("2. Concluir ultimo item (Pop)\n");
        printf("3. Ver proximo item (Topo)\n");
        printf("4. Mostrar todos os itens (Display)\n");
        printf("5. Sair\n");
        printf("----------------------------------\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limpar_buffer(); 

        switch (opcao) {
            case 1:{ 
                system(LIMPAR_TELA);
                printf("--- Adicionar Novo Item ---\n");
                printf("Digite o item a fazer: ");
                
                scanf("%[^\n]", buffer); 
                limpar_buffer();

                push(todo_list, buffer);

                printf("\n--------------------------------------\n");
                printf("Item '%s' adicionado a lista.\n", buffer);
                printf("--------------------------------------\n");
                
                printf("\nAperte <ENTER> para voltar.");
                getchar(); 
                break;
            }
            
            case 2: { // Concluir ultimo item (Pop)
                system(LIMPAR_TELA);
                
                char* item_concluido = pop(todo_list);

                if (item_concluido == NULL) {
                    printf("\n--------------------------------------\n");
                    printf("Parabens! Sua lista esta vazia.\n");
                    printf("--------------------------------------\n");
                } else {
                    printf("\n--------------------------------------\n");
                    printf("Item concluido: %s\n", item_concluido);
                    printf("--------------------------------------\n");
                    
                    free(item_concluido);
                }
                
                printf("\nAperte <ENTER> para voltar.");
                getchar(); 
                break;
            }

            case 3:{
                system(LIMPAR_TELA);
                printf("--- Proximo Item a Fazer ---\n");

                if (estaVazia(todo_list)) {
                    printf("\nSua lista esta vazia.\n");
                } else {
                    printf("\nO proximo item a fazer e: %s\n", todo_list->topo->texto);
                }
                
                printf("\nAperte <ENTER> para voltar.");
                getchar(); 
                break;
            }

            case 4:{
                system(LIMPAR_TELA);
                printf("--- Todos os Itens na Lista ---\n");
                
                display(todo_list); 
                
                printf("\n----------------------------------\n");
                printf("\nAperte <ENTER> para voltar.");
                getchar();
                break;
            }

             case 5:{ 
                system(LIMPAR_TELA);
                printf("--- Contagem de Itens ---\n");
                int qtd = contarItens(todo_list);
                printf("\nA lista possui %d item(ns).\n", qtd);
                printf("\nAperte <ENTER> para voltar.");
                getchar();
                break;
            }

            case 6:{
                system(LIMPAR_TELA);
                printf("Saindo e limpando a memoria...\n");
                break;
            }
            default:{
                system(LIMPAR_TELA);
                printf("Erro");
                printf("Opcao invalida. Tente novamente.\n");
                
                
                printf("\nAperte <ENTER> para voltar.");
                getchar();
            }
        }

    } while (opcao != 5);
    
    limparPilha(todo_list); 
    free(todo_list);        

    printf("Programa finalizado.\n");
    return 0;
}