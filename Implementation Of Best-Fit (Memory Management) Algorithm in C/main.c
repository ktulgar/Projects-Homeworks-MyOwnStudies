#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>


#define Full false
#define Empty true

/* I was not committed to the given tables
 * You can give any numbers you wish */



/*I created a struct called Process to represent processes*/
struct Process{
    int id;       // Id Of Process
    int size;     // Size Of Process
    int blockId;  // Which block is allocated for that process
};

/*I created a struct called Block to represent blocks*/
struct Block {
    int id;        // Id Of Block
    int size;      // Size Of Block
    int processId; // Which does process have that block
    bool status;   // It shows whether block is allocated or not
};

void *bestFit(struct Process*);
void allocations(struct Process* []);
void remainingSizes();
void sortBlocks(struct Block* *,int,int);
void merge(struct Block* *,int,int,int);

int NumberOfProcesses;
int NumberOfBlocks;
struct Block* *listOfBlocks;
char input[50];
sem_t sem;

int main() {

    /* Informations are gathered from user */
    printf("How many process do you want to be created ?\n");
    fgets(input,50,stdin);
    NumberOfProcesses = atoi(input);
    struct Process* listOfProcesses[NumberOfProcesses];
    for(int i = 0; i < NumberOfProcesses ; i++) {
        printf("Plese enter the size of Process ? %d\n",i);
        fgets(input,50,stdin);
        int size = atoi(input);
        listOfProcesses[i] = (struct Process*) malloc(sizeof(struct Process));
        listOfProcesses[i]->id   = i;
        listOfProcesses[i]->size = size;
        listOfProcesses[i]->blockId = -1;
    }

    printf("How many blocks are there ?\n");
    fgets(input,50,stdin);
    NumberOfBlocks = atoi(input);
    listOfBlocks = malloc(sizeof(struct Block)*NumberOfBlocks);
    for(int i = 0 ; i < NumberOfBlocks ; i++) {
        printf("Plese enter the size of Block %d \n",i);
        fgets(input,50,stdin);
        int size = atoi(input);
        listOfBlocks[i] = (struct Block*) malloc(sizeof(struct Block));
        listOfBlocks[i]->id = i;
        listOfBlocks[i]->size = size;
        listOfBlocks[i]->processId = -1;
        listOfBlocks[i]->status = Empty;
    }
    // I sorted the array from smallest to biggest.
    sortBlocks(listOfBlocks,0,NumberOfBlocks-1);


    /* Threads are created and started */
    pthread_t threads[NumberOfProcesses];
    sem_init(&sem,0,1);
    for(int i = 0 ; i < NumberOfProcesses ; i++ ) {
        pthread_create(&threads[i],NULL,(void *)bestFit,listOfProcesses[i]);
    }
    for(int i = 0 ; i < NumberOfProcesses ; i++ ) {
        pthread_join(threads[i],NULL);
    }

   printf("\n");
   allocations(listOfProcesses);
   printf("\n");
   remainingSizes();


}

/*It performs best-fit algorithm.
 * If block's size is bigger than process's size and it was not allocated
 * Then it is allocated for that process.*/

void *bestFit(struct Process* process) {
    sem_wait(&sem); // Only one thread can access at one time
    for(int i = 0 ; i < NumberOfBlocks ; i++) {
        if(listOfBlocks[i]->size >= process->size){
            if(listOfBlocks[i]->status){
                listOfBlocks[i]->status = Full;
                listOfBlocks[i]->processId = process->id;
                listOfBlocks[i]->size = listOfBlocks[i]->size - process->size;
                process->blockId = listOfBlocks[i]->id;
                break;
            }
        }
    }
    sem_post(&sem);
}

/* It prints "Process X fit to Block Y" */

void allocations(struct Process* processes[]) {
    for(int i = 0 ; i < NumberOfProcesses ; i++)
        if(processes[i]->blockId == -1)
            printf("No block is allocated for Process %d\n",processes[i]->id);
        else
        printf("Process %d fit to Block %d\n",processes[i]->id,processes[i]->blockId);
    }

/* It prints "Block X remaining size Y" */

void remainingSizes() {
    for(int i = 0 ; i < NumberOfBlocks ; i++) {
        printf("Block %d remaining size %d\n",listOfBlocks[i]->id,listOfBlocks[i]->size);
    }
}


/* 2 methods below are implementation of merge sort algorithm.
 * But i changed a little bit.Because i don't sort ordinary integer array.
 * I sort an array which is comprised of structs.
 * I sort the blocks from smallest to biggest one.
 * Because we are looking for smallest proper block in Best-Fit Algorithm.*/


void sortBlocks(struct Block* blocks[],int beginning,int ending) {

    if(beginning < ending) {
        int middle = beginning + (ending - beginning)/2;
        sortBlocks(blocks,beginning,middle);
        sortBlocks(blocks,middle + 1,ending);
        merge(blocks,beginning,middle,ending);
    }
}

void merge(struct Block* *blocks,int beginning,int middle,int ending) {

    int i, j, k;
    int n1 = middle - beginning + 1;
    int n2 =  ending - middle;

    /* create temp arrays */
    struct Block* L[n1];
    struct Block* R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = blocks[beginning + i];
    for (j = 0; j < n2; j++)
        R[j] = blocks[middle + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = beginning; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i]->size <= R[j]->size)
        {

            blocks[k] = L[i];
            i++;
        }
        else
        {
            blocks[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        blocks[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        blocks[k] = R[j];
        j++;
        k++;
    }
}




