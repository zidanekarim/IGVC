#include <stdlib.h>
#include <stddef.h>

typedef struct node_s {
    void *data;
    struct node_s *next;
    struct node_s *prev;
} node_t;

typedef struct list_s {
    node_t *head;
    node_t *tail;
    size_t size;
}  list_t;



// functions to implement
list_t *list_alloc(void) {
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void list_free(list_t *list, void (*free_data)(void *data)) {
    node_t* walker = NULL;
    if (list == NULL) return -1;

    while (list->head != NULL && list->size > 0) {
        walker = list->head;
        list->head = list->head->next;
        free_data(walker->data);
        free(walker);
    }
    free(list);
}

void free_data(void* data) {
    void** array = (void**)data;
    for (int i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(data);
}


int list_prepend(list_t *list, int *val) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) return -1;
    
    new->data = val;
    new->next = list->head; // NULL if empty
    if (list->size != 0 && list->tail != NULL) {
        list->tail->next = new;
        new->prev = list->tail; 
    }
    else {
        new->prev = NULL;
        list->tail = new;
    }

    list->head = new;


    list->size++;
    return 0;
    }


int list_append(list_t *list, int* val) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) return -1;

    new->data = val;
    new->next = list->head; // NULL if empty
    if (list->size != 0) {
        list->tail->next = new;
        new->prev = list->tail;
    }
    else {
        new->prev = NULL;
        list->head = new;
    }

    list->tail = new; 
    
    list->size++;
    return 0;
}

int list_insert(list_t *list, int *val, size_t pos) {
    if (pos == 0) {
        return list_prepend(list, val);
    }

    if (pos == list->size) {
        return list_append(list, val);;
    }

    if (pos > list->size) return -1;

    node_t* new = malloc(sizeof(node_t));
    if (new == NULL) return -1;

    new->data = val;

    // node_t* walker = list->head;
    // int tracker = 0;
    // while (walker != NULL) {
    //     if (tracker+1 == pos) { // if the current node should point to inserted value
    //         new->next = walker->next;
    //         walker->next = new;
    //         new->prev = walker;
    //         walker->next->prev = new; 
    //         list->size++;
    //         return 0;
    //     }

    //     walker = walker->next;
    //     tracker++;

    // }

    node_t* walker;
    if (pos < list->size / 2) {
        walker = list->head;
        for (size_t i = 0; i < pos; i++) {
            walker = walker->next;
        }
    } else {
        walker = list->tail;
        for (size_t i = list->size - 1; i > pos; i--) {
            walker = walker->prev;
        }
    }

    if (walker != NULL) {
        new->next = walker->next;
        walker->next = new;
        new->prev = walker;
        walker->next->prev = new; 
        list->size++;
        return 0;
    }

    return -1;
}

int list_rm(list_t *list, int *val, size_t pos) {
    
    if (pos >= list->size) return -1;
    node_t* walker;
    // while (walker != NULL) {
    //     if (tracker+1 == pos && walker->next != NULL) { 
    //         val = walker->next->data;
    //         node_t* remove = walker->next;
    //         walker->next = walker->next->next;
    //         walker->next->prev = walker;
    //         free(remove);
    //         return 0;
    //     }
    //     walker = walker->next;
    //     tracker++;
    // }
    if (pos < list->size / 2) {
        walker = list->head;
        for (size_t i = 0; i < pos; i++) {
            walker = walker->next;
        }
    } else {
        walker = list->tail;
        for (size_t i = list->size - 1; i > pos; i--) {
            walker = walker->prev;
        }
    }

    if (walker != NULL) {
        val = walker->data;
        walker->prev->next = walker->next;
        walker->next->prev = walker->prev;
        free(walker);
        return 0;
    }

    return -1;
}




int list_set(list_t *list, int* val, size_t pos) {


    if (pos >= list->size && pos != 0) return -1;
    if (pos == 0 && list->size == 0) {
        node_t *new = malloc(sizeof(node_t));
        if (new == NULL) return -1;
        new->data = val;
        new->next = NULL;
        new->prev = NULL;
        list->head = new;
        list->tail = new;
        return 0;
    }

    node_t* walker;
    if (pos < list->size / 2) {
        walker = list->head;
        for (size_t i = 0; i < pos; i++) {
            walker = walker->next;
        }
    } else {
        walker = list->tail;
        for (size_t i = list->size - 1; i > pos; i--) {
            walker = walker->prev;
        }
    }

    if (walker != NULL) {
        walker->data = val;
        return 0;
    }
    return -1;
}


int list_get(list_t *list, int *val, size_t pos) {
    if (pos >= list->size) return -1;

    node_t* walker;
    if (pos < list->size / 2) {
        walker = list->head;
        for (size_t i = 0; i < pos; i++) {
            walker = walker->next;
        }
    } else {
        walker = list->tail;
        for (size_t i = list->size - 1; i > pos; i--) {
            walker = walker->prev;
        }
    }

    if (walker != NULL) {
        val = walker->data;
        return 0;
    }
    return -1;
}


