#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include "mid2.c"
int main(int argc,char * argv[],char * filename ){
    char * arg = {argv[1],argv[2],argv[3]};
    int f1 = open("myfile.txt",O_WRONLY,0777);
    if (f1==-1)
    {
        printf("Error opening file");
    }
    if(argc<2)
    {
        printf("you didn't write any arguments");
    }
    for(int i = 0;i<argc;i++)
    {
        write(f1,arg,sizeof(arg));
    }
    close(f1);
    exit(0);
    execl("./midfile2",argv);


}






















#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <args-file>\n", argv[0]);
        return 1;
    }

    // Open the file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: could not open file '%s'\n", argv[1]);
        return 1;
    }

    // Read each line and print it
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    // Close the file and exit
    fclose(file);
    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    // Read the filename from standard input
    char filename[1024];
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        fprintf(stderr, "Error: could not read filename from input\n");
        return 1;
    }

    // Remove the newline character from the end of the filename
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    // Build the command string
    char command[2048];
    snprintf(command, sizeof(command), "cat %s | grep %s", filename, argv[1]);

    // Execute the command and print the output
    FILE *pipe = popen(command, "r");
    if (pipe == NULL) {
        fprintf(stderr, "Error: could not execute command '%s'\n", command);
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), pipe) != NULL) {
        printf("%s", line);
    }

    // Close the pipe and exit
    pclose(pipe);
    return 0;
}