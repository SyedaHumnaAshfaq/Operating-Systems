#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc,char * argv[])
{
    int fd[2];
    // int buffer[1024];
    // int l;
    // scanf("How many arguments do you want to give %d",n);
     pipe(fd);
    // pid_t pid = fork();
    char * filename  = argv[1];
    // char * anotherfile = argv[2];
   
    // int f2 = open(anotherfile,O_WRONLY,0777);
    int f1 = creat(filename,0777);
    // while(int i = 1;i <= argc;i++)
    char *argf[] = {argv[2],argv[3],argv[4]};
    while()
    {
        write(f1,argf,sizeof(argf));
    }
}