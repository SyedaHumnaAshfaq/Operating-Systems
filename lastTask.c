#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(){
    int fd[2];
    pid_t pid;
    if (pipe(fd)==-1 || (pid=fork())==-1)
    {
        printf("ERROR");
        exit(EXIT_FAILURE);
    }
    else 
    {
        if(pid==0)
        {
            if((dup2(fd[1],STDOUT_FILENO)==-1))
            perror("Dup failed");
            else if(close(fd[0])==-1 || close(fd[1])==-1)
        {
            perror("Descriptor failed");
        }
        
            else{
            char * arg[] = {"sort","-o","file.txt","file.txt",NULL};
            execvp("sort",arg);
            perror("fail");
            exit(3);        
            }
        } 
        else{
               char buf[1024];
                int i;
                while((i = read(fd[0], buf, 1024)) > 0)
                {
                    // Do further processing with sorted data
                    // Here we simply write the sorted data to stdout
                    write(STDOUT_FILENO, buf, 1024);
                }
                if(i==-1)
                {
                    perror("Read failed");
                }
            }   
        
    }
    return 1;
}