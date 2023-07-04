#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>

// write a code that makes a  pipe
int main()
{
    int fd[2];
    pipe(fd);
    int pid = fork();
    if(pid == 0)
    {
        close(fd[0]);
        dup2(fd[1],1);
        execlp("ls","ls",NULL);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0],0);
        execlp("wc","wc",NULL);
    }

}

