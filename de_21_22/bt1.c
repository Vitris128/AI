#include <stdio.h>
#include <malloc.h>

#define X_CAPACITY 7
#define Y_CAPACITY 5
#define Z_CAPACITY 3

#define GOAL 1
#define EMPTY 0

#define max(x, y) (x > y) ? x : y
#define min(x, y) (x < y) ? x : y

typedef struct State {
    int x, y, z;
} State;

void make_null_state(State *pS) {
    pS->x = 0;
    pS->y = 0;
    pS->z = 0;
}

void print_state(State S){
    printf("\n> X:%d-----Y:%d-----Z:%d", S.x, S.y, S.z);
}

int goal_check(State S){
    return S.x == GOAL || S.y == GOAL || S.z == GOAL;
}

int X_to_Y(State curr, State *res){
    if(curr.x > 0 && curr.y < Y_CAPACITY){
        res->x = max(curr.x - (Y_CAPACITY - curr.y), EMPTY);
        res->y = min(curr.y + curr.x, Y_CAPACITY);
        res->z = curr.z;
        return 1;
    }
    return 0;
}

int X_to_Z(State curr, State *res){
    if(curr.x > 0 && curr.z < Z_CAPACITY){
        res->x = max(curr.x - (Z_CAPACITY - curr.z), EMPTY);
        res->z = min(curr.z + curr.x, Z_CAPACITY);
        res->y = curr.y;
        return 1;
    }
    return 0;
}

int Y_to_X(State curr, State *res){
    if(curr.y > 0 && curr.x < X_CAPACITY){
        res->y = max(curr.y - (X_CAPACITY - curr.x), EMPTY);
        res->x = min(curr.x + curr.y, X_CAPACITY);
        res->z = curr.z;
        return 1;
    }
    return 0;
}

int Z_to_X(State curr, State *res){
    if(curr.z > 0 && curr.x < X_CAPACITY){
        res->z = max(curr.z - (X_CAPACITY - curr.x), EMPTY);
        res->x = min(curr.x + curr.z, X_CAPACITY);
        res->y = curr.y;
        return 1;
    }
    return 0;
}

int Y_to_Z(State curr, State *res){
    if(curr.y > 0 && curr.z < Z_CAPACITY){
        res->y = max(curr.y - (Z_CAPACITY - curr.z), EMPTY);
        res->z = min(curr.z + curr.y, Z_CAPACITY);
        res->x = curr.x;
        return 1;
    }
    return 0;
}

int Z_to_Y(State curr, State *res){
    if(curr.z > 0 && curr.y < Y_CAPACITY){
        res->z = max(curr.z - (Y_CAPACITY - curr.y), EMPTY);
        res->y = min(curr.y + curr.z, Y_CAPACITY);
        res->x = curr.x;
        return 1;
    }
    return 0;
}

int call_operator(State curr, State *res, int option) {
    switch (option)
    {
    case 1:
        return X_to_Y(curr, res);
    case 2:
        return Y_to_X(curr, res);
    case 3:
        return Y_to_Z(curr, res);
    case 4:
        return Z_to_Y(curr, res);
    case 5:
        return X_to_Z(curr, res);
    case 6:
        return Z_to_Y(curr, res);

    default:
        printf("Error on calling operators!\n");
    }
    return 0;
}

int compare_state(State a, State b){
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

typedef struct Node {
    State state;
    struct Node* parent;
    int option;
} Node;

#define MAX_N 100

typedef struct Stack {
    Node *elements[MAX_N];
    int top_idx;
} Stack;

void make_null_stack(Stack *pS){
    pS->top_idx = MAX_N;
}

int empty_stack(Stack *pS){
    return pS->top_idx == MAX_N;
}

int full_stack(Stack *pS){
    return pS->top_idx <= 0;
}

void push(Stack *pS, Node *x){
    if(full_stack(pS)){
        printf("Error, stack is full!\n");
        return;
    }

    pS->top_idx--;
    pS->elements[pS->top_idx] = x;
}

Node* top(Stack *pS){
    if(!empty_stack(pS)){
        return pS->elements[pS->top_idx];
    }
    return NULL;
}

void pop(Stack *pS){
    if(empty_stack(pS)){
        printf("Error, stack is empty!\n");
        return;
    }
    pS->top_idx++;
}

int find_state(State state, Stack openStack){
    while(!empty_stack(&openStack)){
        if(compare_state(state, top(&openStack)->state)){
            return 1;
        }
        pop(&openStack);
    }
    return 0;
}

Node* DFS(State start){
    Stack open;
    Stack close;
    make_null_stack(&open);
    make_null_stack(&close);

    Node *root = (Node *)malloc(sizeof(Node));
    root->state = start;
    root->parent = NULL;
    root->option = 0;

    push(&open, root);

    while(!empty_stack(&open)){
        Node *node = top(&open);
        pop(&open);
        push(&close, node);

        if(goal_check(node->state)){
            return node;
        }

        for (int option = 1; option <= 6; ++option){
            State newState;
            make_null_state(&newState);

            if(call_operator(node->state, &newState, option)){
                if(find_state(newState, open) || find_state(newState, close)){
                    continue;
                }

                Node *newNode = (Node*)malloc(sizeof(Node));
                newNode->option = option;
                newNode->state = newState;
                newNode->parent = node;
                push(&open, newNode);
            }
        }
    }
    return NULL;
}

const char *action[] = {
    "First state",
    "Pour X to Y",
    "Pour Y to X",
    "Pour Y to Z",
    "Pour Z to Y",
    "Pour X to Z",
    "Pour Z to X"
};

void print_path_to_goal(Node* res){
    Stack stackPrint;
    make_null_stack(&stackPrint);

    while(res != NULL){
        push(&stackPrint, res);
		res = res->parent;
    }

    int iter_count = 0;
    while(!empty_stack(&stackPrint)){
        Node *temp = top(&stackPrint);
        printf("\nAction %d: %s", iter_count, action[temp->option]);
        print_state(temp->state);
        pop(&stackPrint);
        iter_count++;
    }
}


int main(){
    State start = {7, EMPTY, EMPTY};
    Node *res = DFS(start);
    
    print_path_to_goal(res);

    return 0;

    // printf("First state:\n");
    // print_state(start);

    // for (int option = 1; option <= 6; ++option){
    //     if(call_operator(start, &result, option)){
    //         printf("\nAction %s was successfully run", action[option]);
    //         print_state(result);
    //     }else{
    //         printf("\nAction %s failed", action[option]);
    //     }
    

    // }
}
