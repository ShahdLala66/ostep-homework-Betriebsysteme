#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // open file.txt for writing, create if it doesn't exist, truncate if it does
    // 0644 is the permission mode for the file
    if (fd < 0)
    {
        fprintf(stderr, "open file failed\n");
        exit(1);
    }

    int x = 100;
    
    // Flush the file descriptor to ensure any buffered data is written before forking
    fsync(fd);
    
    int rc = fork();
    if (rc < 0)
    { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    { // child (new process)
        dprintf(fd, "x child: %d\n", x);
    }
    else
    { // parent goes down this path (main)
    //wait(NULL); // wait for the child process to finish
        dprintf(fd, "x parent: %d\n", x);
    }

    close(fd);
    return 0;
}
