#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int Id;
typedef struct aux {
    Id id;
    struct aux *left, *right;
    int h;
} Node;

typedef Node* POINTER;

POINTER initTree() {
    return NULL;
}

POINTER find(POINTER root, Id id) {
    if (root == NULL || root->id == id) return root;
    if (id > root->id) return find(root->right, id);
    else return find(root->left, id);
}

int countLRRi(POINTER root) {
    // Left - Root - Right
    if (root == NULL) return 0;
    //printf("%i ", root->id);
    return countLRRi(root->left) 
        + 1
        + countLRRi(root->right);
}

void print(POINTER root) {
    if (root == NULL) return;
    printf("%i", root->id);
    printf("(");
    print(root->left);
    print(root->right);
    printf(")");
}

POINTER findWithFather(POINTER root, Id id, POINTER *father) {
    POINTER current = root;
    *father = NULL;
    while (current != NULL) {
        if(current->id == id) return current;
        *father = current;
        if (id > current->id) current = current->right;
        else current = current->left;
    }
    return NULL;
}

POINTER removeNode(POINTER root, Id id) {
    POINTER father, node, upFather, up;
    node = findWithFather(root, id, &father);
    if (node == NULL) return root; // Doesn't exist
    // Node has only the right child
    if (!node->left && node->right) {
        up = node->right; // up right
    } 
    // Node has only the left child
    else if (node->left && !node->right) {
        up = node->left; // up left
    } 
    // Node has both child
    else {
        // In the left subtree find the far right
        // child (up) and his "father" (upFather)
        upFather = node;
        up = node->left;
        while(up->right) {
            upFather = up;
            up = up->right;
        }
        if(upFather != node) {
            // (far right) child will be the left of previous (far right) 
            // whereas in the right is NULL (line 81)
            upFather->right = up->left;
            // The previous (far right) or current up, will be the father 
            // of the left subtree
            up->left = node->left;
        }
        // Always I'll set the right child of up 
        // to right subtree
        up->right = node->right;
    }
    // If the node (to remove) is the root, just return up - the new root
    if(!father) {
        free(node); return up;
    }
    // Refresh the father pointer
    if (id < father->id) father->left = up;
    else father->right = up;
    free(node);
    return root;
}

POINTER newNode(Id id) {
    POINTER node = (Node*) malloc(sizeof(Node));
    node->id = id;
    node->left = NULL;
    node->right = NULL;
    node->h = 0;
    return node;
}

int heighOf(POINTER root) {
    if (!root) return -1;
    return root->h;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

POINTER rotateL(POINTER root) {
    POINTER aux = root->right;
    root->right = aux->left;
    aux->left = root;
    // Refreshing height
    root->h = max(heighOf(root->right), heighOf(root->left)) + 1;
    aux->h = max(heighOf(aux->right), root->h) + 1;
    return aux;
}

POINTER rotateR(POINTER root) {
    POINTER aux = root->left;
    root->left = aux->right;
    aux->right = root;
    // Refreshing height
    root->h = max(heighOf(root->right), heighOf(root->left)) + 1;
    aux->h = max(heighOf(aux->left), root->h) + 1;
    return aux;
}

POINTER rotateLR(POINTER root) {
    root->left = rotateL(root->left);
    return rotateR(root);
}

POINTER rotateRL(POINTER root) { 
    root->right = rotateR(root->right);
    return rotateL(root);
}

POINTER insert(POINTER root, Id id) {
    if (!root) return newNode(id);
    if (id < root->id) {
        root->left = insert(root->left, id);
        if ((heighOf(root->left) - heighOf(root->right)) == 2) {
            root = (id < root->left->id)
                ? rotateR(root)
                : rotateLR(root);
        }
    } 
    else if (id > root->id) {
        root->right = insert(root->right, id);
        if ((heighOf(root->right) - heighOf(root->left)) == 2) {
            root = (id > root->right->id)
                ? rotateL(root)
                : rotateRL(root); 
        }
    }
    root->h = max(heighOf(root->left), heighOf(root->right)) + 1;
    return root;
}

int main() {

    POINTER root = initTree(); 
    root = insert(root, 15);

    root = insert(root, 8);
    root = insert(root, 2);
    root = insert(root, 12);
    root = insert(root, 23);
    root = insert(root, 20);
    root = insert(root, 30);

    print(root);

}