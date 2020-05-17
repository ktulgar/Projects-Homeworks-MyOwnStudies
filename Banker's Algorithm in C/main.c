#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>


/* A struct which is called Process has been created to represent every process.
 * The struct has 5 features.AllocatedResource specifies the number of resources for the that process.
 * MaxResource specifies the max number of resources the process needs.
 * NeedResource specifies the number of deficient resources.
 * ExecutionStatus specifies that whether process is exucuted or not.Id is process’s id.     */


struct Process {
    int   *allocatedResource;
    bool    executionStatus;
    int       *needResource;
    int        *maxResource;
    int                  id;
};


/* This function initializes the structs. It allocates the memory for arrays. */

void initProcess(struct Process* process,int x) {
    process->allocatedResource = malloc(sizeof(int)*x);
    process->maxResource = malloc(sizeof(int)*x);
    process->needResource = malloc(sizeof(int)*x);
    process->executionStatus = false;
}

/* Prototypes */
void *bankerAlgo(struct Process*);  // Things revolve in here.
bool check(int [], int []);         // Helper Function
void add(int [],int []);            // Helper Function


int NumberOfResources;         // It is taken from user.
int NumberOfProcesses;         // It is taken from user.
int *availableResources;       // It is taken from user.
char input[50];                // It is used whenever an input taken.
int counter; // It is used in bankerAlgo.It is used to keep track of processes that are executed.

sem_t semProcess;

int main() {

    sem_init(&semProcess,0,1);

    /* At the beginning of main some informations are asked to enter from user.
     * These are number of resources and processes.
     * After that numerical values of resources of processes are asked to enter from user. */

    printf("Please enter the number of resources\n");
    fgets(input,50,stdin);
    NumberOfResources = atoi(input);

    availableResources = malloc(sizeof(int)*NumberOfResources);

    printf("Please enter the number of processes\n");
    fgets(input,50,stdin);
    NumberOfProcesses = atoi(input);

    counter = NumberOfProcesses;

    pthread_t threads[NumberOfProcesses];
    struct Process* processes[NumberOfProcesses];


    int x;
    char* token;
    for(int i=0 ; i<NumberOfProcesses ; i++) {

        processes[i] = (struct Process*) malloc(sizeof(struct Process));
        processes[i]->id = i + 1;
        initProcess(processes[i],NumberOfResources);
        x = 0;

       printf("Resource allocated to process %d\n",i+1);
       fgets(input,50,stdin);
       token = strtok(input," ");

       while(token != NULL) {
       processes[i]->allocatedResource[x] = atoi(token);
       token = strtok(NULL, " ");
       x++;
       }

       x = 0;
       printf("Maximum resource required by proces %d\n",i+1);
       fgets(input,50,stdin);
       token = strtok(input," ");
        while(token != NULL) {
            processes[i]->maxResource[x] = atoi(token);
            token = strtok(NULL, " ");
            x++;
        }

    }

    x = 0;
    printf("Please enter the available resources \n");
    fgets(input,50,stdin);
    token = strtok(input," ");
    while(token != NULL) {
        availableResources[x] = atoi(token);
        token = strtok(NULL," ");
        x++;
    }


    /*    At the end of main threads are created and started.   */

    for(int i=0 ; i<NumberOfProcesses ; i++) {
        pthread_create(&threads[i],NULL,(void *)bankerAlgo,processes[i]);
    }

    for(int i=0 ; i<NumberOfProcesses ; i++) {
        pthread_join(threads[i],NULL);
    }

}


/* Every thread performs the same function called bankerAlgo.
 * At the beginning of function numbers of resources that processes need are calculated simultaneously.
 * After this part of function critical section begins.
 * Only one thread can access this part.
 * There is variable called counter in here.
 * At the beginning of function the variable is set to number of process.
 * This variable used to keep track of processes that are executed.
 * Whenever a process is executed counter isreduced one by one.
 * When it reaches zero program terminates itself. */



void *bankerAlgo(struct Process* process) {

    for(int i=0 ; i<NumberOfResources ; i++) {
        process->needResource[i] = process->maxResource[i] - process->allocatedResource[i];
    }

    while(counter>0) {

        sem_wait(&semProcess);

       if(check(process->needResource,availableResources) && !(process->executionStatus)) {

            add(availableResources,process->allocatedResource);
            printf("Process %d executed\n",process->id);
            process->executionStatus = true;
            counter--;
            sleep(2);
            sem_post(&semProcess);
        }
        else if(!check(process->needResource,availableResources) && !(process->executionStatus)){
            printf("Process %d is waiting for execution Due to lack of available resources\n",process->id);
            sleep(1);
            sem_post(&semProcess);
        }

        else{
            sem_post(&semProcess);
        }

    }

}

/* There are two helper functions.
 * First one is check. It returns a boolean expression.
 * It compares allocated resources to max resources that process needs.
 * If there are enough resource for process to be executed then it returns true.
 * Second one is add.
 * After a process is executed its allocated resources are released.
 * This method adds allocated resources into available resources. */

bool check(int array1[],int array2[]) {

    for(int i=0 ; i<NumberOfResources ; i++) {
        if(array1[i]>array2[i])
            return false;
    }

    return true;
}

void add(int array1[],int array2[]) {

    for(int i=0 ; i<NumberOfResources ; i++) {
        array1[i] = array1[i] + array2[i];
    }

}
