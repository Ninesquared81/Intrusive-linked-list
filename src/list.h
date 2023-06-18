#ifndef LIST_H
#define LIST_H

#include <stddef.h>

#define NODE_TO_DATA(node, type, member)                                \
    ((type *)( (unsigned char *)node - offsetof(type, member) ))

struct ListNode;

typedef int (*Comparator)(const struct ListNode *a, const struct ListNode *b);
typedef void (*Printer)(const struct ListNode *node);


struct ListNode {
    struct ListNode *next;
};

struct List {
    struct ListNode *head;
    struct ListNode **tail;
    int length;
    Comparator compare;
    Printer print;
};


void init_list(struct List *list, Comparator compare, Printer print);
void init_sublist(const struct List *super, struct List *sub);

int index_of(const struct List *list, struct ListNode *const *where);
struct ListNode **where_index(const struct List *list, int index);

struct ListNode *get_item(const struct List *list, int index);
struct ListNode **find(const struct List *list, const struct ListNode *item);

struct ListNode **find_inorder(const struct List *list, const struct ListNode *item);
struct ListNode **find_inorder_reverse(const struct List *list, const struct ListNode *item);

struct ListNode *insert_at(struct List *list, struct ListNode **where, struct ListNode *item);
struct ListNode *remove_at(struct List *list, struct ListNode **where);

struct ListNode *insert_inorder(struct List *list, struct ListNode *item);
struct ListNode *insert_inorder_reverse(struct List *list, struct ListNode *item);
struct ListNode *remove_inorder(struct List *list, struct ListNode *item);
struct ListNode *remove_inorder_reverse(struct List *list, struct ListNode *item);

struct ListNode *insert_index(struct List *list, int index, struct ListNode *item);
struct ListNode *remove_index(struct List *list, int index);

struct ListNode *remove_item(struct List *list, struct ListNode *item);

void push_head(struct List *list, struct ListNode *item);
void push_tail(struct List *list, struct ListNode *item);
struct ListNode *pop_head(struct List *list);
struct ListNode *pop_tail(struct List *list);

struct ListNode *insert_sublist(struct List *list, struct ListNode **start, struct List *sublist);
struct List remove_sublist(struct List *list, struct ListNode **start, int length);

void extend_list(struct List *a, struct List *b);
struct List *divide_list(struct List *list, int n, struct List sublists[n]);

void quicksort_list(struct List *list);
void quicksort_list_reverse(struct List *list);

void reverse_list(struct List *list);
struct List copy_list(const struct List *list, void *nodebuf, size_t bufsize, size_t elemsize, size_t offset);

_Bool lists_equal(const struct List *a, const struct List *b);

void print_list(const struct List *list);

#endif
