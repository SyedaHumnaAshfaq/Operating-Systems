#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<time.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sched.h>

int main()
{
    int fd[2];
    pipe(fd);
    int pid = fork();
    if(pid == 0)
    {
        close(fd[0]);
        dup2(fd[1],1);
        execlp("cat","cat","file.txt",NULL);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0],0);
        execlp("sort","sort","-u",NULL);
    }
    return 0;
}