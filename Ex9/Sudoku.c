#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100
#define NB_ROWS 9
#define NB_COLUMNS 9

#define MAX_VALUE 10
#define EMPTY 0
#define AREA_SQUARE_SIZE 3
#define INF 999999

typedef struct List
{
    int data[MAX_LENGTH];
    int size;
} List;

void makeNULLList(List *list)
{
    list->size = 0;
}

int emptyList(List list)
{
    return list.size == EMPTY;
}

int fullList(List list)
{
    return list.size == MAX_LENGTH;
}

int elementAt(List list, int p)
{
    return list.data[p - 1];
}

void pushList(List *list, int n)
{
    list->data[list->size] = n;
    list->size++;
}

typedef struct Coord
{
    int x, y;
} Coord;

typedef struct ListCoord
{
    Coord data[MAX_LENGTH];
    int size;
} ListCoord;

void initListCoord(ListCoord *list)
{
    list->size = 0;
}

void appendListCoord(ListCoord *list, Coord coord)
{
    list->data[list->size++] = coord;
}

typedef struct Constrains
{
    int data[NB_ROWS * NB_COLUMNS][NB_ROWS * NB_COLUMNS];
    int n;
} Constrains;

void initConstrains(Constrains *constrains)
{
    int i, j;
    for (i = 0; i < NB_ROWS * NB_COLUMNS; i++)
        for (j = 0; j < NB_ROWS * NB_COLUMNS; j++)
            constrains->data[i][j] = 0;
    constrains->n = NB_ROWS * NB_COLUMNS;
}

int indexOf(Coord coord)
{
    return NB_ROWS * coord.x + coord.y;
}

Coord positionOfVertex(int vertex)
{
    Coord coord;
    coord.x = vertex / NB_ROWS;
    coord.y = vertex % NB_COLUMNS;
    return coord;
}

int addConstrain(Constrains *constrains, Coord source, Coord target)
{
    int u = indexOf(source);
    int v = indexOf(target);
    if (constrains->data[u][v] == 0)
    {
        constrains->data[u][v] = 1;
        constrains->data[v][u] = 1;
        return 1;
    }

    return 0;
}

ListCoord getConstrains(Constrains constrains, Coord coord)
{
    int i;
    int v = indexOf(coord);
    ListCoord result;
    initListCoord(&result);
    for (i = 0; i < constrains.n; i++)
    {
        if (constrains.data[v][i] == 1)
        {
            appendListCoord(&result, positionOfVertex(i));
        }
    }
    return result;
}

typedef struct Sudoku
{
    int cells[NB_ROWS][NB_COLUMNS];
    Constrains constrains;
} Sudoku;

void initSudoku(Sudoku *sudoku)
{
    int i, j;
    for (i = 0; i < NB_ROWS; i++)
        for (j = 0; j < NB_COLUMNS; j++)
            sudoku->cells[i][j] = EMPTY;
    initConstrains(&sudoku->constrains);
}

void initSudokuWithValues(Sudoku *sudoku, int inputs[NB_ROWS][NB_COLUMNS])
{
    int i, j;

    for (i = 0; i < NB_ROWS; i++)
        for (j = 0; j < NB_COLUMNS; j++)
            sudoku->cells[i][j] = inputs[i][j];

    initConstrains(&sudoku->constrains);
}

void printSudoku(Sudoku sudoku)
{
    int i, j;
    printf("Sudoku:\n");
    for (i = 0; i < NB_ROWS; i++)
    {
        if (i % AREA_SQUARE_SIZE == 0)
            printf("-------------------------\n");
        for (j = 0; j < NB_COLUMNS; j++)
        {
            if (j % AREA_SQUARE_SIZE == 0)
                printf("| ");
            printf("%d ", sudoku.cells[i][j]);
        }
        printf("|\n");
    }
    printf("-------------------------\n");
}

int isFilledSudoku(Sudoku sudoku)
{
    int i, j;
    for (i = 0; i < NB_ROWS; i++)
        for (j = 0; j < NB_COLUMNS; j++)
            if (sudoku.cells[i][j] == EMPTY)
                return 0;
    return 1;
}

