#include "List.h"
#include <stdio.h>
#include <stdlib.h>

List* createList() {
    List* list = (List*)malloc(sizeof(List));
    if (list != NULL) {
        list->head = NULL;
    }
    return list;
}

void destroyList(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void insertFront(List* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = list->head;
        list->head = newNode;
    }
}

void printList(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
