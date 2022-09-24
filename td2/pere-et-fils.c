#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    pid_t pere_pid = getpid();
    pid_t fils_pid = fork();

    if (fils_pid == -1)
    {
        perror("Error on creating process: ");
    }
    else if (fils_pid == 0){
        printf("je m'appelle %d et je suis le fils de %d\n", getpid(), pere_pid);
        return 0;
    }

    int status;
    //waitpid(fils_pid, &status, 0);
    printf("je m'appelle %d et je suis le père de %d\n", pere_pid, fils_pid);
    
    return 0;
}
