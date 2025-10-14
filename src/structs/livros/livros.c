#include <stdio.h>
#include <string.h>
#include "livros.h"

void salvarLivro(Livro *livro, const char *arquivo) {
    FILE *f = fopen(arquivo, "a");  // "a" = append
    if (!f) {
        printf("ERRO: Não foi possível abrir o arquivo %s!\n", arquivo);
        perror("Detalhes");
        return;
    }
    
    fprintf(f, "%d|%s|%s|%s|%d|%d|%d|%d\n",
            livro->codigoLivro,
            livro->titulo,
            livro->autor,
            livro->editora,
            livro->anoPub,
            livro->totalExemplares,
            livro->numDisp,
            livro->status);
    
    fclose(f);
    printf("DEBUG: Livro salvo no arquivo.\n");  // Adicione isso pra testar
}
void lerLivros(const char *arquivo, Livro livros[], int *count) {
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        *count = 0;
        return;
    }
    
    *count = 0;
    char linha[500];
    
    while (fgets(linha, sizeof(linha), f) && *count < 500) {
        Livro l;
        int statusInt;
        
        sscanf(linha, "%d|%99[^|]|%79[^|]|%59[^|]|%d|%d|%d|%d",
               &l.codigoLivro,
               l.titulo,
               l.autor,
               l.editora,
               &l.anoPub,
               &l.totalExemplares,
               &l.numDisp,
               &statusInt);
        
        l.status = statusInt;
        livros[*count] = l;
        (*count)++;
    }
    
    fclose(f);
}