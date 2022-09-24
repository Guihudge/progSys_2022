#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int System(const char *command){
    pid_t exec_process = fork();

    if (exec_process == 0)
    {
        int state = execl("/bin/sh", "sh", "-c", command, NULL);
        return state;
    }
    int status;
    waitpid(-1, &status, 0);
    return status;
}

int main(int argc, char const *argv[])
{
    System("ls -lah\n");
    return 0;
}
