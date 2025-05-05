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
