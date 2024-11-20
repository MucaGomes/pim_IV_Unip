#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RELATORIO_INDIVIDUAL "relatorio_individualizado.txt"
#define RELATORIO_GLOBAL "relatorio_global.csv"

// Função para capturar entrada do usuário como string
void capturarEntrada(const char *mensagem, char *buffer, size_t tamanho) {
    printf("%s", mensagem);
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remover o caractere '\n'
}

// Função para exibir relatórios individualizados
void relatoriosIndividualizados() {
    char totalInsumos[50], totalGastosMensais[50];

    printf("=== Relatórios Individualizados ===\n");
    capturarEntrada("Digite o total de insumos tratados semestralmente: ", totalInsumos, sizeof(totalInsumos));
    capturarEntrada("Digite o total de gastos mensais: ", totalGastosMensais, sizeof(totalGastosMensais));

    printf("\nRelatório Individualizado:\n");
    printf("Total de insumos tratados semestralmente: %s\n", totalInsumos);
    printf("Total de gastos mensais: %s\n", totalGastosMensais);

    // Salvar relatório em arquivo
    FILE *file = fopen(RELATORIO_INDIVIDUAL, "w");
    if (file) {
        fprintf(file, "Relatório Individualizado:\n");
        fprintf(file, "Total de insumos tratados semestralmente: %s\n", totalInsumos);
        fprintf(file, "Total de gastos mensais: %s\n", totalGastosMensais);
        fclose(file);
        printf("\nRelatório salvo em '%s'.\n", RELATORIO_INDIVIDUAL);
    } else {
        printf("\nErro ao salvar o relatório individualizado.\n");
    }
}

// Função para exibir relatórios globais
void relatoriosGlobais() {
    char regiaoMaiorVolume[50], industriaMenorProducao[50], aporteFinanceiroSemestral[50];

    printf("=== Relatórios Globais ===\n");
    capturarEntrada("Digite a região com maior volume de resíduos industriais tratados: ", regiaoMaiorVolume, sizeof(regiaoMaiorVolume));
    capturarEntrada("Digite a indústria com menor produção no último semestre: ", industriaMenorProducao, sizeof(industriaMenorProducao));
    capturarEntrada("Digite o aporte financeiro semestral: ", aporteFinanceiroSemestral, sizeof(aporteFinanceiroSemestral));

    printf("\nRelatório Global:\n");
    printf("Região com maior volume de resíduos industriais tratados: %s\n", regiaoMaiorVolume);
    printf("Indústria com menor produção no último semestre: %s\n", industriaMenorProducao);
    printf("Aporte financeiro semestral: %s\n", aporteFinanceiroSemestral);

    // Salvar relatório em arquivo
    FILE *file = fopen(RELATORIO_GLOBAL, "w");
    if (file) {
        fprintf(file, "Tipo,Descrição\n");
        fprintf(file, "Região Maior Volume: %s\n", regiaoMaiorVolume);
        fprintf(file, "Indústria Menor Produção: %s\n", industriaMenorProducao);
        fprintf(file, "Aporte Financeiro Semestral: %s\n", aporteFinanceiroSemestral);
        fclose(file);
        printf("\nRelatório salvo em '%s'.\n", RELATORIO_GLOBAL);
    } else {
        printf("\nErro ao salvar o relatório global.\n");
    }
}

// Função para consultar relatórios existentes
void consultarRelatorios() {
    char linha[256];

    printf("\n=== Consulta de Relatórios Existentes ===\n");

    // Verifica e exibe o relatório individualizado
    FILE *file = fopen(RELATORIO_INDIVIDUAL, "r");
    if (file == NULL) {
        printf("\n[Relatório Individualizado]\nNenhum relatório individualizado encontrado.\n");
    } else {
        printf("\n[Relatório Individualizado]\n");
        while (fgets(linha, sizeof(linha), file)) {
            printf("%s", linha);
        }
        fclose(file);
    }

    // Verifica e exibe o relatório global
    file = fopen(RELATORIO_GLOBAL, "r");
    if (file == NULL) {
        printf("\n[Relatório Global]\nNenhum relatório global encontrado.\n");
    } else {
        printf("\n[Relatório Global]\n");
        while (fgets(linha, sizeof(linha), file)) {
            printf("%s", linha);
        }
        fclose(file);
    }

    printf("\nPressione Enter para continuar...");
    getchar();
    system("cls");
}

// Função para validar login
int login() {
    char username[20], password[20];

    printf("=== Login ===\n");
    capturarEntrada("Usuário: ", username, sizeof(username));
    capturarEntrada("Senha: ", password, sizeof(password));

    // Verifica credenciais
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Login bem-sucedido!\n");
        return 1;
    } else {
        printf("Credenciais inválidas. Tente novamente.\n");
        return 0;
    }
}

int main() {
    int opcao;

    // Tela de login
    while (!login()) {
        printf("Tentativa de login falhou.\n");
    }

    // Menu principal
    while (1) {
        printf("\n=== Menu Principal ===\n");
        printf("1. Consultar Relatórios\n");
        printf("2. Relatórios Individualizados\n");
        printf("3. Relatórios Globais\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa buffer de entrada
            continue;
        }
        getchar(); // Consome o '\n' restante no buffer

        switch (opcao) {
            case 1:
                system("cls");
                consultarRelatorios();
                break;
            case 2:
                system("cls");
                relatoriosIndividualizados();
                break;
            case 3:
                system("cls");
                relatoriosGlobais();
                break;
            case 4:
                printf("Saindo do sistema...\n");
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
