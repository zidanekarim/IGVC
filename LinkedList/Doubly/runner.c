#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include <time.h>
#include <stdlib.h>




int** allocate_matrix() {
    int **matrix = malloc(3 * sizeof(int *));
    for (int i = 0; i < 3; i++) {
        matrix[i] = malloc(3 * sizeof(int));
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
    return matrix;
}



int main() {
    // Create a new list
    srand(time(NULL));   
    list_t *list = list_alloc();
    printf("List allocated\n");
    printf("List size: %d\n", list->size);

    int** matrix = allocate_matrix();
    list_prepend(list, matrix);

    printf("List size: %d\n", list->size);
    int** val = list->head->data;
    printf("Matrix: %d %d %d\n", val[0][0], val[0][1], val[0][2]);
    printf("Matrix: %d %d %d\n", val[1][0], val[1][1], val[1][2]);
    printf("Matrix: %d %d %d\n", val[2][0], val[2][1], val[2][2]);


    list_free(list, free_data);
    printf("List freed\n");


    



    return 0;
}