#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
    int fd[2];
    pipe(fd);
    if(pipe(fd)==-1)
      {exit(EXIT_FAILURE);}
    printf("Value of fd[0]: %d \n",fd[0]);
    printf("Value of fd[1]: %d",fd[1]);

}