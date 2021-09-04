#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main()
{

    int i;

    void *shared_memory;

    char buffer[100];

    int shmid = shmget((key_t)2345, 1024, 0666 | IPC_CREAT);

    printf("\nKey of shared memory is : %d\n", shmid);

    shared_memory = shmat(shmid, NULL, 0);

    printf("Process attached at %p\n", shared_memory);

    printf("\nEnter the data to write:");
    scanf("%s", buffer);

    strcpy(shared_memory, buffer);

    printf("You wrote:%s\n", (char *)shared_memory);

    return 0;
}