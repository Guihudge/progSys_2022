#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <fnmatch.h>

int getExitCode(int status)
{
    if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }
    return WTERMSIG(status) + 128;
}

int System(char *file, char *const argv[])
{
    pid_t exec_process = fork();

    if (exec_process == 0)
    {
        execvp(file, argv);
        perror(file);
        exit(1);
    }
    int status;
    waitpid(exec_process, &status, 0);
    return getExitCode(status);
}

int main(int argc, char *argv[])
{

    char *motif = argv[argc - 1];

    DIR *folder = opendir(".");
    struct dirent *file;
    do
    {
        file = readdir(folder);
        if (file != NULL)
        {
            argv[argc-1] = file->d_name;

            if (fnmatch(motif, argv[argc-1], 0) == 0)
            {
                int execStatus = System(argv[1], argv+1);

                if (execStatus != 0)
                {
                    fprintf(stderr, "Error during execution. Aborted!");
                    return execStatus;
                }
            }
        }

    } while (file != NULL);

    closedir(folder);
    return 0;
}
