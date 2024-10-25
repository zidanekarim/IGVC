#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

int main() {
    list_t *list = list_alloc();
    if (!list) {
        printf("Failed to allocate memory for the list\n");
        return -1;
    }

    // Append values to the list
    if (list_append(list, 10) == 0)
        printf("Appended 10 to the list\n");
    if (list_append(list, 20) == 0)
        printf("Appended 20 to the list\n");

    // Prepend values to the list
    if (list_prepend(list, 5) == 0)
        printf("Prepended 5 to the list\n");

    // Get and print values from specific positions
    int val;
    if (list_get(list, &val, 1) == 0)
        printf("Value at position 1: %d\n", val);

    // Set a value at a specific position
    if (list_set(list, 15, 1) == 0)
        printf("Set value at position 1 to 15\n");

    if (list_get(list, &val, 1) == 0)
        printf("Value at position 1 after set: %d\n", val);

    // Insert a value at a specific position
    if (list_insert(list, 12, 2) == 0)
        printf("Inserted 12 at position 2\n");

    // Remove a value at a specific position
    if (list_rm(list, &val, 2) == 0)
        printf("Removed value at position 2: %d\n", val);

    // Print the list's current values
    printf("List values: ");
    node_t *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Free the list
    list_free(list);
    printf("Freed the list\n");

    return 0;
}