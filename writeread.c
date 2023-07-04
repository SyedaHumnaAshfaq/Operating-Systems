#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
    int fds[2];
    char message[20]={"Hello world"};
    char msg[11] = {"Humna     "};
    char output[20];
    if(pipe(fds)==-1)
    {
        exit(EXIT_FAILURE);
    }
    write(fds[1],message,sizeof(message));
    read(fds[0],output,sizeof(output));
    printf("%s \n",output);
    write(fds[1],msg,sizeof(msg));
    read(fds[0],output,sizeof(output));
    printf("%s",output);
    exit(EXIT_SUCCESS);
}