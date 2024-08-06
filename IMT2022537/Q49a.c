/*
Question :
Semaphore Implementation: Write a program to implement a semaphore to protect any
critical section:
a. Rewrite the ticket number creation program using a semaphore


Explanation :


User
In the code:

    Decrementing- waiting for the semaphore's value to become greater than 0 before proceeding.
    Incrementing- signaling that the critical section is now available for another process to use.
    The child process waits for permission (semaphore value > 0) to access shared memory, updates ticket count, and releases permission.
    The parent process waits briefly (2 seconds) for access permission, reads ticket count, and then releases permission for others.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

#define SHM_KEY 111
#define SHM_SIZE 1024

int main()
{
    int key = ftok(".", 'k');
    int arg = 1;
    int semid = semget(key, 1, IPC_CREAT | 0644);
    // semaphore is set to value 1
    // and used to protect the crtical section where the shared memory is accessed
    semctl(semid, 0, SETVAL, arg);

    int shmid;
    char *shmaddr;
    struct shmid_ds shminfo;

    //creating a shared memory segment using shmget().
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0644);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }
    printf("Created a shared memory segment.\n");
    // now created shared memory segment is attaches to the address space of the calling process
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }
    printf("Attached the shared memory segment.\n");

    // user gives the input(no.of tickest) and it is stored on shared memory segment
    printf("Enter the number of tickets:\n");
    scanf("%s", shmaddr);


    //CHILD PROCESS IS FORKED - simulate concurrent access to shared memory segment
    int frk = fork();
    if (frk == 0)
    {   
        // decrement
        struct sembuf buf = {0, -1, 0};
        int semid = semget(key, 1, 0); //semaphore identifier 
        semop(semid, &buf, 1);  // waiting for the semaphore to become available 

        //acessing the shared memory - critical section
        printf("Child: Current ticket count: %s\n", shmaddr);
        printf("Child: Enter the new number of tickets:\n");    //user prompt to get new ticket number
        getchar();
        scanf("%s", shmaddr);   // read new ticket number and store in the shared memory

        buf.sem_op = 1; //increment
        semop(semid, &buf, 1);  //release
    }
    else
    {   
        //PARENT process
        //decrement
        struct sembuf buf = {0, -1, 0};
        int semid = semget(key, 1, 0); // semaphore identifier
        sleep(2);   // introducing delay in order to pause its execution any further
        semop(semid, &buf, 1); // waiting for the semaphore to become available

        //critical section
        printf("Parent: Current ticket count: %s\n", shmaddr);

        buf.sem_op = 1; //increment
        semop(semid, &buf, 1);  //release
    }

    if (shmdt(shmaddr) == -1)
    {
        perror("shmdt");
        exit(1);
    }
    printf("Detached the shared memory segment.\n");
    // run q32d.c to remove the semaphore.
}