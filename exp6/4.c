// Write a C program that does the following
// 1. Takes two filenames as argument
// 2. Creates a file with name as second argument
// 3. Copies contents from file1 to file2
// 4. First line of file2 should be “Start” and last line should be “Stop”

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

  if (argc < 2)
  {
    printf("Too few arguments!");
    return 1;
  }

  int fd1, fd2;
  char rbuf[100];

  fd1 = open(argv[1], O_RDONLY);
  fd2 = open(argv[2], O_CREAT | O_WRONLY, S_IRWXU);

  char wbuf1[] = "Start\n";

  write(fd2, wbuf1, strlen(wbuf1));
  read(fd1, rbuf, 100);
  write(fd2, rbuf, strlen(rbuf));

  char wbuf2[] = "\nStop";

  write(fd2, wbuf2, strlen(wbuf2));
  close(fd1);
  close(fd2);

  return 0;
}