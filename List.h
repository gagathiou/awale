#ifndef LIST_H
#define LIST_H

// Define the structure for a node in the linked list
typedef struct Node {
    int data;  // Change the data type as needed
    struct Node* next;
} Node;

// Define the structure for the linked list
typedef struct {
    Node* head;
} List;

// Function prototypes
List* createList();
void destroyList(List* list);
void insertFront(List* list, int data);  // Change the data type as needed
void printList(List* list);

#endif  // LIST_H
