#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../structs/usuarios.h"
#include "../utils/toLowerCase.h"

#define MAX_USUARIOS 100
#define ARQUIVO_USUARIOS "usuarios.txt"

extern Usuario* currentUser;

// Cadastra usuário e salva no arquivo
void cadastrarUsuario() {
    Usuario u;
    printf("Digite a matrícula: ");
    scanf("%d", &u.matricula);
    getchar();

    printf("Digite o nome completo: ");
    fgets(u.nome, NAME_MAX, stdin);
    u.nome[strcspn(u.nome, "\n")] = '\0';
    toLowerCase(u.nome);

    printf("Digite o curso: ");
    fgets(u.curso, COURSE_MAX, stdin);
    u.curso[strcspn(u.curso, "\n")] = '\0';

    printf("Digite o telefone: ");
    fgets(u.telefone, PHONE_MAX, stdin);
    u.telefone[strcspn(u.telefone, "\n")] = '\0';

    // Data automática
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    u.dia = tm.tm_mday;
    u.mes = tm.tm_mon + 1;
    u.ano = tm.tm_year + 1900;

    salvarUsuario(&u, ARQUIVO_USUARIOS);
    printf("\nUsuário cadastrado com sucesso!\n\n");
}

// Lista todos os usuários do arquivo
void listarUsuarios() {
    Usuario array[MAX_USUARIOS];
    int count = 0;
    lerUsuarios(ARQUIVO_USUARIOS, array, &count);

    printf("\n=== Lista de Usuários ===\n");
    for (int i = 0; i < count; i++) {
        Usuario u = array[i];
        printf("Matrícula: %d\nNome: %s\nCurso: %s\nTelefone: %s\nData cadastro: %02d/%02d/%04d\n",
               u.matricula, u.nome, u.curso, u.telefone, u.dia, u.mes, u.ano);
        printf("------------------------\n");
    }
}

// Login do usuário, case-insensitive
void logarUsuario() {
    int matricula;
    char nome[NAME_MAX];

    printf("Digite sua matrícula: ");
    scanf("%d", &matricula);
    getchar();

    printf("Digite seu nome completo: ");
    fgets(nome, NAME_MAX, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    toLowerCase(nome);

    Usuario array[MAX_USUARIOS];
    int count = 0;
    lerUsuarios(ARQUIVO_USUARIOS, array, &count);

    for (int i = 0; i < count; i++) {
        if (array[i].matricula == matricula && strcmp(array[i].nome, nome) == 0) {
            if (currentUser != NULL) free(currentUser);
            currentUser = malloc(sizeof(Usuario));
            if (!currentUser) {
                printf("Erro de memória!\n");
                return;
            }
            *currentUser = array[i];
            printf("\nLogin bem-sucedido! Bem-vindo, %s!\n\n", nome);
            return;
        }
    }

    printf("\nUsuário não encontrado ou dados incorretos.\n\n");
}

// Logout
void logout() {
    if (currentUser == NULL) {
        printf("Nenhum usuário está logado.\n");
        return;
    }

    printf("Usuário %s deslogado com sucesso!\n", currentUser->nome);
    free(currentUser);
    currentUser = NULL;
}
