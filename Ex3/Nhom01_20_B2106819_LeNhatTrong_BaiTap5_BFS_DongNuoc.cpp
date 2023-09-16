#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>

#define tank_CapacityX 9
#define tank_CapacityY 4
#define Empty 0
#define goal 6
#define maxLength 100

const char *action[] = {"First State", "pour Water Full X", "pour Water Full Y", "pour Water Empty X", "pour Water empty Y", "pour Water X to Y", "pour Water Y to X"};

typedef struct State
{
    int X, Y;
} State;

void makeNULLState(State *S)
{
    S->X = 0;
    S->Y = 0;
}

void printState(State S)
{
    printf("\n X: %d\t---\tY: %d\n", S.X, S.Y);
}

int goalCheck(State S)
{
    return (S.X == goal || S.Y == goal);
}

int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a < b ? a : b;
}

int pourWaterFullX(State cur_S, State *result)
{
    if (cur_S.X < tank_CapacityX)
    {
        result->X = tank_CapacityX;
        result->Y = cur_S.Y;
        return 1;
    }
    return 0;
}
int pourWaterFullY(State cur_S, State *result)
{
    if (cur_S.Y < tank_CapacityY)
    {
        result->Y = tank_CapacityY;
        result->X = cur_S.X;
        return 1;
    }
    return 0;
}

int pourWaterEmptyX(State cur_S, State *result)
{
    if (cur_S.X == Empty)
        return 0;
    result->X = Empty;
    result->Y = cur_S.Y;
    return 1;
}
int pourWaterEmptyY(State cur_S, State *result)
{
    if (cur_S.Y == Empty)
        return 0;
    result->Y = Empty;
    result->X = cur_S.X;
    return 1;
}

int pourWaterXY(State cur_S, State *result)
{
    if (cur_S.X <= 0 || cur_S.Y >= tank_CapacityY)
        return 0;
    result->X = max(cur_S.X - (tank_CapacityY - cur_S.Y), Empty);
    result->Y = min(cur_S.Y + cur_S.X, tank_CapacityY);
    return 1;
}
int pourWaterYX(State cur_S, State *result)
{
    if (cur_S.Y <= 0 || cur_S.X >= tank_CapacityX)
        return 0;
    result->Y = max(cur_S.Y - (tank_CapacityX - cur_S.X), Empty);
    result->X = min(cur_S.Y + cur_S.X, tank_CapacityX);
    return 1;
}

int call_operator(State cur_S, State *result, int option)
{
    switch (option)
    {
    case 1:
        return pourWaterFullX(cur_S, result);
    case 2:
        return pourWaterFullY(cur_S, result);
    case 3:
        return pourWaterEmptyX(cur_S, result);
    case 4:
        return pourWaterEmptyY(cur_S, result);
    case 5:
        return pourWaterXY(cur_S, result);
    case 6:
        return pourWaterYX(cur_S, result);
    default:
        printf("Error calls operators\n");
        return 0;
    }
}

typedef struct Node
{
    State state;
    struct Node *parent;
    int no_Function;
} Node;

int compareStates(State S1, State S2)
{
    return (S1.X == S2.X && S1.Y == S2.Y);
}

int findState(State state, std::queue<Node*> openStack)
{
    while (!openStack.empty())
    {
        if (compareStates(openStack.front()->state, state))
            return 1;
        openStack.pop();
    }
    return 0;
}

Node *BFS_Algorithm(State state)
{
    std::queue<Node*> OpenBFS, CloseBFS;

    Node *root = (Node *)malloc(sizeof(Node));
    root->state = state;
    root->parent = NULL;
    root->no_Function = 0;

    OpenBFS.push(root);
    while (!OpenBFS.empty())
    {
        Node *node = OpenBFS.front();
        OpenBFS.pop();
        CloseBFS.push(node);
        if (goalCheck(node->state))
            return node;
        for (int opt = 1; opt <= 6; opt++)
        {
            State newState;
            makeNULLState(&newState);
            if (call_operator(node->state, &newState, opt))
            {
                if (findState(newState, CloseBFS) || findState(newState, OpenBFS))
                    continue;
                Node *newNode = (Node *)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = node;
                newNode->no_Function = opt;
                OpenBFS.push(newNode);
            }
        }
    }
    return NULL;
}

void printWaysToGetGoal(Node *node)
{
    std::stack<Node*> stackPrint;
    while (node->parent != NULL)
    {
        stackPrint.push(node);
        node = node->parent;
    }
    stackPrint.push(node);

    int noAction = 0;
    while (!stackPrint.empty())
    {
        printf("\nAction: %d: %s", noAction, action[stackPrint.top()->no_Function]);
        printState(stackPrint.top()->state);
        stackPrint.pop();
        noAction++;
    }
}

int main()
{

    State cur_S = {0, 0};
    Node *p = BFS_Algorithm(cur_S);
    printWaysToGetGoal(p);

    return 0;
}