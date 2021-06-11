// Q3  Write a C program stat.c that prints File type and mode of a given file.

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char *argv[]) {

    printf("%s", argv[1]);

    execv("/usr/bin/file", &argv[1]);

    return 0;
}