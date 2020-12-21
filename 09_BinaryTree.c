#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int Id;
typedef struct aux {
    Id id;
    struct aux *left, *right;
} Node;

typedef Node* POINTER;

POINTER initTree() {
    return NULL;
}

POINTER insert(POINTER root, POINTER node) {
    if (root == NULL) return node;
    if (node->id > root->id) 
        root->right = insert(root->right, node);
    if (node->id < root->id) 
        root->left = insert(root->left, node);
    return root;
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
    return node;
}

int main() {

    POINTER root = initTree(); 
    root = insert(root, newNode(15));

    root = insert(root, newNode(8));
    root = insert(root, newNode(2));
    root = insert(root, newNode(12));
    root = insert(root, newNode(23));
    root = insert(root, newNode(20));
    root = insert(root, newNode(30));

    print(root);

}