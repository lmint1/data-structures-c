#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 50

typedef int ID;

typedef struct {
    ID key;
} Node;

typedef struct {
    Node values[MAX_SIZE];
    int count;
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
void initList(List* list) { list->count = 0; }

// 2. Get count 
int getCount(List* list) { return list->count; }

// 3. Print elements
void printAll(List* list) {
    printf("\n");
    for (int i = 0; i < list->count; i++)
    {
        printf("> %i \n", list->values[i].key);
    }
    printf("\n");
}

// 4. Find by value
int findByID(List* list, ID find) {
    for (int i = 0; i < list->count; i++)
    {
        if (list->values[i].key == find) 
            return i;
    }
    return -1;
}

// 5. Insert elements
bool insert(List* list, Node node, int position) {
    if (list->count == MAX_SIZE || position < 0 || position > list->count)
        return false;
    for (int i = list->count; i > position; i--) {
        list->values[i] = list->values[i-1];
    }
    list->values[position] = node;
    list->count++;
    return true;
}

// 6. Remove element    [1, x, 4, 5]
bool removeElement(List* list, ID id) {
    int index = findByID(list, id);
    if (index < 0) return false;
    for (int i = index; i < list->count-1; i++)
    {
        list->values[i] = list->values[i+1];
    }
    list->count--;
    return true;
}

Node* newNode(ID id) {
    Node* node = malloc(sizeof(Node));
    node->key = id;
    return node;
}

int main() {
    List* list = malloc(sizeof(List));
    initList(list);

    insert(list, *newNode(1), 0);
    insert(list, *newNode(2), 1);
    insert(list, *newNode(3), 2);
    insert(list, *newNode(4), 0);
    printAll(list);

    printf(">>> Removing 3\n");
    removeElement(list, 3);
    printAll(list);

    printf(">>> Adding 7\n");
    insert(list, *newNode(7), 3);
    printAll(list);

    return 0;
}