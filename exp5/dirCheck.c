// Q4. Write a C program that checks whether a directory by name “fisat” exists in the current directory

#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char *argv[]) {

    struct stat buf;

    stat(argv[1], &buf);

    if(S_ISDIR(buf.st_mode)){
        printf("Directory exists!\n");
    } else {
        printf("Directory does'nt exist!\n");
    }

    return 0;
}