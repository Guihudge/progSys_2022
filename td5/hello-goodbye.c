#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_barrier_t my_barrier;

void *HelloGoodbye(void *p)
{
  printf("%p: bonjour\n", pthread_self()); 
  pthread_barrier_wait(&my_barrier);
  sleep(1);
  printf("%p: a bientot\n", pthread_self()); 

  return NULL;
}

int 
main(int argc, char *argv[])
{
 
  int nb_theards = atoi(argv[1]);
  pthread_t tids[nb_theards];

  pthread_barrier_init(&my_barrier, NULL, nb_theards);

  for (int i = 0; i < nb_theards; i++)
  {
    pthread_create(tids+i, NULL, HelloGoodbye, NULL);
  }

  for (int i = 0; i < nb_theards; i++)
  {
    pthread_join(tids[i], NULL);
  }

  pthread_barrier_destroy(&my_barrier);
  
  printf("Finish!\n");

  return EXIT_SUCCESS;
}
