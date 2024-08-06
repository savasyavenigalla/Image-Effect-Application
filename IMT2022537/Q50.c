/*
Deadlock: Develop a program that intentionally induces a deadlock scenario using
semaphores.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define SEM_KEY1 0x1234 // Key for the first semaphore
#define SEM_KEY2 0x5678 // Key for the second semaphore

// Define a union for the semaphore value
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Function to perform the P operation (wait)
void wait(int semid, int sem_num)
{
    struct sembuf op;
    op.sem_num = sem_num;
    op.sem_op = -1; // Decrement the semaphore
    op.sem_flg = 0;
    semop(semid, &op, 1);
}

// Function to perform the V operation (signal)
void signal(int semid, int sem_num)
{
    struct sembuf op;
    op.sem_num = sem_num;
    op.sem_op = 1; // Increment the semaphore
    op.sem_flg = 0;
    semop(semid, &op, 1);
}

// Function for process 1: acquire semaphores in the order of semid1, then semid2
void process1(int semid1, int semid2)
{
    printf("Process 1: Acquiring semaphore 1...\n");
    wait(semid1, 0); // Acquire semaphore 1
    printf("Process 1: Acquired semaphore 1. Sleeping for 2 seconds...\n");
    sleep(2); // Sleep for 2 seconds

    printf("Process 1: Acquiring semaphore 2...\n");
    wait(semid2, 0); // Attempt to acquire semaphore 2
    printf("Process 1: Acquired semaphore 2.\n");

    // Release the semaphores
    signal(semid1, 0);
    signal(semid2, 0);
    printf("Process 1: Released semaphores.\n");
}

// Function for process 2: acquire semaphores in the order of semid2, then semid1
void process2(int semid1, int semid2)
{
    printf("Process 2: Acquiring semaphore 2...\n");
    wait(semid2, 0); // Acquire semaphore 2
    printf("Process 2: Acquired semaphore 2. Sleeping for 2 seconds...\n");
    sleep(2); // Sleep for 2 seconds

    printf("Process 2: Acquiring semaphore 1...\n");
    wait(semid1, 0); // Attempt to acquire semaphore 1
    printf("Process 2: Acquired semaphore 1.\n");

    // Release the semaphores
    signal(semid2, 0);
    signal(semid1, 0);
    printf("Process 2: Released semaphores.\n");
}

int main()
{
    int semid1; // ID of the first semaphore
    int semid2; // ID of the second semaphore
    union semun sem_union;

    // Create the first semaphore
    semid1 = semget(SEM_KEY1, 1, IPC_CREAT | 0666);
    if (semid1 == -1)
    {
        perror("semget failed");
        exit(1);
    }

    semid2 = semget(SEM_KEY2, 1, IPC_CREAT | 0666);
    if (semid2 == -1)
    {
        perror("semget failed");
        exit(1);
    }

    // Initialize both semaphores to 1
    sem_union.val = 1;
    if (semctl(semid1, 0, SETVAL, sem_union) == -1 || semctl(semid2, 0, SETVAL, sem_union) == -1)
    {
        perror("semctl failed");
        exit(1);
    }

    // Create two child processes
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid1 == 0)
    {
        // Child process 1
        process1(semid1, semid2);
        exit(0);
    }
    else
    {
        // Parent process
        pid2 = fork();
        if (pid2 == -1)
        {
            perror("fork failed");
            exit(1);
        }

        if (pid2 == 0)
        {
            // Child process 2
            process2(semid1, semid2);
            exit(0);
        }
        else
        {
            // Parent process
            // Wait for child processes to finish
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

            // Remove the semaphores
            if (semctl(semid1, 0, IPC_RMID) == -1 || semctl(semid2, 0, IPC_RMID) == -1)
            {
                perror("semctl IPC_RMID failed");
                exit(1);
            }

            printf("Semaphores removed successfully.\n");
        }
    }

    return 0;
}