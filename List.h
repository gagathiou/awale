#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;  
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} List;

List* list_create();
void list_destroy(List* list);
void list_insertFront(List* list, int data);  
void list_print(List* list);

#endif  // LIST_H
