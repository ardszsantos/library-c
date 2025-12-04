#include <stdio.h>
#include <time.h>
#include "emprestimos.h"
#include "../livros/livros.h"
#include "../usuarios/usuarios.h"

// declarações externas necessárias
extern Livro *buscarLivro(int codigo);
extern int usuarioExiste(int matricula);

Emprestimo emprestimos[MAX_EMPRESTIMOS];
int totalEmprestimos = 0;

static void calcularDevolucao(int *d, int *m, int *a) {
    time_t t = time(NULL);
    struct tm dt = *localtime(&t);
    dt.tm_mday += 7;
    mktime(&dt);

    *d = dt.tm_mday;
    *m = dt.tm_mon + 1;
    *a = dt.tm_year + 1900;
}

void registrarEmprestimo() {
    int matricula, codigoLivro;

    printf("Matrícula do usuário: ");
    scanf("%d", &matricula);

    if (!usuarioExiste(matricula)) {
        printf("Usuário não encontrado.\n");
        return;
    }

    printf("Código do livro: ");
    scanf("%d", &codigoLivro);

    Livro *livro = buscarLivro(codigoLivro);
    if (!livro) {
        printf("Livro não encontrado.\n");
        return;
    }

    if (livro->numDisp <= 0) {
        printf("Sem exemplares disponíveis.\n");
        return;
    }

    Emprestimo e;
    e.codigo = totalEmprestimos + 1;
    e.matriculaUsuario = matricula;
    e.codigoLivro = codigoLivro;

    time_t t = time(NULL);
    struct tm dt = *localtime(&t);
    e.dia = dt.tm_mday;
    e.mes = dt.tm_mon + 1;
    e.ano = dt.tm_year + 1900;

    calcularDevolucao(&e.prevDia, &e.prevMes, &e.prevAno);
    e.status = 1;

    emprestimos[totalEmprestimos++] = e;

    livro->numDisp--;
    livro->status = (livro->numDisp > 0);

    printf("Empréstimo registrado. Código: %d\n", e.codigo);
}

void listarEmprestimos() {
    if (totalEmprestimos == 0) {
        printf("Nenhum empréstimo.\n");
        return;
    }

    for (int i = 0; i < totalEmprestimos; i++) {
        Emprestimo e = emprestimos[i];
        printf("ID %d | Usuario %d | Livro %d | %02d/%02d/%d -> %02d/%02d/%d | %s\n",
               e.codigo, e.matriculaUsuario, e.codigoLivro,
               e.dia, e.mes, e.ano,
               e.prevDia, e.prevMes, e.prevAno,
               e.status ? "Ativo" : "Devolvido");
    }
}

void devolverEmprestimo() {
    int id;

    printf("Código do empréstimo: ");
    scanf("%d", &id);

    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].codigo == id) {

            if (!emprestimos[i].status) {
                printf("Já devolvido.\n");
                return;
            }

            emprestimos[i].status = 0;

            Livro *livro = buscarLivro(emprestimos[i].codigoLivro);
            if (livro) {
                livro->numDisp++;
                livro->status = 1;
            }

            printf("Devolução registrada.\n");
            return;
        }
    }

    printf("Empréstimo não encontrado.\n");
}
