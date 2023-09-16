#include <stdio.h>
#include <malloc.h>

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

typedef struct Stack
{
    Node *Elements[MAXLENGTH];
    int top_Idx;
} Stack;

void makeNULLStack(Stack *stack)
{
    stack->top_Idx = MAXLENGTH;
}

int emptyStack(Stack stack)
{
    return stack.top_Idx == MAXLENGTH;
}

int fullStack(Stack stack)
{
    return stack.top_Idx == 0;
}

Node *top(Stack stack)
{
    if (!emptyStack(stack))
        return stack.Elements[stack.top_Idx];
    return NULL;
}

void pop(Stack *stack)
{
    if (!emptyStack(*stack))
        stack->top_Idx += 1;
    else
        printf("Error! Stack is EMPTY");
}

void push(Node *X, Stack *stack)
{
    if (fullStack(*stack))
        printf("Error! Stack is full");
    else
    {
        stack->top_Idx -= 1;
        stack->Elements[stack->top_Idx] = X;
    }
}

typedef struct Queue
{
    Node *Element[MAXLENGTH];
    int front, rear;
} Queue;

void makeNULLQueue(Queue *q)
{
    q->front = -1;
    q->rear = -1;
}

int emptyQueue(Queue q)
{
    return q.front == -1;
}

int fullQueue(Queue q)
{
    return ((q.rear - q.front + 1) % MAXLENGTH) == 0;
}

Node *getFront(Queue q)
{
    if (emptyQueue(q))
        printf("Queue is empty");
    else
        return q.Element[q.front];
}

void delQueue(Queue *q)
{
    if (!emptyQueue(*q))
    {
        if (q->front == q->rear)
            makeNULLQueue(q);
        else
            q->front = (q->front + 1) % MAXLENGTH;
    }
    else
        printf("Eror, Delete");
}

void pushQueue(Node *x, Queue *q)
{
    if (!fullQueue(*q))
    {
        if (emptyQueue(*q))
            q->front = 0;
        q->rear = (q->rear + 1) % MAXLENGTH;
        q->Element[q->rear] = x;
    }
    else
        printf("Error, Push");
}

int compareStates(State S1, State S2)
{
    return (S1.Demon == S2.Demon && S1.Monk == S2.Monk && S1.Boat_Loc == S2.Boat_Loc);
}

int findState(State state, Queue openQueue)
{
    while (!emptyQueue(openQueue))
    {
        if (compareStates(getFront(openQueue)->state, state))
            return 1;
        delQueue(&openQueue);
    }
    return 0;
}

Node *BFS_Algorithm(State state)
{
    Queue OpenBFS, CloseBFS;
    makeNULLQueue(&OpenBFS);
    makeNULLQueue(&CloseBFS);

    Node *root = (Node *)malloc(sizeof(Node));
    root->state = state;
    root->parent = NULL;
    root->no_Function = 0;
    pushQueue(root, &OpenBFS);

    while (!emptyQueue(OpenBFS))
    {
        Node *node = getFront(OpenBFS);
        delQueue(&OpenBFS);
        pushQueue(node, &CloseBFS);

        if (goalCheck(node->state))
            return node;
        int opt;
        for (opt = 1; opt <= 5; opt++)
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
                pushQueue(newNode, &OpenBFS);
            }
        }
    }
    return NULL;
}

void printWaysToGetGoal(Node *node)
{
    Stack stackPrint;
    makeNULLStack(&stackPrint);
    while (node->parent != NULL)
    {
        push(node, &stackPrint);
        node = node->parent;
    }
    push(node, &stackPrint);

    int noAction = 0;
    while (!emptyStack(stackPrint))
    {
        printf("Action: %d:\n%s", noAction, action[top(stackPrint)->no_Function]);
        printState(top(stackPrint)->state);
        printf("\n");
        pop(&stackPrint);
        noAction++;
    }
}

int main()
{

    State cur_S = {3, 3, 'A'};
    Node *p = BFS_Algorithm(cur_S);
    printf("LOCATION: (MONK : DEMON)\n");
    printWaysToGetGoal(p);

    return 0;
}