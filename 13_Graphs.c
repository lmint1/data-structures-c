#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int Id;
typedef int Weight;

typedef struct aux {
    Id verticeId;
    Weight weight;
    struct aux *next;
} Adjacency; //Adjacencia

typedef struct { 
    Id verticeId;
    Adjacency *head; 
} Vertice; // Vertice

typedef struct {
    int vertCount, edgeCount;
    Vertice *edjes;
} Graph; // Grafo

Adjacency* newAdjacency(Id id, Weight w) {
    Adjacency *e = (Adjacency*) malloc(sizeof(Adjacency));
    e->verticeId = id;
    e->next = NULL;
    e->weight = w;
    return e;
}

Graph* newGraph(int size) {
    Graph *g = (Graph*) malloc(sizeof(Graph));
    g->vertCount = size;
    g->edgeCount = 0;
    // Array of Vertice 
    g->edjes = (Vertice*) malloc(size * sizeof(Vertice));
    for (int i = 0; i < size; i++) {
        g->edjes[i].head = NULL;
    }
    return g;
}

bool newEdge(Graph *graph, int start, int end, Weight weight) {
    if (graph == NULL) return false;
    if ((start<0) || (start >= graph->vertCount)) return false;
    if ((end<0) || (end >= graph->vertCount)) return false;
    Adjacency *adj = newAdjacency(end, weight);
    adj->next = graph->edjes[start].head;
    graph->edjes[start].head = adj;
    graph->edgeCount++;
    return true;
}

void printGraph(Graph *graph) {
    printf("Vértices: %d. Arestas: %i.\n", 
        graph->vertCount, graph->edgeCount);
    for (int i = 0; i < graph->vertCount; i++) {
        printf("v%d: ", i);
        Adjacency *adj = graph->edjes[i].head;
        while (adj != NULL) {
            printf("v%d(%d)", adj->verticeId, adj->weight);
            adj = adj->next;
        }
        printf("\n");
    }
}

int main() {
    Graph *gr = newGraph(5);
    
    newEdge(gr, 0, 1, 2);
    newEdge(gr, 1, 2, 4);
    newEdge(gr, 2, 0, 12);
    newEdge(gr, 2, 4, 40);
    newEdge(gr, 3, 1, 3);
    newEdge(gr, 4, 3, 8);

    printGraph(gr);
}