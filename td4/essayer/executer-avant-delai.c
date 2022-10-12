#define _GNU_SOURCE
#include <unistd.h>

#include "essayer.h"


int
executer_avant_delai( void (*fun)(void *), void *parametre, int delai_en_seconde)
{
  fun(parametre);
}
