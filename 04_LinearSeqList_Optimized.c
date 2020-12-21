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


// 4. Find by value
int findByID(List* list, ID find) {
    int left, right, mid;
    left = 0;
    right = list->count;
    while (left < right)
    {
        mid = (left+right)/2;
        int midVal = list->values[mid].key;
        // Found
        if (midVal == find) return mid;
        // Slicing the find
        if (midVal > find) right = mid-1;
        else left = mid+1;
    }
    return -1;
}

// 5. Insert elements - that insertion sorts the list
bool insert(List* list, Node node) {
    if (list->count == MAX_SIZE) return false;
    int pos = list->count;
    while(pos > 0 && list->values[pos-1].key > node.key) {
        list->values[pos] = list->values[pos-1];
        pos--;
    }
    list->values[pos] = node;
    list->count++;
    return true;
}


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

    insert(list, *newNode(8));
    insert(list, *newNode(22));
    insert(list, *newNode(82));
    insert(list, *newNode(2));
    insert(list, *newNode(3));
    insert(list, *newNode(33));
    insert(list, *newNode(23));
    insert(list, *newNode(4));
    printAll(list);

    int find = 80;
    int index = findByID(list, find);
    printf(">>> Index for %i = %i\n", find, index);


    // printf(">>> Removing 3\n");
    // removeElement(list, 3);
    // printAll(list);

    // printf(">>> Adding 7\n");
    // insert(list, *newNode(7));
    //printAll(list);

    return 0;
}