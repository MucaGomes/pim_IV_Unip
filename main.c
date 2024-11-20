#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define CREDENCIAIS_ARQUIVO "credenciais.txt"

void DefinirIdioma()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}
// Função de hash simples baseada no algoritmo DJBX33A
unsigned long GerarHash(const char *str)
{
    unsigned long hash = 5381; // Valor inicial arbitrário
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

void LimparConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void CriarNovoUsuario()
{
    char usuarioInicial[50], senhaInicial[50];

    printf("Nenhum usuário encontrado. \nCrie um nome de usuário inicial: ");
    scanf("%s", usuarioInicial);

    printf("Crie uma senha inicial: ");
    scanf("%s", senhaInicial);

    SalvarCredenciais(usuarioInicial, senhaInicial);

    LimparConsole();

    printf("Usuário e senha criados com sucesso!\n\n");
}

// Função para salvar o nome de usuário e senha no arquivo
void SalvarCredenciais(const char *usuario, const char *senha)
{
    unsigned long hashUsuario = GerarHash(usuario);
    unsigned long hashSenha = GerarHash(senha);

    FILE *file = fopen(CREDENCIAIS_ARQUIVO, "w");
    if (file == NULL)
    {
        printf("Erro: Não foi possível abrir o arquivo para escrita.\n");
        exit(1);
    }

    fprintf(file, "%lu %lu\n", hashUsuario, hashSenha); // Grava os hashes no arquivo
    fclose(file);
}

// Função para carregar os hashes do arquivo
void CarregarCredenciais(unsigned long *hashUsuario, unsigned long *hashSenha)
{
    FILE *file = fopen(CREDENCIAIS_ARQUIVO, "r");
    if (file == NULL)
    {
        printf("Erro: Não foi possível abrir o arquivo de credenciais.\n");
        exit(1);
    }

    if (fscanf(file, "%lu %lu", hashUsuario, hashSenha) != 2)
    {
        printf("Erro: O arquivo de credenciais está vazio ou mal formatado.\n");
        fclose(file);
        exit(1);
    }

    fclose(file);
}

// Função de login
void Login()
{
    unsigned long hashUsuarioArmazenado, hashSenhaArmazenado;

    CarregarCredenciais(&hashUsuarioArmazenado, &hashSenhaArmazenado);

    char inputUsuario[50], inputSenha[50];
    unsigned long inputHashUsuario, inputHashSenha;

    printf("========================\n");
    printf("||  Sistema de Login  ||\n");
    printf("========================\n");

    while (1)
    {
        printf("Digite o nome de usuário: ");
        scanf("%s", inputUsuario);

        printf("Digite a senha: ");
        scanf("%s", inputSenha);

        // Calcula os hashes do usuário e senha digitados
        inputHashUsuario = GerarHash(inputUsuario);
        inputHashSenha = GerarHash(inputSenha);

        if (inputHashUsuario == hashUsuarioArmazenado && inputHashSenha == hashSenhaArmazenado)
        {

            printf("\nLogin realizado com sucesso!\n\n");

            LimparConsole();

            break;
        }
        else
        {
            printf("\nNome de usuário ou senha incorretos. Tente novamente.\n\n");
        }
    }
}

void ExibirMenuPrincipal()
{
    int opcao;

    while (opcao != 4)
    {
        printf("Menu Principal: \n\n");
        printf("1 - Cadastro de Clientes: \n");
        printf("2 - Gerenciamento de Resíduos: \n");
        printf("3 - Criar Relatórios \n");
        printf("4 - Sair do programa: \n");

        scanf("%d", &opcao);

        switch (opcao)
        {

        case 1:

            printf("Opção 1 digitada!\n");

            break;

        case 2:

            printf("Opção 2 digitada!\n");

            break;

        case 3:

            printf("Opção 3 digitada!\n");

            break;

        default:

            printf("Opção inválida!\n");

            break;
        }
    }
}

// Função principal
int main()
{
    DefinirIdioma();

    FILE *file = fopen(CREDENCIAIS_ARQUIVO, "r");

    // Verifica se o arquivo de credenciais já existe
    if (file == NULL)
    {
        CriarNovoUsuario();
    }
    else
    {
        fclose(file);
    }

    // Inicia o processo de login
    Login();

    // Continuação do programa
    printf("Bem-vindo ao sistema!\n\n");

    ExibirMenuPrincipal();

    printf("Obrigado por utilizar o sistema!\n");

    return 0;
}
