#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CREDENCIAIS_ARQUIVO "credenciais.txt"

// Função de hash simples baseada no algoritmo DJBX33A
unsigned long gerarHash(const char *str) {
    unsigned long hash = 5381; // Valor inicial arbitrário
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

// Função para salvar o nome de usuário e senha no arquivo
void salvarCredenciais(const char *usuario, const char *senha) {
    unsigned long hashUsuario = gerarHash(usuario);
    unsigned long hashSenha = gerarHash(senha);

    FILE *file = fopen(CREDENCIAIS_ARQUIVO, "w");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o arquivo para escrita.\n");
        exit(1);
    }

    fprintf(file, "%lu %lu\n", hashUsuario, hashSenha); // Grava os hashes no arquivo
    fclose(file);
}

// Função para carregar os hashes do arquivo
void carregarCredenciais(unsigned long *hashUsuario, unsigned long *hashSenha) {
    FILE *file = fopen(CREDENCIAIS_ARQUIVO, "r");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de credenciais.\n");
        exit(1);
    }

    if (fscanf(file, "%lu %lu", hashUsuario, hashSenha) != 2) {
        printf("Erro: O arquivo de credenciais está vazio ou mal formatado.\n");
        fclose(file);
        exit(1);
    }

    fclose(file);
}

// Função de login
void login() {
    unsigned long hashUsuarioArmazenado, hashSenhaArmazenado;
    carregarCredenciais(&hashUsuarioArmazenado, &hashSenhaArmazenado);

    char inputUsuario[50], inputSenha[50];
    unsigned long inputHashUsuario, inputHashSenha;

    printf("========================\n");
    printf("||  Sistema de Login  ||\n");
    printf("========================\n");

    while (1) {
        printf("Digite o nome de usuário: ");
        scanf("%s", inputUsuario);

        printf("Digite a senha: ");
        scanf("%s", inputSenha);

        // Calcula os hashes do usuário e senha digitados
        inputHashUsuario = gerarHash(inputUsuario);
        inputHashSenha = gerarHash(inputSenha);

        if (inputHashUsuario == hashUsuarioArmazenado && inputHashSenha == hashSenhaArmazenado) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            printf("\nLogin realizado com sucesso!\n\n");
            break;
        } else {
            printf("\nNome de usuário ou senha incorretos. Tente novamente.\n\n");
        }
    }
}

// Função principal
int main() {
    // Verifica se o arquivo de credenciais já existe
    FILE *file = fopen(CREDENCIAIS_ARQUIVO, "r");
    if (file == NULL) {
        // Caso não exista, cria um usuário inicial
        char usuarioInicial[50], senhaInicial[50];
        printf("Nenhum usuário encontrado. \nCrie um nome de usuário inicial: ");
        scanf("%s", usuarioInicial);
        printf("Crie uma senha inicial: ");
        scanf("%s", senhaInicial);
        salvarCredenciais(usuarioInicial, senhaInicial);
        printf("Usuário e senha criados com sucesso!\n\n");
    } else {
        fclose(file);
    }

    // Inicia o processo de login
    login();

    // Continuação do programa
    printf("Bem-vindo ao sistema!\n");
    return 0;
}
