#include "pilha.c"

// Correção para o Windows mostrar os caracteres bonitos (UTF-8)
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif

    Pilha* todo_list = criar_pilha(); 
    Pilha* redo_list = criar_pilha();

    if (todo_list == NULL || redo_list == NULL) {
        printf(COR_VERMELHO "Erro fatal: Falha de memória.\n" COR_RESET);
        return 1;
    }
    
    int opcao = 0;
    char buffer[100];

    do {
        system(LIMPAR_TELA);
        
        int total_itens = contarItens(todo_list);
        int total_redo = contarItens(redo_list);

        printf("\n--- Lista de Tarefas (Itens: %d) | (Refazer: %d) ---\n", total_itens, total_redo);
        printf("----------------------------------\n");
        printf("1. Adicionar novo item\n");
        printf("2. Concluir/Desfazer último item (Undo)\n");
        printf("3. Refazer item desfeito (Redo) " COR_AMARELO "[NOVO!]" COR_RESET "\n");
        printf("4. Ver próximo item (Topo)\n");
        printf("5. Mostrar todos os itens (Display)\n");
        printf("6. Sair\n");
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
                printf("Digite o item a fazer: ");

                // Correção de bugs:
                buffer[0] = '\0'; 
                scanf("%[^\n]", buffer);
                limpar_buffer();

                // Validação: Se o buffer continuar vazio, é porque o usuário não digitou nada
                if (strlen(buffer) == 0 || buffer[0] == ' ') {
                    printf(COR_VERMELHO "\nErro: Você não pode adicionar uma tarefa vazia!\n" COR_RESET);
                } 
                else {
                    push(todo_list, buffer);
                    
                    if (!estaVazia(redo_list)) {
                        printf(COR_AMARELO "Nova ação realizada. Histórico de Refazer limpo.\n" COR_RESET);
                        limparPilha(redo_list);
                    }
                }

                printf("\nAperte <ENTER> para voltar.");
                getchar(); 
                break;
            }
            
            case 2: { // UNDO
                system(LIMPAR_TELA);
                
                if (estaVazia(todo_list)) {
                    printf(COR_VERMELHO "Nada para concluir/desfazer!\n" COR_RESET);
                } else {
                    char* item = pop(todo_list);
                    push(redo_list, item);
                    printf(COR_AMARELO "Item movido para histórico de Refazer: %s\n" COR_RESET, item);
                    free(item);
                }
                
                printf("\nAperte <ENTER> para voltar.");
                getchar(); 
                break;
            }

            case 3: { // REDO
                system(LIMPAR_TELA);

                if (estaVazia(redo_list)) {
                    printf(COR_VERMELHO "Nada para refazer!\n" COR_RESET);
                } else {
                    char* item = pop(redo_list);
                    push(todo_list, item);
                    printf(COR_VERDE "Item restaurado para a lista: %s\n" COR_RESET, item);
                    free(item); 
                }

                printf("\nAperte <ENTER> para voltar.");
                getchar();
                break;
            }

            case 4:{
                system(LIMPAR_TELA);
                printf("--- Próximo Item a Fazer ---\n");

                if (estaVazia(todo_list)) {
                    printf(COR_AMARELO "Sua lista está vazia.\n" COR_RESET);
                } else {
                    printf("\nO próximo item a fazer é: " COR_CYAN "%s\n" COR_RESET, todo_list->topo->texto);
                }
                
                printf("\nAperte <ENTER> para voltar.");
                getchar(); 
                break;
            }

            case 5:{
                system(LIMPAR_TELA);
                
                printf("=== LISTA PRINCIPAL (A Fazer) ===\n");
                display(todo_list);

                printf("\n=== LISTA DE REFAZER (Histórico) ===\n");
                display(redo_list);
                
                printf("\n----------------------------------\n");
                printf("\nAperte <ENTER> para voltar.");
                getchar();
                break;
            }

            case 6:{
                system(LIMPAR_TELA);
                printf("Saindo e limpando a memória...\n");
                break;
            }

            default:{
                system(LIMPAR_TELA);
                printf(COR_VERMELHO "\nOpção inválida. Tente novamente.\n" COR_RESET);
                printf("\nAperte <ENTER> para voltar.");
                getchar();
            }
        }

    } while (opcao != 6);
    
    destruirPilha(todo_list);
    destruirPilha(redo_list);

    printf("Programa finalizado.\n");
    return 0;
}

