#include "essayer.h"
#include <stdio.h>
#include <stddef.h>

void toto(void *p)
{
  printf("toto\n");
}

void titi(void *p)
{
  printf("debut de titi\n");
  printf("attention un segv arrive...\n"); 
  *(volatile int *)0L = 12;
  printf("fin de titi\n");
}

void tutu(void *p)
{
  printf("debut de tutu\n");
  printf("** essai de toto dans essai de tutu : %s\n", essayer(toto, NULL, SIGSEGV) == 0 ? "ok" : "echec");
  printf("attention un segv arrive...\n"); 
  *(volatile int *)0L = 12;
  printf("fin de tutu\n");
}

int main(int argc, char *argv[])
{
  printf("* essai de toto : %s\n", essayer(toto, NULL, SIGSEGV) == 0 ? "ok" : "echec");
  printf("* essai de titi : %s\n", essayer(titi, NULL, SIGSEGV) == 0 ? "ok" : "echec");

  // cf. dernière question
  // printf("* essai de tutu : %s\n", essayer(tutu, NULL, SIGSEGV) == 0 ? "ok" : "echec");
  
  printf("Tout va bien non ?\n");
  
  return 0;
}
