#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

enum Status {
    even,
    odd
};

void *printZero();
void *printOdd();
void *printEven();

sem_t semZero,semOdd,semEven;
pthread_t threadZero,threadOdd,threadEven;

enum Status status = odd;

int n = 10; // Decide what number it will last to
int i = 1;

int main() {

    sem_init(&semZero,0,1);
    sem_init(&semEven,0,0);
    sem_init(&semOdd,0,0);

    pthread_create(&threadZero,NULL,printZero,NULL);
    pthread_create(&threadEven,NULL,printEven,NULL);
    pthread_create(&threadOdd,NULL,printOdd,NULL);

    pthread_join(threadZero,NULL);
    pthread_join(threadEven,NULL);
    pthread_join(threadOdd,NULL);



}


void *printZero() {

    while(i<n) {

        sem_wait(&semZero);

        printf("%d",0);
        fflush(stdout);
        sleep(1);

        if(status == odd)
           sem_post(&semOdd);
        else
            sem_post(&semEven);

    }

}


void *printOdd() {

    while(i<n) {

        sem_wait(&semOdd);
        printf("%d",i);
        fflush(stdout);
        i++;
        sleep(1);
        status = even;
        sem_post(&semZero);

    }

}

void *printEven() {

    while(i<n) {

        sem_wait(&semEven);
        printf("%d",i);
        fflush(stdout);
        i++;
        sleep(1);
        status = odd;
        sem_post(&semZero);

    }

}

