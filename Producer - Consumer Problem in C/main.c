#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>


/* The Producer-Consumer problem is a classic problem this is used for multi-process synchronization i.e.
 * synchronization between more than one processes.In the producer-consumer problem,
 * there is one Producer that is producing something and there is one Consumer that is consuming
 * the products produced by the Producer. The producers and consumers share the same memory buffer that is of fixed-size.
 * The job of the Producer is to generate the data, put it into the buffer, and again start generating data.
 * While the job of the Consumer is to consume the data from the buffer.                                 */



/* The solution for the producer is to either go to sleep or discard data if the buffer is full.
 * The next time the consumer removes an item from the buffer, it notifies the producer,
 * who starts to fill the buffer again. In the same way, the consumer can go to sleep if it finds the buffer empty.
 * The next time the producer puts data into the buffer, it wakes up the sleeping consumer.                */

struct CircularBuffer {

    int *array; // The array we use in buffer
    int   size;
    int   out; // It will be used when we extract element
    int    in; // It will be used when we insert new element

};

// Functions for Circular Buffer
void initBuffer(struct CircularBuffer*,int);
void insert(struct CircularBuffer*,int);
int extract(struct CircularBuffer*);


void *producer(struct CircularBuffer*);
void *consumer(struct CircularBuffer*);

pthread_mutex_t mutex1,mutex2;
sem_t empty;
sem_t full;

struct CircularBuffer* buffer; // Threads share this buffer

int main() {

    sem_init(&empty,0,5); // At the beginning there are 5 empty indexes.
    sem_init(&full,0,0) ; // At the beginning Buffer is not full
    pthread_mutex_init(&mutex1,NULL);
    pthread_mutex_init(&mutex2,NULL);
    buffer = (struct CircularBuffer*) malloc(sizeof(struct CircularBuffer));
    initBuffer(buffer,5); // Buffer's size is 5

    pthread_t producerThreads[5];
    pthread_t consumerThreads[5];


    for(int i=0 ; i<5 ; i++) {
        pthread_create(&producerThreads[i],NULL,(void *)producer,buffer);

    }

    for(int i=0 ; i<5 ; i++) {
        pthread_create(&consumerThreads[i],NULL,(void *)consumer,buffer);
    }


    for(int i=0 ; i<5 ; i++) {
        pthread_join(producerThreads[i],NULL);
        pthread_join(consumerThreads[i],NULL);
    }


}

void initBuffer(struct CircularBuffer* buffer,int size) {

    buffer->array = malloc(sizeof(int)*(size));
    buffer->size  = size;
    buffer->out   = 0;
    buffer->in    = 0;

}

void insert(struct CircularBuffer* buffer,int item) {

    *(buffer->array + buffer->in) = item;
    printf("Item %d is inserted into index %d\n",item,buffer->in);
    buffer->in = (buffer->in + 1) % buffer->size;

}


int extract(struct CircularBuffer* buffer) {

    int item    = *(buffer->array + buffer->out);
    printf("Item %d is extracted from index %d\n",item,buffer->out);
    buffer->out = (buffer->out + 1) % buffer->size;
    return item;
}


void *producer(struct CircularBuffer* buffer) {

    pthread_mutex_lock(&mutex1); // 5 threads try to enter but this block allows only one thread
    sem_wait(&empty);            // If there is no empty index thread waits
    srand(time(NULL)); // Random Number Generator but it generates same number because of multi threading
    int item = rand() % 20;    // I found that it is not proper to use with multiple threads.Bu you got the point
    insert(buffer,item);
    sem_post(&full);  // When we insert new element into buffer it is not empty anymore and we increase semaphore full
    pthread_mutex_unlock(&mutex1);

}

void *consumer(struct CircularBuffer* buffer) {

    pthread_mutex_lock(&mutex2);  // 5 threads try to enter but this block allows only one thread
    sem_wait(&full); // If there is not element in buffer thread waits
    int item = extract(buffer);
    sem_post(&empty);  // There is one more empty index we increase semaphore empty
    pthread_mutex_unlock(&mutex2);

}