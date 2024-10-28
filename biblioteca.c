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
//cria um id uníco para um usuário
int gerarIdUsuario() {
    FILE *file = fopen("id_usuario.txt", "r+");
    int id = 1; 
    if (file == NULL) {
        file = fopen("id_usuario.txt", "w");
        fprintf(file, "%d", id);
        fclose(file);
    } else {
        fscanf(file, "%d", &id);
        id++; 
        fseek(file, 0, SEEK_SET); 
        fprintf(file, "%d", id);
        fclose(file);
    }
    return id; 
}
//cria um id único para um livro
int gerarIdLivro() {
    FILE *file = fopen("id_livro.txt", "r+");
    int id = 1; 
    if (file == NULL) {
        file = fopen("id_livro.txt", "w");
        fprintf(file, "%d", id);
        fclose(file);
    } else {
        fscanf(file, "%d", &id);
        id++;
        fseek(file, 0, SEEK_SET); 
        fprintf(file, "%d", id); 
        fclose(file);
    }
    return id; 
}