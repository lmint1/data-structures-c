#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 50

typedef int ID;

typedef struct aux {
    ID key;
    struct aux* bellow;
} Node;

typedef struct {
    Node* top;
} Stack;


/**
 * 1. Initialize the stack
 * 2. Return elements count
 * 3. Print elements
 * 4. Check is empty
 * 5. Insert elements (push)
 * 6. Remove element  (pop)
 * */

// 1. Initialize stack
void initStack(Stack* stack) { 
    stack->top = NULL;
}

// 2. Get count 
int getCount(Stack* stack) {
    int count = 0;
    Node* node = stack->top;
    while (node != NULL) {
        count++;
        node = node->bellow;
    }
    return count;
}

// 3. Print elements
void printAll(Stack* stack) {
    printf("\n");
    Node* node = stack->top;
    while (node != NULL)
    {
        printf("> %i \n", node->key);
        node = node->bellow;
    }
    printf("\n");
}

// 4. Check is empty
bool isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// 5. Insert elements
bool push(Stack* stack, Node* node) {
    if (stack->top == NULL) {
        stack->top = node;
    } else {
        Node* bellow = stack->top;
        stack->top = node;
        stack->top->bellow = bellow;
    }
    return true;
}

// 6. Remove element    
Node* pop(Stack* stack) {
    if (stack->top == NULL) return NULL;
    Node* node = stack->top;
    stack->top = node->bellow;
    node->bellow = NULL;
    return node;
}

Node* newNode(ID id) {
    Node* node = malloc(sizeof(Node));
    node->key = id;
    node->bellow = NULL;
    return node;
}

int main() {
    Stack* stack = malloc(sizeof(Stack));
    printf("Iniciando...\n");
    initStack(stack);

    printf("Adicionando...\n");
    push(stack, newNode(10));
    push(stack, newNode(2));
    push(stack, newNode(3));
    push(stack, newNode(4));
    printAll(stack);
    printf("Count = %i", getCount(stack));

    pop(stack);
    printAll(stack);
    printf("Count = %i", getCount(stack));

    // printf(">>> Adding 7\n");
    push(stack, newNode(7));
    printAll(stack);

    printf("Count = %i", getCount(stack));
    // initStack(stack);
    // insert(stack, newNode(5));
    // insert(stack, newNode(6));
    // printAll(stack);

    return 0;
}