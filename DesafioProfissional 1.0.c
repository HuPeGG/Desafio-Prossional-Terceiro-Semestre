#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_VEICULOS 10 // Define o numero maximo de veiculos
#define MAX_USERS 100 // Define o numero maximo de usuarios
#define MAX_USERNAME_LENGTH 20 // Define o comprimento maximo do nome de usuario
#define MAX_PASSWORD_LENGTH 20 // Define o comprimento maximo da senha
#define MAX_FUNCIONARIOS 100 // Define o maximo de funcionario

// Estrutura para armazenar informações do usuario
typedef struct
{
    char username[MAX_USERNAME_LENGTH+1]; // Nome de usuario
    char password[MAX_PASSWORD_LENGTH+1]; // Senha
} User;

// Definição da estrutura para armazenar informações do funcionario
struct funcionario
{
    char nome[50];
    char funcao[50];
};

// Definição da estrutura para armazenar informacoes do veiculo
typedef struct
{
    char modelo[50];
    char placa[8];
    int status; // 0 - livre; 1 - em uso; 2 - em manutencao
} Veiculo;

// Função para verificar se um usuario ja existe na lista de usuarios
int user_exists(User users[], int num_users, char username[]);

int opcao;

void login();
void cadastroFuncionario();
void cadastrarVeiculo(Veiculo veiculos[], int *qtdVeiculos);
void exibirVeiculos(Veiculo veiculos[], int qtdVeiculos);
void cadastroVeiculo();
void cadastrarFuncionario();
void reclamacoes();

int main()
{
    setlocale(LC_ALL,"portuguese");
    login();
    return 0;
}

int user_exists(User users[], int num_users, char username[])
{
    for (int i = 0; i < num_users; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            return 1; // Usuario ja existe
        }
    }
    return 0; // Usuario nao existe
}

void login()
{
    User users[MAX_USERS]; // Lista de usuarios
    int num_users = 0; // Numero atual de usuarios cadastrados

    // Loop principal do programa
    while (1)
    {
        printf("\n=== MENU ===\n");
        printf("1. Login\n");
        printf("2. Cadastro\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: // Login
            printf("\n=== LOGIN ===\n");

            // Lê o nome de usuario e a senha
            char username[MAX_USERNAME_LENGTH+1];
            char password[MAX_PASSWORD_LENGTH+1];
            printf("Nome de usuario: ");
            scanf("%s", username);
            printf("Senha: ");
            scanf("%s", password);

            // Verifica se o usuario e a senha estao corretos
            int user_found = 0;
            for (int i = 0; i < num_users; i++)
            {
                if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
                {
                    user_found = 1;
                    break;
                }
            }

            // Imprime uma mensagem de sucesso ou erro de login
            if (user_found)
            {
                printf("\nLogin realizado com sucesso!\n");
            }
            else
            {
                printf("\nUsuario ou senha incorretos.\n");
            }
            tela2();
            break;

        case 2: // Cadastro
            printf("\n=== CADASTRO ===\n");

            // Le o nome de usuario e a senha
            char new_username[MAX_USERNAME_LENGTH+1];
            char new_password[MAX_PASSWORD_LENGTH+1];
            printf("Novo nome de usuario: ");
            scanf("%s", new_username);
            printf("Nova senha: ");
            fflush(stdin);
            scanf("%s", new_password);

            // Verifica se o nome de usuario ja existe
            if (user_exists(users, num_users, new_username))
            {
                printf("\nNome de usuario ja existe. Tente novamente");
            }
            else
            {
                // Adiciona o novo usuário a lista de usuarios
                User new_user;
                strcpy(new_user.username, new_username);
                strcpy(new_user.password, new_password);
                users[num_users] = new_user;
                num_users++;
                printf("\nCadastro realizado com sucesso!\n");
            }
            break;

        case 0: // Sair
            printf("\nSaindo do programa...\n");
            return 0;

        default: // Opção invalida
            printf("\nOpcao invalida. Tente novamente.\n");
            break;
        }
    }
}

void cadastrarVeiculo(Veiculo veiculos[], int *qtdVeiculos)
{
    if (*qtdVeiculos >= MAX_VEICULOS)
    {
        printf("Limite de veiculos atingido!\n");
        return;
    }

    Veiculo v;
    printf("Digite o modelo do veiculo: ");
    scanf("%s", v.modelo);
    printf("Digite a placa do veiculo (formato XXX-YYYY): ");
    scanf("%s", v.placa);
    printf("Digite o status do veiculo (0 - livre, 1 - ocupado, 2 - em manutencao): ");
    scanf("%d", &v.status);

    veiculos[*qtdVeiculos] = v;
    (*qtdVeiculos)++;

    printf("Veiculo cadastrado com sucesso!\n");
}

