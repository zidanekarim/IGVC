#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

void list_print(list_t* list) {
    char* buffer;
    char val[1024];
    node_t* walker = list->head;
    while (walker != NULL) {
        sprintf(val, "%d-->", walker->data);
        strcat(buffer, val);
    }
    printf("%s", buffer);
}

int main() {
    list_t *list = list_alloc();
    
    printf("List allocated\n");

    list_free(list);
    printf("List freed\n");
    

    return 0;
}
