#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./structs/usuarios.h"
#include "utils/user_functions.h"


#define MAX_USUARIOS 100
#define ARQUIVO_USUARIOS "usuarios.txt"

Usuario* currentUser = NULL;

void mostrarBemVindo() {
    printf("====================================\n");
    printf("   GERENCIAMENTO DE BIBLIOTECA\n");
    printf("====================================\n\n");
}

int main() {
    int opcao;
    mostrarBemVindo();

    do {
        if (currentUser == NULL) {
            // MENU PRÉ-LOGIN
            printf("1 - Cadastrar novo usuário\n");
            printf("2 - Fazer login\n");
        } else {
            // MENU PÓS-LOGIN
            printf("1 - Listar usuários\n");
            printf("2 - Outros métodos\n");
            printf("3 - Logout\n");
        }
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa \n

        if (currentUser == NULL) {
            switch(opcao) {
                case 1: cadastrarUsuario(); break;
                case 2: logarUsuario(); break;
                case 0: printf("Saindo...\n"); break;
                default: printf("Opção inválida!\n");
            }
        } else {
            switch(opcao) {
                case 1: listarUsuarios(); break;
                case 2: printf("WIP...\n"); break;
                case 3:
                    logout();
                    break;

                case 0: printf("Saindo...\n"); break;
                default: printf("Opção inválida!\n");
            }
        }
    } while (opcao != 0);


    return 0;
}
