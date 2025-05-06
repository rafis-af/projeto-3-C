#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

int main() {
    srand(time(NULL));

    do{
        char palavra[TAM_PALAVRA + 1];
        char dica[TAM_DICA + 1];
        int letrasUsadas[26] = {0};
        int erros = 0;

        printf("Deseja carregar um jogo? Digite s ou n: ");
        char opcao;
        scanf(" %c", &opcao);
        limparBuffer();

        if(tolower(opcao) == 's'){
            if(!carregarJogo(palavra, dica, letrasUsadas, &erros)){
                printf("Nenhum jogo encontrado, iniciando um novo jogo.\n");
                lerPalavraAleatoria(palavra, dica);
            }
        }else{
            lerPalavraAleatoria(palavra, dica);
        }

        int tamanho = strlen(palavra);
        int tentativas = 8;

        printf("Dica: %s\n", dica);
        logs("Dica", dica, 0);

        while(erros < tentativas){
            mostrarEstadoPalavra(palavra, letrasUsadas, erros);

            printf("Digite 1 se você deseja salvar e sair do jogo.");
            printf("\nDigite uma letra:");
            char letra;
            scanf(" %c", &letra);
            limparBuffer();

            if(letra == '1'){
                salvarJogo(palavra, dica, letrasUsadas, erros);
                return 0;
            }

            letra = tolower(letra);
            if(letraUsada(letra, letrasUsadas)){
                printf("Você já usou a letra '%c'. Tente outra.\n", letra);
                continue;
            }

            letrasUsadas[letra - 'a'] = 1;

            int letraExiste = strchr(palavra, letra) != NULL;
            if(!letraExiste){
                erros++;
                printf("Letra '%c' não existe na palavra.\n", letra);
            }

            logs("Letra", &letra, letraExiste);

            int ganhou = 1;
            for(int i = 0; i < tamanho; i++){
                if(!letrasUsadas[tolower(palavra[i]) - 'a']){
                    ganhou = 0;
                    break;
                }
            }
            if(ganhou){
                printf("Parabéns! Você adivinhou a palavra: %s\n", palavra);
                break;
            }
        }
        if(erros >= tentativas){
            printf("Você perdeu! A palavra era: %s\n", palavra);
        }

    }while(jogarNovamente());

    printf("Obrigado por jogar!");
    return 0;
}