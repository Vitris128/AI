#include <malloc.h>
#include <stdio.h>

#define MAXLENGTH 200
#define MAX_VERTICES 5
#define EMPTY 0

const char name[] = {'A', 'B', 'C', 'D', 'G'};

typedef struct
{
    int neighbor[MAX_VERTICES];
    int h;
} Vertices;

typedef struct Graph {
    int numVertices;
    Vertices V[MAX_VERTICES];
} Graph;

void initGraph(int numVertices, Graph *G) {
    G->numVertices = numVertices;
    int i, j;
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++)
            G->V[i].neighbor[j] = 0;
        G->V[i].h = 0;
    }
}

typedef struct State {
    int Vertex;
} State;

void printState(State state) {
    printf("%c", name[state.Vertex]);
}

int compareStates(State state1, State state2) {
    return state1.Vertex == state2.Vertex;
}

typedef struct Node {
    State state;
    struct Node *parent;
    int f;
    int g;
    int h;
} Node;

typedef struct List {
    Node *Elements[MAXLENGTH];
    int size;
} List;

void makeNULLList(List *list) {
    list->size = 0;
}
int emptyList(List list) {
    return list.size == 0;
}
int fullList(List list) {
    return list.size == MAXLENGTH;
}
Node *elementAt(int p, List list) {
    return list.Elements[p - 1];
}
void pushList(Node *x, int position, List *list) {
    if (!fullList(*list)) {
        int q;
        for (q = list->size; q >= position; q--)
            list->Elements[q] = list->Elements[q - 1];
        list->Elements[position - 1] = x;
        list->size++;
    } else
        printf("List is full\n");
}

void deleteList(int position, List *list) {
    if (emptyList(*list))
        printf("List is empty\n");
    else if (position < 1 || position > list->size)
        printf("Position is not possible to delete\n");
    else {
        int i;
        for (i = position - 1; i < list->size; i++)
            list->Elements[i] = list->Elements[i + 1];
        list->size--;
    }
}

Node *findState(State state, List list, int *position) {
    int i;
    for (i = 1; i <= list.size; i++)
        if (compareStates(elementAt(i, list)->state, state)) {
            *position = i;
            return elementAt(i, list);
        }
    return NULL;
}

int goalCheck(State state, State goal) {
    return compareStates(state, goal);
}

void sortList(List *list) {
    int i, j;
    for (i = 0; i < list->size - 1; i++)
        for (j = i + 1; j < list->size; j++)
            if (list->Elements[i]->f > list->Elements[j]->f) {
                Node *node = list->Elements[i];
                list->Elements[i] = list->Elements[j];
                list->Elements[j] = node;
            }
}

Node *A_Star(Graph G, State state, State goal) {
    List Open_A_Star, Close_A_Star;
    makeNULLList(&Open_A_Star);
    makeNULLList(&Close_A_Star);
    Node *root = (Node *)malloc(sizeof(Node));
    root->state = state;
    root->parent = NULL;
    root->g = 0;
    root->h = G.V[state.Vertex].h;
    root->f = root->g + root->h;
    pushList(root, Open_A_Star.size + 1, &Open_A_Star);
    while (!emptyList(Open_A_Star)) {
        Node *node = elementAt(1, Open_A_Star);
        deleteList(1, &Open_A_Star);
        pushList(node, Close_A_Star.size + 1, &Close_A_Star);
        if (goalCheck(node->state, goal))
            return node;
        int opt;
        for (opt = 0; opt < G.numVertices; opt++) {
            State newstate;
            if (G.V[node->state.Vertex].neighbor[opt] > 0) {
                Node *newNode = (Node *)malloc(sizeof(Node));
                newNode->state.Vertex = opt;
                newNode->parent = node;
                newNode->g = node->g + G.V[node->state.Vertex].neighbor[opt];
                newNode->h = G.V[opt].h;
                newNode->f = newNode->g + newNode->h;
                int posOpen, posClose;
                Node *nodeFoundOpen = findState(newNode->state, Open_A_Star, &posOpen);
                Node *nodeFoundClose = findState(newNode->state, Close_A_Star, &posClose);
                if (nodeFoundOpen == NULL && nodeFoundClose == NULL) {
                    pushList(newNode, Open_A_Star.size + 1, &Open_A_Star);
                } else if (nodeFoundOpen != NULL && nodeFoundOpen->g > newNode->g) {
                    deleteList(posOpen, &Open_A_Star);
                    pushList(newNode, posOpen, &Open_A_Star);
                } else if (nodeFoundClose != NULL && nodeFoundClose->g > newNode->g) {
                    deleteList(posClose, &Close_A_Star);
                    pushList(newNode, Open_A_Star.size + 1, &Open_A_Star);
                }
            }
        }
        sortList(&Open_A_Star);
    }
    return NULL;
}

void printWaysToGetGoal(Node *node) {
    List listPrint;
    makeNULLList(&listPrint);

    while (node->parent != NULL) {
        pushList(node, listPrint.size + 1, &listPrint);
        node = node->parent;
    }
    pushList(node, listPrint.size + 1, &listPrint);

    int no_action = 0, i;
    for (i = listPrint.size; i > 0; i--) {
        printState(elementAt(i, listPrint)->state);
        if (i != 1) {
            printf("->");
        }
        no_action++;
    }
}

int main() {
    int i, j;
    Graph graph;
    freopen("test.txt", "r", stdin);
    initGraph(MAX_VERTICES, &graph);
    for (i = 0; i < MAX_VERTICES; i++) {
        int x;
        scanf("%d", &x);
        graph.V[i].h = x;
        for (j = 0; j < MAX_VERTICES; j++) {
            scanf("%d", &x);
            graph.V[i].neighbor[j] = x;
        }
    }
    State A, G;
    A.Vertex = 0;
    G.Vertex = 4;
    Node *result = A_Star(graph, A, G);
    printWaysToGetGoal(result);

    return 0;
}