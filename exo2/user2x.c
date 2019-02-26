#include <sys/types.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

char *pt;

void writeSHMT() {
  printf("ICI\n");
  strcpy(pt, "BONJOUR2");
  shmdt(pt);
  exit;
}

void main(void) {
  int shm_id, id;
  FILE *file;

  file = fopen("user2PID", "w");
  fprintf(file, "%d", getpid());
  fclose(file);

  file = fopen("PARAM", "r");
  fscanf(file, "%d", &shm_id);
  fclose(file);
  signal(SIGUSR1, writeSHMT);


  sleep(25);

  file = fopen("user1PID", "r");
  fscanf(file, "%d", &id);
  fclose(file);


  pt = (char *) shmat((key_t) shm_id, 0, IPC_NOWAIT);

  if(pt == (char*) -1) {
    perror("\nerreur shmat()\n");
    exit(1);
  }

  printf("\nbuffer = ");
  for(int i = 0; i < 100; i++) {
    printf("%c", pt[i]);
  }
  printf("\n");

  printf("KILL\n");
  kill(id, SIGUSR1);
  while (1);
}
