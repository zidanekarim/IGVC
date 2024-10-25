#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

int main() {
    list_t *list = list_alloc();
    if (!list) {
        printf("Failed to allocate memory for the list\n");
        return -1;
    }
    else printf("List allocated\n");

    list_free(list);
    printf("List freed\n");
    list = list_alloc();
    if (!list) {
        printf("Failed to allocate memory for the list\n");
        return -1;
    }
    else printf("List allocated\n");

    printf("List prepending...")



    return 0;
}