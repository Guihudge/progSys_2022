#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void print_option_list(char *const argv[]){
    int i = 0;
    while (argv[i] != NULL)
    {
        printf("%s ", argv[i]);
        i++;
    }
    printf("\n");
}

int System( char* const argv[], char* file)
{
    pid_t exec_process = fork();

    if (exec_process == 0)
    {
        int state = execvp(file, argv);
        perror(file);
        exit(state);
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
        fprintf(stderr, "not egnoth argument.\n");
        return EXIT_FAILURE;
    }

    char* option_list[(argc)]; //-2 pour enlever le nom du programme + la command et +1 pour ajouter le NULL à la fin.

    for (int i = 0; i < argc-1; i++){
        option_list[i] = argv[i+1];
    }

    option_list[argc-1] = NULL;


    printf("******commande\n");

    printf("file: %s\n", argv[1]);
    printf("option: ");
    print_option_list(option_list);

    printf("\n******execution\n");
    int exec_status = System(option_list, argv[1]);

    printf("******Exit Code: %d\n", exec_status);
    if(exec_status != 0){
        perror("Error on execution: ");
    }

    return exec_status;
}
