#ifndef USUARIOS_H
#define USUARIOS_H
#define NAME_MAX 100
#define COURSE_MAX 50
#define PHONE_MAX 15
#define MAX_USUARIOS 100   // <- define aqui

typedef enum {
    USUARIO_COMUM,
    ADMIN
} TipoUsuario;


typedef struct {
    int matricula;
    char nome[NAME_MAX];
    char curso[COURSE_MAX];
    char telefone[PHONE_MAX];
    int dia;
    int mes;
    int ano;
    TipoUsuario tipo;
} Usuario;

void salvarUsuario(Usuario* u, const char* arquivo);
void lerUsuarios(const char* arquivo, Usuario* array, int* count);

#endif
