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
    printf("\n");
    for (int i = 0; i < 3; ++i) {
        list.print(pop_index(&list, 3));
        printf("\n");
        print_list(&list);
        printf("\n");
    }
    return 0;
}
