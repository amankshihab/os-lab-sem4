// Q - 2 C program to list directories in the given directory.

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char *argv[]) {

    if(argc < 1)
        printf("\nNo arguments received.");
    
    else{

        execl("/usr/bin/ls", "ls", "-d", argv[1], NULL);
    }
}