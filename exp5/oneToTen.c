// Q2  Write a C program that prints 1...10 in both parent and child process. Explain the output

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main() {

    pid_t process;

    process = fork();

    for(int i = 1; i < 10; i++) 
        printf("%d", i);

    printf("\n");

    return 0;
}