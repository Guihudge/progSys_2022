
#include "essayer.h"

#include <assert.h>
#include <signal.h>
#include <setjmp.h>
#include <stddef.h>


typedef void (*func_t)(void);


int essayer(void  (*f)(void*), void *p, int sig)
{
    f(p);
    return 0;
}
