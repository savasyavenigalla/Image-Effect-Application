// i dont know how to check if it's removed or created and all shit

/*
Question : 
Semaphore Implementation: Write a program to implement a semaphore to protect any critical section:

d. Remove the created semaphore
Explanation:

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    int key = ftok(".", 'k');
    int semid = semget(key, 1, 0);  // flag 0 ensures that it's open for removal
    if (semctl(semid, IPC_RMID, 0) == -1) // used to remove semaphore of semid with IPC_RMID
    {
        perror("");
        exit(1);
    }
    printf("Semaphore removed.\n");

    return 0;
}

