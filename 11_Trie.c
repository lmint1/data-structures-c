#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N_ALPHABET 26

typedef int Id;

typedef struct aux {
    struct aux *sons [N_ALPHABET];
    bool end;
} Node;

typedef Node* POINTER;

POINTER newNode() {
    POINTER node = (POINTER) malloc(sizeof(Node));
    if (node == NULL) return node;
    node->end = false;
    for (int i = 0; i < N_ALPHABET; i++) { 
        node->sons[i] = NULL; 
    }
    return node;
}

POINTER init() {
    return newNode();
}

int toIndex(char c) {
    return (int)c - (int) 'a';
}

void insert(POINTER root, char *str) {
    POINTER node = root;
    int i;
    // Interate each level, where the maxi is string's size
    for (int level = 0; level < strlen(str); level++) {
        i = toIndex(str[level]);
        printf("%c", str[level]);
        // Contains next char index ?
        if (node->sons[i] == NULL) { 
            node->sons[i] = newNode(); 
        }
        node = node->sons[i];
    }
    printf(" - true\n");
    node->end = true;
}

bool contains(POINTER root, char *str) {
    int i;
    POINTER node = root;
    for (int level = 0; level < strlen(str); level++) {
        i = toIndex(str[level]);
        if (node->sons[i] == NULL) return false;
        node = node->sons[i];
    }
    return node->end;
}

int main() {
    POINTER root = init();
    insert(root, "merda");
    // insert(root, "porra");

    printf("> %d\n", contains(root, "poxa"));
    printf("> %d\n", contains(root, "pqp"));
    printf("> %d\n", contains(root, "porra"));
    printf("> %d\n", contains(root, "merda"));
}