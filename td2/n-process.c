#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of argument!");
    return EXIT_FAILURE;
  }

  int number_of_process = atoi(argv[1]);
  for (int i = 0; i < number_of_process; i++) {
    pid_t child = fork();
    if (child == 0) {
      printf("Je suis le numero: %d\n", i);
      return 0;
    }
  }
  int status;
  for (int i = 0; i < number_of_process; i++) {
    waitpid(-1, &status, 0);
  }
  printf("je suis le père! Et c'est fini!\n");
  return 0;
}