void spreadConstrainsForm(Coord position, Constrains *constrains, ListCoord *changeds)
{
    int row = position.x, column = position.y;
    int i, j;
    for (i = 0; i < NB_ROWS; i++)
    {
        if (i != row)
        {
            Coord pos = {i, column};
            if (addConstrain(constrains, position, pos))
                appendListCoord(changeds, pos);
        }
    }
    for (i = 0; i < NB_COLUMNS; i++)
    {
        if (i != column)
        {
            Coord pos = {row, i};
            if (addConstrain(constrains, position, pos))
                appendListCoord(changeds, pos);
        }
    }

    for (i = 0; i < AREA_SQUARE_SIZE; i++)
    {
        for (j = 0; j < AREA_SQUARE_SIZE; j++)
        {
            int areaX = (row / AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
            int areaY = (column / AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
            if (areaX + i != row || areaY + j != column)
            {
                Coord pos = {areaX + i, areaY + j};
                if (addConstrain(constrains, position, pos))
                    appendListCoord(changeds, pos);
            }
        }
    }
}

List getAvailableValues(Coord position, Sudoku sudoku)
{
    ListCoord posList = getConstrains(sudoku.constrains, position);
    int availables[MAX_VALUE];
    int i;
    for (i = 1; i < MAX_VALUE; i++)
        availables[i] = 1;
    for (i = 0; i < posList.size; i++)
    {
        Coord pos = posList.data[i];
        if (sudoku.cells[pos.x][pos.y] != EMPTY)
        {
            availables[sudoku.cells[pos.x][pos.y]] = 0;
        }
    }
    List result;
    makeNULLList(&result);
    for (i = 1; i < MAX_VALUE; i++)
    {
        if (availables[i])
            pushList(&result, i);
    }
    return result;
}

Coord getNextEmptyCell(Sudoku sudoku)
{
    int i, j;
    for (i = 0; i < NB_ROWS; i++)
    {
        for (j = 0; j < NB_COLUMNS; j++)
        {
            Coord pos = {i, j};
            if (sudoku.cells[i][j] == EMPTY)
                return pos;
        }
    }
}

Coord getNextMinDomainCell(Sudoku sudoku)
{
    int minLength = INF;
    int i, j;
    Coord result;
    for (i = 0; i < NB_ROWS; i++)
    {
        for (j = 0; j < NB_COLUMNS; j++)
        {
            if (sudoku.cells[i][j] == EMPTY)
            {
                Coord pos = {i, j};
                int availablesLength = getAvailableValues(pos, sudoku).size;
                if (availablesLength < minLength)
                {
                    minLength = availablesLength;
                    result = pos;
                }
            }
        }
    }
    return result;
}

int exploredCounter = 0;
int sudokuBackTracking(Sudoku *sudoku)
{
    if (isFilledSudoku(*sudoku))
        return 1;
    // Coord position = getNextEmptyCell(*sudoku);
    Coord position = getNextMinDomainCell(*sudoku);
    List availables = getAvailableValues(position, *sudoku);
    if (availables.size == 0)
    {
        return 0;
    }
    int j;
    for (j = 0; j < availables.size; j++)
    {
        int value = availables.data[j];
        sudoku->cells[position.x][position.y] = value;
        exploredCounter++;
        if (sudokuBackTracking(sudoku))
            return 1;
        sudoku->cells[position.x][position.y] = EMPTY;
    }
    return 0;
}

Sudoku solveSudoku(Sudoku sudoku)
{
    int i, j;
    initConstrains(&sudoku.constrains);
    for (i = 0; i < NB_ROWS; i++)
    {
        for (j = 0; j < NB_COLUMNS; j++)
        {
            ListCoord history;
            initListCoord(&history);
            Coord pos = {i, j};
            spreadConstrainsForm(pos, &sudoku.constrains, &history);
        }
    }
    exploredCounter = 0;
    if (sudokuBackTracking(&sudoku))
        printf("Solved\n");
    else
        printf("Can not solve\n");
    printf("Explored %d states\n", exploredCounter);
    return sudoku;
}

int main()
{
    Sudoku sudoku;
    int inputs[9][9] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
   int inputs2[9][9] = {
       {5, 3, 0, 0, 7, 0, 0, 0, 0},
       {6, 0, 0, 1, 9, 5, 0, 0, 0},
       {0, 9, 8, 0, 0, 0, 0, 6, 0},
       {8, 0, 0, 0, 6, 0, 0, 0, 3},
       {4, 0, 0, 8, 0, 3, 0, 0, 1},
       {7, 0, 0, 0, 2, 0, 0, 0, 6},
       {0, 6, 0, 0, 0, 0, 2, 8, 0},
       {0, 0, 0, 4, 1, 9, 0, 0, 5},
       {0, 0, 0, 0, 8, 0, 0, 7, 9},
   };
    initSudokuWithValues(&sudoku, inputs);
    printSudoku(sudoku);
    Sudoku result = solveSudoku(sudoku);
    printSudoku(result);
}
