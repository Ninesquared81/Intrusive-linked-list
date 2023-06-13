#include <stdlib.h>
#include <stdio.h>

#include "list.h"

void init_list(struct List *list, Comparator compare, Printer print) {
    list->head = NULL;
    list->tail = &list->head;
    list->length = 0;
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
    ++list->length;
    return item;
}

struct ListNode *remove_index(struct List *list, int index) {
    struct ListNode **node_ptr = &list->head;
    if (*node_ptr == NULL) return NULL;
    
    while (index > 0 && (*node_ptr)->next != NULL) {
        node_ptr = &(*node_ptr)->next;
        --index;
    }

    if (index > 0) return NULL;  // Index out of range.
    
    struct ListNode *item = *node_ptr;
    if (item->next == NULL) {
        // Item is at end of list.
        list->tail = node_ptr;
    }
    
    *node_ptr = item->next;
    item->next = NULL;
    --list->length;

    return item;
}

void push_head(struct List *list, struct ListNode *item) {
    item->next = list->head;
    list->head = item;
    ++list->length;
}

void push_tail(struct List *list, struct ListNode *item) {
    item->next = NULL;
    *list->tail = item;
    list->tail = &item->next;
    ++list->length;
}

struct ListNode *pop_head(struct List *list) {
    if (list->head == NULL) return NULL;

    struct ListNode *node = list->head;
    list->head = node->next;
    node->next = NULL;
    --list->length;
    return node;
}

struct ListNode *pop_tail(struct List *list) {
    return remove_index(list, list->length - 1);
}

struct ListNode *insert_sublist(struct List *list, int start_index, struct List *sublist) {
    struct ListNode **node_ptr = &list->head;
    while (index > 0 && *node_ptr != NULL) {
        node_ptr = &(*node_ptr)->next;
        --index;
    }
    struct ListNode *next = *node_ptr;
    *node_ptr = sublist->head;
    list->length += sublist->length;
    *sublist->tail = next;

    return next;
}

struct List remove_sublist(struct List *list, int start_index, int length) {
    struct List sublist;
    init_list(&sublist, list->compare, list->print);
    struct ListNode **node_ptr = &list->head;
    while (start_index > 0 && node_ptr != NULL) {
        node_ptr = &(*node_ptr)->next;
        --start_index;
    }
    sublist->head = *node_ptr;
    struct ListNode **next_ptr = node_ptr;
    while (length > 0 && node_ptr != NULL) {
        node_ptr = &(*node_ptr)->next;
        // Note: these are done as increments/decrements rather than additions/subtractions
        // so that a shorter list is handled correctly.
        --length;
        ++sublist->length;
        --list->length;
    }
    sublist->tail = node_ptr;
    *next_ptr = *node_ptr;
    return sublist;
}

void concatenate_lists(struct List *a, struct List *b) {
    *a->tail = b->head;
    a->tail = b->tail;
    a->length += b->length;
}

struct List *divide_list(struct List *list, int n, struct List sublists[n]) {
    if (n <= 0) {
        // n must be positive.
        return NULL;
    }
    const int length = list->length / n;
    struct ListNode **node_ptr = &list->head;
    for (struct ListNode *sublist = sublists; sublist < sublists + n; ++sublist ) {
        init_list(sublist, list->compare, list->print);
        sublist->head = *node_ptr;
        for (int i = 0; i < length && *node_ptr != NULL; ++i) {
            node_ptr = &(*node_ptr)->next;
        }
        sublist->tail = node_ptr;
        sublist->length = length;
    }
    // Trailing items (if any) go into the last sublist.
    sublist[n-1]->tail = list->tail;
    sublist[n-1]->length += list->length % n;
    return sublists;
}

void print_list(struct List *list)  {
    for (struct ListNode **node_ptr = &list->head;
        *node_ptr != NULL; 
        node_ptr = &(*node_ptr)->next) {
            printf("[ ");
            list->print(*node_ptr);
            printf(" ] -> ");
        }
    printf("NULL");
}
