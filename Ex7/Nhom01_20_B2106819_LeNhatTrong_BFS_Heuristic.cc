#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <vector>
#include <iterator>
#define ROWS 3
#define COLS 3
#define EMPTY 0
#define MAX_OPERATOR 4
#define MAXLENGTH 500

const char *action[] = {"First State", "Move cell EMPTY to UP", "Move cell EMPTY to DOWN", "Move cell EMPTY to LEFT", "Move cell EMPTY to RIGHT"};

typedef struct State
{
    int eightPuzzel[ROWS][COLS];
    int emptyRow;
    int emptyCol;
} State;

void printState(State state)
{
    int row, col;
    printf("\n--------\n");
    for (row = 0; row < ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
            printf("|%d ", state.eightPuzzel[row][col]);
        printf("|\n");
    }
    printf("--------\n");
}

int compareStates(State state1, State state2)
{
    if (state1.emptyRow != state2.emptyRow || state1.emptyCol != state2.emptyCol)
        return 0;
    int row, col;
    for (row = 0; row < ROWS; row++)
        for (col = 0; col < COLS; col++)
            if (state1.eightPuzzel[row][col] != state2.eightPuzzel[row][col])
                return 0;
    return 1;
}

int goalCheck(State state, State goal)
{
    return compareStates(state, goal);
}

int upOperator(State state, State *result)
{
    *result = state;
    int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
    if (empRowCurrent > 0)
    {
        result->emptyRow = empRowCurrent - 1;
        result->emptyCol = empColCurrent;
        result->eightPuzzel[empRowCurrent][empColCurrent] = state.eightPuzzel[empRowCurrent - 1][empColCurrent];
        result->eightPuzzel[empRowCurrent - 1][empColCurrent] = EMPTY;
        return 1;
    }
    return 0;
}
int downOperator(State state, State *result)
{
    *result = state;
    int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
    if (empRowCurrent < ROWS-1)
    {
        result->emptyRow = empRowCurrent + 1;
        result->emptyCol = empColCurrent;
        result->eightPuzzel[empRowCurrent][empColCurrent] = state.eightPuzzel[empRowCurrent + 1][empColCurrent];
        result->eightPuzzel[empRowCurrent + 1][empColCurrent] = EMPTY;
        return 1;
    }
    return 0;
}
int leftOperator(State state, State *result)
{
    *result = state;
    int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
    if (empColCurrent > 0)
    {
        result->emptyRow = empRowCurrent;
        result->emptyCol = empColCurrent - 1;
        result->eightPuzzel[empRowCurrent][empColCurrent] = state.eightPuzzel[empRowCurrent][empColCurrent - 1];
        result->eightPuzzel[empRowCurrent][empColCurrent - 1] = EMPTY;
        return 1;
    }
    return 0;
}
int rightOperator(State state, State *result)
{
    *result = state;
    int empRowCurrent = state.emptyRow, empColCurrent = state.emptyCol;
    if (empColCurrent < COLS-1)
    {
        result->emptyRow = empRowCurrent;
        result->emptyCol = empColCurrent + 1;
        result->eightPuzzel[empRowCurrent][empColCurrent] = state.eightPuzzel[empRowCurrent][empColCurrent + 1];
        result->eightPuzzel[empRowCurrent][empColCurrent + 1] = EMPTY;
        return 1;
    }
    return 0;
}

int callOperators(State state, State *result, int opt)
{
    switch (opt)
    {
    case 1:
        return upOperator(state, result);
    case 2:
        return downOperator(state, result);
    case 3:
        return leftOperator(state, result);
    case 4:
        return rightOperator(state, result);
    default:
        printf("Cannot call operators");
        return 0;
    }
}
int heuristicOne(State state, State goal)
{
    int row, col, count = 0;
    for (row = 0; row < ROWS; row++)
        for (col = 0; col < COLS; col++)
            if (state.eightPuzzel[row][col] != goal.eightPuzzel[row][col])
                count++;
    return count;
}
typedef struct Node
{
    State state;
    struct Node *parent;
    int no_function;
    int heuristic;
} Node;


Node *findState(State state, std::vector<Node*> list, int *position)
{
    int i = 0;  
    for (auto it = list.begin();it < list.end();it++) {
        i++;
        if(compareStates((*it)->state, state))
        {
            *position = i;
            return *it;
            }
        }
        return NULL;
}

