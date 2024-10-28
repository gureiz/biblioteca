# Sistema de Gerenciamento de Biblioteca

Este é um sistema de gerenciamento de biblioteca implementado em C. Ele permite o cadastro de usuários e livros, empréstimo e reempréstimo de livros, listagem de acervo e doação de livros. O sistema inclui controle de acesso para diferenciar usuários regulares de administradores.

## Funcionalidades

  ### Usuário Comum
  	
  - **Cadastro de Usuário**: Permite que um usuário se registre no sistema.
  - **Login**: Autentica o usuário no sistema.
  - **Visualização do Acervo**: Exibe a lista de livros disponíveis na biblioteca.
  - **Empréstimo de Livros**: Permite que o usuário realize empréstimos de livros.
  - **Renovação de Livros**: Usuários podem renovar o empréstimo de livros.
  - **Listagem de Empréstimos**: Exibe a lista de livros atualmente emprestados pelo usuário.
  - **Doação de Livros**: Usuários podem doar livros ao acervo da biblioteca.

  ### Administrador

  - **Login Administrativo**: Um administrador pode fazer login com um e-mail e senha específicos (`adm@adm.com` e `adm`).
  - **Cadastro de Livros**: Permite que o administrador adicione novos livros ao acervo da biblioteca.
  
## Estrutura de Arquivos

O sistema utiliza arquivos para armazenar informações de usuários, livros e empréstimos:
- **usuarios.txt**: Armazena dados de usuários (ID, nome, e-mail, senha).
- **livros.dat**: Armazena dados dos livros cadastrados (ID, título, autor, ano).
- **emprestimos.dat**: Armazena dados dos empréstimos realizados (ID do usuário, ID do livro, datas de empréstimo e devolução).
Cada arquivo é criado automaticamente, caso não exista, ao iniciar o programa.

## Compilação

Certifique-se de que possui o compilador GCC instalado. Para compilar o programa, execute o seguinte comando no terminal, no diretório onde está o arquivo `biblioteca.c`:
gcc biblioteca.c -o biblioteca –Wall
Esse comando compilará o código-fonte biblioteca.c e criará um executável chamado biblioteca.

##Execução

Após compilar o código, execute o programa com o seguinte comando:
./biblioteca
O programa exibirá um menu inicial para que o usuário se registre, faça login ou encerre o programa.

##Uso do Sistema

  ###Cadastro e Login
  
  1.	Ao executar o programa, o usuário verá três opções no menu principal:
  o	Cadastrar: Para criar uma nova conta de usuário.
  o	Login: Para entrar no sistema usando e-mail e senha.
  o	Sair: Para fechar o programa.
  2.	Login Administrativo: O administrador pode fazer login usando o e-mail adm@adm.com e a senha adm, que oferece acesso a funcionalidades adicionais.
  	
  ###Menu Principal
  
  Após o login, o usuário verá o menu principal:
  •	Cadastrar Livro: Permite ao administrador adicionar novos livros ao sistema.
  •	Acervo: Exibe a lista completa de livros cadastrados.
  •	Empréstimo: Permite que o usuário empreste um livro.
  •	Renovar Empréstimo: Permite que o usuário renove o prazo de devolução de um livro emprestado.
  •	Doe um Livro: O usuário pode doar um novo livro ao acervo.
  •	Meus Empréstimos: Exibe a lista de livros emprestados pelo usuário.
  •	Voltar: Retorna ao menu inicial.
  
  ###Gerenciamento de Empréstimos
  
  •	Empréstimo de Livro: O usuário fornece o ID do livro desejado. O sistema verifica a disponibilidade e realiza o empréstimo caso esteja disponível.
  •	Revovar Livro: Permite que o usuário renove o prazo de devolução de um livro emprestado.
  
  ###Estrutura de Código
  
  As principais estruturas de dados e funções no código incluem:
  •	Estruturas
    o	Livro: Representa um livro, armazenando ID, título, autor e ano de publicação.
    o	Usuario: Representa um usuário, armazenando ID, nome, e-mail e senha.
    o	Emprestimo: Representa um empréstimo, armazenando ID do usuário, ID do livro e datas de empréstimo e devolução.
  •	Funções
    o	criarArquivos(): Cria arquivos de dados se eles não existirem.
    o	gerarIdUsuario() e gerarIdLivro(): Gera IDs únicos para usuários e livros.
    o	cadastrarUsuario(): Cadastra um novo usuário.
    o	realizarLogin(): Autentica o usuário ou administrador.
    o	menuPrincipal(): Exibe o menu principal com as funcionalidades do sistema.
    o	menuLogin(): Exibe o menu inicial para cadastro e login.
    o	cadastrarLivro(): Adiciona um novo livro ao sistema (exclusivo para o administrador).
    o	listarLivros(): Exibe o acervo de livros disponíveis.
    o	emprestarLivro(): Realiza o empréstimo de um livro para um usuário.
    o	reemprestarLivro(): Renova o empréstimo de um livro.
    o	doarLivro(): Permite que o usuário doe um livro.
    o	listarEmprestimos(): Exibe os livros atualmente emprestados pelo usuário.
    
##Notas Adicionais

  •	Prazo de Empréstimo: O prazo padrão para devolução de um livro é de duas semanas. No caso de renovação, o prazo é estendido por uma semana adicional.
  •	Controle de Acesso: O administrador tem permissões exclusivas para adicionar livros ao sistema.
  
##Exemplos de Uso

  1.	Cadastro e Login
  o	Execute o programa e escolha a opção "Cadastrar" para criar uma nova conta.
  o	Após o cadastro, faça login com seu e-mail e senha.
  2.	Realizar Empréstimo
  o	Após o login, escolha a opção "Empréstimo".
  o	Digite o ID do livro desejado para realizar o empréstimo.
  3.	Reempréstimo
  o	Escolha a opção "Atualizar Empréstimo" e insira o ID do livro para estender o prazo.
  4.	Doação de Livro
  o	Escolha "Doe um Livro" para adicionar um novo livro ao acervo.

##Autores	

Gustavo Reis Teixeira     RA: 22.124.055-9
Lucas Gasparetto Pimentel RA: 22.124.025-2

