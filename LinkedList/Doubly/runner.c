#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"



int main() {
    list_t *list = list_alloc();
    
    printf("List allocated\n");

    list_free(list);
    printf("List freed\n");
    

    return 0;
}
