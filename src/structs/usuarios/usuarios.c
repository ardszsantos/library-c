#include <stdio.h>
#include "usuarios.h"

// Salva um usuário no arquivo (em modo append)
void salvarUsuario(Usuario* u, const char* arquivo) {
    FILE* f = fopen(arquivo, "a");
    if (!f) {
        perror("Erro ao abrir arquivo");
        return;
    }
    fprintf(f, "%d;%s;%s;%s;%02d/%02d/%04d\n",
            u->matricula,
            u->nome,
            u->curso,
            u->telefone,
            u->dia,
            u->mes,
            u->ano);
    fclose(f);
}

void lerUsuarios(const char* arquivo, Usuario* array, int* count) {
    FILE* f = fopen(arquivo, "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        *count = 0;
        return;
    }

    int i = 0;
    while (i < MAX_USUARIOS && !feof(f)) {
        Usuario u;
        int ret = fscanf(f, "%d;%99[^;];%49[^;];%14[^;];%d/%d/%d\n",
                         &u.matricula,
                         u.nome,
                         u.curso,
                         u.telefone,
                         &u.dia,
                         &u.mes,
                         &u.ano);
        if (ret == 7) {
            array[i++] = u;
        } else {
            break;
        }
    }
    *count = i;
    fclose(f);
}