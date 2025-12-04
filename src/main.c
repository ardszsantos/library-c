#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./structs/usuarios/usuarios.h"
#include "./structs/livros/livros.h"
#include "./structs/emprestimos/emprestimos.h"
#include "utils/user_functions.h"
#include "utils/livro_functions.h"

#define MAX_USUARIOS 100
#define MAX_LIVROS 500

void mostrarBemVindo() {
    printf("====================================\n");
    printf("   GERENCIAMENTO DE BIBLIOTECA\n");
    printf("====================================\n\n");
}

void menuPrincipal() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1 - Gerenciar Usuários\n");
    printf("2 - Gerenciar Livros\n");
    printf("3 - Empréstimos\n");
    printf("4 - Relatórios\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

void menuUsuarios() {
    printf("\n=== GERENCIAR USUÁRIOS ===\n");
    printf("1 - Cadastrar usuário\n");
    printf("2 - Listar usuários\n");
    printf("3 - Pesquisar usuário\n");
    printf("0 - Voltar\n");
    printf("Escolha uma opção: ");
}

void menuLivros() {
    printf("\n=== GERENCIAR LIVROS ===\n");
    printf("1 - Cadastrar livro\n");
    printf("2 - Listar livros\n");
    printf("3 - Pesquisar livro\n");
    printf("0 - Voltar\n");
    printf("Escolha uma opção: ");
}

void menuEmprestimos() {
    printf("\n=== EMPRÉSTIMOS ===\n");
    printf("1 - Registrar empréstimo\n");
    printf("2 - Listar empréstimos\n");
    printf("3 - Devolver livro\n");
    printf("0 - Voltar\n");
    printf("Escolha uma opção: ");
}

int main() {
    int opcao, subOpcao;
    mostrarBemVindo();

    do {
        menuPrincipal();
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: // Usuários
                do {
                    menuUsuarios();
                    scanf("%d", &subOpcao);
                    getchar();
                    
                    switch(subOpcao) {
                        case 1: cadastrarUsuario(); break;
                        case 2: listarUsuarios(); break;
                        case 3: printf("WIP - Pesquisar usuário\n"); break;
                        case 0: break;
                        default: printf("Opção inválida!\n");
                    }
                } while (subOpcao != 0);
                break;

            case 2: // Livros
                do {
                    menuLivros();
                    scanf("%d", &subOpcao);
                    getchar();
                    
                    switch(subOpcao) {
                        case 1: cadastrarLivro(); break;
                        case 2: listarLivros(); break;
                        case 3: pesquisarLivro(); break;
                        case 0: break;
                        default: printf("Opção inválida!\n");
                    }
                } while (subOpcao != 0);
                break;

            case 3: // Empréstimos
                do {
                    menuEmprestimos();
                    scanf("%d", &subOpcao);
                    getchar();

                    switch(subOpcao) {
                        case 1: registrarEmprestimo(); break;
                        case 2: listarEmprestimos(); break;
                        case 3: devolverEmprestimo(); break;
                        case 0: break;
                        default: printf("Opção inválida!\n");
                    }
                } while (subOpcao != 0);
                break;

            case 4: // Relatórios
                printf("WIP - Relatórios\n");
                break;

            case 0:
                printf("Encerrando sistema...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
