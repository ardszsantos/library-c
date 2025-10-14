#ifndef LIVROS_H
#define LIVROS_H

#include <stdbool.h>

#define TITULO_MAX 100
#define AUTOR_MAX 80
#define EDITORA_MAX 60

typedef struct {
    int codigoLivro;
    char titulo[TITULO_MAX];
    char autor[AUTOR_MAX];
    char editora[EDITORA_MAX];
    int anoPub;
    int totalExemplares;  // Total de exemplares
    int numDisp;          // Disponíveis
    bool status;          // true = tem disponível, false = todos emprestados
} Livro;

// Funções básicas (igual usuarios.h)
void salvarLivro(Livro *livro, const char *arquivo);
void lerLivros(const char *arquivo, Livro livros[], int *count);

#endif