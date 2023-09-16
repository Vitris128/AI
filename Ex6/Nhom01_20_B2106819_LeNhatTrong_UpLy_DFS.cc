#include <stdio.h>
#include <malloc.h>
#include <stack>
#include <queue>

#define EMPTY 0
#define MAXLENGTH 100
#define MAXGLASSES 6
#define GLASSESPERMOVE 3
#define UP 1
#define DOWN 0

// const char *action[] = {"--First State--", "Move 1 Monk:", "Move 1 Demon:", "Move 2 Monk:", "Move 1 Monk and 1 Demon:", "Move 2 Demon:"};

typedef struct State
{
    int arrGlasses[6];
} State;

void makeNULLState(State *s)
{
    int i;
    for (i = 0; i < 6; i++)
        s->arrGlasses[i] = !(i % 2); // 1 = UP // 0 = DOWN
}

void changeState(State *s, int a, int b, int c, int x, int y, int z)
{
    s->arrGlasses[0] = a;
    s->arrGlasses[1] = b;
    s->arrGlasses[2] = c;
    s->arrGlasses[3] = x;
    s->arrGlasses[4] = y;
    s->arrGlasses[5] = z;
}
void printState(State s)
{
    int i;
    for (i = 0; i < 6; i++)
    {
        if (s.arrGlasses[i] == DOWN)
            printf("DOWN\t");
        else
            printf("UP\t");
    }
    printf("\n");
}

int goalCheck(State s)
{
    int i;
    for (i = 0; i < 6; i++)
        if (s.arrGlasses[i] == DOWN)
            return 0;
    return 1;
}

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int flipGlass(State cur_S, State *result, int start_Pos)
{
    if (start_Pos < 1 || start_Pos > (MAXGLASSES - GLASSESPERMOVE + 1))
        return 0;
    int i;
    *result = cur_S;
    for (i = start_Pos - 1; i < start_Pos - 1 + GLASSESPERMOVE; i++)
    {
        result->arrGlasses[i] = !cur_S.arrGlasses[i];
    }
    return 1;
}

int call_operator(State cur_S, State *result, int option)
{

    return flipGlass(cur_S, result, option);
}

typedef struct Node
{
    State state;
    struct Node *parent;
    int no_Function;
} Node;



int compareStates(State S1, State S2)
{
    int i;
    for (i = 0; i < MAXGLASSES; i++)
    {
        if (S1.arrGlasses[i] != S2.arrGlasses[i])
            return 0;
    }
    return 1;
}

int findState(State state, std::stack<Node*> openQueue)
{
    while (!openQueue.empty())
    {
        if (compareStates(openQueue.top()->state, state))
            return 1;
        openQueue.pop();
    }
    return 0;
}

Node *DFS_Algorithm(State state)
{
    std::stack<Node*> OpenDFS, CloseDFS;

    Node *root = (Node *)malloc(sizeof(Node));
    root->state = state;
    root->parent = NULL;
    root->no_Function = 0;
    OpenDFS.push(root);

    while (!OpenDFS.empty())
    {
        Node *node = OpenDFS.top();
        OpenDFS.pop();
        CloseDFS.push(node);

        if (goalCheck(node->state))
            return node;
        int opt;
        for (opt = 4; opt >= 1; opt--)
        {
            State newState;
            makeNULLState(&newState);
            if (call_operator(node->state, &newState, opt))
            {

                if (findState(newState, CloseDFS) || findState(newState, OpenDFS))
                    continue;
                Node *newNode = (Node *)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = node;
                newNode->no_Function = opt;
                OpenDFS.push(newNode);
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
        printf("Action: %d: \n", noAction);
        printState(stackPrint.top()->state);
        printf("\n");
        stackPrint.pop();
        noAction++;
    }
}

int main()
{
    State cur_S;
    makeNULLState(&cur_S);
    // makeNULLState(&state);
    // changeState(&cur_S, 1, 0, 1, 0, 1, 0);
    Node *p = DFS_Algorithm(cur_S);
    printWaysToGetGoal(p);
    // flipGlass(cur_S, &state, 1);
    // printState(state);
    // printf("%d", goalCheck(state));

    return 0;
}