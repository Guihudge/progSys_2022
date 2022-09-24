#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#include "error.h"


void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

int open_wr(char* filename){
  int fd = open(filename, O_WRONLY | O_CREAT, 0600);
  verifier(fd, "Error open file");
  return fd;
}

int open_rd(char* filename){
  int fd = open(filename, O_RDONLY);
  verifier(fd, "Error open file");
  return fd;
}

void usage(char* exeption){
  fprintf(stderr, "Error: %s", exeption);
  fprintf(stderr, "\nUsage: copy input_file output_file bufsize\n");
}

int main(int argc, char **argv)
{
  if (argc < 4)
  {
    usage("Not enoght argument");
    return EXIT_FAILURE;
  }
  else if(argc > 4){
    usage("Too many argument");
    return EXIT_FAILURE;
  }
  int input_file = open_rd(argv[1]);
  int output_file = open_wr(argv[2]);
  int bufsize = atoi(argv[3]);

  char* buffer = malloc(sizeof(char)*bufsize);
  int read_byte = 0;
  int ret_write = 0;

  do
  {
    read_byte = read(input_file, buffer, bufsize);
    //verifier(read_byte, "Error on read.");
    if (read_byte == 0)
    {
      continue;
    }
    
    ret_write = write(output_file, buffer, read_byte);
    verifier(ret_write, "Error on writing file.");
  } while (read_byte > 0);
  

  
 
  return EXIT_SUCCESS;
}
