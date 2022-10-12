#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    R,
    W
};

int getExitCode(int status)
{
    if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }
    return WTERMSIG(status) + 128;
}


int main(int argc, char *argv[])
{
    int pipe_tab[2];
    pipe(pipe_tab);

    char *first_command[2];
    first_command[0] = argv[1];
    first_command[1] = NULL;

    pid_t fils = fork();
    if (fils == 0)
    {
        close(pipe_tab[R]);
        dup2(pipe_tab[W], STDOUT_FILENO);
        close(pipe_tab[W]);

        execvp(first_command[0], first_command);
        exit(1);
    }

    pid_t fils2 = fork();
    if (fils2 == 0)
    {
        close(pipe_tab[W]);
        dup2(pipe_tab[R], STDIN_FILENO);
        close(pipe_tab[R]);

        argv += 2;
        execvp(argv[0], argv);
        exit(1);
    }
    
    close(pipe_tab[R]);
    close(pipe_tab[W]);

    int status1;
    int status2;

    waitpid(fils, &status1, 0);
    waitpid(fils2, &status2, 0);

    if (getExitCode(status1) != 0)
    {
        return getExitCode(status1);
    }
    
    return getExitCode(status2);
}