bool compareNode(Node* i1, Node* i2) {
        return (i1->heuristic < i2->heuristic);
}

// void sortList(List *list)
// {
//     int i, j;
//     for (i = 0; i < list->size - 1; i++)
//         for (j = i + 1; j < list->size; j++)
//             if (list->Elements[i]->heuristic > list->Elements[j]->heuristic)
//             {
//                 Node* node = list->Elements[i];
//                 list->Elements[i] = list->Elements[j];
//                 list->Elements[j] = node;
//             }
// }

Node *bestFirstSearch(State state, State goal)
{
    std::vector<Node*> OpenBFS, CloseBFS;
    Node *root = (Node *)malloc(sizeof(Node));
    root->state = state;
    root->parent = NULL;
    root->no_function = 0;
    root->heuristic = heuristicOne(root->state, goal);
    OpenBFS.push_back(root);
    while (!OpenBFS.empty())
    {
        Node *node = OpenBFS.front();
        OpenBFS.erase(OpenBFS.begin());
        CloseBFS.push_back(node);

        if (goalCheck(node->state, goal))
            return node;
        int opt;
        for (opt = 1; opt <= MAX_OPERATOR; opt++)
        {
            State newState;
            newState = node->state;
            if (callOperators(node->state, &newState, opt))
            {
                Node *newNode = (Node *)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = node;
                newNode->no_function = opt;
                newNode->heuristic = heuristicOne(newState, goal);

                int posOpen, posClose;
                Node *nodeFoundOpen = findState(newState, OpenBFS, &posOpen);
                Node *nodeFoundClose = findState(newState, CloseBFS, &posClose);
                if (nodeFoundOpen == NULL && nodeFoundClose == NULL)
                {
                    OpenBFS.push_back(newNode);
                }
                else if (nodeFoundOpen != NULL && nodeFoundOpen->heuristic > newNode->heuristic)
                {
                    OpenBFS.erase(OpenBFS.begin() + posOpen);
                    OpenBFS.insert( OpenBFS.begin() + posOpen, newNode);
                    // pushList(newNode, posOpen, &OpenBFS);
                }
                else if (nodeFoundClose != NULL && nodeFoundClose->heuristic > newNode->heuristic)
                {
                    CloseBFS.erase(CloseBFS.begin() + posClose);
                    OpenBFS.push_back(newNode);
                }
                std::sort(OpenBFS.begin(), OpenBFS.end(), compareNode);
            }
        }
    }
    return NULL;
}

void printWaysToGetGoal(Node *node)
{
    std::vector<Node*> listPrint;
    while (node->parent != NULL)
    {
        listPrint.push_back(node);
        node = node->parent;
    }
    listPrint.push_back(node);

    int no_action = 0, i;

    for (auto it = listPrint.end()-1; it > listPrint.begin(); it--)
    {
        printf("\nAction %d: %s", no_action, action[(*it)->no_function]);
        printState((*it)->state);
        no_action++;

    }
}

int main()
{
    State state, goal;
    state.emptyCol = 1;
    state.emptyRow = 1;
    state.eightPuzzel[0][0] = 3;
    state.eightPuzzel[0][1] = 4; 
    state.eightPuzzel[0][2] = 5;
    state.eightPuzzel[1][0] = 1;
    state.eightPuzzel[1][1] = 0;
    state.eightPuzzel[1][2] = 2;
    state.eightPuzzel[2][0] = 6;
    state.eightPuzzel[2][1] = 7;
    state.eightPuzzel[2][2] = 8;

    goal.emptyCol = 0;
    goal.emptyRow = 0;
    goal.eightPuzzel[0][0] = 0;
    goal.eightPuzzel[0][1] = 1;
    goal.eightPuzzel[0][2] = 2;
    goal.eightPuzzel[1][0] = 3;
    goal.eightPuzzel[1][1] = 4;
    goal.eightPuzzel[1][2] = 5;
    goal.eightPuzzel[2][0] = 6;
    goal.eightPuzzel[2][1] = 7;
    goal.eightPuzzel[2][2] = 8;
    Node *p = bestFirstSearch(state, goal);
    printWaysToGetGoal(p);

    // printState(state);
    // int opt;
    // for (opt = 1; opt <= 4; opt++)
    // {
    //     callOperators(state, &result, opt);
    //     printState(result);
    // }

    return 0;
}