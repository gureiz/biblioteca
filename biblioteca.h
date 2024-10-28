#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EMPRESTIMO (14 * 24 * 3600) //constante para o tempo de emprestimo (2 SEMANAS)
#define REEMPRESTIMO (7 * 24 * 3600) //constante para reemprestimo (1 SEMANA)

//armazenar informações de um livro
typedef struct {
    int id;
    char titulo[50];
    char autor[50];
    int ano;
} Livro;

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
int realizarLogin(int *isAdmin);
void menuLogin();
int main() {
    criarArquivos();  //cria os arquivos automaticamente
    menuLogin();
    return 0;
}
void menuPrincipal(int isAdmin);
void cadastrarLivro();
void listarLivros();