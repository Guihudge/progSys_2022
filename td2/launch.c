#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int System(const char *command) {
  pid_t exec_process = fork();

  if (exec_process == 0) {
    int state = execl("/bin/sh", "sh", "-c", command, NULL);
    perror("/bin/sh: ");
    exit(state);
    return state;
  }
  int status;
  waitpid(exec_process, &status, 0);
  return status;
}

int main(int argc, char const *argv[]) {
  if (fork() == 0) {
    exit(0);
  }

  System("sleep 1; ls -lah");
  System("echo fin");
  return 0;
}
