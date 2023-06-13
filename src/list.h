#ifndef LIST_H
#define LIST_H

#include <stddef.h>

#define NODE_TO_DATA(node, type, member) \
    ((type *)( (unsigned char *)node - offsetof(type, member) ))

struct ListNode;

typedef int (*Comparator)(struct ListNode *a, struct ListNode *b);
typedef void (*Printer)(struct ListNode *node);


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

struct ListNode *get_item(struct List *list, int index);
int find(struct List *list, struct ListNode *item);

struct ListNode *insert_index(struct List *list, int index, struct ListNode *item);
struct ListNode *remove_index(struct List *list, int index);

void push_head(struct List *list, struct ListNode *item);
void push_tail(struct List *list, struct ListNode *item);
struct ListNode *pop_head(struct List *list);
struct ListNode *pop_tail(struct List *list);

struct ListNode *insert_sublist(struct List *list, int start_index, struct List *sublist);
struct List remove_sublist(struct List *list, int start_index, int length);

void concatenate_lists(struct List *a, struct List *b);
struct List *divide_list(struct List *list, int n, struct List sublists[n]);

void print_list(struct List *list);

#endif
