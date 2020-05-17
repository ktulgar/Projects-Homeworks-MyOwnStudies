#include <stdio.h>
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"
#include "unistd.h"

enum Direction {
    East,
    West
};

struct Car {
    enum Direction direction;
                      int id;
};

void *start(struct Car*);
void *goEast(struct Car*);
void *goWest(struct Car*);
void *bridge();

sem_t lock,lock2,east,west,vehicle,journey;

int westCar = 0;
int eastCar = 0;

int numberofcar;
char input[50];

int main() {

    printf("How many cars do you want to be created ?\n");
    fgets(input,50,stdin);
    numberofcar = atoi(input);

    sem_init(&lock,0,1);
    sem_init(&lock2,0,1);
    sem_init(&east,0,1);
    sem_init(&west,0,0);
    sem_init(&journey,0,0);
    sem_init(&vehicle,0,0);

    pthread_t threads[numberofcar];
    pthread_t ferryboat;
    struct Car* cars[numberofcar];
    enum Direction directions[] = {West,East};

    for(int i=0 ; i<numberofcar ; i++) {
        int index = rand() % 2;
        cars[i] = (struct Car*) malloc(sizeof(struct Car));
        cars[i]->id = i + 1;
        cars[i]->direction = directions[index];
        if(cars[i]->direction == East)
            eastCar++;
        else
            westCar++;
    }

    for(int i=0 ; i<numberofcar ; i++) {
        pthread_create(&threads[i],NULL,(void *)start,cars[i]);
    }

    pthread_create(&ferryboat,NULL,bridge,NULL);

    for(int i=0 ; i<numberofcar ; i++) {
        pthread_join(threads[i],NULL);
    }

    pthread_join(ferryboat,NULL);

}

void *start(struct Car* car) {
    if(car->direction == East)
        goEast(car);
    else
        goWest(car);

}


void *goEast(struct Car* car) {

    sem_wait(&lock);
    printf("Car %d is waiting to enter the bridge to go East\n",car->id);
    sem_wait(&east);
    sleep(1);
    sem_post(&lock);
    sleep(1);
    printf("Car %d entered the bridge\n",car->id);
    sem_post(&vehicle);
    printf("Car %d is crossing the bridge to go East\n",car->id);
    sleep(2);
    printf("Car %d crossed the bridge\n",car->id);
    sem_post(&journey);
    eastCar--;

    if(westCar == 0) {
        sem_post(&east) ;
    }
    else {
        sem_post(&west);
    }
}

void *goWest(struct Car* car) {

    sem_wait(&lock2);
    printf("Car %d is waiting to enter the bridge to go West\n",car->id);
    sem_wait(&west);
    sleep(1);
    sem_post(&lock2);
    sleep(1);
    printf("Car %d entered the bridge\n",car->id);
    sem_post(&vehicle);
    printf("Car %d is crossing the bridge to go West\n",car->id);
    sleep(2);
    printf("Car %d crossed the bridge\n",car->id);
    westCar--;
    sem_post(&journey);

    if(eastCar == 0) {
        sem_post(&west);
    }
    else
    {
        sem_post(&east);
    }
}

void *bridge() {
    while(1) {
        if(eastCar + westCar == 0) {
            exit(0);
        }
        sem_wait(&vehicle);
        printf("The bridge is full\n");
        sem_wait(&journey);
        printf("The bridge is empty\n");

    }
}