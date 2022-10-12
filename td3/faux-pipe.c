#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <unistd.h>

#define SUFFIXE ".idx"

void verifier(int cond, char *s) {
  if (!cond) {
    perror(s);
    exit(EXIT_FAILURE);
  }
}

void print_option_list(char *const argv[]) {
  int i = 0;
  while (argv[i] != NULL) {
    printf("%s ", argv[i]);
    i++;
  }
}

int open_w(char *filename)
{
    int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    verifier(fd, "Error open file");
    return fd;
}

int open_r(char *filename)
{
    int fd = open(filename, O_RDONLY);
    verifier(fd, "Error open file");
    return fd;
}

int getExitCode(int status) {
  if (WIFEXITED(status)) {
    return WEXITSTATUS(status);
  }
  return WTERMSIG(status) + 128;
}

int System(char *const argv[])
{
    pid_t exec_process = fork();

    if (exec_process == 0)
    {
        execvp(argv[0], argv);
        perror(argv[0]);
        exit(1);
    }
    int status;
    waitpid(exec_process, &status, 0);
    return getExitCode(status);
}

int main(int argc, char *argv[]) {

    char* filename= "temporary";

    int temp_file = open_w(filename);
    char* first_command[2];
    first_command[0] = argv[1];
    first_command[1] = NULL;

    int save_stdout = dup(STDOUT_FILENO);

    dup2(temp_file, STDOUT_FILENO);
    close(temp_file);

    System(first_command);

    dup2(save_stdout, STDOUT_FILENO);
    print_option_list(argv+2);


    temp_file = open_r(filename);
    int save_stdin = dup(STDIN_FILENO);
    dup2(temp_file, STDIN_FILENO);
    close(temp_file);

    System(argv + 2);

    dup2(save_stdin, STDIN_FILENO);

  return 0;
}