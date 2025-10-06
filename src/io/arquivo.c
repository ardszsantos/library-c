#include "arquivo.h"
#include <stdio.h>
#include <string.h>

void salvarArquivo(const char* nomeArquivo, void* obj, void (*converter)(void*, FILE*)) {
    FILE* arquivo = fopen(nomeArquivo, "a"); // append
    if (!arquivo) {
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        return;
    }

    converter(obj, arquivo); // converte e escreve
    fclose(arquivo);
}

int lerArquivo(const char* nomeArquivo, void* array, int max, int (*lerLinha)(char*, void*)) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) return 0;

    char linha[512];
    int count = 0;

    while (fgets(linha, sizeof(linha), arquivo) && count < max) {
        // remove newline
        linha[strcspn(linha, "\n")] = 0;

        if (lerLinha(linha, &((char*)array)[count * sizeof(void*)])) {
            count++;
        }
    }

    fclose(arquivo);
    return count;
}
