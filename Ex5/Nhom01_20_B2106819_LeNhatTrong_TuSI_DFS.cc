#include <stdio.h>
#include <malloc.h>
#include <stack>

#define EMPTY 0
#define MAXLENGTH 100
#define MAXPERSON 3

const char *action[] = {"--First State--", "Move 1 Monk:", "Move 1 Demon:", "Move 2 Monk:", "Move 1 Monk and 1 Demon:", "Move 2 Demon:"};

typedef struct State
{
    int Monk;
    int Demon;
    char Boat_Loc;
} State;

void makeNULLState(State *S)
{
    S->Monk = 0;
    S->Demon = 0;
    S->Boat_Loc = 'A';
}

void changeState(State *s, int monk, int demon, char boat)
{
    s->Monk = monk;
    s->Demon = demon;
    s->Boat_Loc = boat;
}
void printState(State S)
{
    // printf("\nA:%d:%d\tB:%d:%d\tBoat location: %c\n", S.Monk, S.Demon, MAXPERSON - S.Monk, MAXPERSON - S.Demon, S.Boat_Loc);
    if (S.Boat_Loc == 'A')
        printf("\nA:%d:%d-Boat-------B:%d:%d\n", S.Monk, S.Demon, MAXPERSON - S.Monk, MAXPERSON - S.Demon);
    if (S.Boat_Loc == 'B')
        printf("\nA:%d:%d-------Boat-B:%d:%d\n", S.Monk, S.Demon, MAXPERSON - S.Monk, MAXPERSON - S.Demon);
}

int goalCheck(State S)
{
    return (S.Monk == 0 && S.Demon == 0 && S.Boat_Loc == 'B');
}

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int checkState(State s)
{
    if (s.Demon > MAXPERSON || s.Demon < 0 || s.Monk > MAXPERSON || s.Monk < 0)
        return 0;
    if (s.Monk > 0 && s.Monk < s.Demon)
        return 0;
    if ((MAXPERSON - s.Monk) > 0 && (MAXPERSON - s.Monk) < (MAXPERSON - s.Demon))
        return 0;
    return 1;
}
char moveBoat(char c) { return c == 'A' ? 'B' : 'A'; }

int moveOneMonk(State cur_S, State *result)
{
    if (cur_S.Boat_Loc == 'A')
    {
        cur_S.Monk--;
        if (checkState(cur_S))
        {
            result->Demon = cur_S.Demon;
            result->Monk = cur_S.Monk;
            result->Boat_Loc = moveBoat(cur_S.Boat_Loc);
            return 1;
        }
        return 0;
    }
    else
    {
        cur_S.Monk++;
        if (checkState(cur_S))
        {
            result->Demon = cur_S.Demon;
            result->Monk = cur_S.Monk;
            result->Boat_Loc = moveBoat(cur_S.Boat_Loc);
            return 1;
        }
        return 0;
    }
}
int moveOneDemon(State cur_S, State *result)
{
    if (cur_S.Boat_Loc == 'A')
    {
        cur_S.Demon--;
        if (checkState(cur_S))
        {
            result->Demon = cur_S.Demon;
            result->Monk = cur_S.Monk;
            result->Boat_Loc = moveBoat(cur_S.Boat_Loc);
            return 1;
        }
        return 0;
    }
    else
    {
        cur_S.Demon++;
        if (checkState(cur_S))
        {
            result->Demon = cur_S.Demon;
            result->Monk = cur_S.Monk;
            result->Boat_Loc = moveBoat(cur_S.Boat_Loc);
            return 1;
        }
        return 0;
    }
}
int moveTwoMonks(State cur_S, State *result)
{
    if (cur_S.Boat_Loc == 'A')
    {
        cur_S.Monk -= 2;
        if (checkState(cur_S))
        {
            result->Demon = cur_S.Demon;
            result->Monk = cur_S.Monk;
            result->Boat_Loc = moveBoat(cur_S.Boat_Loc);
            return 1;
        }
        return 0;
    }
    else
    {
        cur_S.Monk += 2;
        if (checkState(cur_S))
        {
            result->Demon = cur_S.Demon;
            result->Monk = cur_S.Monk;
            result->Boat_Loc = moveBoat(cur_S.Boat_Loc);
            return 1;
        }
        return 0;
    }
}
int moveMonkAndDemon(State cur_S, State *result)
{
    if (cur_S.Boat_Loc == 'A')
    {
        cur_S.Monk--;
        cur_S.Demon--;
        if (checkState(cur_S))
        {
            result->Demon = cur_S.Demon;
            result->Monk = cur_S.Monk;
            result->Boat_Loc = moveBoat(cur_S.Boat_Loc);
            return 1;
        }
        return 0;
    }
    else
    {
        cur_S.Monk++;
        cur_S.Demon++;
        if (checkState(cur_S))
        {
            result->Demon = cur_S.Demon;
            result->Monk = cur_S.Monk;
            result->Boat_Loc = moveBoat(cur_S.Boat_Loc);
            return 1;
        }
        return 0;
    }
}
int moveTwoDemon(State cur_S, State *result)
{
    if (cur_S.Boat_Loc == 'A')
    {
        cur_S.Demon -= 2;
        if (checkState(cur_S))
        {
            result->Demon = cur_S.Demon;
            result->Monk = cur_S.Monk;
            result->Boat_Loc = moveBoat(cur_S.Boat_Loc);
            return 1;
        }
        return 0;
    }
    else
    {
        cur_S.Demon += 2;
        if (checkState(cur_S))
        {
            result->Demon = cur_S.Demon;
            result->Monk = cur_S.Monk;
            result->Boat_Loc = moveBoat(cur_S.Boat_Loc);
            return 1;
        }
        return 0;
    }
}
int call_operator(State cur_S, State *result, int option)
{
    switch (option)
    {
    case 1:
        return moveOneMonk(cur_S, result);
    case 2:
        return moveOneDemon(cur_S, result);
    case 3:
        return moveTwoMonks(cur_S, result);
    case 4:
        return moveMonkAndDemon(cur_S, result);
    case 5:
        return moveTwoDemon(cur_S, result);
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
    return (S1.Demon == S2.Demon && S1.Monk == S2.Monk && S1.Boat_Loc == S2.Boat_Loc);
}

int findState(State state, std::stack<Node*> openStack)
{
    while (!openStack.empty())
    {
        if (compareStates(openStack.top()->state, state))
            return 1;
        openStack.pop();
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
        for (opt = 1; opt <= 5; opt++)
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
        printf("Action: %d:\n%s", noAction, action[stackPrint.top()->no_Function]);
        printState(stackPrint.top()->state);
        printf("\n");
        stackPrint.pop();
        noAction++;
    }
}

int main()
{

    State cur_S = {3, 3, 'A'};
    Node *p = DFS_Algorithm(cur_S);
    printf("LOCATION: (MONK : DEMON)\n");
    printWaysToGetGoal(p);

    return 0;
}