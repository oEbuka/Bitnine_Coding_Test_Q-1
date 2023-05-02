#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    TypeTag type;
    void *left;
    void *right;
} Node;

typedef enum TypeTag {
    ADD,
    SUB,
    MUL,
    DIV,
    FIBO,
    NUM
} TypeTag;

Node* makeNum(int num) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->type = NUM;
    newNode->left = NULL;
    newNode->right = NULL;
    *((int*)(&newNode->left)) = num;
    return newNode;
}

Node* makeFunc(TypeTag type) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->type = type;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void calc(Node *node) {
    if (node == NULL) {
        return;
    }
    if (node->type == NUM) {
        return;
    }
    calc(node->left);
    calc(node->right);
    switch (node->type) {
        case ADD:
            *((int*)(&node->left)) += *((int*)(&node->right));
            node->type = NUM;
            node->right = NULL;
            break;
        case SUB:
            *((int*)(&node->left)) -= *((int*)(&node->right));
            node->type = NUM;
            node->right = NULL;
            break;
        case MUL:
            *((int*)(&node->left)) *= *((int*)(&node->right));
            node->type = NUM;
            node->right = NULL;
            break;
        case DIV:
            *((int*)(&node->left)) /= *((int*)(&node->right));
            node->type = NUM;
            node->right = NULL;
            break;
        case FIBO: {
            int n = *((int*)(&node->left));
            int fibo[n+1];
            fibo[0] = 0;
            fibo[1] = 1;
            for (int i = 2; i <= n; i++) {
                fibo[i] = fibo[i-1] + fibo[i-2];
            }
            *((int*)(&node->left)) = fibo[n];
            node->type = NUM;
            node->right = NULL;
            break;
        }
        default:
            printf("Invalid operation\n");
            break;
    }
}

int main() {
    Node *add = (*makeFunc(ADD))(10, 6);
    Node *mul = (*makeFunc(MUL))(5, 4);
    Node *sub = (*makeFunc(SUB))(mul, add);
    Node *fibo = (*makeFunc(FIBO))(makeNum(2), NULL);
    calc(add);
    calc(mul);
    calc(sub);
    calc(fibo);
    printf("add: %d\n", *((int*)(&add->left)));
    printf("mul: %d\n", *((int*)(&mul->left)));
    printf("sub: %d\n", *((int*)(&sub->left)));
    printf("fibo: %d\n", *((int*)(&fibo->left)));
    return 0;
}

