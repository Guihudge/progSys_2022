#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

#define BUFSIZE 4

char *filename = "file.txt";

void lire (int fd)
{
  int n  = 0;
  char buffer[BUFSIZE + 1];

  // TODO : read BUFSIZE bytes from file
  n = read (fd, buffer, BUFSIZE);
  check (n, "Cannot read from file %s", filename);

  buffer[n] = 0;

  printf ("%d octets lus : <%s>\n", n, buffer);
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    filename = argv[1];

  int fd = open (filename, O_RDONLY);
  check (fd, "Cannot open %s file", filename);

  lire (fd); lire (fd);

  close (fd);

  return 0;
}