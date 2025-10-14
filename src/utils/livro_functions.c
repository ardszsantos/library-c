#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../structs/livros/livros.h"

#define MAX_LIVROS 500
#define ARQUIVO_LIVROS "livros.txt"

// Verifica se código já existe
int codigoJaExiste(int codigo) {
    Livro array[MAX_LIVROS];
    int count = 0;
    lerLivros(ARQUIVO_LIVROS, array, &count);
    
    for (int i = 0; i < count; i++) {
        if (array[i].codigoLivro == codigo) {
            return 1;
        }
    }
    return 0;
}

void cadastrarLivro() {
    Livro l;
    printf("\n=== CADASTRAR LIVRO ===\n");
    
    printf("Código do livro: ");
    if (scanf("%d", &l.codigoLivro) != 1) {
        printf("Erro: código inválido!\n");
        while (getchar() != '\n');
        return;
    }
    getchar();
    
    // Verifica duplicidade
    if (codigoJaExiste(l.codigoLivro)) {
        printf("Erro: Já existe um livro com este código!\n");
        return;
    }

    printf("Título: ");
    fgets(l.titulo, TITULO_MAX, stdin);
    l.titulo[strcspn(l.titulo, "\n")] = '\0';
    
    if (strlen(l.titulo) == 0) {
        printf("Erro: Título não pode ser vazio!\n");
        return;
    }

    printf("Autor: ");
    fgets(l.autor, AUTOR_MAX, stdin);
    l.autor[strcspn(l.autor, "\n")] = '\0';

    printf("Editora: ");
    fgets(l.editora, EDITORA_MAX, stdin);
    l.editora[strcspn(l.editora, "\n")] = '\0';

    printf("Ano de publicação: ");
    if (scanf("%d", &l.anoPub) != 1) {
        printf("Erro: ano inválido!\n");
        while (getchar() != '\n');
        return;
    }
    
    printf("Número de exemplares: ");
    if (scanf("%d", &l.totalExemplares) != 1 || l.totalExemplares < 1) {
        printf("Erro: número de exemplares deve ser maior que zero!\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    l.numDisp = l.totalExemplares;
    l.status = 1;  // true

    // SALVA NO ARQUIVO
    salvarLivro(&l, ARQUIVO_LIVROS);
    printf("\n✓ Livro cadastrado com sucesso!\n");
}

void listarLivros() {
    Livro array[MAX_LIVROS];
    int count = 0;
    lerLivros(ARQUIVO_LIVROS, array, &count);

    if (count == 0) {
        printf("\nNenhum livro cadastrado.\n");
        return;
    }

    printf("\n=== LISTA DE LIVROS ===\n\n");

    for (int i = 0; i < count; i++) {
        Livro l = array[i];
        printf("Código       : %d\n", l.codigoLivro);
        printf("Título       : %s\n", l.titulo);
        printf("Autor        : %s\n", l.autor);
        printf("Editora      : %s\n", l.editora);
        printf("Ano          : %d\n", l.anoPub);
        printf("Disponíveis  : %d de %d\n", l.numDisp, l.totalExemplares);
        printf("Status       : %s\n", l.status ? "Disponível" : "Indisponível");
        printf("──────────────────────────────\n");
    }

    printf("Total de livros: %d\n", count);
}



// Busca por código
int buscarPorCodigo(Livro livros[], int count, int codigo) {
    for (int i = 0; i < count; i++) {
        if (livros[i].codigoLivro == codigo) {
            return i;
        }
    }
    return -1;
}

// Exibe detalhes de um livro
void exibirLivro(Livro *l) {
    printf("\n--- DETALHES DO LIVRO ---\n");
    printf("Código: %d\n", l->codigoLivro);
    printf("Título: %s\n", l->titulo);
    printf("Autor: %s\n", l->autor);
    printf("Editora: %s\n", l->editora);
    printf("Ano: %d\n", l->anoPub);
    printf("Exemplares: %d disponíveis de %d total\n", l->numDisp, l->totalExemplares);
    printf("Status: %s\n", l->status ? "Disponível" : "Indisponível");
    printf("─────────────────────────\n");
}

// Busca case-insensitive
void toLowerStr(char *str, char *dest) {
    int i = 0;
    while (str[i]) {
        dest[i] = tolower(str[i]);
        i++;
    }
    dest[i] = '\0';
}

void pesquisarLivro() {
    Livro array[MAX_LIVROS];
    int count = 0;
    lerLivros(ARQUIVO_LIVROS, array, &count);
    
    if (count == 0) {
        printf("\nNenhum livro cadastrado.\n");
        return;
    }
    
    int opcao;
    printf("\n=== PESQUISAR LIVRO ===\n");
    printf("1 - Por código\n");
    printf("2 - Por título\n");
    printf("3 - Por autor\n");
    printf("0 - Cancelar\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    getchar();
    
    switch(opcao) {
        case 1: {
            int codigo;
            printf("Digite o código: ");
            scanf("%d", &codigo);
            getchar();
            
            int idx = buscarPorCodigo(array, count, codigo);
            if (idx != -1) {
                exibirLivro(&array[idx]);
            } else {
                printf("Livro não encontrado!\n");
            }
            break;
        }
        
        case 2: {
            char busca[TITULO_MAX];
            printf("Digite o título (ou parte dele): ");
            fgets(busca, TITULO_MAX, stdin);
            busca[strcspn(busca, "\n")] = '\0';
            
            char buscaLower[TITULO_MAX], tituloLower[TITULO_MAX];
            toLowerStr(busca, buscaLower);
            
            int encontrados = 0;
            printf("\n=== RESULTADOS ===\n");
            
            for (int i = 0; i < count; i++) {
                toLowerStr(array[i].titulo, tituloLower);
                if (strstr(tituloLower, buscaLower) != NULL) {
                    exibirLivro(&array[i]);
                    encontrados++;
                }
            }
            
            if (encontrados == 0) {
                printf("Nenhum livro encontrado.\n");
            } else {
                printf("Total encontrado: %d\n", encontrados);
            }
            break;
        }
        
        case 3: {
            char busca[AUTOR_MAX];
            printf("Digite o autor (ou parte do nome): ");
            fgets(busca, AUTOR_MAX, stdin);
            busca[strcspn(busca, "\n")] = '\0';
            
            char buscaLower[AUTOR_MAX], autorLower[AUTOR_MAX];
            toLowerStr(busca, buscaLower);
            
            int encontrados = 0;
            printf("\n=== RESULTADOS ===\n");
            
            for (int i = 0; i < count; i++) {
                toLowerStr(array[i].autor, autorLower);
                if (strstr(autorLower, buscaLower) != NULL) {
                    exibirLivro(&array[i]);
                    encontrados++;
                }
            }
            
            if (encontrados == 0) {
                printf("Nenhum livro encontrado.\n");
            } else {
                printf("Total encontrado: %d\n", encontrados);
            }
            break;
        }
        
        case 0:
            printf("Pesquisa cancelada.\n");
            break;
            
        default:
            printf("Opção inválida!\n");
    }
}