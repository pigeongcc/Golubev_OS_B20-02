#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

void print_list(node* list) {
    for (node *tmp = list->next; tmp != NULL; tmp = tmp->next)
        printf("%d ", tmp->number);
    printf("\n");
}

void insert_node(node* head, node *newNode, node *prevNode) {
    bool found = false;
    for (node *tmp = head; tmp != NULL; tmp = tmp->next)
        if (tmp == prevNode) {
            found = true;
            break;
        }

    if(!found) {
        printf("Impossible to insert a node since the given previous node is not in the list.\n");
        return;
    }

    node *nextNode = prevNode->next;
    prevNode->next = newNode;
    newNode->next = nextNode;

    printf("The node inserted.\n");
}

void delete_node(node* list, node* deletedNode) {
    bool found = false;
    node* prev = list;

    for (node *tmp = list->next; tmp != NULL; tmp = tmp->next) {
        if (tmp == deletedNode) {
            found = true;
            break;
        } else
            prev = prev->next;
    }
    if(!found) {
        printf("Impossible to delete a node which is not in the list.\n");
        return;
    }

    prev->next = deletedNode->next;
    free(deletedNode);
    printf("The node deleted.\n");
}

node* initialize_list() {
    node *list = malloc(sizeof(node));
    list->number = NULL;
    list->next = NULL;

    return list;
}

node* initialize_node(int value) {
    node *n = malloc(sizeof(node));
    n->number = value;
    n->next = NULL;

    return n;
}

int main(void)
{
    node *head = initialize_list();

    node *n1 = initialize_node(1), *n2 = initialize_node(2), *n3 = initialize_node(3);

    insert_node(head, n1, head);
    print_list(head);

    insert_node(head, n2, n1);
    print_list(head);

    insert_node(head, n3, n1);
    print_list(head);

    insert_node(head, n3, initialize_node(8));
    print_list(head);

    delete_node(head, n2);
    print_list(head);

    delete_node(head, n2);
    print_list(head);

    delete_node(head, n3);
    print_list(head);
}
