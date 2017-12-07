#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#define KEY 12341

int main(int argc, char **argv) {

  if (!strcmp(argv[1], "-c")) {
    int sem = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (sem == -1) {
      printf("Semaphore already exists.\n");
    }
    else {
      int val;
      sscanf(argv[2], "%d", &val);
      semctl(sem, 0, SETVAL, val);
      printf("Semaphore created: %d\n", sem);
      printf("Value set: %d\n", val);
    }
  }
  else if (!strcmp(argv[1], "-v")) {
    int sem = semget(KEY, 0, 0);
    printf("Semaphore value: %d\n", semctl(sem, 0, GETVAL));
  }
  else if (!strcmp(argv[1], "-r")) {
    int sem = semget(KEY, 0, 0);
    printf("Semaphore removed: %d\n", semctl(sem, 0, IPC_RMID));
  }
  return 0;
  
}
