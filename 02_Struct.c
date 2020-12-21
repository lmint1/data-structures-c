#include <stdlib.h>
#include <stdio.h>

// Definindo constantes do código
#define alturaMaxima 225

// Definindo uma struct
typedef struct {
    int peso;
    int altura;
} PesoAltura; // Alias para a struct

// Pode ser utilizado como um typealias:
typedef int NUMERO;

int main() {
    
    // Exemplo de struct
    // PesoAltura pesoAltura;
    // printf("Digite a altura: ");
    // scanf("%i", &pesoAltura.altura);
    // printf("Digite a peso: ");
    // scanf("%i", &pesoAltura.peso);
    // printf("Altura: %i, peso %i", pesoAltura.altura, pesoAltura.peso);

    // Ponteiro Y aponta para o endereço de X
    int x = 10;
    int* y = &x;
    *y = 30;
    printf("X = %i \n", x);    

    // Alloca para o ponteiro A
    int* a = malloc(sizeof(int));
    *a = 20;
    // Tamanho do Int
    int b = sizeof(int);
    printf("A = %i, B = %i \n", *a, b);

    // Exemplo Alocação dinamica
    // PesoAltura* pesoAltura2 = (PesoAltura*) malloc(sizeof(PesoAltura));
    // printf("Digite a altura: ");
    // scanf("%i", &pesoAltura2->altura);
    // printf("Digite a peso: ");
    // scanf("%i", &pesoAltura2->peso);
    // printf("Altura: %i, peso %i", pesoAltura2->altura, pesoAltura2->peso);
    

    // Defining an array dynamically
    // Pointer of array
    int *array;
    int size;
    printf("Digite o tamanho do array: ");
    scanf("%i", &size);
    array = (int*) malloc(size * sizeof(int));
    
    for(int i = 0; i <size; i++) {
        array[i] = i * 2;
    }
    for(int i = 0; i <size; i++) {
        printf("> %i\n", array[i]);
    }

    return 0;
}

