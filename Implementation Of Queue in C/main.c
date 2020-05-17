#include "Queue.h"

int main() {

    // Testing the functions of queue

    struct Queue* myQueue = (struct Queue*) malloc(sizeof(struct Queue));
    initQueue(myQueue,8);

    enqueue(myQueue,1);
    enqueue(myQueue,2);
    enqueue(myQueue,3);
    enqueue(myQueue,4);
    enqueue(myQueue,5);
    enqueue(myQueue,6);
    enqueue(myQueue,7);
    enqueue(myQueue,8);
    enqueue(myQueue,9);

    int x = dequeue(myQueue);

    printQueue(myQueue);

    printf("%d\n",contain(myQueue,8));
    printf("%d\n",contain(myQueue,10));

    struct Queue* myQueue2 = (struct Queue*) malloc(sizeof(struct Queue));
    initQueue(myQueue2,10);

    enqueue(myQueue2,5);
    int data = dequeue(myQueue2);
    printf("%d\n",data);
    data = dequeue(myQueue2);
    printf("%d\n",data);


    struct Queue* myQueue3 = (struct Queue*) malloc(sizeof(struct Queue));
    initQueue(myQueue3,4);
    enqueue(myQueue3,5);
    enqueue(myQueue3,12);
    dequeue(myQueue3);
    printf("%d\n",myQueue3->tail->data);
    printf("%d\n",myQueue3->head->data);

    struct Queue* myQueue4 = (struct Queue*) malloc(sizeof(struct Queue));
    initQueue(myQueue4,0);

    enqueue(myQueue4,85);
}
