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

#define MAX_LEN 100

typedef struct {
    int id;                      // ID da empresa
    char nomeEmpresa[MAX_LEN];   // Nome da empresa
    int mes;                     // Mês correspondente
    int quantidadeResiduos;      // Quantidade de resíduos tratados
    float valorEstimado;         // Valor estimado
} Residuo;


#define MAX_LEN 256

// Estrutura para armazenar dados da empresa
typedef struct {
    int id;
    char nomeResponsavel[MAX_LEN];
    char telefoneResponsavel[MAX_LEN];
    char emailResponsavel[MAX_LEN];
    char nomeEmpresa[MAX_LEN];
    char cnpj[MAX_LEN];
    char razaoSocial[MAX_LEN];
    char nomeFantasia[MAX_LEN];
    char telefoneEmpresa[MAX_LEN];
    char rua[MAX_LEN];
    char numero[MAX_LEN];
    char bairro[MAX_LEN];
    char cidade[MAX_LEN];
    char estado[MAX_LEN];
    char cep[MAX_LEN];
    char emailEmpresa[MAX_LEN];
    char dataAbertura[MAX_LEN];
    char outrosDados[MAX_LEN];
} Empresa;


int obterUltimoIdEmpresa() {
    FILE *arquivo = fopen(EMPRESAS_ARQUIVO, "r");
    if (arquivo == NULL) {
        return 0; // Se não houver arquivo, retorna 0 (primeiro ID)
    }

    int ultimoId = 0;
    char linha[MAX_LEN];

    while (fgets(linha, sizeof(linha), arquivo)) {
        Empresa e;
        sscanf(linha, "%d|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]",
               &e.id, e.nomeResponsavel, e.telefoneResponsavel, e.emailResponsavel,
               e.nomeEmpresa, e.cnpj, e.razaoSocial, e.nomeFantasia, e.telefoneEmpresa,
               e.rua, e.numero, e.bairro, e.cidade, e.estado, e.cep, e.emailEmpresa,
               e.dataAbertura, e.outrosDados);

        if (e.id > ultimoId) {
            ultimoId = e.id;
        }
    }

    fclose(arquivo);
    return ultimoId;
}


