// 4. Write a C program that does the following
// 1. Takes two filenames as argument
// 2. Creates a file with name as second argument
// 3. Copies contents from file1 to file2
// 4. First line of file2 should be “Start” and last line should be “Stop”

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char *argv[]) {

    if(argc < 2) 
        printf("\nEnter all the arguments.\n");
    else {

        // creating a file
        execl("/usr/bin/touch", "touch", argv[2], NULL);

        //writing in start
        execl("/usr/bin/echo", "echo", "\"Start\" >", argv[2], NULL);
    
        // copying first file to second
        execl("/usr/bin/cp", "cp", argv[1], argv[2], NULL);
    
        //writing in stop
        execl("/usr/bin/echo", "echo", "\"Stop\" >", argv[2], NULL);
    }
}