#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main() 
{
    int x = 100;
    printf("%d\n", x);
    int rc = fork();
    if (rc < 0) 
    { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) 
    { // child (new process)
        x += 10;                        // Child hat eigenen Speicherbereich, daher wird x nicht verändert	
        printf("x child: %d\n", x);
    } else 
    { // parent goes down this path (main)
        x += 20;                        // Parent hat eigenen Speicherbereich, daher wird x nicht verändert
        printf("x parent: %d\n", x);
    }
    return 0;
}
//Memory isolation: The parent and child processes each have their own copy of the variable x. Changes in one process do not affect the other.
//Fork: This creates two separate processes running independently. The child process is a copy of the parent process, 
// including the memory state at the time of the fork.