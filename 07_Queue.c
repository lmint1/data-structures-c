#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 50

typedef int ID;

typedef struct aux {
    ID key;
    struct aux* next;
} Node, * POINTER;

typedef struct {
    POINTER first;
    POINTER last;
} Queue;


/**
 * 1. Initialize the queue
 * 2. Return elements count
 * 3. Print elements
 * 4. Check is empty
 * 5. Insert elements (insert)
 * 6. Remove element  (pop)
 * */

// 1. Initialize queue
void initQueue(Queue* queue) { 
    queue->first = NULL;
    queue->last = NULL;
}

// 2. Get count 
int getCount(Queue* queue) {
    int count = 0;
    POINTER node = queue->first;
    while (node != NULL)
    {
        count++;
        node = node->next;
    }
    return count;
}

// 3. Print elements
void printAll(Queue* queue) {
    printf("\n");
    POINTER node = queue->first;
    while (node != NULL)
    {
        printf("> %i \n", node->key);
        node = node->next;
    }
    printf("\n");
}

// 4. Check is empty
bool isEmpty(Queue* queue) {
    return queue->first == NULL;
}

// 5. Insert elements
bool insert(Queue* queue, POINTER node) {
    if (queue->last == NULL) queue->first = node;
    else queue->last->next = node;
    queue->last = node;
    return true;
}

// 6. Remove element    
bool removeNode(Queue* queue) {
    if (queue->first == NULL) return false;
    POINTER first = queue->first;
    queue->first = first->next;
    free(first);
    if (queue->first==NULL) { queue->last = NULL; }
    return true;
}


POINTER newNode(ID id) {
    POINTER node = malloc(sizeof(Node));
    node->key = id;
    node->next = NULL;
    return node;
}

int main() {
    Queue* queue = malloc(sizeof(Queue));
    printf("Iniciando...\n");
    initQueue(queue);

    printf("Adicionando...\n");
    insert(queue, newNode(10));
    insert(queue, newNode(2));
    insert(queue, newNode(3));
    insert(queue, newNode(4));
    printAll(queue);
    printf("Count = %i\n", getCount(queue));

    printf("Removendo: %i", removeNode(queue));
    
    printAll(queue);
    printf("Count = %i", getCount(queue));

    // printf(">>> Adding 7\n");
    insert(queue, newNode(7));
    insert(queue, newNode(4));
    insert(queue, newNode(6));
    printAll(queue);

    printf("Count = %i", getCount(queue));

    return 0;
}