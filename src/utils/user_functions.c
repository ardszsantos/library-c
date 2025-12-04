#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../structs/usuarios/usuarios.h"
#include "../utils/toLowerCase.h"

#define MAX_USUARIOS 100
#define ARQUIVO_USUARIOS "usuarios.txt"

void cadastrarUsuario() {
    Usuario u;
    printf("\n=== CADASTRAR USUÁRIO ===\n");
    
    printf("Matrícula: ");
    scanf("%d", &u.matricula);
    getchar();

    printf("Nome completo: ");
    fgets(u.nome, NAME_MAX, stdin);
    u.nome[strcspn(u.nome, "\n")] = '\0';

    printf("Curso: ");
    fgets(u.curso, COURSE_MAX, stdin);
    u.curso[strcspn(u.curso, "\n")] = '\0';

    printf("Telefone: ");
    fgets(u.telefone, PHONE_MAX, stdin);
    u.telefone[strcspn(u.telefone, "\n")] = '\0';

    // Data automática
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    u.dia = tm.tm_mday;
    u.mes = tm.tm_mon + 1;
    u.ano = tm.tm_year + 1900;

    salvarUsuario(&u, ARQUIVO_USUARIOS);
    printf("\n✓ Usuário cadastrado com sucesso!\n");
}

void listarUsuarios() {
    Usuario array[MAX_USUARIOS];
    int count = 0;
    lerUsuarios(ARQUIVO_USUARIOS, array, &count);

    if (count == 0) {
        printf("\nNenhum usuário cadastrado.\n");
        return;
    }

    printf("\n=== LISTA DE USUÁRIOS ===\n");
    for (int i = 0; i < count; i++) {
        Usuario u = array[i];
        printf("\nMatrícula: %d\n", u.matricula);
        printf("Nome: %s\n", u.nome);
        printf("Curso: %s\n", u.curso);
        printf("Telefone: %s\n", u.telefone);
        printf("Cadastro: %02d/%02d/%04d\n", u.dia, u.mes, u.ano);
        printf("------------------------");
    }
    printf("\nTotal: %d usuário(s)\n", count);
}

void pesquisarUsuario() {
    // TODO: implementar busca por matrícula ou nome
}

int usuarioExiste(int matricula) {
    Usuario array[MAX_USUARIOS];
    int count = 0;
    lerUsuarios(ARQUIVO_USUARIOS, array, &count);

    for (int i = 0; i < count; i++) {
        if (array[i].matricula == matricula)
            return 1;
    }

    return 0;
}
