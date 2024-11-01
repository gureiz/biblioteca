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

//mostra o munu principal
void menuPrincipal(int isAdmin) {
    int opcao;
    int idUsuario = isAdmin ? -1 : 1;

    do {
        printf("\n========================\n");
        printf("     MENU PRINCIPAL  ");
        printf("\n========================\n");
        if (isAdmin) {
            printf("1. Cadastrar Livro (Administrador)\n");
        }
        printf("2. Acervo\n");
        printf("3. Empréstimo\n");
        printf("4. Renovar Empréstimo\n");
        printf("5. Doe um Livro\n");
        printf("6. Meus Empréstimos\n");
        printf("7. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (isAdmin) cadastrarLivro();
                else printf("Acesso negado. Opção exclusiva para o administrador.\n");
                break;
            case 2:
                listarLivros();
                break;
            case 3:
                emprestarLivro(idUsuario);
                break;
            case 4:
                reemprestarLivro(idUsuario);
                break;
            case 5:
                doarLivro();
                break;
            case 6:
                listarEmprestimos(idUsuario);
                break;
            case 7:
                printf("\nSaindo do menu principal...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 7);
}

//função de cadastrar livro, disponível apenas para o administrador
void cadastrarLivro() {
    FILE *file = fopen("livros.dat", "ab");
    if (file == NULL) {
        perror("ERRO");
        return;
    }
    Livro livro;
    livro.id = gerarIdLivro();  
    printf("\nTítulo: ");
    scanf(" %[^\n]", livro.titulo);
    printf("Autor: ");
    scanf(" %[^\n]", livro.autor);
    printf("Ano de Publicação: ");
    scanf("%d", &livro.ano);
    fwrite(&livro, sizeof(Livro), 1, file);
    fclose(file);
    printf("\nLivro cadastrado com sucesso!\n");
}

//função para mostrar o acervo
void listarLivros() {
    FILE *file = fopen("livros.dat", "rb");
    if (file == NULL) {
        perror("ERRO");
        return;
    }
    Livro livro;
    printf("\n========================\n");
    printf("  LISTA DE LIVROS  ");
    printf("\n========================\n");
    while (fread(&livro, sizeof(Livro), 1, file) == 1) {
        printf("ID: %d | Título: %s | Autor: %s | Ano: %d\n", livro.id, livro.titulo, livro.autor, livro.ano);
    }
    fclose(file);
}

//verificar a disponibilidade do livro para realizar o empréstiimo
int verificarLivroDisponivel(int idLivro) {
    FILE *fileEmprestimos = fopen("emprestimos.dat", "rb");
    if (fileEmprestimos == NULL) {
        perror("ERRO");
        return 1; 
    }
    Emprestimo emprestimo;
    while (fread(&emprestimo, sizeof(Emprestimo), 1, fileEmprestimos) == 1) {
        if (emprestimo.idLivro == idLivro && time(NULL) < emprestimo.dataDevolucao) {
            fclose(fileEmprestimos);
            return 0; 
        }
    }
    fclose(fileEmprestimos);
    return 1; 
}

//função de empréstimo
void emprestarLivro(int idUsuario) {
    FILE *file = fopen("livros.dat", "rb");
    if (file == NULL) {
        perror("ERRO");
        return;
    }
    int idLivro;
    printf("Digite o ID do livro que deseja emprestar: ");
    scanf("%d", &idLivro);
    if (!verificarLivroDisponivel(idLivro)) {
        printf("Livro já emprestado.\n");
        fclose(file);
        return;
    }
    Emprestimo emprestimo;
    emprestimo.idUsuario = idUsuario;
    emprestimo.idLivro = idLivro;
    emprestimo.dataEmprestimo = time(NULL);
    emprestimo.dataDevolucao = emprestimo.dataEmprestimo + EMPRESTIMO;
    FILE *fileEmprestimos = fopen("emprestimos.dat", "ab");
    if (fileEmprestimos == NULL) {
        perror("ERRO");
        fclose(file);
        return;
    }
    fwrite(&emprestimo, sizeof(Emprestimo), 1, fileEmprestimos);
    fclose(fileEmprestimos);
    fclose(file);
    printf("Livro emprestado com sucesso!\n");
}

//função para "reempréstimo" do livro
void reemprestarLivro(int idUsuario) {
    FILE *file = fopen("emprestimos.dat", "rb+");
    if (file == NULL) {
        perror("ERRO");
        return;
    }
    int idLivro;
    printf("Digite o ID do livro que deseja reemprestar: ");
    scanf("%d", &idLivro);
    Emprestimo emprestimo;
    while (fread(&emprestimo, sizeof(Emprestimo), 1, file) == 1) {
        if (emprestimo.idUsuario == idUsuario && emprestimo.idLivro == idLivro) {
            emprestimo.dataDevolucao += REEMPRESTIMO;
            fseek(file, -sizeof(Emprestimo), SEEK_CUR);
            fwrite(&emprestimo, sizeof(Emprestimo), 1, file);
            printf("Data atualizado com sucesso! Nova data de devolução: %s\n", ctime(&emprestimo.dataDevolucao));
            fclose(file);
            return;
        }
    }
    printf("Empréstimo não encontrado.\n");
    fclose(file);
}

//função que permite que o usuário adicione um livro no acervo
void doarLivro() {
    cadastrarLivro(); //é possível utilizar a lógica de uma função já existente
    printf("\nLivro doado com sucesso! Obrigado pela sua contribuição.\n");
}

//função que exibe os empréstimos do usuário
void listarEmprestimos(int idUsuario) {
    FILE *fileEmprestimos = fopen("emprestimos.dat", "rb");
    FILE *fileLivros = fopen("livros.dat", "rb");
    if (fileEmprestimos == NULL || fileLivros == NULL) {
        perror("ERRO");
        if (fileEmprestimos) fclose(fileEmprestimos);
        if (fileLivros) fclose(fileLivros);
        return;
    }
    Emprestimo emprestimo;
    Livro livro;
    printf("\nLivros Emprestados:\n");
    printf("\n-------------------\n");
    while (fread(&emprestimo, sizeof(Emprestimo), 1, fileEmprestimos) == 1) {
        if (emprestimo.idUsuario == idUsuario) { 
            rewind(fileLivros);
            while (fread(&livro, sizeof(Livro), 1, fileLivros) == 1) {
                if (livro.id == emprestimo.idLivro) {
                    struct tm *dataDevolucao = localtime(&emprestimo.dataDevolucao);
                    printf("Título: %s\nAutor: %s\nAno de Publicação: %d\nData de Devolução: %02d/%02d/%04d\n",
                           livro.titulo, livro.autor, livro.ano,
                           dataDevolucao->tm_mday, dataDevolucao->tm_mon + 1, dataDevolucao->tm_year + 1900);
                    printf("--------------------------\n");
                    break;
                }
            }
        }
    }
    fclose(fileEmprestimos);
    fclose(fileLivros);
}