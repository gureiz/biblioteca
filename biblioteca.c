#include "biblioteca.h"

void criarArquivos() {
    FILE *file;
    //arquivo de usuários
    file = fopen("usuarios.txt", "a");
    if (file) fclose(file);
    //arquivo de livros
    file = fopen("livros.dat", "ab");
    if (file) fclose(file);
    //arquivo de empréstimos
    file = fopen("emprestimos.dat", "ab");
    if (file) fclose(file);
}
