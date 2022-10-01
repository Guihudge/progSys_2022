#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print_option_list(char *const argv[]) {
  int i = 0;
  while (argv[i] != NULL) {
    printf("%s ", argv[i]);
    i++;
  }
  printf("\n");
}

int getExitCode(int status) {
  if (WIFEXITED(status)) {
    return WEXITSTATUS(status);
  }
  return WTERMSIG(status) + 128;
}

int System(char *const argv[], char *file) {
  pid_t exec_process = fork();

  if (exec_process == 0) {
    execvp(file, argv);
    perror(file);
    exit(1);
  }
  int status;
  waitpid(exec_process, &status, 0);
  return getExitCode(status);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fprintf(stderr, "not egnoth argument.\n");
    return EXIT_FAILURE;
  }

  printf("******commande\n");

  printf("file: %s\n", argv[1]);
  printf("option: ");
  print_option_list(argv + 1);

  printf("\n******execution\n");
  int exec_status = System(argv + 1, argv[1]);

  printf("******Exit Code: %d\n", exec_status);
  if (exec_status != 0) {
    perror("Error on execution: ");
  }

  return exec_status;
}
