#define XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define NSIGNORT 32

int emetteur(int pere, int argc, char * argv[]) {
  int k = atoi(argv[1]);

  sleep(1); 

  for(int i = 0 ; i < k ; i++) 
    for(int j = 2; j < argc; j++){
      kill(pere,atoi(argv[j]));
  }

  //kill(pere,9);
  return 0;
}



int recepteur(int fils) {
  printf("récepteur : %d\n", getpid());

  // installation du handler pour tous les signaux non RT  

  for(int sig = 0 ; sig < NSIGNORT ; sig++) {
    //sigaction( , , ); 
  }
    
  while(1) 
    pause();
  
  return 0;
}


int main(int argc, char *argv[]){
  pid_t pid = fork();  
  if (pid == 0)
    emetteur(getppid(),argc,argv);
  else
    recepteur(pid);  
}
