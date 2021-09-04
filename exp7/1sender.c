#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int main()
{

    // creating shared memory region using shm_open
    // name = "ipcshm"
    int fd = shm_open("/ipcshm", O_CREAT | O_RDWR, 0666);

    // setting size of the shared memeory region
    ftruncate(fd, sizeof(int));

    // maps the shm to address space of the process
    int *data = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Reading a number to store
    printf("Enter a number:");
    scanf("%d", &data[0]);

    // unmapping data from fd in the shm area
    munmap(data, sizeof(int));

    // closing the file descriptor
    close(fd);

    return 0;
}