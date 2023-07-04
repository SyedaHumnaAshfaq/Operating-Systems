#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char* argv[]){
    char * args [] = {"rmdir","humna",0};
    execvp(args[0],args);
    exit(0);




}