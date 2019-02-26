#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFSIZE 100

int main(int argc, char* argv[]){
    char bufferParams[2][BUFSIZE];
    FILE* paramFile = fopen("PARAM","r");
    fread(bufferParams[0], 1,5,paramFile);
    printf("%s",bufferParams[0]);
    printf("");


}


