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

    FILE *fp = open("palavras-sortidas.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char linhas[TAM_MAX][TAM_PALAVRA + TAM_DICA];
    int total = 0;
    
    while (fgets(linhas[total], sizeof(linhas[total]), fp)) {

        if(strchr(linhas[total], ':')){
            total++;
        }
        fclose(fp);

        srand(time(NULL));
        int sorteio = rand() % total;

        char *token = strtok(linhas[sorteio], ":");
        strcpy(palavra, token);
        token = strtok(NULL, ":");
        strcpy(dica, token);
    }
}

void mostrarForca(int erros){

    printf("\n");
    printf("  _______\n");
    printf(" |/      |\n");
    printf(" |      %c%c%c\n", (erros >= 1) ? 'O' : ' ', (erros >= 3) ? '/' : ' ', (erros >= 2) ? '\\' : ' ');
    printf(" |      %c %c\n", (erros >= 5) ? '/' : ' ', (erros >= 4) ? '\\' : ' ');
    printf(" |      \n");
    printf(" |______\n\n");
    printf("Erros: %d\n", erros);
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
