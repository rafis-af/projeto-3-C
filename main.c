#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

int main() {
    srand(time(NULL));
    char palavra[TAM_PALAVRA + 1];
    char dica[TAM_DICA + 1];
    int letrasUsadas[26] = {0};
    int erros = 0;

    lerPalavraAleatoria(palavra, dica);

    int tamanho = strlen(palavra);
    int tentativas = 8;

    printf("Dica: %s\n", dica);

    while(erros < tentativas){
        mostrarEstadoPalavra(palavra, letrasUsadas, erros);

        printf("\nDigite uma letra: ");
        char letra;
        scanf(" %c", &letra);
        limparBuffer();

        letra = tolower(letra);
        if(letraUsada(letra, letrasUsadas)){
            printf("Você já usou a letra '%c'. Tente outra.\n", letra);
            continue;
        }

        letrasUsadas[letra - 'a'] = 1;

        if(strchr(palavra, letra) == NULL){
            erros++;
            printf("Letra '%c' não existe na palavra.\n", letra);
        }

        int ganhou = 1;
        for(int i = 0; i < tamanho; i++){
            if(!letrasUsadas[tolower(palavra[i]) - 'a']){
                ganhou = 0;
                break;
            }
        }
        if(ganhou){
            printf("Parabéns! Você adivinhou a palavra: %s\n", palavra);
            return 0;
        }
    }
    printf("Você perdeu! A palavra era: %s\n", palavra);
    return 0;
}