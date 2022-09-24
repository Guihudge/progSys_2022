#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

#define BUFSIZE 4

char *filename = "file.txt";

void lire (int fd)
{
  char buffer[BUFSIZE + 1];

  int n = read (fd, buffer, BUFSIZE);
  check (n, "Cannot read from %s file", filename);

  buffer[n] = 0;
  printf ("%d octets lus : <%s>\n", n, buffer);
}

void ecrire (int fd)
{
  // TODO: write something!
  int n = write (fd, "Bonjour vous", 12);
  check (n, "Cannot write into file %s", filename);
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    filename = argv[1];

  int fd = open (filename, O_RDWR);
  check (fd, "Cannot open %s file", filename);

  lire (fd);
  ecrire (fd);

  close (fd);

  return 0;
}