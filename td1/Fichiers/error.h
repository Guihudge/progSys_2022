#include <string.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>


#define exit_with_error(format, ...)                                           \
  do {                                                                         \
    fprintf (stderr, "Error: " format "\n", ##__VA_ARGS__);                    \
    exit (EXIT_FAILURE);                                                       \
  } while (0)

#define check(n, format, ...)                                                  \
  do {                                                                         \
    if ((n) == -1)                                                             \
      exit_with_error (format " (%s)", ##__VA_ARGS__,                   \
                       strerror (errno));                                      \
                                                                               \
  } while (0)

//   check (fd, "Cannot open file \"%s\"", filename);
