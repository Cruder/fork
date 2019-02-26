#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int pipe_number = atoi(argv[1]);
  char filename[11];
  sprintf(filename, "/tmp/Tube%d", pipe_number);
  printf("%s\n", filename);

  int semid = atoi(argv[2]);

  close(0);
  int fd;
  fd = open(filename, O_RDONLY);

  int a, b;
  read(fd, &a, sizeof(a));
  read(fd, &b, sizeof(a));

  printf("%d - %d\n", a, b);

  close(fd);
  open(0, O_WRONLY);

  int shmid = atoi(argv[2]);

  printf("shmid %d\n", shmid);

  void* data = shmat(shmid, (void *)0, 0);
  if (data == (void *)(-1)) {
    perror("shmat");
    exit(1);
  }

  int sum = a + b;
  memcpy(data + sizeof(int) * (pipe_number - 1), &sum, sizeof(a));

  shmdt(data);

  struct sembuf semopinc = {
    .sem_num = 0,
    .sem_op = 1,
    .sem_flg = 0
  };
  semop(semid, &semopinc, 1);


  return 0;
}
