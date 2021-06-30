// Q-1 - Create a C program that does the following
// 1. Takes a filename as an argument
// 2. Creates a child process
// 3. Execute ‘cat‘ command in the child
// 4. Call ‘wait()‘ so that parent blocks until child terminates

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {

    if(argc < 1)
        printf("No arguments received.");
    else{ 
    
        pid_t process = fork();
        int status;

        if(process == 0){
            execl("/usr/bin/cat", "cat", argv[1], NULL);
            sleep(20);
        } else if(process < 0) {
            printf("\nFailed to create child.\n");
        } else {
            printf("\nInside parent.\n");
            wait(&status);
        }

    }    
    
    return 0;
}