// Q - 2 C program to list directories in the given directory.

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[])
{

  if (argc < 2)
  {
    printf("\nEnter the arguments!");
    return 1;
  }

  DIR *d;

  struct dirent *de;

  d = opendir(argv[1]);
  while (de = readdir(d))
  {

    if (de->d_type == DT_DIR)
    {
      printf("%s\n", de->d_name);
    }
  }

  return 0;
}