void exibirVeiculos(Veiculo veiculos[], int qtdVeiculos)
{
    printf("Lista de veiculos cadastrados:\n");
    printf("-------------------------------\n");
    for (int i = 0; i < qtdVeiculos; i++)
    {
        printf("Modelo: %s\n", veiculos[i].modelo);
        printf("Placa: %s\n", veiculos[i].placa);
        switch (veiculos[i].status)
        {
        case 0:
            printf("Status: livre\n");
            break;
        case 1:
            printf("Status: ocupado\n");
            break;
        case 2:
            printf("Status: em manutencao\n");
            break;
        default:
            printf("Status invalido!\n");
            break;
        }
        printf("-------------------------------\n");
    }
}

void cadastroVeiculo()
{
    Veiculo veiculos[MAX_VEICULOS];
    int qtdVeiculos = 0;

    do
    {
        printf("\n1 - Cadastrar veiculo\n");
        printf("2 - Exibir veiculos cadastrados\n");
        printf("0 - Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarVeiculo(veiculos, &qtdVeiculos);
            break;
        case 2:
            exibirVeiculos(veiculos, qtdVeiculos);
            break;
        case 0:
            printf("Encerrando programa...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    }
    while (opcao != 0);
}

void reclamacoes()
{
    char reclamacao[1000]; // Define um array para armazenar a reclamação do usuario

    // Solicita ao usuario para digitar a reclamacao
    printf("Digite sua reclamacao:\n");
    fflush(stdin);
    scanf("%[^\n]", reclamacao);

    // Abre o arquivo para escrita
    FILE *arquivo = fopen("reclamacoes.txt", "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Escreve a reclamacao do usuario no arquivo
    fprintf(arquivo, "%s\n", reclamacao);

    // Fecha o arquivo
    fclose(arquivo);

    // Exibe uma mensagem de confirmação para o usuario
    printf("Sua reclamacao foi salva com sucesso.\n");
}

void cadastroFuncionario()
{
    // Tela de cadastro
    int qtdVeiculos = 0;
    printf("Cadastro\n");
    printf("Escolha uma opcao:\n");
    printf("1 - Cadastrar funcionario\n");
    printf("2 - Cadastrar veiculo\n");
    printf("0 - Sair\n");
    scanf("%d", &opcao);

    do
    {
        switch(opcao)
        {
        case 1:
            cadastrarFuncionario();
            break;

        case 2:
            cadastroVeiculo();
            break;
        case 0:
            printf("Encerrando programa...\n");
            break;

        default:
            printf("Opcao invalida\n");
            break;
        }
        return tela2();
    }
    while (opcao != 1);
}
void tela2()
{
    do
    {
        printf("Escolha uma opcao:\n");
        printf("1 - Cadastro\n");
        printf("2 - Reclamacoes\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);

        switch(opcao)
        {
        case 1:
            cadastroFuncionario();
            break;

        case 2:
            reclamacoes();
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida\n");
            break;
        }

    }
    while(opcao != 0);
}

void cadastrarFuncionario()
{
    struct funcionario funcionarios[MAX_FUNCIONARIOS];
    int num_funcionarios = 0;

    while (1)
    {
        printf("\nCadastro de Funcionarios\n");
        printf("1. Cadastrar novo funcionario\n");
        printf("2. Exibir funcionarios cadastrados\n");
        printf("0. Sair\n");

        int opcao;
        scanf("%d", &opcao);

        if (opcao == 0)
        {
            break;
        }
        else if (opcao == 1)
        {
            if (num_funcionarios >= MAX_FUNCIONARIOS)
            {
                printf("Erro: maximo de funcionarios cadastrados atingido\n");
                continue;
            }

            struct funcionario novo_funcionario;

            printf("\nDigite o nome do funcionario: ");
            scanf("%s", novo_funcionario.nome);

            printf("Digite a funcao do funcionario: ");
            scanf("%s", novo_funcionario.funcao);

            funcionarios[num_funcionarios++] = novo_funcionario;
            printf("Funcionario cadastrado com sucesso!\n");
        }
        else if (opcao == 2)
        {
            if (num_funcionarios == 0)
            {
                printf("Nenhum funcionario cadastrado ainda.\n");
                continue;
            }

            printf("\nFuncionarios cadastrados:\n");
            printf("-------------------------------\n");
            for (int i = 0; i < num_funcionarios; i++)
            {
                printf("%d. Nome: %s\n   Funcao: %s\n", i+1, funcionarios[i].nome, funcionarios[i].funcao);
                printf("-------------------------------\n");
            }

        }
        else
        {
            printf("Opcao invalida\n");
        }
    }

    printf("Programa encerrado.\n");

}
