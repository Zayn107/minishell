#include <stdio.h>
#include <unistd.h>

int main(void)
{
  printf("Main program started\n");
  // argv[0] is the name of the program to be executed, but it could be anything
  // the program is still called if path is correct
  dup2(100, 0);
  char *argv[] = { "ls", "hello", NULL };
//   char* envp[] = { "some", "environment", NULL };
  if (execve("/usr/bin/ls", argv, NULL) == -1)
    perror("Could not execve");
  return 1;
}