// Q3  Write a C program stat.c that prints File type and mode of a given file.

#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char *argv[]) {

    struct stat buf;

    stat(argv[1], &buf);

    printf("%ld\n", buf.st_mode);

    return 0;
}