void cadastrarEmpresa() {
    FILE *arquivo = fopen(EMPRESAS_ARQUIVO, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Empresa e;
    int ultimoId = obterUltimoIdEmpresa();
    e.id = ultimoId + 1; // Incrementa o último ID registrado

    printf("Digite os dados da empresa:\n");

    // Coletar dados
    printf("Nome do responsável: ");
    getchar(); // Limpar o buffer do teclado
    fgets(e.nomeResponsavel, MAX_LEN, stdin);
    e.nomeResponsavel[strcspn(e.nomeResponsavel, "\n")] = 0;

    printf("Telefone do responsável: ");
    fgets(e.telefoneResponsavel, MAX_LEN, stdin);
    e.telefoneResponsavel[strcspn(e.telefoneResponsavel, "\n")] = 0;

    printf("E-mail do responsável: ");
    fgets(e.emailResponsavel, MAX_LEN, stdin);
    e.emailResponsavel[strcspn(e.emailResponsavel, "\n")] = 0;

    printf("Nome da empresa: ");
    fgets(e.nomeEmpresa, MAX_LEN, stdin);
    e.nomeEmpresa[strcspn(e.nomeEmpresa, "\n")] = 0;

    printf("CNPJ: ");
    fgets(e.cnpj, MAX_LEN, stdin);
    e.cnpj[strcspn(e.cnpj, "\n")] = 0;

    printf("Razão social: ");
    fgets(e.razaoSocial, MAX_LEN, stdin);
    e.razaoSocial[strcspn(e.razaoSocial, "\n")] = 0;

    printf("Nome fantasia: ");
    fgets(e.nomeFantasia, MAX_LEN, stdin);
    e.nomeFantasia[strcspn(e.nomeFantasia, "\n")] = 0;

    printf("Telefone da empresa: ");
    fgets(e.telefoneEmpresa, MAX_LEN, stdin);
    e.telefoneEmpresa[strcspn(e.telefoneEmpresa, "\n")] = 0;

    printf("Rua: ");
    fgets(e.rua, MAX_LEN, stdin);
    e.rua[strcspn(e.rua, "\n")] = 0;

    printf("Número: ");
    fgets(e.numero, MAX_LEN, stdin);
    e.numero[strcspn(e.numero, "\n")] = 0;

    printf("Bairro: ");
    fgets(e.bairro, MAX_LEN, stdin);
    e.bairro[strcspn(e.bairro, "\n")] = 0;

    printf("Cidade: ");
    fgets(e.cidade, MAX_LEN, stdin);
    e.cidade[strcspn(e.cidade, "\n")] = 0;

    printf("Estado: ");
    fgets(e.estado, MAX_LEN, stdin);
    e.estado[strcspn(e.estado, "\n")] = 0;

    printf("CEP: ");
    fgets(e.cep, MAX_LEN, stdin);
    e.cep[strcspn(e.cep, "\n")] = 0;

    printf("E-mail da empresa: ");
    fgets(e.emailEmpresa, MAX_LEN, stdin);
    e.emailEmpresa[strcspn(e.emailEmpresa, "\n")] = 0;

    printf("Data de abertura: ");
    fgets(e.dataAbertura, MAX_LEN, stdin);
    e.dataAbertura[strcspn(e.dataAbertura, "\n")] = 0;

    printf("Outros dados relevantes: ");
    fgets(e.outrosDados, MAX_LEN, stdin);
    e.outrosDados[strcspn(e.outrosDados, "\n")] = 0;

   // Salvar dados no arquivo
    fprintf(arquivo, "%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
            e.id, e.nomeResponsavel, e.telefoneResponsavel, e.emailResponsavel,
            e.nomeEmpresa, e.cnpj, e.razaoSocial, e.nomeFantasia, e.telefoneEmpresa,
            e.rua, e.numero, e.bairro, e.cidade, e.estado, e.cep, e.emailEmpresa,
            e.dataAbertura, e.outrosDados);

    fclose(arquivo);
    printf("Cadastro realizado com sucesso!\n");
}


// Fun��o para buscar empresa por ID
void buscarEmpresaPorID() {
    FILE *arquivo = fopen("empresas.txt", "r"); // Abre o arquivo para leitura
    if (arquivo == NULL) {
        printf("Nenhum registro encontrado. O arquivo n�o existe.\n");
        return;
    }

    int idBusca;
    printf("Digite o ID da empresa que deseja buscar (somente numeros) : ");
    scanf("%d", &idBusca);

    char linha[1024];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        Empresa e;

        // Divide os campos da linha usando "/" como delimitador
        sscanf(linha, "%d/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^\n]",
               &e.id, e.nomeResponsavel, e.telefoneResponsavel, e.emailResponsavel,
               e.nomeEmpresa, e.cnpj, e.razaoSocial, e.nomeFantasia,
               e.telefoneEmpresa, e.rua, e.numero, e.bairro, e.cidade,
               e.estado, e.cep, e.emailEmpresa, e.dataAbertura, e.outrosDados);

        if (e.id == idBusca) {
            printf("\n========== Empresa Encontrada ==========\n");
            printf("ID: %d\n", e.id);
            printf("Respons�vel:\n");
            printf("  Nome: %s\n", e.nomeResponsavel);
            printf("  Telefone: %s\n", e.telefoneResponsavel);
            printf("  E-mail: %s\n", e.emailResponsavel);
            printf("\nDados da Empresa:\n");
            printf("  Nome: %s\n", e.nomeEmpresa);
            printf("  CNPJ: %s\n", e.cnpj);
            printf("  Raz�o Social: %s\n", e.razaoSocial);
            printf("  Nome Fantasia: %s\n", e.nomeFantasia);
            printf("  Telefone: %s\n", e.telefoneEmpresa);
            printf("\nEndere�o:\n");
            printf("  Rua: %s, N�mero: %s\n", e.rua, e.numero);
            printf("  Bairro: %s, Cidade: %s, Estado: %s, CEP: %s\n", e.bairro, e.cidade, e.estado, e.cep);
            printf("\nOutros Dados:\n");
            printf("  E-mail: %s\n", e.emailEmpresa);
            printf("  Data de Abertura: %s\n", e.dataAbertura);
            printf("  Informa��es Adicionais: %s\n", e.outrosDados);
            printf("========================================\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Nenhuma empresa encontrada com o ID informado.\n");
    }

    fclose(arquivo);
}


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


// Função para carregar as empresas do arquivo
Empresa* carregarEmpresas(int *tamanho) {
    FILE *arquivo = fopen("empresas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de empresas.\n");
        return NULL;
    }

    Empresa* lista = NULL;
    char linha[MAX_LEN];
    int count = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        Empresa novaEmpresa;

        // Certifique-se de que o formato da linha está correto
        if (sscanf(linha, "%d|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]",
                   &novaEmpresa.id, novaEmpresa.nomeResponsavel, novaEmpresa.telefoneResponsavel,
                   novaEmpresa.emailResponsavel, novaEmpresa.nomeEmpresa, novaEmpresa.cnpj,
                   novaEmpresa.razaoSocial, novaEmpresa.nomeFantasia, novaEmpresa.telefoneEmpresa,
                   novaEmpresa.rua, novaEmpresa.numero, novaEmpresa.bairro, novaEmpresa.cidade,
                   novaEmpresa.estado, novaEmpresa.cep, novaEmpresa.emailEmpresa,
                   novaEmpresa.dataAbertura, novaEmpresa.outrosDados) == 17) {

            Empresa* novaLista = realloc(lista, (count + 1) * sizeof(Empresa));
            if (!novaLista) {
                printf("Erro ao alocar memória para as empresas.\n");
                free(lista);
                fclose(arquivo);
                return NULL;
            }

            lista = novaLista;
            lista[count++] = novaEmpresa;
        } else {
            printf("Formato inválido na linha: %s\n", linha);  // Imprime a linha que está com formato errado
        }
    }

    fclose(arquivo);
    *tamanho = count;
    return lista;
}


