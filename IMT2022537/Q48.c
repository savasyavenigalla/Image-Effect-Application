#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/sem.h>
#include<fcntl.h>
#include <sys/shm.h>
#include<string.h>

/*
Question :
Semaphore Creation and Initialization: Write a program to create a semaphore and
initialize its value:
a. Create a binary semaphore
b. Create a counting semaphore

Explanation :
Binary semaphores have only two states (0 and 1) and are typically used for mutual exclusion,
allowing only one process to access a resource at a time.

Counting semaphores can have multiple states, usually ranging from 0 to some maximum value, 
and are used for resource allocation problems where multiple instances of a resource need to be shared among processes.
*/


int main()
{
    // Creating and initializing a binary semaphore
    int key1 = ftok(".", 'a');                      // unique key
    int arg1 = 1;                                   // set semaphore value to 1
    int semid1 = semget(key1, 1, IPC_CREAT | 0644); // Creats semaphore set with one semaphore value
    semctl(semid1, 0, SETVAL, arg1);                // sets the initial value
    printf("Created a binary semaphore.\n");  


    // Creating and initializing a counting semaphore
    int key2 = ftok(".", 'z');                      // unique key
    int arg2 = 4;                                   // set semaphore value to 4
    int semid2 = semget(key2, 1, IPC_CREAT | 0644); // Creats semaphore set with one semaphore value
    semctl(semid2, 0, SETVAL, arg2);                // sets the initial value
    printf("Created a counting semaphore.\n");      

    return 0; 
}

//RUN : gcc and ./a.out

