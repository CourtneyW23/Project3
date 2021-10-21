#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "sem.h"

#define MEM_SIZE 20
/*
int main(int argc, char *argv[])
           {
               int semid, shmid, i;
               union semun arg;
               struct sembuf sop;
               char *addr;
	       time_t tmptr;
	       char *tm;

	       tmptr = time(NULL);
	       tm = ctime(&tmptr);


               shmid = shmget(ftok(".",200), MEM_SIZE, IPC_CREAT | 0600);
               if (shmid == -1)
                   perror("shmget");

               semid = semget(ftok(".",100), 1, IPC_CREAT | 0600);
               if (shmid == -1)
                   perror("shmget");


               addr = shmat(shmid, NULL, 0);
               if (addr == (void *) -1)
                   perror("shmat");


               arg.val = 1;
               if (semctl(semid, 0, SETVAL, arg) == -1)
                   perror("semctl");
	       
	       sop.sem_num = 0;
               sop.sem_op = -1;
               sop.sem_flg = 0;

               if (semop(semid, &sop, 1) == -1)
                   perror("semop");

	       for (i = 0; i < atoi(argv[1]); i++)
        	{
           	    sleep (atoi(argv[2]));
          	    printf ("[time: %s] print from ID: %ld\n", tm, (long)getpid ());
        	}
	       
	       sop.sem_num = 0;
               sop.sem_op = 1;
               sop.sem_flg = 0;

               if (semop(semid, &sop, 1) == -1)
                   perror("semop");


		
	       if (shmdt(addr) == -1)
                   perror("shmdt");
               if (shmctl(shmid, IPC_RMID, NULL) == -1)
                   perror("shmctl");
               if (semctl(semid, 0, IPC_RMID, arg) == -1)
                   perror("semctl");

               exit(EXIT_SUCCESS);
	
	       return 0;	       
 }
 */

int main (int argc, char *argv[])
{
  int i;
  if (argc != 3) {
    printf ("Usage: %s loop_c sleeptime\n", argv[0]);
    return 1;
  }

  for (i = 0; i < atoi(argv[1]); i++)
  {
    sleep (atoi(argv[2]));
    printf ("print from ID: %ld\n", (long)getpid ());
  }
  return 0;
}

