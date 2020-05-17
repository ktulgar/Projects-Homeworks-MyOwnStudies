#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

struct Node { // Every node holds an integer value and next node's address

    int data;
    struct Node* next;

};

struct Queue { // Queue has a head node and tail node

    struct Node* head;
    struct Node* tail;
    int size;
    int limit;

};

// Functions
void initQueue(struct Queue*,int); // It initializes funtion
void enqueue(struct Queue*,int); // It addes a new item to queue
int dequeue(struct Queue*); // It extracts the head from queue
void printQueue(struct Queue*); // It prints the elements of queue
bool contain(struct Queue*,int); // It checks that whether the queue contains the given element or not



