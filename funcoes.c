#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "funcoes.h"

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void lerPalavraAleatoria(char *palavra, char *dica){

    FILE *fp = fopen("palavras-sortidas.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char linhas[TAM_MAX][TAM_PALAVRA + TAM_DICA];
    int total = 0;

    while (fgets(linhas[total], sizeof(linhas[total]), fp)) {

        if(strchr(linhas[total], ':')){
            linhas[total][strcspn(linhas[total], "\n")] = '\0';
            total++;
        }   
    }

    fclose(fp);

    int sorteio = rand() % total;
    char *token = strtok(linhas[sorteio], ":");
    strcpy(palavra, token);
    token = strtok(NULL, ":");
    strcpy(dica, token);
}

void salvarJogo(char *palavra, char *dica, int letrasUsadas[], int erros){
    FILE *arquivo = fopen("salvar-forca.txt", "w");
    if(arquivo == NULL){
        printf("Erro ao salvar o jogo!\n");
        return;
    }

    fprintf(arquivo, "Dica - %s\n", dica);
    fprintf(arquivo, "Palavra - %s\n", palavra);

    fprintf(arquivo, "\nLetras Erradas:\n");

    int temErradas = 0;
    for(int i = 0; i < 26; i++){
        if (letrasUsadas[i] && !strchr(palavra, 'a' + i)){
            fprintf(arquivo, "%c ", 'a' + i);
            temErradas = 1;
        }
    }
    if(!temErradas) fprintf(arquivo, "Nenhuma");
    fprintf(arquivo, "\n\n");

    fprintf(arquivo, "Letras Corretas\n");
    int temCorretas = 0;
    for(int i = 0; i < 26; i++){
        if(letrasUsadas[i] && strchr(palavra, 'a' + i)){
            fprintf(arquivo, "%c ", 'a' + i);
            temCorretas = 1;
        }
    }
    if(!temCorretas) fprintf(arquivo, "Nenhuma");
    fprintf(arquivo, "\n");

    fclose(arquivo);
    printf("Jogo salvo com sucesso!\n");
}

int carregarJogo(char *palavra, char *dica, int letrasUsadas[], int *erros){
    FILE *arquivo = fopen("salvar-forca.txt", "r");
    if(arquivo == NULL) return 0;

    char linha[200];

    fgets(linha, sizeof(linha), arquivo);
    sscanf(linha, "Dica - %[^\n]", dica);

    fgets(linha, sizeof(linha), arquivo);
    sscanf(linha, "Palavra - %[^\n]", palavra);

    for(int i = 0; i < 26; i++){
        letrasUsadas[i] = 0;
    }

    fgets(linha, sizeof(linha), arquivo);

    fgets(linha, sizeof(linha), arquivo);

    fgets(linha, sizeof(linha), arquivo);
    if(strcmp(linha, "Nenhuma\n") != 0){
        char *token = strtok(linha, " ");
        while(token != NULL){
            letrasUsadas[tolower(token[0]) - 'a'] = 1;
            token = strtok(NULL, " ");
        }
    }

    fgets(linha, sizeof(linha), arquivo);

    fgets(linha, sizeof(linha), arquivo);

    fgets(linha, sizeof(linha), arquivo);
    if(strcmp(linha, "Nenhuma\n") != 0){
        char *token = strtok(linha, " ");
        while(token != NULL){
            letrasUsadas[tolower(token[0]) - 'a'] = 1;
            token = strtok(NULL, " ");
        }
    }

    *erros = 0;
    for(int i = 0; i < 26; i++){
        if(letrasUsadas[i] && !strchr(palavra, 'a' + i)){
            (*erros)++;
        }
    }

    fclose(arquivo);
    return 1;
}

void logs(char *tipo, char *info, int acertou){
    FILE *log = fopen("logs-forca.txt", "a");
    if(log == NULL){
        return;
    }

    time_t agora;
    time(&agora);
    char hora[10];
    strftime(hora, 10, "%H:%M:%S", localtime(&agora));

    if(strcmp(tipo, "Letra") == 0){
        fprintf(log, "[%s] %s - %c (%s)\n", hora, tipo, *info, acertou ? "Acertou" : "Errou");
    }else{
        fprintf(log, "[%s] %s - %s\n", hora, tipo, info);
    }

    fclose(log);
}

void mostrarForca(int erros) {
    printf("\n");
    printf("  _______     \n");
    printf(" |/      |    \n");

    switch (erros) {
        case 0:
            printf(" |            \n");
            printf(" |            \n");
            printf(" |            \n");
            printf(" |            \n");
            break;
        case 1:
            printf(" |     (_)    \n");
            printf(" |            \n");
            printf(" |            \n");
            printf(" |            \n");
            break;
        case 2:
            printf(" |     (_)    \n");
            printf(" |      |     \n");
            printf(" |            \n");
            printf(" |            \n");
            break;
        case 3:
            printf(" |     (_)    \n");
            printf(" |     \\|     \n");
            printf(" |            \n");
            printf(" |            \n");
            break;
        case 4:
            printf(" |     (_)    \n");
            printf(" |     \\|/    \n");
            printf(" |            \n");
            printf(" |            \n");
            break;
        case 5:
            printf(" |     (_)    \n");
            printf(" |     \\|/    \n");
            printf(" |      |     \n");
            printf(" |            \n");
            break;
        case 6:
            printf(" |     (_)    \n");
            printf(" |     \\|/    \n");
            printf(" |      |     \n");
            printf(" |     / \  \n");
            break;
        case 7:
            printf(" |     (_)    \n");
            printf(" |     \\|/    \n");
            printf(" |      |     \n");
            printf(" |     / \\  \n");
            break;
        default:
            printf(" |            \n");
            printf(" |            \n");
            printf(" |            \n");
            printf(" |            \n");
            break;
    }

    printf(" |\n");
    printf("_|___\n");
    printf("\nErros: %d\n", erros);
}

void mostrarEstadoPalavra(char *palavraSecreta, int letrasUsadas[], int erros){
    mostrarForca(erros);
    printf("Palavra: ");
    for (int i = 0; i < strlen(palavraSecreta); i++) {
        if (letrasUsadas[tolower(palavraSecreta[i]) - 'a'] ) {
            printf("%c ", palavraSecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int letraUsada(char letra, int letrasUsadas[]){
    return letrasUsadas[tolower(letra) - 'a'];
}

int jogarNovamente(){
    printf("\nVocê deseja jogar novamente? Digite s ou n: ");
    char resposta;
    scanf(" %c", &resposta);
    limparBuffer();
    return tolower(resposta) == 's';
}