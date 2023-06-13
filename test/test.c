#include <stdio.h>

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
    
    return 0;
}
