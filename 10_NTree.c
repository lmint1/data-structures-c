#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int Id;
typedef struct aux
{
    Id id;
    struct aux *son;
    struct aux *brother;
} Node;

typedef Node* POINTER;

POINTER newNode(Id id) {
    POINTER node = (POINTER) malloc(sizeof(Node));
    node->id = id;
    node->son = NULL;
    node->brother = NULL;
    return node;
}

POINTER findById(POINTER root, Id id) {
    if (root == NULL) return NULL;
    if (root->id == id) return root;
    POINTER son = root->son;
    while (son != NULL) {
        POINTER res = findById(son, id);
        if (res) return res;
        son = son->brother;
    }
    return NULL;
}

POINTER init(Id id) {
    return newNode(id);
}

bool insert(POINTER root, Id id, Id fatherId) {
    POINTER father = findById(root, fatherId);
    if (!father) return false;
    POINTER newSon = newNode(id);
    POINTER son = father->son;
    if (son == NULL) father->son = newSon;
    else {
        while (son->brother != NULL) son = son->brother;
        son->brother = newSon;
    }
    return true;
}

void printTree(POINTER root) {
    if (root == NULL) return;
    printf("%i(", root->id);
    POINTER p = root->son;
    while (p)
    {
        printTree(p);
        p = p->brother;
    }
    printf(")");
}

int main() {

    POINTER root = init(8);
    insert(root, 15, 8);
    insert(root, 23, 8);
    insert(root, 2, 8);
    
    insert(root, 20, 15);
    insert(root, 10, 15);
    insert(root, 28, 15);
    
    insert(root, 36, 2);
    insert(root, 7, 2);

    printTree(root);
}