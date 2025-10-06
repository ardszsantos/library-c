#ifndef DATETIME_H
#define DATETIME_H

// Estrutura para data
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

// Função que retorna a data atual
Data getDataAtual();

#endif
