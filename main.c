#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define CREDENCIAIS_ARQUIVO "credenciais.txt"
#define EMPRESAS_ARQUIVO "empresas.txt"
#define RESIDUOS_ARQUIVO "residuos.txt"

typedef struct
{
    int id;
    int quantidadeResiduos;
    int mes;
    float valorEstimado;

} Residuo;

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
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
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

    fprintf(file, "%lu %lu\n", hashUsuario, hashSenha);
    fclose(file);
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

void CadastrarResiduo()
{
    Residuo novoResiduo;

    printf("Empresas:\n");
    printf("1 - Empresa1\n");
    printf("2 - Empresa2\n");

    printf("Digite o código da empresa selecionada:");
    scanf("%d", &novoResiduo.id);

    printf("Digite o número do mês correspondente: ");
    scanf("%d", &novoResiduo.mes);

    if(novoResiduo.mes <1 || novoResiduo.mes >12)
    {
        printf("Mês inválido!\n");
        return;
    }

    printf("Digite a quantidade de resíduos ambientais tratados: ");
    scanf("%d", &novoResiduo.quantidadeResiduos);

    if(novoResiduo.quantidadeResiduos <0)
    {
        printf("Quantidade de resíduos inválida!\n");
        return;
    }

    printf("Digite o valor estimado de custo: ");
    scanf("%f", &novoResiduo.valorEstimado);

    if(novoResiduo.valorEstimado <0.01)
    {
        printf("Valor estimado de custo inválido!\n");
        return;
    }

    FILE *file = fopen(RESIDUOS_ARQUIVO, "a");

    if (file == NULL)
    {
        printf("Erro: Não foi possível abrir o arquivo para de resíduos para escrita.\n");
    }
    else
    {
        fprintf(file, "%d|%d|%d|%f\n", novoResiduo.id, novoResiduo.mes, novoResiduo.quantidadeResiduos, novoResiduo.valorEstimado);
        printf("Cadastro realizado com sucesso.\n\n");
    }

    fclose(file);
}

Residuo* CarregarResiduos(int* tamanho)
{

    FILE* file = fopen(RESIDUOS_ARQUIVO, "r");
    if (!file)
    {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    Residuo* lista = NULL;

    char linha[256];
    int count = 0;

    while (fgets(linha, sizeof(linha), file))
    {
        Residuo novoResiduo;

        if (sscanf(linha, "%d|%d|%d|%f", &novoResiduo.id, &novoResiduo.mes, &novoResiduo.quantidadeResiduos, &novoResiduo.valorEstimado) == 4)
        {
            Residuo* novaLista = realloc(lista, (count + 1) * sizeof(Residuo));

            if (!novaLista)
            {
                printf("Erro ao carregar memória!\n");
                free(lista);
                fclose(file);
                return NULL;
            }

            lista = novaLista;
            lista[count++] = novoResiduo;
        }
    }

    fclose(file);

    *tamanho = count;

    return lista;
}

void GerenciarResiduos()
{
    int opcao;
    int tamanho;
    int i;
    Residuo* lista;

    while (opcao != 3)
    {
        printf("Gerenciar Resíduos: \n\n");
        printf("Menu Principal: \n\n");
        printf("1 - Cadastro: \n");
        printf("2 - Listar: \n");
        printf("3 - Voltar: \n");

        scanf("%d", &opcao);

        switch (opcao)
        {

        case 1:

            CadastrarResiduo();

            break;

        case 2:

            lista = CarregarResiduos(&tamanho);

            for(i = 0; i < tamanho; i++)
            {
                printf( "Empresa ID: %d, Mês: %d, Qtd. Resíduos: %d, Valor Estimado: %.2f\n", lista[i].id, lista[i].mes, lista[i].quantidadeResiduos, lista[i].valorEstimado);
            }

            break;

        default:

            if (opcao != 3)
            {
                printf("Opção inválida!\n");
            }
            else
            {
                LimparConsole();
            }

            break;
        }
    }
}

void ExibirMenuPrincipal()
{
    int opcao;

    while (opcao != 4)
    {
        printf("Menu Principal: \n\n");
        printf("1 - Cadastro de Clientes\n");
        printf("2 - Gerenciamento de Resíduos\n");
        printf("3 - Criar Relatórios\n");
        printf("4 - Sair do programa\n");

        scanf("%d", &opcao);

        LimparConsole();

        switch (opcao)
        {

        case 1:

            printf("Opção 1 digitada!\n");

            break;

        case 2:

            GerenciarResiduos();

            break;

        case 3:

            printf("Opção 3 digitada!\n");

            break;

        default:

            if (opcao != 4)
            {
                printf("Opção inválida!\n");
            }

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

    LimparConsole();

    printf("Obrigado por utilizar o sistema!\n");

    return 0;
}
