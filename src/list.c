#include <stdlib.h>
#include <stdio.h>

#include "list.h"

void init_list(struct List *list, Comparator compare, Printer print) {
    list->head = NULL;
    list->tail = &list->head;
    list->compare = compare;
    list->print = print;
}

struct ListNode *get_item(struct List *list, int index) {
    struct ListNode **node_ptr = &list->head;
    while (*node_ptr != NULL && index > 0) {
        node_ptr = &(*node_ptr)->next;
        --index;
    }
    return *node_ptr;
}

int find(struct List *list, struct ListNode *item) {
    struct ListNode **node_ptr = &list->head;
    int index = 0;
    while (*node_ptr != NULL && list->compare(*node_ptr, item) != 0) {
        node_ptr = &(*node_ptr)->next;
        ++index;
    }
    if (*node_ptr == NULL) return -1;
    return index;
}

struct ListNode *insert_index(struct List *list, int index, struct ListNode *item) {
    struct ListNode **node_ptr = &list->head;
    while (*node_ptr != NULL && index > 0) {
        node_ptr = &(*node_ptr)->next;
        --index;
    }
    if (index > 0) {
        // Could not find index to insert at.
        return NULL;
    }
    item->next = *node_ptr;
    *node_ptr = item;
    if (item->next == NULL) {
        list->tail = &item->next;
    }
    return item;
}

struct ListNode *pop_index(struct List *list, int index) {
    struct ListNode **node_ptr = &list->head;
    while (*node_ptr != NULL && index > 0) {
        node_ptr = &(*node_ptr)->next;
        --index;
    }
    struct ListNode *item = *node_ptr;
    if (item != NULL) {
        *node_ptr = item->next;
        item->next = NULL;
    }
    return item;
}

void print_list(struct List *list)  {
    for (struct ListNode **node_ptr; *node_ptr != NULL; 
        node_ptr = &(*node_ptr)->next) {
            printf("[ ");
            list->print(*node_ptr);
            printf(" ] -> ");
        }
    printf("NULL");
}
