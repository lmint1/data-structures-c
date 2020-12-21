#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 4

typedef int ID;

typedef struct aux {
    int column;
    struct aux* next;
} Node;

typedef struct {
    Node* start;
    Node* end;
} List;

typedef List* ListPointer;

typedef struct {
    ListPointer* array;
    int lines;
    int columns;
} Matrix;

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
        printf("> %i \n", node->column);
        node = node->next;
    }
    printf("\n");
}

// 4. Find by value
Node* findByColumn(List* list, int find) {
    Node* node = list->start;
    while(node != NULL) {
        if (node->column == find) return node;
        node = node->next;
    }
    return NULL;
}

// 3. Print elements
void printColumns(List* list) {
    printf("\n");
    for(int i =0; i < MAX_SIZE; i++) {
        Node* node = findByColumn(list, i);
        if (node == NULL) { printf("0 "); }
        else { printf("1 "); }
    }
    printf("\n");
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
bool removeElement(List* list, int column) {
    Node* node = list->start;
    Node* prev = NULL;
    while(node->next != NULL) {
        if (node->column == column){
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
Node* newNode(int column) {
    Node* node = malloc(sizeof(Node));
    node->column = column;
    node->next = NULL;
    return node;
}

void initMatrix(Matrix* matrix, int lines, int columns) {
    matrix->lines = lines;
    matrix->columns = columns;
    matrix->array = (ListPointer*) malloc(lines * sizeof(ListPointer));
    for(int i = 0; i < lines; i++) {
        matrix->array[i] = malloc(sizeof(List));
    }
}

bool insertInMatrix(Matrix* matrix, int line, int column) {
    if (line < 0 || line >= matrix->lines || column < 0 || column >= matrix->columns) return false;
    List* list = matrix->array[line];
    if (findByColumn(list, column) != NULL) {
        printf("$ Já existe!\n"); return false;
    };
    return insert(list, newNode(column));
}

int getInMatrix(Matrix* matrix, int line, int column) {
    if (line < 0 || line >= matrix->lines || column < 0 || column >= matrix->columns) return false;
    List* list = matrix->array[line];
    Node* node = findByColumn(list, column);
    if (node == NULL) return 0;
    else return 1;
}

void printMatrix(Matrix* matrix) {
    for(int l = 0; l < matrix->lines; l++) {
        for (int c = 0; c < matrix->columns; c++) {
            int value = getInMatrix(matrix, l, c);
            printf("%i ", value);
        }
        printf("\n");
    }
}

// Main
int main() {
    Matrix* matrix = malloc(sizeof(Matrix));
    initMatrix(matrix, 5, 5);
    
    printf("Printando a matriz...\n\n");
    
    insertInMatrix(matrix, 0, 0);
    insertInMatrix(matrix, 0, 4);

    insertInMatrix(matrix, 1, 1);
    insertInMatrix(matrix, 1, 3);

    insertInMatrix(matrix, 2, 2);
    
    insertInMatrix(matrix, 3, 1);
    insertInMatrix(matrix, 3, 3);

    insertInMatrix(matrix, 4, 0);
    insertInMatrix(matrix, 4, 4);

    printMatrix(matrix);
    return 0;
}