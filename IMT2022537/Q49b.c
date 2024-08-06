/*Question:
Semaphore Implementation: Write a program to implement a semaphore to protect any
critical section:

b. Protect shared memory from concurrent write access

explanation :
 code segment initializes a semaphore to protect shared memory,
  waits for permission to access the shared memory using the semaphore,
  modifies the shared memory, and then releases the semaphore after modification.
  Finally, it detaches and removes the shared memory segment.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

#define SHM_KEY 112
#define SHM_SIZE 1024

int main()
{   
    //semaphore value is set to 1
    int key = ftok(".", 'k');
    int arg = 1;
    int semid = semget(key, 1, IPC_CREAT | 0644);
    semctl(semid, 0, SETVAL, arg);

    int shmid;
    char *shmaddr;
    struct shmid_ds shminfo;

    //this shmget allocates shared memory 
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0644);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }
    printf("Created a shared memory segment.\n");
    //attaches it to the address space of the calling process
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }
    printf("Attached the shared memory segment.\n");

    // writing to the shared memory segment
    printf("Enter the number of tickets:\n");
    scanf("%s", shmaddr);

    // decrements(waiting) before the modifying the shared memory
    struct sembuf buf = {0, -1, 0};
    semid = semget(key, 1, 0);
    semop(semid, &buf, 1);  //waits for availability

    // Changing the value of the number of tickets.

    strcpy(shmaddr, "101");
    sleep(10);
    buf.sem_op = 1;
    semop(semid, &buf, 1);  // changed to signal (critical section) available for other process

    if (shmdt(shmaddr) == -1)
    {
        perror("shmdt");
        exit(1);
    }
    printf("Detached the shared memory segment.\n");
    if (shmctl(shmid, IPC_RMID, &shminfo) == -1)
    {
        perror("shmctl");
        exit(1);
    }

    // run q32d.c to remove the semaphore.
}
/*
nly one process can access the shared memory (critical section) at any given time.
 This prevents concurrent write access */