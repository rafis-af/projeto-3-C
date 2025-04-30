#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "funcoes.h"

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
