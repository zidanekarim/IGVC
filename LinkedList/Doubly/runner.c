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


    int **matrix2 = allocate_matrix();
    list_t *list2 = list_alloc();
    list_prepend(list2, matrix2);
    list_append(list2, allocate_matrix());

    printf("List size: %d\n", list2->size);
    int** val2 = list2->head->data;\
    printf("Matrix1: %d %d %d\n", val2[0][0], val2[0][1], val2[0][2]);
    printf("Matrix1: %d %d %d\n", val2[1][0], val2[1][1], val2[1][2]);
    printf("Matrix1: %d %d %d\n", val2[2][0], val2[2][1], val2[2][2]);

    printf("List size: %d\n", list2->size);
    int** val3 = list2->tail->data;
    printf("Matrix2: %d %d %d\n", val3[0][0], val3[0][1], val3[0][2]);
    printf("Matrix2: %d %d %d\n", val3[1][0], val3[1][1], val3[1][2]);
    printf("Matrix2: %d %d %d\n", val3[2][0], val3[2][1], val3[2][2]);

    list_free(list2, free_data);
    printf("List freed\n");
    




    return 0;
}