// Função para exibir as empresas carregadas
void exibirEmpresas() {
    int tamanho;
    Empresa* empresas = carregarEmpresas(&tamanho);
    if (empresas != NULL) {
        printf("Empresas disponíveis:\n");
        for (int i = 0; i < tamanho; i++) {
            printf("ID: %d | Nome: %s\n", empresas[i].id, empresas[i].nomeEmpresa);
        }
        free(empresas);
    }
}


void CadastrarResiduo() {
    Residuo novoResiduo;

    // Passo 1: Carregar as empresas do arquivo
    int tamanhoEmpresas;
    Empresa* empresas = carregarEmpresas(&tamanhoEmpresas);

    if (empresas == NULL) {
        printf("Erro ao carregar empresas.\n");
        return;
    }

    // Passo 2: Exibir as empresas para o usuário
    printf("Empresas disponíveis:\n");
    for (int i = 0; i < tamanhoEmpresas; i++) {
        printf("ID: %d | Nome: %s\n", empresas[i].id, empresas[i].nomeEmpresa);
    }

    // Passo 3: Solicitar que o usuário escolha uma empresa
    printf("Digite o ID da empresa selecionada: ");
    scanf("%d", &novoResiduo.id);  // A empresa associada ao resíduo

    // Verificar se o ID selecionado é válido
    int empresaSelecionadaValida = 0;
    for (int i = 0; i < tamanhoEmpresas; i++) {
        if (empresas[i].id == novoResiduo.id) {
            empresaSelecionadaValida = 1;
            break;
        }
    }
    if (!empresaSelecionadaValida) {
        printf("ID de empresa inválido!\n");
        return;
    }

    // Passo 4: Solicitar os dados do resíduo
    printf("Digite o número do mês correspondente: ");
    scanf("%d", &novoResiduo.mes);

    if(novoResiduo.mes < 1 || novoResiduo.mes > 12) {
        printf("Mês inválido!\n");
        return;
    }

    printf("Digite a quantidade de resíduos tratados: ");
    scanf("%d", &novoResiduo.quantidadeResiduos);

    if(novoResiduo.quantidadeResiduos < 0) {
        printf("Quantidade de resíduos inválida!\n");
        return;
    }

    printf("Digite o valor estimado de custo: ");
    scanf("%f", &novoResiduo.valorEstimado);

    if(novoResiduo.valorEstimado < 0.01) {
        printf("Valor estimado de custo inválido!\n");
        return;
    }

    // Passo 5: Salvar o resíduo no arquivo
    FILE *file = fopen("residuos.txt", "a");

    if (file == NULL) {
        printf("Erro: Não foi possível abrir o arquivo para resíduos.\n");
    } else {
        fprintf(file, "%d|%d|%d|%f\n", novoResiduo.id, novoResiduo.mes, novoResiduo.quantidadeResiduos, novoResiduo.valorEstimado);
        printf("Cadastro realizado com sucesso.\n\n");
    }

    fclose(file);

    // Liberar a memória da lista de empresas carregada
    free(empresas);
}


