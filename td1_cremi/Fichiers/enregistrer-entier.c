#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define INTSIZE 64

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

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Wrong numbre of argument\n Usage: %s filename position value", argv[0]);
        return EXIT_FAILURE;
    }

    int file = open_wr(argv[1]);
    int position = atoi(argv[2]);
    off_t value = atoi(argv[3]);
    
    
    return 0;
}
