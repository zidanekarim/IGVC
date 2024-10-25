#include <stdlib.h>
#include <stddef.h>

typedef struct node_s {
    int data;
    struct node_s *next;
} node_t;

typedef struct list_s {
    node_t *head;
    node_t *tail;
    size_t size;
}  list_t;



// functions to implement
list_t *list_alloc(void) {
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void list_free(list_t *list) {
    node_t* walker = NULL;
    while (list->head != NULL) {
        walker = list->head;
        list->head = list->head->next;
        free(walker);
    }
    free(list);
}


int list_prepend(list_t *list, int val) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) return -1;
    
    new->data = val;
    new->next = list->head;
    list->head = new;
    list->size++;
    if (list->head == new && list->head->data != NULL) return 0;
    return -1;
    }


int list_append(list_t *list, int val) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) return -1;
    new->next = NULL;
    new->data = val;
    list->tail->next = new;
    list->size++;
    if (list->tail == new && list->head->data != NULL) return 0;
    return -1;
    }

int list_insert(list_t *list, int val, size_t pos) {
    node_t* new = malloc(sizeof(node_t));
    new->data = val;

    node_t* walker = list->head;
    int tracker = 0;
    while (walker != NULL) {
        if (tracker+1 == pos) { // if the current node should point to inserted value
            new->next = walker->next;
            walker->next = new;
            list->size++;
            return 0;
            
        }
        walker = walker->next;
        tracker++;

    }
    return -1;
}

int list_rm(list_t *list, int *val, size_t pos) {
    node_t* walker = list->head;
    int tracker = 0;
    while (walker != NULL) {
        if (tracker+1 == pos) { 
            *val = walker->next->data;
            walker->next = walker->next->next;
            return 0;
        }
        walker = walker->next;
        tracker++;
    }
    return -1;
}




int list_set(list_t *list, int val, size_t pos) {
    node_t* walker = list->head;
    int tracker = 0;
    while (walker != NULL) {
        if (tracker == pos) { 
            list->head->data = val;
            return 0;
        }
        walker = walker->next;
        tracker++;
    }
    return -1;
}


int list_get(list_t *list, int *val, size_t pos) {
    node_t* walker = list->head;
    int tracker = 0;
    while (walker != NULL) {
        if (tracker == pos) { 
            *val = list->head->data;
            return 0;
        }
        walker = walker->next;
        tracker++;
    }
    return -1;
}




