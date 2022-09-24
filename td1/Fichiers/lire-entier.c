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

off_t lire(int fd){
    off_t value;
    int status = read(fd, &value, sizeof(off_t));
    verifier(status, "Error on read");
    return value;
}

int open_rd(char *filename)
{
  int fd = open(filename, O_RDONLY, 0600);
  verifier(fd, "Error open file");
  return fd;
}

int main(int argc, char *argv[])
{
  //check argument
  if (argc != 3)
  {
    fprintf(stderr, "Wrong numbre of argument\n Usage: %s filename position value", argv[0]);
    return EXIT_FAILURE;
  }

  //setup variable and open file
  int file = open_rd(argv[1]);
  int offset = atoi(argv[2])*sizeof(off_t);

  //Moving in file
  off_t position = lseek(file, offset, SEEK_SET);
  if (position != offset){
    perror("Error when moving in file\n");
  }
  

  //read value and close file
  off_t value = lire(file);
  printf("Value: %d\n", value);
  close(file);
  return EXIT_SUCCESS;
}
