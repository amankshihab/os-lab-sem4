// Q5 Write a C program that prints PID of itself and its parent. You should create a child process and PID
//    of itself and its parent should be printed for both

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main() {

    pid_t process;

    process = fork();

    if(process == -1) {
        printf("Failed to create process.");
    }
    if(process == 0){
        printf("\nSuccessfully created child, pid is %d. My parents pid is %d.\n", getpid(), getppid());
    } 
    else{
        printf("In parent process, pid is %d. My parents pid is %d. My childs pid is %d.", getpid(), getppid(), process);
    }

    return 0;
}