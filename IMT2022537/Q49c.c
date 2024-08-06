/*Question:
Semaphore Implementation: Write a program to implement a semaphore to protect any critical section:

c. Protect multiple pseudo resources (maybe two) using a counting semaphore

Explanation :

we use counting sepmaphore as 2 to ensure this.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define SHM_KEY 121
#define SHM_SIZE 1024

// represents the critical section where the pseudo resources are accessed
int file_write(int key, int fd)
{
    // decrementation
    struct sembuf buf = {0, -1, 0};
    int semid = semget(key, 1, 0);
    semop(semid, &buf, 1);
    printf("Indside the semaphore.\n");
    printf("Value of the semaphore = %d\n", semctl(semid, 0, GETVAL));
    // char data[50];
    // write to file
    fd = open("32c.txt", O_RDWR | O_CREAT, 0777);
    write(fd, "data", sizeof("data"));
    sleep(10);
    // increment
    buf.sem_op = 1;
    semop(semid, &buf, 1);
}

int main()
{
    // here we use counting semaphore with value 2
    // can be used for acting as lock for two pseudo resource(atmost two
    // process can access this resource)
    int key = ftok(".", 'k');
    int arg = 2;
    int semid = semget(key, 1, IPC_CREAT | 0644);
    semctl(semid, 0, SETVAL, arg); // counting semaphore with value = 2

    // one process opening and writing to the file
    int fd = open("32c.txt", O_RDWR | O_CREAT, 0777);
    write(fd, "Hello", sizeof("Hello"));
    // same like previous ones- shared memory
    int shmid;
    char *shmaddr;
    struct shmid_ds shminfo;

    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0644);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }
    printf("Created a shared memory segment.\n");
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }
    printf("Attached the shared memory segment.\n");

    // writing to the shared memory segment
    strcpy(shmaddr, "Hello");

    int frk = fork();
    if (frk == 0)
    {
        if (fork() == 0)
        {
            file_write(key, fd); // child 1
        }
        else
        {
            file_write(key, fd); // child 2
        }
    }
    else
    {
        file_write(key, fd); // parent process
    }
}