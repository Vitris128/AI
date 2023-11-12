#include <stdio.h>
#define MAX_N 50
#define MAX_LENGTH 100

#define NON_COLOR 0
#define RED 1
#define BLUE 2
#define GREEN 3
typedef struct Graph {
    int n;
    int A[MAX_N][MAX_N];
} Graph;

void init_Graph(Graph* G, int n) {
    G->n = n;
    int i, j;
    for (i = 0; i <= MAX_N; i++)
        for (j = 0; j <= MAX_N; j++)
            G->A[i][j] = 0;
}
void add_Edge(Graph* G, int u, int v) {
    G->A[u][v] = 1;
    G->A[v][u] = 1;
}

int isNeighbor(Graph G, int u, int v) {
    return G.A[u][v];
}
typedef struct List {
    int index;
    int data[MAX_LENGTH];
} List;

void init_List(List* L) {
    L->index = 0;
}
void add_List(List* L, int n) {
    L->data[L->index] = n;
    L->index++;
}

int remainColor(int color[]) {
    int i;
    for (i = 0; i < 3; i++)
        if (color[i] != NON_COLOR)
            return color[i];
}

int colorD[MAX_N];

int finishOrNot(Graph G) {
    int i;
    for (i = 1; i <= G.n; i++) {
        if (colorD[i] == 0)
            return 0;
    }
    return 1;
}

int colorize(Graph G, int u) {
    if (finishOrNot(G))
        return 1;
    int color[3] = {RED, BLUE, GREEN};
    int i;
    for (i = 1; i <= G.n; i++) {
        if (isNeighbor(G, u, i)) {
            if (colorD[i] == RED)
                color[0] = NON_COLOR;
            if (colorD[i] == GREEN)
                color[2] = NON_COLOR;
            if (colorD[i] == BLUE)
                color[1] = NON_COLOR;
        }
    }
    if (color[0] == NON_COLOR && color[1] == NON_COLOR && color[2] == NON_COLOR) {
        return 0;
    }
    if (colorD[u] == NON_COLOR) {
        colorD[u] = remainColor(color);
        int i;
        for (i = 1; i <= G.n; i++) {
            if (isNeighbor(G, i, u)) {
                colorize(G, i);
            }
        }
    }
    return 0;
}

int main() {
    Graph G;
    int i, j, n;
    freopen("graph2.txt", "r", stdin);
    // printf("Number of City: ");
    scanf("%d", &n);
    init_Graph(&G, n);
    for (i = 1; i <= n; i++) {
        // printf("Enter number neighbors of city %d: \n", i);
        int k;
        scanf("%d", &k);
        // printf("List of neighbors: \n");
        for (j = 0; j < k; j++) {
            int m;
            scanf("%d", &m);
            add_Edge(&G, i, m);
        }
    }
    for (i = 1; i <= G.n; i++) {
        colorD[i] = 0;
    }
    colorize(G, 1);
    for (i = 1; i <= G.n; i++) {
        if (colorD[i] == NON_COLOR)
            colorize(G, i);
    }
    if (finishOrNot(G)) {
        for (i = 1; i <= G.n; i++) {
            printf("Solved\n");
            for (i = 1; i <= G.n; i++) {
                printf("Color of %d City: ", i);
                switch (colorD[i]) {
                    case 0:
                        printf("NONE\n");
                        break;
                    case 1:
                        printf("RED\n");
                        break;
                    case 2:
                        printf("BLUE\n");
                        break;
                    case 3:
                        printf("GREEN\n");
                        break;

                    default:
                        break;
                }
            }
        }
    } else {
        printf("Can't solved\n.");
    }
    return 0;
}
