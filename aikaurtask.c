#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>

int main()
{
    int fds[2];
    pipe(fds);
    char output[50];
    char Read[50];
    char output1[50];
 
    for(int i=0;i<3;i++)
    {
        
        scanf("%s",Read); 
        write(fds[1],Read,sizeof(Read));
        read(fds[0],output,sizeof(output));
        if(i==0)
        {
            strcpy(output1,output);
        }
        else
        {
            strcat(output1,output);
        }
        

    }
    printf("%s \n",output1);

    exit(EXIT_SUCCESS);
}