#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

typedef struct {
    int codigo;             // auto-increment
    int matriculaUsuario;
    int codigoLivro;
    int dia, mes, ano;      // data do empréstimo
    int prevDia, prevMes, prevAno; // data prevista de devolução (7 dias)
    int status;             // 1 = ativo, 0 = devolvido
} Emprestimo;

#define MAX_EMPRESTIMOS 1000

extern Emprestimo emprestimos[];
extern int totalEmprestimos;

void registrarEmprestimo();
void listarEmprestimos();
void devolverEmprestimo();

#endif
