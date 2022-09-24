#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUFFIXE ".idx"
#define BUF_SIZE 2048

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
  int fd = open(filename, O_RDONLY, 0600);
  verifier(fd, "Error open file");
  return fd;
}

int open_write(char *filename)
{
  int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
  verifier(fd, "Error open file");
  return fd;
}

off_t lire(int fd, off_t size)
{
  off_t value;
  int status = read(fd, &value, size);
  verifier(status, "Error on read");
  return value;
}

int main(int argc, char *argv[])
{
  verifier(argc == 2, "il faut un paramètre.");

  // construire le chemin au fichier index
  int l = strlen(argv[1]);
  char idx_filename[l + strlen(SUFFIXE) + 1];
  strncpy(idx_filename, argv[1], l);
  strcpy(idx_filename + l, SUFFIXE);

  // ouverture du fichier et préparation de variable
  int file = open_read(argv[1]);
  int index = open_write(idx_filename);
  int position_in_index = 0;
  char c;
  int read_length = 0;
  off_t position = 0;

  // on ajoute la ligne 0 dans l'index
  write(index, &position, sizeof(off_t));
  position_in_index += sizeof(off_t);
  lseek(index, position_in_index, SEEK_SET);

  do
  {
    read_length = read(file, &c, 1);

    if (c == '\n')
    {
      position = lseek(file, 0, SEEK_CUR);    // On récupére la position dans le gros fichier
      write(index, &position, sizeof(off_t)); // on écrit dnas l'index
      position_in_index += sizeof(off_t);
      lseek(index, position_in_index, SEEK_SET);
    }
  } while (read_length > 0);

  close(index);
  close(file);

  return EXIT_SUCCESS;
}
