#include <stdio.h>
#include <stdbool.h>

#define ROWS 10
#define COLS 10
#define SHIP_SIZE 3
#define WATER 0
#define SHIP 3

typedef enum { HORIZONTAL, VERTICAL } Orientation;

/* Inicializa o tabuleiro com água (0) */
void initBoard(int board[ROWS][COLS]) {
    int r, c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            board[r][c] = WATER;
        }
    }
}

/* Imprime o tabuleiro */
void printBoard(int board[ROWS][COLS]) {
    int r, c;
    printf("   ");
    for (c = 0; c < COLS; c++) {
        printf("%2d ", c);
    }
    printf("\n");
    for (r = 0; r < ROWS; r++) {
        printf("%2d ", r);
        for (c = 0; c < COLS; c++) {
            printf("%2d ", board[r][c]);
        }
        printf("\n");
    }
}

/* Verifica se é possível posicionar o navio */
bool canPlaceShip(int board[ROWS][COLS], int startRow, int startCol, Orientation o) {
    int i;
    if (o == HORIZONTAL) {
        if (startCol < 0 || startCol + SHIP_SIZE - 1 >= COLS || startRow < 0 || startRow >= ROWS)
            return false;
        for (i = 0; i < SHIP_SIZE; i++) {
            if (board[startRow][startCol + i] != WATER) return false;
        }
    } else { // vertical
        if (startRow < 0 || startRow + SHIP_SIZE - 1 >= ROWS || startCol < 0 || startCol >= COLS)
            return false;
        for (i = 0; i < SHIP_SIZE; i++) {
            if (board[startRow + i][startCol] != WATER) return false;
        }
    }
    return true;
}

/* Posiciona o navio no tabuleiro */
bool placeShip(int board[ROWS][COLS], const int shipVec[SHIP_SIZE],
               int startRow, int startCol, Orientation o) {
    int i;
    if (!canPlaceShip(board, startRow, startCol, o)) return false;

    if (o == HORIZONTAL) {
        for (i = 0; i < SHIP_SIZE; i++) {
            board[startRow][startCol + i] = shipVec[i];
        }
    } else {
        for (i = 0; i < SHIP_SIZE; i++) {
            board[startRow + i][startCol] = shipVec[i];
        }
    }
    return true;
}

/* Programa principal */
int main(void) {
    int board[ROWS][COLS];
    int shipHorizontal[SHIP_SIZE] = { SHIP, SHIP, SHIP };
    int shipVertical[SHIP_SIZE]   = { SHIP, SHIP, SHIP };

    int hRow = 2, hCol = 4; // início do navio horizontal
    int vRow = 6, vCol = 1; // início do navio vertical

    initBoard(board);

    if (!placeShip(board, shipHorizontal, hRow, hCol, HORIZONTAL)) {
        printf("Erro: nao foi possivel posicionar o navio horizontal.\n");
        return 1;
    }

    if (!placeShip(board, shipVertical, vRow, vCol, VERTICAL)) {
        printf("Erro: nao foi possivel posicionar o navio vertical.\n");
        return 1;
    }

    printBoard(board);

    printf("\nPressione ENTER para sair...");
    getchar(); // mantém a janela aberta até apertar ENTER
    return 0;
}
