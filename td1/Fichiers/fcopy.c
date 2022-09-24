#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#include "error.h"

#define BUFSIZE 1


void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

void usage(char* exeption){
  fprintf(stderr, "Error: %s", exeption);
  fprintf(stderr, "\nUsage: copy input_file output_file\n");
}

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    usage("Not enoght argument");
    return EXIT_FAILURE;
  }
  else if(argc > 3){
    usage("Too many argument");
    return EXIT_FAILURE;
  }
  FILE* input_file = fopen(argv[1], "r");
  FILE* output_file = fopen(argv[2], "w");

  char buffer[BUFSIZ];
  int read_byte = 0;
  int ret_write = 0;

  do
  {
    read_byte = fread(buffer, sizeof(char)*BUFSIZE, BUFSIZE, input_file);
    if (read_byte == 0)
    {
      continue;
    }
    
    ret_write = fwrite(buffer, sizeof(char)*BUFSIZE, BUFSIZE, output_file);
    verifier(ret_write, "Erroron writing file.");
  } while (read_byte > 0);
  
  fclose(input_file);
  fclose(output_file);
  
 
  return EXIT_SUCCESS;
}
