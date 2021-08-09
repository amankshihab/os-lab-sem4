#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stddef.h>
#include<stdio.h>
#include<unistd.h>

int main() {

    // opening the created share memory
    int fd = shm_open("/ipcshm", O_RDONLY, 0666);

    // retreiveing data in shm area
    int *data = (int *)mmap(NULL, sizeof(int), PROT_READ, MAP_SHARED, fd, 0);

    // calculating factorial
    int i, k;
    for (i = 1, k = 1; i < data[0]; i++, k *= i);
    printf("\nFactorial of %d is %d.\n", data[0], k);

    // unmapping the shm area
    munmap(data, sizeof(int));

    // closing file descriptor
    close(fd);

    shm_unlink("/ipcshm");

    return 0;
}