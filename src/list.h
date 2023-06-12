#ifndef LIST_H
#define LIST_H


typedef int (*Comparator)(struct ListNode *a, struct ListNode *b);


struct ListNode {
    struct ListNode *next;
};

struct LinkedList {
    struct ListNode *head;
    struct ListNode **tail;
    Comparator compare;
};


void init_list(struct List *list, Comparator compare);
struct List *get_item(struct List *list, int index);
int find(struct List *list, struct ListNode *item);

struct List *insert_index(struct List *list, int index, struct ListNode *item);
struct List *pop_index(struct List *list, int index);

#endif
