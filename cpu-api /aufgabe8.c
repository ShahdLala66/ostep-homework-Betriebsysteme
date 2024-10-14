#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
    int pipefd[2]; // File descriptors for the pipe
    if (pipe(pipefd) == -1) //  Create the pipe
    {
        perror("pipe"); // Print an error message
        exit(EXIT_FAILURE); //  Exit the program
    }

    pid_t rc1 = fork(); // Fork a child process
    if (rc1 < 0) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (rc1 == 0) 
    { // First child
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe write end
        close(pipefd[1]); // Close original write end
        execlp("ls", "ls", NULL); // Example command that writes to stdout
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    pid_t rc2 = fork(); // Fork another child process
    if (rc2 < 0) cd -
    {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (rc2 == 0) 
    { // Second child
        close(pipefd[1]); // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe read end
        close(pipefd[0]); // Close original read end
        execlp("wc", "wc", "-l", NULL); // Example command that reads from stdin
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent closes both ends of the pipe
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both children to finish
    wait(NULL);
    wait(NULL);

    return 0;

    //output is the number of files in the current directory 30
}