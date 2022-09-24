
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

char *filename = "primes.bin";

int is_prime (int i)
{
  if ((i & 1) == 0)
    return i == 2;
  
  for (int d = 3; d*d <= i; d += 2) {
    if ((i / d) * d == i)
      return 0;
  }
  return 1;
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    filename = argv[1];

  int fd = open (filename, O_WRONLY | O_CREAT, 0666);
  check (fd, "Cannot open %s file", filename);

  // TODO: write all prime numbers 2 <= p < 100 into file
  for (int i = 2; i < 100; i++) {
    if (is_prime (i))
      write (fd, &i, sizeof(int));
  }
  
  close (fd);
  
  return 0;
}
