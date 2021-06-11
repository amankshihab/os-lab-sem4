/* Q1  Write a C program to create a new child process and print “I am child” in parent process and “I am
       Parent” in parent process
*/

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