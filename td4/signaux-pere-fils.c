#define XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define NSIGNORT 32

sigset_t mask;

void handler(int sig){
  printf("signal(%d): %s\n",sig, strsignal(sig));
}

int emetteur(int pere, int argc, char * argv[]) {
  int k = atoi(argv[1]);

  sleep(1); 

  for(int i = 0 ; i < k ; i++) 
    for(int j = 2; j < argc; j++){
      kill(pere,atoi(argv[j]));
      sleep(1);
  }

  //sleep(2);
  //kill(pere,9);
  return 0;
}



int recepteur(int fils) {
  printf("récepteur : %d\n", getpid());

  // installation du handler pour tous les signaux non RT  
  struct sigaction new;
  new.sa_flags = 0;
  sigemptyset(&new.sa_mask);
  new.sa_handler = handler;

  for(int sig = 1 ; sig < NSIGNORT ; sig++) {
    if (sig != 9)
    {
      sigaction( sig, &new, NULL); 
    }
  }

  sigprocmask(SIG_UNBLOCK, &mask, NULL);
    
  while(1);
  
  return 0;
}


int main(int argc, char *argv[]){
  sigemptyset(&mask);
  for(int sig = 1 ; sig < NSIGNORT ; sig++){
      sigaddset(&mask, sig);
  }
  
  sigprocmask(SIG_BLOCK, &mask, NULL);

  pid_t pid = fork();
  if (pid == 0)
    emetteur(getppid(),argc,argv);
  else
    recepteur(pid);  
}
