#include "List.h"
#include <stdio.h>
#include <stdlib.h>

List* list_create() {
    List* list = (List*)malloc(sizeof(List));
    if (list != NULL) {
        list->head = NULL;
    }
    return list;
}

void list_destroy(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void list_insertFront(List* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = list->head;
        list->head = newNode;
    }
}

void list_print(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
