#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdio.h>

// Função genérica para salvar uma struct
void salvarArquivo(const char* nomeArquivo, void* obj, void (*converter)(void*, FILE*));

// Função genérica para ler structs de um arquivo
// array: ponteiro para array de structs
// max: tamanho máximo do array
// lerLinha: função que converte linha lida em struct
// retorna: número de elementos lidos
int lerArquivo(const char* nomeArquivo, void* array, int max, int (*lerLinha)(char*, void*));

#endif
