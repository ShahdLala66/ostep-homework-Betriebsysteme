//
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int rc = fork(); 
    if(rc < 0) {
        fprintf(stderr, "fork failed\n"); // fork failed
        exit(1);
 } else if(rc == 0) {
        printf("hello\n"); // child (new process)
    } else {
        // wait () is a system call that causes the calling process to
        // be suspended until one of its child processes exits to pervent Zombie processes
     sleep(1); 
     printf("goodbye\n");
    }
    return 0;
}