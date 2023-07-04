#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char* argv[]){

printf("first program %d   ", getpid());
fflush(stdout);
execv("./prog2",argv);
printf("Bye Bye first program");

}