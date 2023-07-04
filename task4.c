#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    execl("/bin/sort","sort","-o","text.txt","text.txt",NULL);//sort file
}