
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFSIZE 4096

int tailRegularFile(int inputFD, int outputFD, int numlines)
{
    int nbLineFound = 0;
    int completBufferRead = 1;
    int startWritingPosition = 0;
    bool endOfFile = false;

    char *buffer = malloc(sizeof(char) * BUFSIZE);
    off_t fileSize = lseek(inputFD, 0, SEEK_END);

    if (fileSize < BUFSIZE)
    {
        lseek(inputFD, 0, SEEK_SET);
        endOfFile = true;
    }
    else
    {
        lseek(inputFD, fileSize - BUFSIZE, SEEK_SET);
    }

    do
    {
        int sizeRead = read(inputFD, buffer, BUFSIZE);

        if (sizeRead < BUFSIZE)
        {
            endOfFile = true;
        }

        for (int i = sizeRead; i >= 0; i--)
        {
            if (buffer[i] == '\n' || (endOfFile && i == sizeRead))
            {
                nbLineFound++;
                if (nbLineFound == numlines+1)
                {
                    if (endOfFile)
                    {
                        startWritingPosition += fileSize - i;
                    }
                    else
                    {
                        startWritingPosition += BUFSIZE - i;
                    }
                    break;
                }
            }
        }

        if (nbLineFound < numlines)
        {
            startWritingPosition += sizeRead;
            completBufferRead++;
            if (completBufferRead * BUFSIZE > fileSize)
            {
                lseek(inputFD, 0, SEEK_SET);
            }
            else
            {
                lseek(inputFD, fileSize - (BUFSIZE * completBufferRead), SEEK_SET);
            }
        }
    } while (nbLineFound < numlines && !endOfFile);
    if (endOfFile && nbLineFound < numlines)
    {
        return 1;
    }

    int readChar = 0;
    lseek(inputFD, fileSize - startWritingPosition +1, SEEK_SET);
    do
    {
        readChar = read(inputFD, buffer, BUFSIZE);
        write(outputFD, buffer, readChar);
    } while (readChar > 0);

    return 0;
}

int main(int argc, char const *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    if (fd <= 0)
    {
        perror("fail to oppen mytail.c\n");
    }

    return tailRegularFile(fd, STDOUT_FILENO, 10);
}
