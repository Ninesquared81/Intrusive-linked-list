#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void init_list(struct List *list, Comparator compare, Printer print) {
    list->head = NULL;
    list->tail = &list->head;
    list->length = 0;
    list->compare = compare;
    list->print = print;
}

void init_sublist(const struct List *super, struct List *sub) {
    init_list(sub, super->compare, super->print);
}

int index_of(const struct List *list, struct ListNode *const *where) {
    struct ListNode *const *node_ptr = &list->head;
    int index = 0;
    while (node_ptr != where && *node_ptr != NULL) {
        node_ptr = &(*node_ptr)->next;
        ++index;
    }
    if (node_ptr != where) return -1;
    return index;
}

struct ListNode **where_index(const struct List *list, int index) {
    struct ListNode *const *node_ptr = &list->head;
    while(index > 0 && *node_ptr != NULL) {
        node_ptr = &(*node_ptr)->next;
        --index;
    }
    if (index != 0) return NULL;
    return (struct ListNode**)node_ptr;
}

struct ListNode *get_item(const struct List *list, int index) {
    struct ListNode **node_ptr = where_index(list, index);
    if (node_ptr == NULL) return NULL;
    return *node_ptr;
}

struct ListNode **find(const struct List *list, const struct ListNode *item) {
    struct ListNode *const *node_ptr = &list->head;
    while (*node_ptr != NULL && list->compare(*node_ptr, item) != 0) {
        node_ptr = &(*node_ptr)->next;
    }
    return (struct ListNode **)node_ptr;
}

struct ListNode **find_inorder(const struct List *list, const struct ListNode *item) {
    struct ListNode *const *node_ptr = &list->head;
    while (*node_ptr != NULL && list->compare(*node_ptr, item) < 0) {
        node_ptr = &(*node_ptr)->next;
    }
    return (struct ListNode **)node_ptr;
}

struct ListNode **find_inorder_reverse(const struct List *list, const struct ListNode *item) {
    struct ListNode *const *node_ptr = &list->head;
    while (*node_ptr != NULL && list->compare(*node_ptr, item) > 0) {
        node_ptr = &(*node_ptr)->next;
    }
    return (struct ListNode **)node_ptr;
}

struct ListNode *insert_at(struct List *list, struct ListNode **where, struct ListNode *item) {
    item->next = *where;
    if (where == list->tail) {
        list->tail = &item->next;
    }
    *where = item;
    ++list->length;
    return item;
}

struct ListNode *remove_at(struct List *list, struct ListNode **where) {
    if (where == list->tail) return NULL;

    struct ListNode *item = *where;
    if (&item->next == list->tail) {
        list->tail = where;
    }
    *where = item->next;
    item->next = NULL;
    --list->length;

    return item;
}

struct ListNode *insert_inorder(struct List *list, struct ListNode *item) {
    struct ListNode **where = find_inorder(list, item);
    return insert_at(list, where, item);
}

struct ListNode *insert_inorder_reverse(struct List *list, struct ListNode *item) {
    struct ListNode **where = find_inorder_reverse(list, item);
    return insert_at(list, where, item);
}

struct ListNode *remove_inorder(struct List *list, struct ListNode *item) {
    struct ListNode **where = find_inorder(list, item);
    if (list->compare(*where, item) != 0) {
        // Item was not in list.
        return NULL;
    }
    return remove_at(list, where);
}

struct ListNode *remove_inorder_reverse(struct List *list, struct ListNode *item) {
    struct ListNode **where = find_inorder_reverse(list, item);
    if (list->compare(*where, item) != 0) {
        return NULL;
    }
    return remove_at(list, where);
}

struct ListNode *insert_index(struct List *list, int index, struct ListNode *item) {
    struct ListNode **where = where_index(list, index);
    if (where == NULL) return NULL;

    return insert_at(list, where, item);
}

struct ListNode *remove_index(struct List *list, int index) {
    struct ListNode **where = where_index(list, index);
    if (where == NULL) return NULL;

    return remove_at(list, where);
}

struct ListNode *remove_item(struct List *list, struct ListNode *item) {
    struct ListNode **where = find(list, item);
    return remove_at(list, where);
}

void push_head(struct List *list, struct ListNode *item) {
    insert_at(list, &list->head, item);
}

void push_tail(struct List *list, struct ListNode *item) {
    insert_at(list, list->tail, item);
}

struct ListNode *pop_head(struct List *list) {
    if (list->length == 0) return NULL;

    return remove_at(list, &list->head);
}

struct ListNode *pop_tail(struct List *list) {
    return remove_index(list, list->length - 1);
}

struct ListNode *insert_sublist(struct List *list, struct ListNode **start, struct List *sublist) {
    if (sublist->length == 0) return NULL;

    struct ListNode *next = *start;
    *start = sublist->head;
    list->length += sublist->length;
    *sublist->tail = next;
    if (start == list->tail) {
        list->tail = sublist->tail;
    }

    return next;
}

struct List remove_sublist(struct List *list, struct ListNode **start, int length) {
    struct List sublist;
    init_sublist(list, &sublist);
    if (length == 0) {
        /* Return empty list. */
        return sublist;
    }

