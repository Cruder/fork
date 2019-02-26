#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define PATH_PIPE_LEN 11

int main(int argc, char* argv[]){
    char *writeBuffer = "Hey, salut Bigard!";
    char readBuffer[100];
    int pid, fd[2];
    char namedPipe[2][PATH_PIPE_LEN];
    int paramFile = open("PARAM",O_RDONLY);

    read(paramFile,namedPipe[0],10);
    lseek(paramFile,11,0);
    read(paramFile,namedPipe[1],10);
    printf("(%s:%s)\n",namedPipe[0],namedPipe[1]);

    pid=fork();
    if(pid==-1){
        perror("Failed fork");
        exit(EXIT_FAILURE);
    }
    if(pid>0){
        close(0);
        fd[1]=open(namedPipe[1],O_RDONLY);
        if(fd[1]==-1){
            perror("\nerreur open en lecture\n");
            exit(EXIT_FAILURE);
        }
        sleep(1);
        read(fd[1],readBuffer,100);
        printf("John: %s\n",readBuffer);
    }
    else{
        close(1);
        fd[0] = open(namedPipe[0],O_WRONLY);
        if(fd[0]==-1){
            perror("\nerreur open en ecriture\n");
            exit(EXIT_FAILURE);
        }
        write(fd[0],writeBuffer, strlen(writeBuffer));
    }


}


