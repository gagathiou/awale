#include "List_P.h"
#include <stdio.h>
#include <stdlib.h>



List_P* list_p_create() {
    List_P* list = (List_P*)malloc(sizeof(List_P));
    if (list != NULL) {
        list->head = NULL;
    }
    return list;
}

void list_p_destroy(List_P* list) {
    Node_P* current = list->head;
    while (current != NULL) {
        Node_P* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void list_p_insertFront(List_P* list, Player player) {
    Node_P* newNode = (Node_P*)malloc(sizeof(Node_P));
    if (newNode != NULL) {
        newNode->data = player;
        newNode->next = list->head;
        list->head = newNode;
    }
}

void list_p_printPlayers(List_P* list) {
    Node_P* current = list->head;
    while (current != NULL) {
        printf("Pseudo: %s, State: %d\n", current->data.pseudo, current->data.state);
        current = current->next;
    }
    printf("\n");
}