    sublist.head = *start;

    struct ListNode **node_ptr = start;
    while (length > 0 && *node_ptr != NULL) {
        node_ptr = &(*node_ptr)->next;
        // Note: these are done as increments/decrements rather than additions/subtractions
        // so that a shorter list is handled correctly.
        --length;
        ++sublist.length;
        --list->length;
    }
    sublist.tail = node_ptr;
    *start = *node_ptr;
    *sublist.tail = NULL;
    return sublist;
}

void extend_list(struct List *a, struct List *b) {
    /*
     *a->tail = b->head;
     a->tail = b->tail;
     a->length += b->length;
    */
    insert_sublist(a, a->tail, b);
}

struct List *divide_list(struct List *list, int n, struct List sublists[n]) {
    if (n <= 0) {
        // n must be positive.
        return NULL;
    }
    const int length = list->length / n;
    struct ListNode **node_ptr = &list->head;
    for (struct List *sublist = sublists; sublist < sublists + n; ++sublist ) {
        init_sublist(list, sublist);
        sublist->head = *node_ptr;
        for (int i = 0; i < length && *node_ptr != NULL; ++i) {
            node_ptr = &(*node_ptr)->next;
        }
        sublist->tail = node_ptr;
        sublist->length = length;
    }
    // Trailing items (if any) go into the last sublist.
    sublists[n-1].tail = list->tail;
    sublists[n-1].length += list->length % n;
    for (struct List *sublist = sublists; sublist < sublists + n; ++sublist) {
        *sublist->tail = NULL;
    }
    return sublists;
}

void quicksort_list(struct List *list) {
    if (list->length <= 1) return;  // An empty or single-element list is trivally sorted.
    struct List left;
    struct List right;
    init_sublist(list, &left);
    init_sublist(list, &right);

    struct ListNode *pivot = pop_head(list);

    /* Partition list */
    struct ListNode *current;
    while ((current = pop_head(list)) != NULL) {
        if (list->compare(current, pivot) < 0) {
            push_tail(&left, current);
        }
        else {
            push_tail(&right, current);
        }
    }
    /* Sort sublists */
    quicksort_list(&left);
    quicksort_list(&right);

    /* Rebuild list */
    extend_list(list, &left);
    push_tail(list, pivot);
    extend_list(list, &right);
}

void quicksort_list_reverse(struct List *list) {
    if (list->length <= 1) return;
    struct List left;
    struct List right;
    init_sublist(list, &left);
    init_sublist(list, &right);

    struct ListNode *pivot = pop_head(list);

    /* Partition List */
    struct ListNode *current;
    while ((current = pop_head(list)) != NULL) {
        if (list->compare(current, pivot) > 0) {
            push_tail(&left, current);
        }
        else {
            push_tail(&right, current);
        }
    }
    /* Sort sublists */
    quicksort_list_reverse(&left);
    quicksort_list_reverse(&right);

    /* Rebuild list */
    extend_list(list, &left);
    push_tail(list, pivot);
    extend_list(list, &right);
}

void reverse_list(struct List *list) {
    if (list->length <= 1) return;

    struct ListNode *prev = NULL;
    struct ListNode *curr = list->head;
    while (curr != NULL) {
        struct ListNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->tail = &list->head->next;
    list->head = prev;
}

struct List copy_list(const struct List *list, void *nodebuf, size_t bufsize, size_t elemsize, size_t offset) {
    struct List out_list;
    init_sublist(list, &out_list);
    if (bufsize < elemsize) return out_list;

    unsigned char *out_node = nodebuf;
    size_t bytes_written = 0;
    struct ListNode **out_node_ptr = &out_list.head;
    for (struct ListNode *const *node_ptr = &list->head;
         *node_ptr != NULL && bytes_written + elemsize <= bufsize;
         node_ptr = &(*node_ptr)->next) {
        memcpy(out_node, *node_ptr, elemsize);
        *out_node_ptr = (struct ListNode *)(out_node + offset);
        out_node_ptr = &(*out_node_ptr)->next;
        ++out_list.length;

        bytes_written += elemsize;
        out_node += elemsize;
    }
    *out_node_ptr = NULL;
    out_list.tail = out_node_ptr;
    return out_list;
}

bool lists_equal(const struct List *a, const struct List *b) {
    if (a->length != b->length) return false;

    struct ListNode *const *node_ptr_a = &a->head;
    struct ListNode *const *node_ptr_b = &b->head;
    while (*node_ptr_a != NULL) {
        if (a->compare(*node_ptr_a, *node_ptr_b) != 0) {
            return false;
        }
        node_ptr_a = &(*node_ptr_a)->next;
        node_ptr_b = &(*node_ptr_b)->next;
    }
    return true;
}

void print_list(const struct List *list)  {
    printf("HEAD -> ");
    for (struct ListNode *const *node_ptr = &list->head;
         *node_ptr != NULL;
         node_ptr = &(*node_ptr)->next) {
        printf("[ ");
        list->print(*node_ptr);
        printf(" ] -> ");
    }
    printf("NULL");
}
