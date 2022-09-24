#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <fnmatch.h>

int System(const char *command)
{
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

char *genCommand(int argc, char *argv[])
{
    char *base_command = "sh -c ";
    int str_len = strlen(base_command) + 1; // + 1 pour le premier "

    for (int i = 1; i < argc - 1; i++)
    {
        str_len += strlen(argv[i]);
        str_len++; // pour l'espace dans la commande
    }

    char *command = malloc(sizeof(char) * str_len);

    strcat(command, base_command);
    strcat(command, "\"");

    for (int i = 1; i < argc - 1; i++)
    {
        strcat(command, argv[i]);
        strcat(command, " ");
    }

    return command;
}

char *addFilenameToCommand(char *commande, char *filename)
{
    int totalsize = 0;
    totalsize += strlen(commande) + 1 + strlen(filename)+1;

    char *finalCommand = malloc(sizeof(char) * totalsize);

    strcat(finalCommand, commande);
    strcat(finalCommand, " ");
    strcat(finalCommand, filename);
    strcat(finalCommand, "\"");

    return finalCommand;
}

int main(int argc, char *argv[])
{

    char *motif = argv[argc - 1];

    char *fileCommand = genCommand(argc, argv);

    printf("----SUMARRY----\n");
    printf("file commande:   %s\n", fileCommand);
    printf("motif: %s\n", motif);
    printf("--END SUMMARY--\n\n");

    DIR *folder = opendir(".");
    struct dirent *file;
    do
    {
        file = readdir(folder);
        if (file != NULL)
        {
            char *filename = file->d_name;

            if (fnmatch(motif, filename, 0) == 0)
            {
                char *cmd = addFilenameToCommand(fileCommand, filename);
                int execStatus = System(cmd);
                // free(cmd);
                if (execStatus != 0)
                {
                    fprintf(stderr, "Error during execution. Aborted!");
                    return EXIT_FAILURE;
                }
            }
        }

    } while (file != NULL);

    closedir(folder);
    // free(fileCommand);
    return 0;
}
