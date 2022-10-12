#ifndef ESSAYER_H
#define ESSAYER_H

#include <signal.h>

int essayer(void  (*f)(void*), void *p, int sig);

#endif
