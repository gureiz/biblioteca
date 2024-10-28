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

//função para cadatrar novos usuários
void cadastrarUsuario() {
    FILE *file = fopen("usuarios.txt", "a");
    if (file == NULL) {
        perror("ERRO");
        return;
    }
    Usuario usuario;
    usuario.id = gerarIdUsuario();
    printf("\nDigite o Nome do Usuário: ");
    scanf(" %[^\n]", usuario.nome);
    printf("Digite o Email do Usuário: ");
    scanf(" %[^\n]", usuario.email);
    printf("Digite a Senha: ");
    scanf(" %[^\n]", usuario.senha);
    Usuario temp;
    FILE *fileTemp = fopen("usuarios.txt", "r");
    int existe = 0;
    while (fscanf(fileTemp, "%d %49s %49s %19s", &temp.id, temp.nome, temp.email, temp.senha) == 4) {
        if (strcmp(temp.email, usuario.email) == 0) {
            existe = 1;
            break;
        }
    }
    fclose(fileTemp);
    if (existe) {
        printf("\nEsse e-mail já está cadastrado.\n");
    } else {
        fprintf(file, "%d %s %s %s\n", usuario.id, usuario.nome, usuario.email, usuario.senha);
        printf("\nUsuário cadastrado com sucesso!\n");
    }

    fclose(file);
}

//função para o login do usuário
int realizarLogin(int *isAdmin) {
    FILE *file = fopen("usuarios.txt", "r");
    if (file == NULL) {
        perror("ERRO");
        return 0;
    }
    char email[50], senha[20];
    printf("\nE-mail: ");
    scanf(" %[^\n]", email);
    printf("Senha: ");
    scanf(" %[^\n]", senha);
    if (strcmp(email, "adm@adm.com") == 0 && strcmp(senha, "adm") == 0) {
        *isAdmin = 1;
        fclose(file);
        return 1;
    }
    Usuario usuario;
    while (fscanf(file, "%d %49s %49s %19s", &usuario.id, usuario.nome, usuario.email, usuario.senha) == 4) {
        if (strcmp(usuario.email, email) == 0 && strcmp(usuario.senha, senha) == 0) {
            *isAdmin = 0;
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

//mostra o menu de cadastro e login
void menuLogin() {
    int opcao;
    do {
        printf("\n========================\n");
        printf("       BIBLIOTECA  ");
        printf("\n========================\n");
        printf("1. Cadastrar\n");
        printf("2. Login\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2: {
                int isAdmin = 0;
                if (realizarLogin(&isAdmin)) {
                    printf("\nLogin bem-sucedido!\n");
                    menuPrincipal(isAdmin);
                } else {
                    printf("\nFalha no login!\n");
                }
                break;
            }
            case 3:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 3);
}