#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_VEICULOS 10 // Define o n�mero m�ximo de ve�culos
#define MAX_USERS 100 // Define o n�mero m�ximo de usu�rios
#define MAX_USERNAME_LENGTH 20 // Define o comprimento m�ximo do nome de usu�rio
#define MAX_PASSWORD_LENGTH 20 // Define o comprimento m�ximo da senha

// Estrutura para armazenar informa��es do usu�rio
typedef struct
{
    char username[MAX_USERNAME_LENGTH+1]; // Nome de usu�rio
    char password[MAX_PASSWORD_LENGTH+1]; // Senha
} User;

// Defini��o da estrutura para armazenar informa��es do funcion�rio
typedef struct
{
    char nome[50];
    char funcao[50];
    char cpf[12];
} Funcionario;

// Defini��o da estrutura para armazenar informa��es do ve�culo
typedef struct
{
    char modelo[50];
    char placa[8];
    int status; // 0 - livre; 1 - em uso; 2 - em manuten��o
} Veiculo;

// Fun��o para verificar se um usu�rio j� existe na lista de usu�rios
int user_exists(User users[], int num_users, char username[]);

int opcao;

void login();
void cadastroFuncionario();
void cadastrarVeiculo(Veiculo veiculos[], int *qtdVeiculos);
void exibirVeiculos(Veiculo veiculos[], int qtdVeiculos);
void cadastroVeiculo();
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
            return 1; // Usu�rio j� existe
        }
    }
    return 0; // Usu�rio n�o existe
}

void login()
{
    User users[MAX_USERS]; // Lista de usu�rios
    int num_users = 0; // N�mero atual de usu�rios cadastrados

    // Loop principal do programa
    while (1)
    {
        printf("\n=== MENU ===\n");
        printf("1. Login\n");
        printf("2. Cadastro\n");
        printf("0. Sair\n");
        printf("Escolha uma op��o: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: // Login
            printf("\n=== LOGIN ===\n");

            // L� o nome de usu�rio e a senha
            char username[MAX_USERNAME_LENGTH+1];
            char password[MAX_PASSWORD_LENGTH+1];
            printf("Nome de usuario: ");
            scanf("%s", username);
            printf("Senha: ");
            scanf("%s", password);

            // Verifica se o usu�rio e a senha est�o corretos
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
                do
                {
                    printf("Escolha uma opcao:\n");
                    printf("1 - Cadastro\n");
                    printf("2 - Reclama��es\n");
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
            else
            {
                printf("\nUsuario ou senha incorretos.\n");
            }
            break;

        case 2: // Cadastro
            printf("\n=== CADASTRO ===\n");

            // L� o nome de usu�rio e a senha
            char new_username[MAX_USERNAME_LENGTH+1];
            char new_password[MAX_PASSWORD_LENGTH+1];
            printf("Novo nome de usuario: ");
            scanf("%s", new_username);
            printf("Nova senha: ");
            fflush(stdin);
            scanf("%s", new_password);

            // Verifica se o nome de usu�rio j� existe
            if (user_exists(users, num_users, new_username))
            {
                printf("\nNome de usuario ja existe. Tente novamente");
            }
            else
            {
                // Adiciona o novo usu�rio � lista de usu�rios
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

        default: // Op��o inv�lida
            printf("\nOpcao invalida. Tente novamente.\n");
            break;
        }
    }
}

void cadastrarVeiculo(Veiculo veiculos[], int *qtdVeiculos)
{
    if (*qtdVeiculos >= MAX_VEICULOS)
    {
        printf("Limite de ve�culos atingido!\n");
        return;
    }

    Veiculo v;
    printf("Digite o modelo do ve�culo: ");
    scanf("%s", v.modelo);
    printf("Digite a placa do ve�culo (formato XXX-YYYY): ");
    scanf("%s", v.placa);
    printf("Digite o status do ve�culo (0 - livre, 1 - ocupado, 2 - em manuten��o): ");
    scanf("%d", &v.status);

    veiculos[*qtdVeiculos] = v;
    (*qtdVeiculos)++;

    printf("Ve�culo cadastrado com sucesso!\n");
}

void exibirVeiculos(Veiculo veiculos[], int qtdVeiculos)
{
    printf("Lista de ve�culos cadastrados:\n");
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
            printf("Status: em manuten��o\n");
            break;
        default:
            printf("Status inv�lido!\n");
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
        printf("\n1 - Cadastrar ve�culo\n");
        printf("2 - Exibir ve�culos cadastrados\n");
        printf("0 - Sair\n");
        printf("Digite a op��o desejada: ");
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
            printf("Op��o inv�lida!\n");
            break;
        }
    }
    while (opcao != 0);
}

void reclamacoes()
{
    char reclamacao[1000]; // Define um array para armazenar a reclama��o do usu�rio

    // Solicita ao usu�rio para digitar a reclama��o
    printf("Digite sua reclama��o:\n");
    fflush(stdin);
    scanf("%[^\n]", reclamacao);

    // Abre o arquivo para escrita
    FILE *arquivo = fopen("reclamacoes.txt", "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Escreve a reclama��o do usu�rio no arquivo
    fprintf(arquivo, "%s\n", reclamacao);

    // Fecha o arquivo
    fclose(arquivo);

    // Exibe uma mensagem de confirma��o para o usu�rio
    printf("Sua reclama��o foi salva com sucesso.\n");
}

void cadastroFuncionario()
{
    // Tela de cadastro
    int numFuncionarios = 0;
    int qtdVeiculos = 0;
    Funcionario funcionarios[50];
    printf("Cadastro\n");
    printf("Escolha uma opcao:\n");
    printf("1 - Cadastrar funcionario\n");
    printf("2 - Cadastrar veiculo\n");
    printf("0 - Sair\n");
    scanf("%d", &opcao);

    do{
    switch(opcao)
    {
    case 1:
        // Cadastro de funcion�rio
        printf("Cadastro de funcionario\n");
        printf("Digite o nome: ");
        scanf("%s", funcionarios[numFuncionarios].nome);
        printf("Digite a funcao: ");
        scanf("%s", funcionarios[numFuncionarios].funcao);
        printf("Funicion�rio registrado!\n");
        numFuncionarios++;
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
        return 0;
    }while (opcao != 1);
}
