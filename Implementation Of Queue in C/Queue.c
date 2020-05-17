#include "Queue.h"

void initQueue(struct Queue* queue,int limit) {

    queue->size = 0;     // Because queue is empty
    queue->head = NULL;  // In the beginning head and tail point to null
    queue->tail = NULL;
    queue->limit = limit;
}

void enqueue(struct Queue* queue,int x) {

// If user exceeds the capacity of queue a warning message is printed

    if(queue->size == queue->limit) {
        printf("You can not add one more number to queue.\nBecause you exceed the capacity.\n");
    }

    else if(queue->size == 0) {

// If queue is empty when we add an new element to queue it becames head and tail at the same time

        struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
        newNode->data = x;
        newNode->next = NULL;
        queue->head = newNode;
        queue->tail = newNode;
        queue->size = queue->size + 1;

    }

    else   {

// If queue is not empty when we add new element to queue it becomes tail

        struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
        newNode->data = x;
        newNode->next = NULL;

        struct Node* temp = queue->head;

        while(temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
        queue->tail = newNode;
        queue->size = queue->size + 1;

    }

}


int dequeue(struct Queue* queue) {

    int data;

// If queue is empty it prints a warning message and returns -1

    if(queue->head == NULL) {
        data = -1;
        printf("Queue is empty\n");
        return data;
    }

// This if block is for the cases the LinkedList has only one node
    else if (queue->head->next == NULL) {
        struct Node* iter = queue->head;
        int data = iter->data;
        free(iter);
        queue->head = NULL;
        queue->tail = NULL;
        queue->size--;
        return data;
    }

// This block is for the cases the LinkedList has more than one nodes
    else {
        data = queue->head->data;
        struct Node* iter = queue->head;
        queue->head = queue->head->next;
        iter->next = NULL;
        free(iter);
        queue->size--;
        return data;
    }



}

void printQueue(struct Queue* queue) {

    // It prints the elements of the queue.

    struct Node* temp;
    temp = queue->head;

    printf("Head -> ");

    while(temp != NULL) {
        printf(" %d -> ",temp->data);
        temp = temp->next;
    }

    printf(" Tail\n");

}

bool contain(struct Queue* queue,int x) {

// It checks that whether the queue contains the given element or not

    struct Node* iter = queue->head;

    while(iter != NULL) {

        if(iter->data == x)
            return true;

        iter = iter ->next;

    }

    return false;

}
