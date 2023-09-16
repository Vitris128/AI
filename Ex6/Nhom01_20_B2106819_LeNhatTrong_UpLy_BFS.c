#include <stdio.h>
#include <malloc.h>

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
    int i;
    for (i = 0; i < MAXGLASSES; i++)
    {
        if (S1.arrGlasses[i] != S2.arrGlasses[i])
            return 0;
    }
    return 1;
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
        for (opt = 4; opt >= 1; opt--)
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
        printf("Action: %d: \n", noAction);
        printState(top(stackPrint)->state);
        printf("\n");
        pop(&stackPrint);
        noAction++;
    }
}

int main()
{
    State cur_S;
    makeNULLState(&cur_S);
    // makeNULLState(&state);
    // changeState(&cur_S, 1, 0, 1, 0, 1, 0);
    Node *p = BFS_Algorithm(cur_S);
    printWaysToGetGoal(p);
    // flipGlass(cur_S, &state, 1);
    // printState(state);
    // printf("%d", goalCheck(state));

    return 0;
}