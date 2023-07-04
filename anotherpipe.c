#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
//write a C program that creates a child process of a parent process, child process 
//communicates an array of integers to parent process. parent process then sums the array
//and communicate sum back to child process, which displays the msg on console
int main()
{
    int fds1[2];
    int fds2[2];
    int child_num[10] = {1,2,3,4,5,6,7,8,9,10};
    // int parent_num[10] = {0,0,0,0,0,0,0,0,0,0};
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
        int sum2[1];
        write(fds1[1],child_num,sizeof(child_num));
        read(fds2[0],sum2,sizeof(sum2));
        printf("%d",sum2[0]);
    }
    else if(pid>0)
    {
        close(fds1[1]);
        close(fds2[0]);
        int arr[10]; 
        
        read(fds1[0],arr,sizeof(arr));
        int sum[1];
        for(int i=0;i<10;i++)
        {
            sum[0]=sum[0]+arr[i];
        }

        write(fds2[1],sum,sizeof(sum));
    }


}
