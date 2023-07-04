#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
//write a C program that creates a child process of a parent process, child process 
//communicates its name to parent process. parent process then concatenates the child
//name with it's name and communicate it back to child process, which displays the msg on console
int main()
{
    int fds1[2];
    int fds2[2];
    char child_name[10] = {"child"};
    char parent_name[20] = {"parent"};
    pid_t pid;
    pipe(fds1);
    pipe(fds2);

    pid=fork();

    if (pid==-1)
    {
        exit(EXIT_FAILURE);
    }
    
    if (pid==0)
    {
        close(fds1[0]);
        close(fds2[1]);
        char arr2[50];
        write(fds1[1],child_name,sizeof(child_name));
        read(fds2[0],arr2,sizeof(arr2));
        printf("%s",arr2);
    }
    else if(pid>0)
    {
        close(fds1[1]);
        close(fds2[0]);
        char arr[50]; 
        
        read(fds1[0],arr,sizeof(arr));
        strcat(parent_name,arr);
        write(fds2[1],parent_name,sizeof(parent_name));
    }


}
