// Q6  Write a C program with 4 calls to fork() as below and print ”Hello” after that. Explain the output.


#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main() {

    fork();
    fork();
    fork();
    fork();

    printf("Hello World!\n");

    return 0;
}