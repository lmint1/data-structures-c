#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 50

typedef int ID;

typedef struct aux {
    ID key;
    struct aux* next;
} Node;

typedef struct {
    Node* start;
    Node* end;
} List;


/**
 * 1. Initialize the list
 * 2. Return elements count
 * 3. Print elements
 * 4. Find elements
 * 5. Insert elements
 * 6. Remove element
 * */

// 1. Initialize list
void initList(List* list) { 
    Node* next = list->start;
    while (next != NULL) {
        Node* old = next;
        next = old->next;
        free(old);
    }
    list->start = NULL; 
    list->end = NULL; 
}

// 2. Get count 
int getCount(List* list) { 
    int count = 0;
    Node* node = list->start;
    while(node->next != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

// 3. Print elements
void printAll(List* list) {
    printf("\n");
    Node* node = list->start;
    while(node != NULL) {
        printf("> %i \n", node->key);
        node = node->next;
    }
    printf("\n");
}

// 4. Find by value
Node* findByID(List* list, ID find) {
    Node* node = list->start;
    while(node != NULL) {
        if (node->key == find) return node;
        node = node->next;
    }
    return NULL;
}

// 5. Insert elements
bool insert(List* list, Node* node) {
    if (list->start == NULL && list->end == NULL) {
        list->start = node;
        list->end = node;
    }
    else if (list->end->next == NULL) {
        Node* prev = list->end;
        prev->next = node;
        list->end = node;
    } else {
        list->start = node;
        list->end = node;
    }
    return true;
}

// 6. Remove element    
bool removeElement(List* list, ID id) {
    Node* node = list->start;
    Node* prev = NULL;
    while(node->next != NULL) {
        if (node->key == id){
            if (prev == NULL) {
                list->start = node->next;
                free(node);
            } else {
                prev->next = node->next;
                if (node->next == NULL) { list->end = NULL; }
                free(node);
            }
        }
        prev = node;
        node = node->next;
    }
    return false;
}

// Creates a Node
Node* newNode(ID id) {
    Node* node = malloc(sizeof(Node));
    node->key = id;
    node->next = NULL;
    return node;
}

// Main
int main() {
    List* list = malloc(sizeof(List));
    printf("Iniciando...\n");
    initList(list);

    printf("Adicionando...\n");
    insert(list, newNode(10));
    insert(list, newNode(2));
    insert(list, newNode(3));
    insert(list, newNode(4));
    printAll(list);

    Node* node = findByID(list, 4);
    printf(">>> FOUND %i\n", node->key);
    // printf(">>> Removing 3\n");
    // removeElement(list, 3);
    // printAll(list);

    // printf(">>> Adding 7\n");
    // insert(list, newNode(7));
    // printAll(list);


    // printf(">>> Restarting 7\n");
    // initList(list);
    // insert(list, newNode(5));
    // insert(list, newNode(6));
    // printAll(list);

    return 0;
}