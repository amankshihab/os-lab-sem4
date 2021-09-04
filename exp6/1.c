// Create a C program that does the following
// 1. Takes a filename as an argument
// 2. Creates a child process
// 3. Execute ‘cat‘ command in the child
// 4. Call ‘wait()‘ so that parent blocks until child terminates

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Argument Error.\n");
        return 1;
    }

    char *name = argv[1];
    int status;

    pid_t p = fork();

    if (p < 0)
    {
        printf("Fork Error.\n");
    }
    else if (p == 0)
    {
        printf("\nInside parent!");
        printf("\nWaiting for child!");
        wait(&status);
    }
    else
    {

        execlp("/usr/bin/cat", "cat", name, NULL);
    }
    return 0;
}