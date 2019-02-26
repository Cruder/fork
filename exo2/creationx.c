#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <errno.h>
#define CLE 101

void main(void) {
	int id;
	struct shmid_ds shm;

	id = shmget((key_t) CLE, 100, IPC_CREAT | 0700);
	if (id == -1) {
		perror("\nerreur shmget()\n");
		exit(0);
	}
	printf("\nSHM id : %d\n", id);
}
