#include <stdio.h>
#include "hash.h"
#include <conio.h>

int input(size_t size, char *str){
    int c, i = 0;
    
    while((c = getchar()) != '\n'){
        if(i < size){
            str[i] = c;
            i++;
        }
    }
    str[i] = '\0';
    return i;
}

int main(void){
    printf("Iniciando...\n\n");

    int ls[] = {82, 31, 28, 4, 05, 45, 27, 59, 79, 35, 13, 5, 33, 16, 12, 00, 07, 104, 67, 18, 91, 77, 61, 58, 21, 15,\
    19, 87, 40, 75, 23, 41, 1, 61, 82, 24, 67, 13, 5, 99, 43, 9, 70, 50, 56, 76, 62, 64, 88, 87, 80, 72, 90, 73,\
    39, 63, 70, 78, 26, 24, 95, 46, 2}, tam, i;

    printf("Digite o tamanho da tabela:\n>>");
    scanf("%d", &tam);
    getchar();
    Hash *hash = criaHash(tam);
    Data data;

    for(i = 0; i < sizeof(ls) / sizeof(int); i++){
        data.i = ls[i];
        insereHash(hash, ls[i], data);
    }

    int ch, check = 1, valor, status;

    printf("\033c\n\nEscolha o que fazer (ESC para sair):\n\
        \n\t> Adicionar chave;\
        \n\t  Remover chave;\
        \n\t  Procurar chave;\
        \n\t  Mostrar tabela hash;");

    ch = _getch();

    while (ch != 27) {
        if(ch == 13){
            printf("\n");
            if(check == 1){
                printf("\n\n\nDigite o valor da chave:\n>>");
                scanf("%d", &valor);
                getchar();
                printf("%d\n\n", valor);
                data.i = valor;
                status = insereHash(hash, valor, data);
                if(status == -1){
                    printf("Sem espaco para inserir nova chave.");
                } else {
                    printf("\n\nElemento inserido com sucesso na posicao \'%d\'.\n", status);
                }
            } else if(check == 2) {
                printf("\n\n\nDigite o valor da chave:\n>>");
                scanf("%d", &valor);
                getchar();
                if(removerHash(hash, valor) == 0){
                    printf("\nElemento nao existe ou a tabela hash passada e invalida.\n");
                } else {
                    printf("\n\nElemento removido com sucesso.\n");
                }
            } else if(check == 3){
                printf("\n\n\nDigite o valor da chave:\n>>");
                scanf("%d", &valor);
                getchar();
                mostra_tabela_com_enfase(hash, valor);
            } else if(check == 4) {
                mostra_tabelahash(hash);
                printf("\n\n");
            }
            printf("Fator de carga: %.2f.\n\n\tPressione ENTER para continuar\n", load_factor(hash));
            getchar();

            check = 1;
        }
        if (ch == 0 || ch == 224){
            int a = ch;
            ch = _getch();

            printf("%d, %d\n", a, ch);
            if(ch == 72){
                if(check == 1 || check == 2){
                    
                    check = 1;
                } else if(check == 3){
                    
                    check = 2;
                } else if(check == 4) {
                    
                    check = 3;
                }
            } else if(ch == 80){
                if(check == 1){
                    
                    check = 2;
                } else if(check == 2){
                    
                    check = 3;
                } else if(check == 3 || check == 4) {
                    
                    check = 4;
                }
            }
            printf("\n");
        }

        if(check == 1){
            printf("\033c\n\nEscolha o que fazer (ESC para sair):\n\
                \n\t> Adicionar chave;\
                \n\t  Remover chave;\
                \n\t  Procurar chave;\
                \n\t  Mostrar tabela hash;");
        } else if(check == 2){
            printf("\033c\n\nEscolha o que fazer (ESC para sair):\n\
                \n\t  Adicionar chave;\
                \n\t> Remover chave;\
                \n\t  Procurar chave;\
                \n\t  Mostrar tabela hash;");
        } else if(check == 3){
            printf("\033c\n\nEscolha o que fazer (ESC para sair):\n\
                \n\t  Adicionar chave;\
                \n\t  Remover chave;\
                \n\t> Procurar chave;\
                \n\t  Mostrar tabela hash;");
        } else if(check == 4){
            printf("\033c\n\nEscolha o que fazer (ESC para sair):\n\
                \n\t  Adicionar chave;\
                \n\t  Remover chave;\
                \n\t  Procurar chave;\
                \n\t> Mostrar tabela hash;");
        }

        ch = _getch();
    }

    liberaHash(hash);

    printf("\n\nPrograma finalizado!");
    return 1;
}