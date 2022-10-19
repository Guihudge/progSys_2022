#include <signal.h>
#include <string.h>
#include <stdio.h>

struct sigaction new, old;

void handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("ctrl-c\n");
        
    }
}

int main()
{
    while (1)
    {
        new.sa_flags = 0;
        sigemptyset(&new.sa_mask);
        new.sa_handler = handler;
        sigaction(SIGINT, &new, &old);
    }
}