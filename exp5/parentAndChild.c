// Q1


#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main() {

    pid_t process;
    
    process = fork();

    if(process == -1)
        printf("Failed to create child process.");
    
    if(process == 0) 
        printf("I am child\n");

    else
        printf("I am parent!\n");

    return 0;
}