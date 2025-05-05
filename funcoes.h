#ifndef MAIN_H
#define MAIN_H

#define TAM_MAX 100
#define TAM_PALAVRA 30
#define TAM_DICA 100

void lerPalavraAleatoria(char *palavra, char *dica);
void mostrarForca(int erros);
void mostrarEstadoPalavra(char *palavra, int letrasUsadas[], int erros);
void limparBuffer();
void salvarJogo(char *palavra, char *dica, int letrasUsadas[], int erros);
void logs(char *tipo, char *info, int acertou);
int carregarJogo(char *palavra, char *dica, int letrasUsadas[], int *erros);
int letraUsada(char letra, int letrasUsadas[]);
int jogarNovamente();

#endif