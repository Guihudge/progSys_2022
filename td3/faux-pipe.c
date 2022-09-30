#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUFFIXE ".idx"

void verifier(int cond, char *s)
{
    if (!cond)
    {
        perror(s);
        exit(EXIT_FAILURE);
    }
}

void print_option_list(char *const argv[])
{
    int i = 0;
    while (argv[i] != NULL)
    {
        printf("%s ", argv[i]);
        i++;
    }
}

int open_rw(char *filename)
{
    int fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0600);
    verifier(fd, "Error open file");
    return fd;
}

int getExitCode(int status)
{
    if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }
    return WTERMSIG(status) + 128;
}

int System(char *const argv[], int out, int in)
{
    pid_t exec_process = fork();

    if (exec_process == 0)
    {
        dup2(in, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);
        execvp(argv[0], argv);
        perror(argv[0]);
        exit(1);
    }
    int status;
    waitpid(exec_process, &status, 0);
    return getExitCode(status);
}

int main(int argc, char *argv[])
{

    int temp_file = open_rw("temporary");
    char* first_command[2];
    first_command[0] = argv[1];
    first_command[1] = NULL;

    System(first_command, temp_file, STDIN_FILENO);
    print_option_list(argv+2);
    System(argv + 2, STDOUT_FILENO, temp_file);

    return 0;
}