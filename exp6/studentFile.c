#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

// 1. create student.txt
// 2. user input stu name reg no
// 3. write into student.txt
// 4. Wrote name into name.txt
int main() {

    printf("\nCreating student.txt\n");
    // to create a new file
    // int fd = open("./resources/student.txt", O_CREAT, S_IRWXU);
    int fd = open("./resources/student.txt", O_RDWR);
    printf("\nCreated student.txt\n");
    // int fe = open("./resources/name.txt", O_CREAT || O_RDWR);

    printf("Enter the no. of students:");
    int students;
    scanf("%d", &students);

    for(int i = 0; i < students; i++) {

        printf("Details of student %d:\n", i+1);

        //Reading name
        printf("\nEnter name:");
        char name[50];
        scanf("%s", name);
        //writing name
        write(fd, name, strlen(name));

        // Added new line for beauty
        write(fd, "\n", strlen("\n"));

        // Reading register no.
        printf("\nEnter reg no:");
        char regno[30];
        scanf("%s", regno);
        //Writing register no
        write(fd, regno, strlen(regno));

        // Adding new line for beauty
        write(fd, "\n\n", strlen("\n\n"));

        printf("\nWritten details of student %d.\n", i+1);
    } 

    lseek(fd, 0, SEEK_SET);

    // int fn = open("./resources/name.txt", O_CREAT, S_IRWXU);
    int fn = open("./resources/name.txt", O_RDWR);
    int k = 0;

    while(k != 7) {

        printf("Writing name into names.txt\n");

        char readbuf[100];

        k = read(fd, readbuf, strlen(readbuf));

        for(int j = 0; j < strlen(readbuf); j++){
        if(readbuf[j] >= '1' && readbuf[j] <= '9'){}
        else
            write(fn, readbuf, strlen(readbuf));}

        lseek(fn, 2, SEEK_CUR); k+=1;
    }

    close(fd);
    close(fn);

    return 0;
}
