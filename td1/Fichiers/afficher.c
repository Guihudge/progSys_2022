#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUFFIXE ".idx"

void verifier(int cond, char *s)
{
  if (!cond)
  {
    perror(s);
    exit(EXIT_FAILURE);
  }
}

int open_read(char *filename)
{
  int fd = open(filename, O_RDONLY);
  verifier(fd, "Error open file");
  return fd;
}

int open_write(char *filename)
{
  int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0600);
  verifier(fd, "Error open file");
  return fd;
}

int main(int argc, char *argv[])
{
  verifier(argc == 3, "il faut deux paramètres.");

  // construire le chemin au fichier index
  int l = strlen(argv[1]);
  char idx_filename[l + strlen(SUFFIXE) + 1];

  strncpy(idx_filename, argv[1], l);
  strcpy(idx_filename + l, SUFFIXE);

  // On ouvre les fichier
  int file = open_read(argv[1]);
  int index = open_read(idx_filename);
  int log_file = open_write("ERREURS-LIRE.log");
  int line = atoi(argv[2]);

  // on redirige la sortie sur le fichier log
  dup2(STDERR_FILENO, log_file);

  // on récupère la postion dans l'index
  int index_pos = line * sizeof(off_t);

  lseek(index, index_pos, SEEK_SET);
  off_t file_position;
  read(index, &file_position, sizeof(off_t));

  // on lit le gros fichier
  lseek(file, file_position, SEEK_SET);
  char c;

  do
  {
    read(file, &c, sizeof(char));
    write(STDOUT_FILENO, &c, sizeof(char));
  } while (c != '\n');

  return EXIT_SUCCESS;
}