Residuo* CarregarResiduos(int* tamanho) {
    FILE* file = fopen(RESIDUOS_ARQUIVO, "r");

    if (!file) {
        printf("Arquivo de resíduos não encontrado. Certifique-se de que o arquivo '%s' existe.\n", RESIDUOS_ARQUIVO);
        *tamanho = 0;
        return NULL;
    }

    Residuo* lista = NULL;
    char linha[256];
    int count = 0;

    while (fgets(linha, sizeof(linha), file)) {
        Residuo novoResiduo;

        if (sscanf(linha, "%d|%d|%d|%f", &novoResiduo.id, &novoResiduo.mes,
                   &novoResiduo.quantidadeResiduos, &novoResiduo.valorEstimado) == 4) {
            Residuo* novaLista = realloc(lista, (count + 1) * sizeof(Residuo));

            if (!novaLista) {
                printf("Erro ao alocar memória!\n");
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
        printf("1 - Cadastro \n");
        printf("2 - Listar \n");
        printf("3 - Voltar \n");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            CadastrarResiduo();
            break;

        case 2:
            lista = CarregarResiduos(&tamanho);

            for (i = 0; i < tamanho; i++)
            {
                printf("ID Empresa: %d | Nome: %s | Mês: %d | Qtd. Resíduos: %d | Valor Estimado: %.2f\n",
                       lista[i].id, lista[i].nomeEmpresa, lista[i].mes, lista[i].quantidadeResiduos, lista[i].valorEstimado);
            }

            free(lista);
            break;

        default:
            if (opcao != 3)
            {
                printf("Opção inválida!\n");
            }
            break;
        }
    }
}


void CriarRelatorios() {
     // Passo 1: Carregar as empresas do arquivo
    int tamanhoEmpresas;
    Empresa* empresas = carregarEmpresas(&tamanhoEmpresas);

    if (empresas == NULL) {
        printf("Erro ao carregar empresas.\n");
        return;
    }

    // Passo 2: Exibir as empresas para o usuário
    printf("Empresas disponíveis:\n");
    for (int i = 0; i < tamanhoEmpresas; i++) {
        printf("ID: %d | Nome: %s\n", empresas[i].id, empresas[i].nomeEmpresa);
    }

    // Passo 3: Solicitar que o usuário escolha uma empresa
    int empresaEscolhida;
    printf("Digite o ID da empresa para gerar o relatório: ");
    scanf("%d", &empresaEscolhida);

    // Verificar se o ID da empresa é válido
    int empresaValida = 0;
    for (int i = 0; i < tamanhoEmpresas; i++) {
        if (empresas[i].id == empresaEscolhida) {
            empresaValida = 1;
            break;
        }
    }

    if (!empresaValida) {
        printf("ID de empresa inválido!\n");
        free(empresas);
        return;
    }

    // Passo 4: Carregar os resíduos tratados para a empresa escolhida
    FILE *residuosArquivo = fopen(RESIDUOS_ARQUIVO, "r");
    if (residuosArquivo == NULL) {
        printf("Erro ao abrir o arquivo de resíduos.\n");
        free(empresas);
        return;
    }

    int totalResiduosSemestral = 0;
    float totalGastosMensais = 0.0f;
    char linha[MAX_LEN];
    while (fgets(linha, sizeof(linha), residuosArquivo)) {
        Residuo res;
        if (sscanf(linha, "%d|%d|%d|%f", &res.id, &res.mes, &res.quantidadeResiduos, &res.valorEstimado) == 4) {
            if (res.id == empresaEscolhida) {
                // Calcular total de resíduos tratados semestralmente
                if (res.mes >= 1 && res.mes <= 6) {
                    totalResiduosSemestral += res.quantidadeResiduos;
                }

                // Calcular total de gastos mensais
                totalGastosMensais += res.valorEstimado;
            }
        }
    }
    fclose(residuosArquivo);

    // Passo 5: Gerar o relatório
    printf("\n======== Relatório da Empresa: %s ========\n", empresas[empresaEscolhida - 1].nomeEmpresa);
    printf("Total de resíduos tratados semestralmente: %d unidades\n", totalResiduosSemestral);
    printf("Total de gastos mensais estimados: R$ %.2f\n", totalGastosMensais);

    // Liberar a memória da lista de empresas carregada
    free(empresas);
}


void ExibirMenuPrincipal()
{
    int opcao;

    while (opcao != 5)
    {
        printf("Menu Principal: \n\n");
        printf("1 - Cadastro de Clientes\n");
        printf("2 - Buscar empresa cadastrada por ID\n");
        printf("3 - Gerenciamento de Resíduos\n");
        printf("4 - Criar Relatórios\n");
        printf("5 - Sair do programa\n");

        scanf("%d", &opcao);

        LimparConsole();

        switch (opcao)
        {

        case 1:

            cadastrarEmpresa();

            break;

        case 2:

            buscarEmpresaPorID();

            break;

        case 3:

            GerenciarResiduos();

            break;

        case 4:

            CriarRelatorios();

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
