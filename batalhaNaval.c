#include <stdio.h>

#define TAMANHO 10
#define AGUA 0
#define NAVIO 3

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    int i, j;

    // Cabeçalho com os números das colunas
    printf("   ");
    for (j = 0; j < TAMANHO; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    // Exibe o tabuleiro com os números das linhas
    for (i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);
        for (j = 0; j < TAMANHO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    int i, j;
    for (i = 0; i < TAMANHO; i++) {
        for (j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para posicionar um navio no tabuleiro
// tipo: 0 para horizontal, 1 para vertical, 2 para diagonal (crescente), 3 para diagonal (decrescente)
// tamanho: tamanho do navio
void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linhaInicial, int colunaInicial, int tipo, int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        if (tipo == 0) { // Horizontal
            tabuleiro[linhaInicial][colunaInicial + i] = NAVIO;
        } else if (tipo == 1) { // Vertical
            tabuleiro[linhaInicial + i][colunaInicial] = NAVIO;
        } else if (tipo == 2) { // Diagonal (crescente: i+1, j+1)
            tabuleiro[linhaInicial + i][colunaInicial + i] = NAVIO;
        } else if (tipo == 3) { // Diagonal (decrescente: i+1, j-1)
            tabuleiro[linhaInicial + i][colunaInicial - i] = NAVIO;
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    // 1. Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // 2. Posiciona os quatro navios

    // Navios horizontais/verticais
    // Navio vertical de tamanho 4
    posicionarNavio(tabuleiro, 2, 2, 1, 4);

    // Navio horizontal de tamanho 3
    posicionarNavio(tabuleiro, 5, 5, 0, 3);

    // Navios diagonais
    // Navio diagonal crescente de tamanho 3
    posicionarNavio(tabuleiro, 1, 6, 2, 3);

    // Navio diagonal decrescente de tamanho 4
    posicionarNavio(tabuleiro, 0, 9, 3, 4);

    // 3. Exibe o tabuleiro completo
    printf("Tabuleiro de Batalha Naval 10x10\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
