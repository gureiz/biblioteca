#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EMPRESTIMO (14 * 24 * 3600) //constante para o tempo de emprestimo (2 SEMANAS)
#define REEMPRESTIMO (7 * 24 * 3600) //constante para reemprestimo (1 SEMANA)

//armazenar informações de um usuário
typedef struct {
    int id;
    char nome[50];
    char email[50];
    char senha[20];
} Usuario;


void criarArquivos();
int gerarIdUsuario();
int gerarIdLivro();
void cadastrarUsuario();