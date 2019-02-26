#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>

#define KEY 101

int main(int argc, char const *argv[]) {
  // Create 6 int into file F
  FILE* file_f = fopen("F", "w");

  for(size_t i = 0; i < 6; ++i) {
    int to_file;
    scanf("%d", &to_file);

    fprintf(file_f, "%d ", to_file);
  }

  // Create 3 named pipe Tube1, Tube2, Tube3
  mkfifo("/tmp/Tube1", 0666);
  mkfifo("/tmp/Tube2", 0666);
  mkfifo("/tmp/Tube3", 0666);

  // Create SHM 3 integers
  struct shmid_ds shm;
  int id_shm;

  id_shm = shmget((key_t)KEY, sizeof(int) * 3, IPC_CREAT | 0700);
  shmat(id_shm, NULL, 0);

  // Init semaphore
  key_t key_sem;
  int id_sem;

  key_sem = ftok("/tmp/sem", 3);
  id_sem = semget(key_sem, 1, IPC_CREAT);

  // Print ID SHM
  printf("%d ", id_shm);

  // Print ID Semaphore
  printf("%d\n", id_sem);
  return 0;
}
