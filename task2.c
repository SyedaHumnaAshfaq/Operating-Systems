#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    pid_t process  = fork();
    if(process>0)
    {
        execl("/bin/mkdir","mkdir","execfolder",NULL);
    }
    else if(process==0)
    {
        execl("/bin/touch","touch","task3",NULL);
    }
}