#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define CREDENCIAIS_ARQUIVO "credenciais.txt"
#define EMPRESAS_ARQUIVO "empresas.txt"
#define RESIDUOS_ARQUIVO "residuos.txt"

#define MAX_LEN 256

typedef struct
{
    int id;                      // ID da empresa
    char nomeEmpresa[MAX_LEN];   // Nome da empresa
    int mes;                     // Mês correspondente
    int quantidadeResiduos;      // Quantidade de resíduos tratados
    float valorEstimado;         // Valor estimado
} Residuo;

typedef struct
{
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

typedef struct
{
    Empresa empresaSelecionada;
    int quantidadeResiduosPrimeiro;
    int quantidadeResiduosSegundo;
    int quantidadeResiduosTotal;
    float valorEstimadoPrimeiro;
    float valorEstimadoSegundo;
    float valorEstimadoTotal;
} RelatorioIndividual;

typedef struct
{
    Empresa empresaMaiorProducao;
    Empresa empresaMenorProducao;
    float aporteFinanceiroPrimeiro;
    float aporteFinanceiroSegundo;
    float aporteFinanceiroTotal;
} RelatorioGlobal;

void DefinirIdioma()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

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

int ObterUltimoIdEmpresa()
{
    FILE *arquivo = fopen(EMPRESAS_ARQUIVO, "r");
    if (arquivo == NULL)
    {
        return 0;
    }

    int ultimoId = 0;
    char linha[MAX_LEN];

    while (fgets(linha, sizeof(linha), arquivo))
    {
        Empresa e;
        sscanf(linha, "%d|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]",
               &e.id, e.nomeResponsavel, e.telefoneResponsavel, e.emailResponsavel,
               e.nomeEmpresa, e.cnpj, e.razaoSocial, e.nomeFantasia, e.telefoneEmpresa,
               e.rua, e.numero, e.bairro, e.cidade, e.estado, e.cep, e.emailEmpresa,
               e.dataAbertura, e.outrosDados);

        if (e.id > ultimoId)
        {
            ultimoId = e.id;
        }
    }

    fclose(arquivo);
    return ultimoId;
}

void CadastrarEmpresa()
{
    FILE *arquivo = fopen(EMPRESAS_ARQUIVO, "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Empresa e;
    int ultimoId = ObterUltimoIdEmpresa();
    e.id = ultimoId + 1;

    printf("Digite os dados da empresa:\n");

    // Coletar dados
    printf("Nome do responsável: ");
    getchar();
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

    fprintf(arquivo, "%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
            e.id, e.nomeResponsavel, e.telefoneResponsavel, e.emailResponsavel,
            e.nomeEmpresa, e.cnpj, e.razaoSocial, e.nomeFantasia, e.telefoneEmpresa,
            e.rua, e.numero, e.bairro, e.cidade, e.estado, e.cep, e.emailEmpresa,
            e.dataAbertura, e.outrosDados);

    fclose(arquivo);
    printf("Cadastro realizado com sucesso!\n");
}

Empresa* CarregarEmpresas(int *tamanho)
{
    FILE *arquivo = fopen(EMPRESAS_ARQUIVO, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de empresas.\n");
        return NULL;
    }

    Empresa* lista = NULL;
    char linha[MAX_LEN];
    int count = 0;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        Empresa novaEmpresa;

        int colunas;

        if(sscanf(linha, "%d|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]",
                  &novaEmpresa.id, novaEmpresa.nomeResponsavel, novaEmpresa.telefoneResponsavel,
                  novaEmpresa.emailResponsavel, novaEmpresa.nomeEmpresa, novaEmpresa.cnpj,
                  novaEmpresa.razaoSocial, novaEmpresa.nomeFantasia, novaEmpresa.telefoneEmpresa,
                  novaEmpresa.rua, novaEmpresa.numero, novaEmpresa.bairro, novaEmpresa.cidade,
                  novaEmpresa.estado, novaEmpresa.cep, novaEmpresa.emailEmpresa,
                  novaEmpresa.dataAbertura, novaEmpresa.outrosDados) == 18)
        {

            Empresa* novaLista = realloc(lista, (count + 1) * sizeof(Empresa));

            if (!novaLista)
            {
                printf("Erro ao alocar memória para as empresas.\n");
                free(lista);
                fclose(arquivo);
                return NULL;
            }

            lista = novaLista;
            lista[count++] = novaEmpresa;
        }
    }

    fclose(arquivo);
    *tamanho = count;
    return lista;
}

Empresa* LocalizarEmpresa(Empresa* lista, int tamanhoLista, int idEmpresaSelecionada)
{

    for (int i = 0; i < tamanhoLista; i++)
    {
        if (lista[i].id == idEmpresaSelecionada)
        {
            return &lista[i];
        }
    }

    return NULL;
}

void BuscarEmpresaPorID()
{
    int idBusca;
    int encontrado = 0;
    int tamanhoLista;

    Empresa* empresas = CarregarEmpresas(&tamanhoLista);

    printf("Digite o ID da empresa que deseja buscar (somente numeros) : ");
    scanf("%d", &idBusca);

    Empresa* empresaLocalizada = LocalizarEmpresa(empresas, tamanhoLista, idBusca);

    if(empresaLocalizada == NULL)
    {
        printf("Nenhuma empresa encontrada com o ID informado.\n");
    }
    else
    {
        printf("\n========== Empresa Encontrada ==========\n");
        printf("ID: %d\n", empresaLocalizada->id);
        printf("Responsável:\n");
        printf("  Nome: %s\n", empresaLocalizada->nomeResponsavel);
        printf("  Telefone: %s\n", empresaLocalizada->telefoneResponsavel);
        printf("  E-mail: %s\n", empresaLocalizada->emailResponsavel);
        printf("\nDados da Empresa:\n");
        printf("  Nome: %s\n", empresaLocalizada->nomeEmpresa);
        printf("  CNPJ: %s\n", empresaLocalizada->cnpj);
        printf("  Razão Social: %s\n", empresaLocalizada->razaoSocial);
        printf("  Nome Fantasia: %s\n", empresaLocalizada->nomeFantasia);
        printf("  Telefone: %s\n", empresaLocalizada->telefoneEmpresa);
        printf("\nEndereço:\n");
        printf("  Rua: %s, Número: %s\n", empresaLocalizada->rua, empresaLocalizada->numero);
        printf("  Bairro: %s, Cidade: %s, Estado: %s, CEP: %s\n", empresaLocalizada->bairro, empresaLocalizada->cidade, empresaLocalizada->estado, empresaLocalizada->cep);
        printf("\nOutros Dados:\n");
        printf("  E-mail: %s\n", empresaLocalizada->emailEmpresa);
        printf("  Data de Abertura: %s\n", empresaLocalizada->dataAbertura);
        printf("  Informações Adicionais: %s\n", empresaLocalizada->outrosDados);
        printf("========================================\n");
    }
}

void ExibirListaEmpresas(Empresa* lista, int tamanhoLista)
{
    printf("Empresas disponíveis:\n");
    for (int i = 0; i < tamanhoLista; i++)
    {
        printf("ID: %d - Nome: %s\n", lista[i].id, lista[i].nomeEmpresa);
    }
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

    int tamanhoLista;

    Empresa* empresas = CarregarEmpresas(&tamanhoLista);

    if (empresas == NULL)
    {
        printf("Erro ao carregar empresas.\n");
        return;
    }

    ExibirListaEmpresas(empresas, tamanhoLista);

    Empresa* empresaLocalizada = NULL;

    while(empresaLocalizada == NULL)
    {
        printf("Digite o ID da empresa selecionada: ");
        scanf("%d", &novoResiduo.id);

        empresaLocalizada = LocalizarEmpresa(empresas, tamanhoLista, novoResiduo.id);

        if(empresaLocalizada == NULL)
        {
            printf("Nenhuma empresa encontrada com o ID informado.\n");
        }
        else
        {

            strcpy(novoResiduo.nomeEmpresa, empresaLocalizada->nomeEmpresa);

            printf("Digite o número do mês correspondente: ");
            scanf("%d", &novoResiduo.mes);

            if(novoResiduo.mes < 1 || novoResiduo.mes > 12)
            {
                printf("Mês inválido!\n");
                return;
            }

            printf("Digite a quantidade de resíduos tratados: ");
            scanf("%d", &novoResiduo.quantidadeResiduos);

            if(novoResiduo.quantidadeResiduos < 0)
            {
                printf("Quantidade de resíduos inválida!\n");
                return;
            }

            printf("Digite o valor estimado de custo: ");
            scanf("%f", &novoResiduo.valorEstimado);

            if(novoResiduo.valorEstimado < 0.01)
            {
                printf("Valor estimado de custo inválido!\n");
                return;
            }

            FILE *file = fopen(RESIDUOS_ARQUIVO, "a");

            if (file == NULL)
            {
                printf("Erro: Não foi possível abrir o arquivo para resíduos.\n");
            }
            else
            {
                fprintf(file, "%d|%s|%d|%d|%f\n", novoResiduo.id, novoResiduo.nomeEmpresa, novoResiduo.mes, novoResiduo.quantidadeResiduos, novoResiduo.valorEstimado);
                printf("Cadastro realizado com sucesso.\n\n");
            }

            fclose(file);

        }
    }

    free(empresas);

}

Residuo* CarregarResiduos(int* tamanho)
{
    FILE* file = fopen(RESIDUOS_ARQUIVO, "r");

    if (!file)
    {
        printf("Arquivo de resíduos não encontrado. Certifique-se de que o arquivo '%s' existe.\n", RESIDUOS_ARQUIVO);
        *tamanho = 0;
        return NULL;
    }

    Residuo* lista = NULL;
    char linha[256];
    int count = 0;

    while (fgets(linha, sizeof(linha), file))
    {
        Residuo novoResiduo;

        if (sscanf(linha, "%d|%99[^|]|%d|%d|%f", &novoResiduo.id, novoResiduo.nomeEmpresa, &novoResiduo.mes, &novoResiduo.quantidadeResiduos, &novoResiduo.valorEstimado) == 5)
        {
            Residuo* novaLista = realloc(lista, (count + 1) * sizeof(Residuo));

            if (!novaLista)
            {
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
        printf("Gerenciar Resíduos\n\n");
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

            LimparConsole();

            printf("Resíduos cadastrados\n\n");

            lista = CarregarResiduos(&tamanho);

            for (i = 0; i < tamanho; i++)
            {
                printf("ID Empresa: %d; Nome: %s; Mês: %d; Qtd. Resíduos: %d; Valor Estimado: %.2f \n",
                       lista[i].id, lista[i].nomeEmpresa, lista[i].mes, lista[i].quantidadeResiduos, lista[i].valorEstimado);
            }

            printf("\n");

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

RelatorioIndividual GerarRelatorioIndividual(Empresa empresaSelecionada)
{
    RelatorioIndividual relatorio;

    relatorio.empresaSelecionada = empresaSelecionada;
    relatorio.quantidadeResiduosPrimeiro = 0;
    relatorio.quantidadeResiduosSegundo = 0;
    relatorio.quantidadeResiduosTotal = 0;
    relatorio.valorEstimadoPrimeiro = 0;
    relatorio.valorEstimadoSegundo = 0;
    relatorio.valorEstimadoTotal = 0;
    int tamanho;

    Residuo* lista = CarregarResiduos(&tamanho);

    for (int i = 0; i < tamanho; i++)
    {
        if (lista[i].id == relatorio.empresaSelecionada.id)
        {

            if (lista[i].mes >= 1 && lista[i].mes <= 6)
            {
                relatorio.quantidadeResiduosPrimeiro += lista[i].quantidadeResiduos;
                relatorio.valorEstimadoPrimeiro += lista[i].valorEstimado;
            }
            else
            {
                relatorio.quantidadeResiduosSegundo += lista[i].quantidadeResiduos;
                relatorio.valorEstimadoSegundo += lista[i].valorEstimado;
            }

            relatorio.quantidadeResiduosTotal += lista[i].quantidadeResiduos;
            relatorio.valorEstimadoTotal += lista[i].valorEstimado;

        }
    }

    return relatorio;
}

void ImprimirRelatorioIndividual(RelatorioIndividual relatorio)
{
    printf("\n======== Relatório da Empresa: %s ========\n", relatorio.empresaSelecionada.nomeEmpresa);
    printf("Total de resíduos tratados no primeiro semestre: %d unidades\n", relatorio.quantidadeResiduosPrimeiro);
    printf("Total de resíduos tratados no segundo semestre %d unidades\n", relatorio.quantidadeResiduosSegundo);
    printf("Total de gastos mensais estimados: R$ %.2f \n", relatorio.valorEstimadoTotal);
}

void SalvarRelatorioIndividual(RelatorioIndividual relatorio)
{
    char opcao;
    char caminho[256];

    printf("\nDeseja salvar o relatório em um arquivo? (s/n): ");
    scanf(" %c", &opcao);

    if (opcao == 's' || opcao == 'S')
    {
        printf("Informe o caminho para salvar o relatório (ex: C:\\relatorios\\relatorio.txt): ");
        scanf(" %255s", caminho);

        FILE *arquivo = fopen(caminho, "w");

        if (arquivo == NULL)
        {
            perror("Erro ao criar o arquivo");
            return;
        }

        fprintf(arquivo,"======== Relatório da Empresa: %s ========\n", relatorio.empresaSelecionada.nomeEmpresa);
        fprintf(arquivo,"Total de resíduos tratados no primeiro semestre: %d unidades\n", relatorio.quantidadeResiduosPrimeiro);
        fprintf(arquivo,"Total de resíduos tratados no segundo semestre %d unidades\n", relatorio.quantidadeResiduosSegundo);
        fprintf(arquivo,"Total de gastos mensais estimados: R$ %.2f \n", relatorio.valorEstimadoTotal);

        fclose(arquivo);

        printf("Relatório salvo em: %s\n", caminho);
    }
    else
    {
        printf("Relatório não será salvo.\n");
    }
}

RelatorioGlobal GerarRelatorioGlobal()
{

    int tamanhoLista;
    int quantidadeMaiorProducao = NULL;
    int quantidadeMenorProducao = NULL;
    Empresa* empresas;

    RelatorioGlobal relatorio;

    relatorio.aporteFinanceiroPrimeiro = 0;
    relatorio.aporteFinanceiroSegundo = 0;
    relatorio.aporteFinanceiroTotal = 0;

    empresas = CarregarEmpresas(&tamanhoLista);

    if (empresas == NULL)
    {
        printf("Erro ao carregar empresas.\n");
        return;
    }

    for(int i =0; i < tamanhoLista; i++)
    {
        RelatorioIndividual relatorioEmpresa = GerarRelatorioIndividual(empresas[i]);

        if(quantidadeMaiorProducao == NULL || relatorioEmpresa.quantidadeResiduosTotal > quantidadeMaiorProducao)
        {
            relatorio.empresaMaiorProducao = relatorioEmpresa.empresaSelecionada;
            quantidadeMaiorProducao = relatorioEmpresa.quantidadeResiduosTotal;
        }

        if(quantidadeMenorProducao == NULL || relatorioEmpresa.quantidadeResiduosSegundo < quantidadeMenorProducao)
        {
            relatorio.empresaMenorProducao = relatorioEmpresa.empresaSelecionada;
            quantidadeMenorProducao = relatorioEmpresa.quantidadeResiduosSegundo;
        }

        relatorio.aporteFinanceiroPrimeiro += relatorioEmpresa.valorEstimadoPrimeiro;
        relatorio.aporteFinanceiroSegundo += relatorioEmpresa.valorEstimadoSegundo;
        relatorio.aporteFinanceiroTotal += relatorioEmpresa.valorEstimadoTotal;
    }

    return relatorio;

}

void ImprimirRelatorioGlobal(RelatorioGlobal relatorio)
{
    printf("\n======== Relatório Global ========\n");
    printf("Empresa com a maior produção de resíduos tratados: %s unidades\n", relatorio.empresaMaiorProducao.nomeEmpresa);
    printf("Empresa com a menor produção de resíduos tratados %s unidades\n", relatorio.empresaMenorProducao.nomeEmpresa);
    printf("Aporte Financeiro\n");
    printf("\tPrimeiro semestre: R$ %.2f \n", relatorio.aporteFinanceiroPrimeiro);
    printf("\tSegundo semestre: R$ %.2f \n", relatorio.aporteFinanceiroSegundo);
    printf("\tTotal: R$ %.2f \n", relatorio.aporteFinanceiroTotal);
}

void SalvarRelatorioGlobal(RelatorioGlobal relatorio)
{
    char opcao;
    char caminho[256];

    printf("Deseja salvar o relatório em um arquivo? (s/n): ");
    scanf(" %c", &opcao);

    if (opcao == 's' || opcao == 'S')
    {
        printf("Informe o caminho para salvar o relatório (ex: C:\\relatorios\\relatorio.txt): ");
        scanf(" %255s", caminho);

        FILE *arquivo = fopen(caminho, "w");

        if (arquivo == NULL)
        {
            perror("Erro ao criar o arquivo");
            return;
        }

        fprintf(arquivo,"======== Relatório Global ========\n");
        fprintf(arquivo,"Empresa com a maior produção de resíduos tratados: %s unidades\n", relatorio.empresaMaiorProducao.nomeEmpresa);
        fprintf(arquivo,"Empresa com a menor produção de resíduos tratados %s unidades\n", relatorio.empresaMenorProducao.nomeEmpresa);
        fprintf(arquivo,"Aporte Financeiro\n");
        fprintf(arquivo,"\tPrimeiro semestre: R$ %.2f \n", relatorio.aporteFinanceiroPrimeiro);
        fprintf(arquivo,"\tSegundo semestre: R$ %.2f \n", relatorio.aporteFinanceiroSegundo);
        fprintf(arquivo,"\tTotal: R$ %.2f \n", relatorio.aporteFinanceiroTotal);

        fclose(arquivo);

        printf("Relatório salvo em: %s\n", caminho);
    }
    else
    {
        printf("Relatório não será salvo.\n");
    }
}

void GerarRelatorios()
{
    int opcao;
    char opcaoSalvamento;
    char caminho[256];
    int tamanhoLista;
    Empresa* empresas;
    RelatorioIndividual relatorioInvidual;
    RelatorioGlobal relatorioGlobal;

    while (opcao != 3)
    {
        printf("\nRelatórios: \n\n");
        printf("1 - Relatórios Individuais\n");
        printf("2 - Relatórios Globais\n");
        printf("3 - Voltar\n");

        scanf("%d", &opcao);

        LimparConsole();

        switch (opcao)
        {

        case 1:

            empresas = CarregarEmpresas(&tamanhoLista);

            if (empresas == NULL)
            {
                printf("Erro ao carregar empresas.\n");
                return;
            }

            ExibirListaEmpresas(empresas, tamanhoLista);

            Empresa* empresaLocalizada = NULL;

            while(empresaLocalizada == NULL)
            {
                int empresaEscolhida;
                printf("Digite o ID da empresa para gerar o relatório: ");
                scanf("%d", &empresaEscolhida);

                empresaLocalizada = LocalizarEmpresa(empresas, tamanhoLista, empresaEscolhida);

                if(empresaLocalizada == NULL)
                {
                    printf("Nenhuma empresa encontrada com o ID informado.\n");
                }
                else
                {
                    relatorioInvidual = GerarRelatorioIndividual(*empresaLocalizada);

                    ImprimirRelatorioIndividual(relatorioInvidual);

                    SalvarRelatorioIndividual(relatorioInvidual);

                }
            }

            free(empresas);

            break;

        case 2:

            relatorioGlobal = GerarRelatorioGlobal();

            ImprimirRelatorioGlobal(relatorioGlobal);

            SalvarRelatorioGlobal(relatorioGlobal);

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

            CadastrarEmpresa();

            break;

        case 2:

            BuscarEmpresaPorID();

            break;

        case 3:

            GerenciarResiduos();

            break;

        case 4:

            GerarRelatorios();

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

