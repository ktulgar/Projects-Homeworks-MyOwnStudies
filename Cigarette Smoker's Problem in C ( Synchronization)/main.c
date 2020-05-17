#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>


#define tobacco 0
#define matches 1
#define paper   2

// I created a struct to hold smoker's features
struct Smoker {
    int id;
    bool items[3];  // This array holds the ingredients that smoker has at that time
};


// Prototypes
void *smoker(struct Smoker*);
void *agent();

pthread_mutex_t mutex;

int table[2];  // It holds the ingredients which are on the table at that time
int totalCigarette = 0;
int out = 0;   // It is used when we get ingredient from table
int in = 0;    // It is used when we put ingredient onto table
int counter = 0;

int main() {

    //Smoker 1 has only tobacco at the beginning
    struct Smoker* smoker1 = (struct Smoker*) malloc(sizeof(struct Smoker));
    smoker1->id = 1;
    smoker1->items[tobacco] = true;
    smoker1->items[matches] = false;
    smoker1->items[paper]   = false ;

    //Smoker 2 has only matches at the beginning
    struct Smoker* smoker2 = (struct Smoker*) malloc(sizeof(struct Smoker));
    smoker2->id = 2;
    smoker2->items[tobacco] = false;
    smoker2->items[matches] = true;
    smoker2->items[paper]   = false ;

    //Smoker 3 has only paper at the beginning
    struct Smoker* smoker3 = (struct Smoker*) malloc(sizeof(struct Smoker));
    smoker3->id = 3;
    smoker3->items[tobacco] = false;
    smoker3->items[matches] = false;
    smoker3->items[paper]   = true ;

    pthread_mutex_init(&mutex,NULL);
    pthread_t thread1,thread2,thread3,thread4;

    pthread_create(&thread4,NULL,agent,NULL);
    pthread_create(&thread1,NULL,(void *)smoker,smoker1);
    pthread_create(&thread2,NULL,(void *)smoker,smoker2);
    pthread_create(&thread3,NULL,(void *)smoker,smoker3);

    pthread_join(thread4,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);


}

void *smoker(struct Smoker* smoker) {

    while(true) {

        if(counter>0) {
            // Smoker can pick up an ingredient, Although smoker has already it.
            pthread_mutex_lock(&mutex);
            int item = table[out];
            out = (out + 1) % 2;
            counter--;
            if(item == tobacco) {
                printf("Tobacco is picked up by Smoker %d\n",smoker->id);
                smoker->items[tobacco] = true;
            }
            else if(item == matches) {
                printf("Matches is picked up by Smoker %d\n",smoker->id);
                smoker->items[matches] = true;
            }
            else {
                printf("Paper is picked up by Smoker %d\n",smoker->id);
                smoker->items[paper] = true;
            }

            if(smoker->items[tobacco]&&smoker->items[matches]&&smoker->items[paper]) {
                totalCigarette++;
                printf("Smoker %d is smoking now and %d New cigarette is rolled\n",smoker->id,totalCigarette);
                sleep(2);
                // After a cigarette was rolled Smoker who rolled cigarette returns to initial form.
                if(smoker->id == 1) {
                    smoker->items[tobacco] = true;
                    smoker->items[matches] = false;
                    smoker->items[paper]   = false;
                }

                else if(smoker->id == 2) {
                    smoker->items[tobacco] = false;
                    smoker->items[matches] = true;
                    smoker->items[paper]   = false;
                }

                else  {
                    smoker->items[tobacco] = false;
                    smoker->items[matches] = false;
                    smoker->items[paper]   = true;
                }
            }
            pthread_mutex_unlock(&mutex);
        }
    }
}


void *agent(){

    int items[] = {tobacco,paper,matches}; // Our ingredients

    while(true) {
        if(counter<2){
            int index = rand() % 3;  // Agent puts ingredients randomly. We don't know what is next.
            table[in] = items[index];
            if(items[index] == tobacco) {
                printf("Tabocco is put onto table by Agent\n");
            }
            else if(items[index] == paper) {
                printf("Paper is put onto table by Agent\n");
            }
            else {
                printf("Matches is put onto table by Agent\n");
            }
            in = (in + 1) % 2;
            counter++;
        }
    }
}

