#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "funcoes.h"

int main(int argc, char const *argv[]){
    
    srand(time(NULL));
    char palavra[TAM_PALAVRA];    
    char dica[TAM_DICA];
    int letrasUsadas[26] = {0};
    int erros = 0;
    int acertos = 0;

    lerPalavraAleatoria(palavra,dica);
    int tamanhoPalavra = strlen(palavra);

    printf("Dica: %s\n", dica);

    while (erros < 6 && acertos < tamanhoPalavra) {
        mostrarEstadoPalavra(palavra, letrasUsadas, erros);
        printf("Digite uma letra: ");
        char tentativa;
        scanf(" %c", &tentativa);
        limparBuffer();

        tentativa = tolower(tentativa);

        if (letraUsada(tentativa, letrasUsadas)) {
            printf("Letra já utilizada!\n");
            continue;
        }

        letrasUsadas[tolower(tentativa) - 'a'] = 1;

        int acerto = 0;
        for (int i = 0; i < tamanhoPalavra; i++) {
            if (palavra[i] == tentativa) {
                acerto = 1;
                acertos++;
            }
        }
        if (!acerto) {
            erros++;
            printf("Letra errada!\n");
        } else {
            printf("Letra correta!\n");
        }
    }
    if (erros == tamanhoPalavra) {
        printf("Você perdeu! A palavra era: %s\n", palavra);
    } else {
        mostrarForca(erros);
        printf("Parabéns! Você adivinhou a palavra: %s\n", palavra);
    }

    system("pause");
    return 0;
}
