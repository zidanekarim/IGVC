#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

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
        if (walker->next != NULL) {
            list->head = walker->next;
            list->head->prev = NULL;
        }
        else {
            list->head = NULL;
            list->tail = NULL;
        }
        free_data(walker->data);
        free(walker);
        list->size--;

    }
    free(list);
}

void free_data(void* data) {
    void** array = (void**)data;
    for (int i = 0; i<3; i++) {
        free(array[i]);
    }
    free(data);
}


int list_prepend(list_t *list, int **val) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) return -1;
    new->data = val;
    if (list->size == 0) {
        list->head = new;
        list->tail = new;
        new->next = NULL;
        new->prev = NULL;
        list->size++;
        return 0;
    }
    else {
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
        new->prev = NULL;
        list->size++;
        return 0;
    }
    
    return -1;
    
}

int list_append(list_t *list, int** val) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) return -1;
    new->data = val;
    if (list->size == 0) {
        list->tail = new;
        list->head = new;
        new->next = NULL;
        new->prev = NULL;
        list->size++;
        return 0;
    }
    else {
        new->prev = list->tail;
        list->tail->next = new;
        list->tail = new;
        new->next = NULL;
        list->size++;
        return 0;
    }
    
    return -1;
    
}

int list_insert(list_t *list, int **val, size_t pos) {
    if (pos > list->size) return -1;
    if (pos == 0) list_append(list, val);
    if (pos == list->size) list_append(list, val);


    node_t *new = malloc(sizeof(node_t));


    if (new == NULL) return -1;
    new->data = val;
    node_t* walker;
    if (pos < list->size / 2) {
        walker = list->head;
        for (size_t i = 0; i < pos; i++) {
            walker = walker->next;
        }
    } 
    else {
        walker = list->tail;
        for (size_t i = list->size - 1; i > pos; i--) {
            walker = walker->prev;
        }
    }

    if (walker != NULL) {
        new->next = walker;
        new->prev = walker->prev;
        walker->prev->next = new;
        walker->prev = new;
        list->size++;
        return 0;
    
    }
    return -1;
}

int list_rm(list_t *list, int **val, size_t pos) {
    if (pos >= list->size) return -1;
    node_t* walker;
    if (pos < list->size / 2) {
        walker = list->head;
        for (size_t i = 0; i < pos; i++) {
            walker = walker->next;
            //printf("Walker: %d\n", walker->data);
        }
    } 
    else {
        walker = list->tail;
        for (size_t i = list->size - 1; i > pos; i--) {
            walker = walker->prev;
            //printf("Walker: %d\n", walker->data);
        }
    }

    if (walker != NULL) {
        if (walker->prev != NULL) {
            walker->prev->next = walker->next;
        }
        else {
            list->head = walker->next;
        }
        if (walker->next != NULL) {
            walker->next->prev = walker->prev;
        }
        else {
            list->tail = walker->prev;
        }
        val = walker->data;
        list->size--;
        return 0;
    }
    return -1;
    
}




int list_set(list_t *list, int** val, size_t pos) {
    if (pos >= list->size) return -1;
    node_t* walker;
    if (pos < list->size / 2) {
        walker = list->head;
        for (size_t i = 0; i < pos; i++) {
            walker = walker->next;
        }
    } 
    else {
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


int list_get(list_t *list, int **val, size_t pos) {
    if (pos >= list->size) return -1;
    node_t* walker;
    if (pos < list->size / 2) {
        walker = list->head;
        for (size_t i = 0; i < pos; i++) {
            walker = walker->next;
            //printf("Walker: %d\n", walker->data);
        }
    } 
    else {
        walker = list->tail;
        for (size_t i = list->size - 1; i > pos; i--) {
            walker = walker->prev;
            //printf("Walker: %d\n", walker->data);
        }
    }

    if (walker != NULL) {
        *val = (int **)walker->data;
        return 0;
    }
    return -1;
}