/*
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠠⡀⠀⠀⠀⠠⡀⠀⢄⠀⠀⡐⢀⡀⠀⠀⠀⡄⣦⠀⠀⠆⠰⢀⠀⠀⠐⠀⣠⢂⠒⠀⠀⠀⠀⠀⣠⠔⠂⠀
⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠁⠀⠀⢐⠀⠀⡇⢸⠀⠀⣃⢸⡆⠀⡄⢠⠰⡜⡇⠀⠀⠆⢁⠀⢰⠀⡐⠀⠌⠀⠀⠀⠀⠀⠈⢀⠄⠀⠀
⠀⠀⠀⠀⠀⠀⢀⣤⡀⡀⠀⠀⠀⠐⢄⠙⢆⢳⠈⢦⠀⡿⠀⣧⠘⣧⢰⠀⠀⣿⠀⠀⡔⠁⣸⠘⠀⠀⠀⠀⢀⣀⢀⠀⠀⠀⠄⠄⡠⠀
⠀⠀⠀⠀⠀⣷⣿⢿⠋⢀⡤⠀⠀⠀⠀⢢⠈⠸⡆⠈⢆⢳⠀⠙⢧⡁⣾⠀⠀⠘⠀⠌⠀⢀⡟⠀⠀⠀⠀⠀⠹⣿⣿⣶⣦⣀⠀⡼⠁⡔
⠀⠀⠀⣢⣿⣿⣿⠃⡴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠈⠊⡄⠀⠀⢡⡇⠀⠀⠀⠀⠀⠀⠈⠀⣶⣦⠀⠀⠀⠀⢹⣿⣿⣿⣷⡈⢀⠜⠀
⠀⠀⢠⣾⣿⡿⡏⠰⠁⠀⢀⠄⠀⠀⠀⢠⡾⠀⠀⠀⠀⠀⠈⠀⠀⠈⠀⠀⢀⠀⠀⠀⢠⡀⢀⢹⣿⣧⠘⡆⡆⢸⣿⣿⣿⣿⢃⠔⠊⠀
⠀⠀⠈⣿⣿⡇⢳⢀⠄⣠⠇⠀⠀⣰⢀⣿⠁⠀⠀⣠⡞⢀⠆⣰⠀⠀⢀⠀⣸⠀⣶⢀⣿⣧⠈⣎⣿⣿⠄⠀⣿⢸⢿⣿⣿⣏⠀⠄⠂⠀
⠀⠀⠀⠸⠿⠗⠈⢾⠀⣟⡇⠀⠠⣽⢸⡇⠀⢀⢠⣿⠁⢃⣼⢃⡀⠀⡏⢸⣿⠀⠀⣼⣿⣿⠀⢸⣿⣿⠁⣸⣿⣿⢸⣿⣿⡇⠈⠔⠀⠀
⡅⠀⢠⣥⣷⣶⣿⣿⡔⣿⠇⢀⡄⠸⡘⡇⠀⢀⣾⠛⠀⢘⣵⣿⡀⠘⢀⣿⣿⠀⢠⣿⣿⣿⠀⣸⣿⡏⣠⣿⣿⣿⣷⣾⣿⣷⣶⡄⠀⡇
⢡⠀⣾⣧⡙⠿⣿⣿⣿⣿⡆⢰⣷⣶⣙⠄⣸⣼⣿⡇⢠⣺⣿⣿⡇⠀⢸⣿⠟⠀⢸⡿⣛⡟⢠⣿⣿⣿⣿⣿⣿⣿⡿⠟⣻⣿⣿⣷⢸⠁
⢸⡄⣿⣿⣷⣄⠀⠈⠙⢿⣷⠸⣿⣿⣿⣆⢣⣿⣿⣿⠀⢺⣿⣿⣷⠀⡟⢣⣾⠀⣿⣾⣿⣣⣾⡟⣿⣿⣿⠿⠛⠁⢀⣴⣿⣿⣿⣯⣾⡆
⢰⢻⣿⣿⣿⣿⣷⣦⣀⠀⠈⠑⠙⠿⣿⣿⣧⣿⣿⣿⣿⡎⣿⣿⣿⡆⢧⣾⣿⣇⣾⡿⠿⠛⠁⠀⠁⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⠆
⢠⣹⣿⣿⣿⣿⣿⣎⠻⡿⢶⣤⡄⣀⠀⠀⠀⠀⠙⠻⠟⠁⣟⣿⣿⠀⠼⠛⠟⠋⠁⠀⠀⠀⠀⣀⢀⣠⣠⡤⢀⣾⣿⣿⣿⣿⣿⣿⢷⠂
⠀⢿⣻⣿⣿⣿⣿⣿⣥⣆⢍⢉⣉⣉⣁⠀⠀⠀⠀⢀⡠⠀⠸⢿⣧⢂⠀⠀⠀⠀⠀⠀⠺⠿⠷⠶⢚⡛⠋⣡⣾⣿⣿⣿⣿⣿⣿⣣⡏⠀
⠀⠈⠃⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⠿⠿⠿⣶⣯⣤⣀⣲⠀⠀⢸⣯⣥⣷⣶⣶⣾⣿⣿⣿⣯⣤⣶⣤⣶⣾⣿⣿⣿⣿⣿⣿⣿⡏⢛⡤⠀
⠀⠀⣷⢸⣿⣿⣿⣿⣿⣿⣿⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⡶⣄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢃⣿⣏⠀
⠀⠀⢹⡎⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡛⠘⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⣾⣏⡞⠀
⠀⠀⠸⣷⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡕⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣸⣟⡿⠁⠀
⠀⠀⠀⢿⣆⡘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡥⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢡⡿⣿⠃⠀⠀
⠀⠀⠀⠀⠳⠥⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⢠⣿⣽⠏⠀⠀⠀
⠀⠈⠀⠀⠐⠒⠶⢠⣌⣉⠉⠉⠉⠛⠽⣻⣿⣿⣿⠇⠻⣿⡿⣿⣿⣿⣿⣿⢟⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠛⠋⠀⠀⠈⢉⠀⣀⣀⣷⡆
⠂⠀⠀⠀⠀⠀⠀⠀⠚⠉⠳⢒⣦⣀⢀⠈⠙⠩⠴⣞⡁⠌⠻⠿⣿⣿⠟⢡⣾⣿⣿⠿⠛⠋⠁⠀⠀⡀⠀⡀⢀⠀⠠⣠⣞⠀⣂⠗⠁⠃
⠠⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠟⠿⠆⡄⠀⠀⠈⠙⠳⠤⠤⠄⠀⠒⠛⠉⠉⠀⠀⣠⣀⣦⣤⣠⣴⣒⡻⢺⠛⠓⠓⠎⠘⠟⠁⠀⠀
⢤⠀⠀⠙⠤⡀⠀⡀⠤⢤⡀⠀⠀⠀⠠⣒⠿⠿⠧⡦⣰⣄⣄⢤⣀⣐⢦⣔⠄⡒⠦⡼⠿⣽⣻⡷⠟⡉⠉⠁⠊⠀⠌⠀⠀⠀⠀⠀⠀⠀
⢤⠐⠀⠘⠀⣉⠀⠀⠰⠈⠹⠀⠀⠀⠁⠀⠈⠀⠀⠒⠓⠉⠟⠋⠘⠁⠈⠐⠉⠁⠉⠐⠉⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
*/
