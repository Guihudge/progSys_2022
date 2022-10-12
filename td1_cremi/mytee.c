#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "contant.h"
#include "error.h"

int file_open(char *filename) {
  if (filename == NULL) {
    exit(EXIT_FAILURE);
  }

  int fd = open(filename, O_WRONLY | O_CREAT);
  check(fd, "Cannot open %s file", filename);
  return fd;
}

int main(int argc, char *argv[]) {

  char *filename = "file.txt";
  bool write_to_file = false;
  int fd;

  if (argc >= 2) {
    filename = argv[1];
    write_to_file = true;
  }

  if (write_to_file) {
    fd = file_open(filename);
  }

  char *buffer[BUFSIZE + 1];
  int input_len = 0;
  bool run = true;

  while (run) {
    input_len = read(STDIN_FILENO, buffer, BUFSIZE);
    check(input_len, "Error on reading input");

    if (input_len == 0) {
      run = false;
    }
    if (write_to_file) {
      int state = write(fd, buffer, input_len);
      check(fd, "Cannot write %s file", filename);
    } else {
      buffer[input_len] = '\0';
      printf("%s", buffer);
    }
  }
  return 0;
}