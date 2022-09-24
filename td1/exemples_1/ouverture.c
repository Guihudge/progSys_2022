#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

char *filename = "file.txt";

int main (int argc, char *argv[])
{
  if (argc > 1)
    filename = argv[1];

  int fd = -1;

  // TODO : open the file and check if operation succeeded
  fd = open (filename, O_RDONLY);
  check (fd, "Cannot open file %s", filename);

  printf ("Ouverture réussie : fd = %d\n", fd);

  return EXIT_SUCCESS;
}