#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define INTSIZE 64

void verifier(int cond, char *s)
{
  if (!cond)
  {
    perror(s);
    exit(EXIT_FAILURE);
  }
}

void ecrire(int fd, off_t value)
{
  int status = write(fd, &value, sizeof(off_t));
  verifier(status, "Error on writing file: ");
}

int open_wr(char *filename)
{
  int fd = open(filename, O_WRONLY | O_CREAT, 0600);
  verifier(fd, "Error open file");
  return fd;
}

int main(int argc, char *argv[])
{
  //check argument
  if (argc != 4)
  {
    fprintf(stderr, "Wrong numbre of argument\n Usage: %s filename position value", argv[0]);
    return EXIT_FAILURE;
  }

  //setup variable and open file
  int file = open_wr(argv[1]);
  int offset = atoi(argv[2])*sizeof(off_t);
  off_t value = atoi(argv[3]);

  //Moving in file
  off_t position = lseek(file, offset, SEEK_SET);
  if (position != offset){
    perror("Error when moving in file\n");
  }
  

  //write value and close file
  ecrire(file, value);
  close(file);
  return EXIT_SUCCESS;
}
