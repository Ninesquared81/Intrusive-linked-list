#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct IntNode {
    struct ListNode node;
    int data;
};

static int compare(struct ListNode *a, struct ListNode *b) {
    struct IntNode *x = NODE_TO_DATA(a, struct IntNode, node);
    struct IntNode *y = NODE_TO_DATA(b, struct IntNode, node);
    return x - y;
}

static void print(struct ListNode *node) {
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
    for (int i = 1; i <= 100; ++i) {
        push_tail(&new_list, (struct ListNode *)new_int_node(i));
    }
    struct List sublists[3];
    divide_list(&new_list, 3, sublists);
    for (int i = 0; i < 3; ++i) {
        printf("\nSublist %d:\n", i);
        print_list(&sublists[i]);
        printf("\n");
    }
    struct List concatenated = concatenate_lists(&sublists[0], &sublists[2]);
    concatenated = concatenate_lists(&sublists[1], &concatenated);
    printf("\nConcatenated:\n");
    print_list(&concatenated);
    printf("\n\n");
    printf("Start removing nodes.\n");
    {
        struct IntNode *node = NULL;
        while (node = (struct IntNode *)pop_head(&concatenated)) {
            free(node);
        }
    }
    printf("Finish removing nodes.\n");
    print_list(&concatenated);
    printf("\n");
    return 0;
}
