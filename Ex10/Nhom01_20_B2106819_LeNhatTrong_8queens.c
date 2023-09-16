#include <stdio.h>
#include <stdlib.h>

#define NB_ROWS 8
#define NB_COLUMNS 8
#define QUEEN 1
#define EMPTY 0
#define INF 999999

typedef struct Coord {
    int x, y;
} Coord;

typedef struct Constrains {
    int data[NB_ROWS][NB_COLUMNS];
} Constrains;

void initConstrains(Constrains *constrains) {
    int i, j;
    for (i = 0; i < NB_ROWS; i++)
        for (j = 0; j < NB_ROWS; j++)
            constrains->data[i][j] = 0;
}

void addConstrain(Constrains *constrains, int u, int v) {
    constrains->data[u][v] = 1;
}

typedef struct Chess {
    int cells[NB_ROWS][NB_COLUMNS];
    int queens;
    Constrains constrains;
} Chess;

void initChess(Chess *chess) {
    int i, j;
    for (i = 0; i < NB_ROWS; i++)
        for (j = 0; j < NB_COLUMNS; j++)
            chess->cells[i][j] = EMPTY;
    chess->queens = 0;
    initConstrains(&chess->constrains);
}

void printChess(Chess chess) {
    int i, j;
    printf("Chess board:\n");
    for (i = 0; i < NB_ROWS; i++) {
        for (j = 0; j < NB_COLUMNS; j++) {
            printf("| ");
            if (chess.cells[i][j] == 0) {
                printf("  ");
            } else
                printf("Q ");
        }
        printf("|\n");
    }
    printf("Queens: %d \n", chess.queens);
    printf("--------------------------------\n");
}

int isFilledChess(Chess chess) {
    return chess.queens == NB_COLUMNS;
}

void spreadConstrainsForm(Coord position, Constrains *constrains) {
    int row = position.x, column = position.y;
    int i, j;
    for (i = 0; i < NB_ROWS; i++) {
        if (i != row)
            addConstrain(constrains, i, column);
    }
    for (i = 0; i < NB_COLUMNS; i++) {
        if (i != column)
            addConstrain(constrains, row, i);
    }
    for (i = row, j = column; i < NB_ROWS && j < NB_COLUMNS; i++, j++) {
        addConstrain(constrains, i, j);
    }
    for (i = row, j = column; i >= 0 && j >= 0; i--, j--) {
        addConstrain(constrains, i, j);
    }
    for (i = row, j = column; i < NB_ROWS && j >= 0; i++, j--) {
        addConstrain(constrains, i, j);
    }
    for (i = row, j = column; i >= 0 && j < NB_COLUMNS; i--, j++) {
        addConstrain(constrains, i, j);
    }
}
void resetConstrains(Constrains *constrains, int cells[NB_ROWS][NB_COLUMNS]) {
    int i, j;
    for (i = 0; i < NB_ROWS; i++)
        for (j = 0; j < NB_COLUMNS; j++)
            constrains->data[i][j] = 0;
    for (i = 0; i < NB_ROWS; i++)
        for (j = 0; j < NB_COLUMNS; j++)
            if (cells[i][j] != 0)
                spreadConstrainsForm((Coord){i, j}, constrains);
}
void printConstrain(Constrains constrains) {
    int i, j;
    printf("Constrain: \n");
    for (i = 0; i < NB_ROWS; i++) {
        for (j = 0; j < NB_COLUMNS; j++)
            printf("%d ", constrains.data[i][j]);
        printf("\n");
    }
}

int exploredCounter = 0;

int solveChess(Chess *chess, int col) {
    if (isFilledChess(*chess))
        return 1;
    int i;
    for (i = 0; i < NB_COLUMNS; i++) {
        if (chess->constrains.data[i][col] != 1) {
            chess->cells[i][col] = QUEEN;
            chess->queens++;
            spreadConstrainsForm((Coord){i, col}, &chess->constrains);
            if (solveChess(chess, col + 1))
                return 1;
            chess->cells[i][col] = EMPTY;
            chess->queens--;
            resetConstrains(&chess->constrains, chess->cells);
        }
    }
    return 0;
}

int main() {
    Chess chess;
    initChess(&chess);
    printf("------%d QUEENS PROBLEMS------\n", NB_ROWS);
    if (solveChess(&chess, 0)) {
        printf("Solved\n");
        printChess(chess);
    } else {
        printf("Can't find solution!!!");
    }
    return 0;
}
