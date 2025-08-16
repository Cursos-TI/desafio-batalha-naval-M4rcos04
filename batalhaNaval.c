#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define AGUA 0
#define NAVIO 3
#define AFETADO 5

#define TAMANHO_CONE 5
#define TAMANHO_CRUZ 5
#define TAMANHO_OCTAEDRO 5

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int i, j;
    printf("   ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int i, j;
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int tipo, int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        if (tipo == 0) {
            tabuleiro[linhaInicial][colunaInicial + i] = NAVIO;
        } else if (tipo == 1) {
            tabuleiro[linhaInicial + i][colunaInicial] = NAVIO;
        } else if (tipo == 2) {
            tabuleiro[linhaInicial + i][colunaInicial + i] = NAVIO;
        } else if (tipo == 3) {
            tabuleiro[linhaInicial + i][colunaInicial - i] = NAVIO;
        }
    }
}

void criarMatrizCone(int cone[TAMANHO_CONE][TAMANHO_CONE]) {
    int i, j;
    int centro = TAMANHO_CONE / 2;
    for (i = 0; i < TAMANHO_CONE; i++) {
        for (j = 0; j < TAMANHO_CONE; j++) {
            if (j >= centro - i && j <= centro + i) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }
}

void criarMatrizCruz(int cruz[TAMANHO_CRUZ][TAMANHO_CRUZ]) {
    int i, j;
    int centro = TAMANHO_CRUZ / 2;
    for (i = 0; i < TAMANHO_CRUZ; i++) {
        for (j = 0; j < TAMANHO_CRUZ; j++) {
            if (i == centro || j == centro) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }
}

void criarMatrizOctaedro(int octaedro[TAMANHO_OCTAEDRO][TAMANHO_OCTAEDRO]) {
    int i, j;
    int centro = TAMANHO_OCTAEDRO / 2;
    for (i = 0; i < TAMANHO_OCTAEDRO; i++) {
        for (j = 0; j < TAMANHO_OCTAEDRO; j++) {
            if ((i + j >= centro) && (i + j <= centro + (TAMANHO_OCTAEDRO - 1 - centro)) && 
                (j - i >= -centro) && (j - i <= centro)) {
                octaedro[i][j] = 1;
            } else {
                octaedro[i][j] = 0;
            }
        }
    }
}

void sobreporHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_CRUZ][TAMANHO_CRUZ], int tamHabilidade, int linhaOrigem, int colunaOrigem) {
    int i, j;
    int centro = tamHabilidade / 2;
    for (i = 0; i < tamHabilidade; i++) {
        for (j = 0; j < tamHabilidade; j++) {
            if (habilidade[i][j] == 1) {
                int tabuleiro_i = linhaOrigem + i - centro;
                int tabuleiro_j = colunaOrigem + j - centro;
                if (tabuleiro_i >= 0 && tabuleiro_i < TAMANHO_TABULEIRO && tabuleiro_j >= 0 && tabuleiro_j < TAMANHO_TABULEIRO) {
                    if (tabuleiro[tabuleiro_i][tabuleiro_j] != NAVIO) {
                        tabuleiro[tabuleiro_i][tabuleiro_j] = AFETADO;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int cone[TAMANHO_CONE][TAMANHO_CONE];
    int cruz[TAMANHO_CRUZ][TAMANHO_CRUZ];
    int octaedro[TAMANHO_OCTAEDRO][TAMANHO_OCTAEDRO];

    inicializarTabuleiro(tabuleiro);
    posicionarNavio(tabuleiro, 2, 2, 1, 4);
    posicionarNavio(tabuleiro, 5, 5, 0, 3);
    posicionarNavio(tabuleiro, 1, 6, 2, 3);
    posicionarNavio(tabuleiro, 0, 9, 3, 4);

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    sobreporHabilidade(tabuleiro, cone, TAMANHO_CONE, 1, 4);
    sobreporHabilidade(tabuleiro, cruz, TAMANHO_CRUZ, 7, 7);
    sobreporHabilidade(tabuleiro, octaedro, TAMANHO_OCTAEDRO, 5, 2);

    printf("Tabuleiro de Batalha Naval com Habilidades Especiais\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
