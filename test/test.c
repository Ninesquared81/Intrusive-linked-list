#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct IntNode {
    struct ListNode node;
    int data;
};

static int compare(const struct ListNode *a, const struct ListNode *b) {
    struct IntNode *x = NODE_TO_DATA(a, struct IntNode, node);
    struct IntNode *y = NODE_TO_DATA(b, struct IntNode, node);
    return x->data - y->data;
}

static void print(const struct ListNode *node) {
    if (node == NULL) {
        printf("<null>");
        return;
    }
    printf("%d", NODE_TO_DATA(node, struct IntNode, node)->data);
}

static struct IntNode *new_int_node(int data) {
    struct IntNode *new = malloc(sizeof *new);
    new->data = data;
    return new;
}

int main(void) {
    struct List list;
    init_list(&list, compare, print);
    struct IntNode nodes[] = {
        {.data = 1},
        {.data = 2},
        {.data = 3},
        {.data = 4},
        {.data = 5},
    };
    for (int i = 0; i < 5; ++i) {
        insert_index(&list, i, &nodes[i].node);
    }
    print_list(&list);
    printf("\n\n");
    for (int i = 0; i < 3; ++i) {
        list.print(remove_index(&list, 3));
        printf("\n");
        print_list(&list);
        printf("\n\n");
    }
    printf("Pop tail:\n");
    list.print(pop_tail(&list));
    printf("\n");
    print_list(&list);
    printf("\nPush tail 42:\n");
    push_tail(&list, (struct ListNode *)&(struct IntNode){.data = 42});
    print_list(&list);
    printf("\n\n");

    printf("Pop head:\n");
    list.print(pop_head(&list));
    printf("\n");
    print_list(&list);
    printf("\nPush head 69:\n");
    push_head(&list, (struct ListNode *)&(struct IntNode){.data = 69});
    print_list(&list);
    printf("\n");

    printf("Insert at end (not using special function) 420:\n");
    insert_index(&list, list.length, (struct ListNode *)&(struct IntNode){.data = 420});
    print_list(&list);
    printf("\n");

    printf("Insert at beginning 72:\n");
    insert_index(&list, 0, (struct ListNode *)&(struct IntNode){.data = 72});
    print_list(&list);
    printf("\n");

    printf("Insert at index 3 -1:\n");
    insert_index(&list, 3, (struct ListNode *)&(struct IntNode){.data = -1});
    print_list(&list);
    printf("\n");

    printf("Remove index 3:\n");
    list.print(remove_index(&list, 3));
    printf("\n");
    print_list(&list);
    printf("\n");

    printf("Remove from beginning:\n");
    list.print(remove_index(&list, 0));
    printf("\n");
    print_list(&list);
    printf("\n");

    printf("\n\n");

    struct List new_list;
    init_list(&new_list, compare, print);
    for (int i = 1; i <= 14; ++i) {
        push_tail(&new_list, (struct ListNode *)new_int_node(i));
    }
    struct List sublists[3];
    divide_list(&new_list, 3, sublists);
    for (int i = 0; i < 3; ++i) {
        printf("\nSublist %d:\n", i);
        print_list(&sublists[i]);
        printf("\n");
    }
    extend_list(&sublists[0], &sublists[2]);
    extend_list(&sublists[1], &sublists[0]);
    printf("\nConcatenated:\n");
    print_list(&sublists[1]);
    printf("\n\n");
    printf("Start removing nodes.\n");
    {
        struct IntNode *node = NULL;
        while (node = (struct IntNode *)pop_head(&sublists[1])) {
            free(node);
        }
    }
    printf("Finish removing nodes.\n");
    print_list(&sublists[1]);
    printf("\n");
    struct List ordered;
    struct List revordered;
    init_list(&ordered, compare, print);
    init_list(&revordered, compare, print);
    int elems[] = {-4, 10, 12, 13, -6, 0, 0, 3, 4, -7, -4, 5};
#define LENGTH sizeof elems / sizeof elems[0]
    struct IntNode n1[LENGTH], n2[LENGTH];
    for (int i = 0; i < LENGTH; ++i) {
        n1[i].data = elems[i];
        n2[i].data = elems[i];
        insert_inorder(&ordered, (struct ListNode *)&n1[i]);
        insert_inorder_reverse(&revordered, (struct ListNode *)&n2[i]);
    }
    printf("\nOrdered list:\n");
    print_list(&ordered);
    printf("\n");
    list.print(remove_inorder(&ordered, (struct ListNode *)&(struct IntNode){.data = 12}));
    printf("\n");
    print_list(&ordered);
    printf("\n");
    printf("\nReverse-ordered list:\n");
    print_list(&revordered);
    printf("\n");

    struct IntNode n3[LENGTH/2];
    for (int i = 0; i < LENGTH / 2; ++i) {
        n3[i].data = elems[i];
        push_tail(&list, (struct ListNode *)&n3[i]);
    }
    size_t bufsize = list.length * sizeof(struct IntNode);
    struct IntNode *buffer = malloc(bufsize);
    struct List list2 = copy_list(&list, buffer, bufsize, sizeof *buffer, 0);
    printf("\nUnsorted list:\n");
    print_list(&list);
    printf("\n");
    printf("\nCopied list:\n");
    print_list(&list2);
    printf("\n");
    quicksort_list(&list);
    printf("\nSorted list:\n");
    print_list(&list);
    printf("\n");
    quicksort_list_reverse(&list2);
    printf("\nReverse-sorted list:\n");
    print_list(&list2);
    printf("\n");

    reverse_list(&list2);
    printf("\nPrevious list reversed:\n");
    print_list(&list2);
    printf("\n");

    printf("\nComapring two lists:\n");
    printf("list (length: %d) == list2 (length: %d): %s\n",
           list.length, list2.length,
           (lists_equal(&list, &list2)) ? "true": "false");
    remove_inorder_reverse(&revordered, (struct ListNode *)&(struct IntNode){.data = 12});
    printf("\nComapring different lists:\n");
    printf("ordered (length: %d) == revordered (length: %d): %s\n",
           ordered.length, revordered.length,
           (lists_equal(&ordered, &revordered)) ? "true" : "false");
    printf("\nComparing two lists of different lengths:\n");
    printf("list (length: %d) == ordered (length: %d): %s\n",
           list.length, ordered.length,
           (lists_equal(&list, &ordered)) ? "true" : "false");

    free(buffer);
}
