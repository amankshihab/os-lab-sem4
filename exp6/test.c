#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

#include<stdlib.h>

// int main(int argc, char *argv[]) {

//     pid_t process = fork();

//     if(process == 0){
//         execl("/usr/bin/cat", argv[1], argv[2], NULL);
//     } else if(process < 0) {
//         printf("Failed to create a process :(");
//     } else {

//     }
// }

int main() {

    // pid_t process = fork();

    // if(process == 0) {
    //     printf("Child!");
    // } else {
    //     printf("Parent!");
    //     sleep(10);
    // }


execl("/usr/bin/echo", "echo", "\"Start\" >", "tet.txt", NULL);

    return 0;
}