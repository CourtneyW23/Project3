#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "limits.h"
#include "config.h"

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                                   } while (0)
union semun {   /* Used in calls to semctl() */
      int val;
      struct semid_ds *buf;
      unsigned short *array;
      #if defined(__linux__)
      struct seminfo *__buf;
      #endif
};

struct shmseg {
   int cntr;
   int write_complete;
   int read_complete;
};

pid_t r_wait(int *stat_loc) {
   pid_t retval;
   while (((retval = wait(stat_loc)) == -1) && (errno == EINTR)) ;
   return retval;
}

void logmsg(const char *msg){
        FILE *f;
        char *log;
        int i;
        time_t t;
        char *tm;

        t = time(NULL);
        tm = ctime(&t);

        f = fopen(msg, "a");
        if(!f)
        {
                perror("Error opening file: ");
                exit(0);
        }

        if(log == NULL)
        {
                printf("Empty Log\n");
                exit(0);
        }
        log = tm;

        fprintf(f, "%s\n", log);
        fclose(f);

}

static void handler(int sig)
{
   const char *name = "logfile.txt";
   printf("Caught signal %d, coming out...\n", sig);
   logmsg(name);
   exit(1);
}


void docommand ( char *cline){
	pid_t grandchild;
	
	if (grandchild == 0){
		execlp ("./testsim", "./testsim", NULL);
	}
}

int main(int argc, char *argv[]){
    int semid, shmid, nlicense, count;
    int i, status, exit_status, n;
    int val, opt, timer = 100;
    union semun arg;
    struct sembuf sop[1];
    char *shmp;
    char buff[MAX_CANON];
    char **myargv;
    pid_t child, grandchild;
    struct sigaction sa;
     const char *name = "logfile.txt";

    setbuf(stdout, NULL); 

    while ((opt = getopt(argc, argv, "t:")) != -1) {
		switch (opt) {
			case 't':
				timer = atoi(optarg);
				break;
			default:
				perror("getopt");
				exit(1);
		}
	}

    /* Create shared memory and semaphore set containing one
                  semaphore */

     shmid = shmget(ftok(".", 200), sizeof(char), IPC_CREAT | 0666);
     if (shmid == -1)
         errExit("shmget");

     semid = semget(ftok(".", 300), 1, IPC_CREAT | 0666);
     if (shmid == -1)
         errExit("shmget");

    // Attach shared memory into our address space 

     shmp = shmat(shmid, NULL, 0);
     if (shmp == (void *) -1)
         errExit("shmat");

    // Initialize semaphore 0 in set with value 1 

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGHUP, &sa, NULL) == -1)
        perror("sigaction");

     //sigalarm();
    arg.val=1;
    semctl(semid,0,SETVAL,arg);
 
    sop[0].sem_num=0;
    sop[0].sem_flg=0;

    signal(SIGINT, handler);
    alarm(timer);
    while (fgets(buff, MAX_CANON, stdin) != NULL) {
    n = atoi(argv[2]);
    for ( i = 0; i < n; i++){
      child = fork();
      if (child == 0){//i am child 
	      sop[0].sem_op=-1;  //set semaphore, "occupied" 
	      semop(semid,sop,1);//I lock semaphore 1
	      printf("childpid = %d\n", getpid());
	      sleep(1);
	      sop[0].sem_op=1;
	      semop(semid,sop,1);//release semaphore
	      //docommand(shmp);
	      if (grandchild == 0)
              	execlp ("./testsim", "./testsim", NULL);
	      	printf("execlp error\n");
              	sleep(1);
	     //alarm(timer);
      	     //while(1);
	       
    }else if(child > 0){
    //parent
      sleep(2);
      sop[0].sem_op = -1;
      semop(semid,sop,1);//try to "occupy" semaphore
      //do action
      printf("parent = %d\n", getpid());
      //Remove  immediately  the semaphore set
      semctl(semid,0,IPC_RMID,arg);
      //alarm(timer);
      //while(1);
      }
    }
      while( (waitpid(child, &status, WNOHANG)) == 0 ){
		sleep(1);
		}
		if (WIFEXITED(status)){
			exit_status = WEXITSTATUS(status);
		}
			exit(0);
//	alarm(timer);
      	while(1);
    }
     /* Remove shared memory and semaphore set */
    
     if (shmdt(shmp) == -1)
        errExit("shmdt");
     if (shmctl(shmid, IPC_RMID, 0) == -1)
         errExit("shmctl");

     kill(shmid, SIGKILL);
    
     exit(EXIT_SUCCESS);

     return 0;
}
