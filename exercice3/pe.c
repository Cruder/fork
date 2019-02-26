#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int shmid = atoi(argv[1]);

  FILE* file_f = fopen("F", "r");

  for(size_t i = 0; i < 3; ++i) {
    char filename[11];
    sprintf(filename, "/tmp/Tube%d", i + 1);
    int fd = open(filename, O_WRONLY);

    for(size_t j = 0; j < 2; ++j) {
      int number;
      fscanf(file_f, "%d ", &number);

      write(fd, &number, sizeof(number));
    }

    close(fd);
  }

  void* data = shmat(shmid, (void *)0, 0);
  if (data == (void *)(-1)) {
    perror("shmat");
    exit(1);
  }

  for(size_t i = 0; i < 3; ++i) {
    int sum;
    memcpy(&sum, data + sizeof(int) * i, sizeof(sum));

    printf("%d ", sum);
  }

  printf("\n");
  return 0;
}
