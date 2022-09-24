#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

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

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "not egnoth argument.");
        return EXIT_FAILURE;
    }

    char *base_command = "sh -c ";
    int str_len = strlen(base_command) + 2; // + 2 pour les " pour sh

    for (int i = 1; i < argc; i++)
    {
        str_len += strlen(argv[i]);
        str_len++; // pour l'espace dans la commande
    }

    char *command = malloc(sizeof(char) * str_len);

    strcat(command, base_command);
    strcat(command, "\"");

    for (int i = 1; i < argc; i++)
    {
        strcat(command, argv[i]);
        strcat(command, " ");
    }
    strcat(command, "\"");

    printf("******commande\n");

    printf("%s", command);

    printf("\n******execution\n");
    int exec_status = System(command);

    printf("******Exit Code: %d\n", exec_status);

    return exec_status;
}
