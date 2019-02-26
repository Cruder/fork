#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>


void main(void) {
    int ret;
    char str1[] = "/tmp/tube1";
    char str2[] = "/tmp/tube2";
    printf("%s\n", str1);
    printf("%s\n", str2);

    ret = mkfifo(str1, 0700);
    if (ret == -1) {
        perror("mkfifo:");
    }

    ret = mkfifo(str2, 0700);
    if (ret == -1) {
        perror("mkfifo:");
    }

    FILE *file;
    file = fopen("PARAM", "w");
    fprintf(file, "%s\n", str1);
    fprintf(file, "%s\n", str2);
    fclose(file);
}
