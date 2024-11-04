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
    if (val == NULL) return -1;

    if (list->size == 0) {
        list->head = new;
        return 0;
    }

    new->next = list->head; // NULL if empty
    list->head->prev = new;
    if (list->size != 0 && list->tail != NULL) {
        list->tail->next = new;
        new->prev = list->tail; 
        new->next = list->head;
    }
    else {
        new->prev = NULL;
    }

    list->head = new;


    list->size++;
    return 0;
}


int list_append(list_t *list, int** val) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) return -1;

    new->data = val;
    if (val == NULL) return -1;
    if (list->size == 0) {
        list->tail = new;
        return 0;
    }
    new->next = list->head; // NULL if empty
    if (list->size != 0) {
        list->tail->next = new;
        new->prev = list->tail;
    }
    else {
        new->prev = NULL;
        list->head->prev = new;
    }

    list->tail = new; 
    
    list->size++;
    return 0;
}

int list_insert(list_t *list, int **val, size_t pos) {
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
        new->next = walker->next;
        walker->next = new;
        new->prev = walker;
        walker->next->prev = new; 
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
        }
    } 
    else {
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
        list->size--;
        return 0;
    }

    return -1;
}




int list_set(list_t *list, int** val, size_t pos) {


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
        }
    } 
    else {
        walker = list->tail;
        for (size_t i = list->size - 1; i > pos; i--) {
            walker = walker->prev;
        }
    }

    if (walker != NULL) {
        val = walker->data;
        printf("Matrix4: %d %d %d\n", val[0][0], val[0][1], val[0][2]);
        printf("Matrix4: %d %d %d\n", val[1][0], val[1][1], val[1][2]);
        printf("Matrix4: %d %d %d\n", val[2][0], val[2][1], val[2][2]);
        return 0;
    }
    return -1;
}


