#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status;
    if (argc != 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd[2];
    pid_t pid;
    if (pipe(fd) == -1 || (pid = fork()) == -1)
    {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (pid == 0)
        {
            if (dup2(fd[1], STDOUT_FILENO) == -1)
                perror("Dup failed");
            else if (close(fd[0]) == -1 || close(fd[1]) == -1)
                perror("Descriptor failed");
            else
            {
                char *arg[] = {"cat", "myfile", "|", "grep","orange", NULL};
                execvp("cat", arg);
                perror("fail");0
                exit(3);
            }
        }
        else
        {  
            wait(&status);
        }
    }
    return 0;
}