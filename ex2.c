/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#define MILLION 1000000L

void function_to_time(void);

int main (int argc, char *argv[]) {
double timedif;
struct timespec tpend, tpstart;
int i, n;

if (clock_gettime(CLOCK_REALTIME, &tpstart) == -1) { 
	perror("Failed to get starting time"); 

return 1;
}

n = atoi(argv[1]);

for(i = 0; i < n; i++){
function_to_time(); // timed code goes here
}

if (clock_gettime(CLOCK_REALTIME, &tpend) == -1) {
	perror("Failed to get ending time"); 

return 1;
}

timedif = (tpend.tv_sec - tpstart.tv_sec) + (tpend.tv_nsec - tpstart.tv_nsec)/1000;

printf("The function_to_time took %f microseconds\n", timedif); 

 return 0;
 }

void function_to_time(void){

	printf("working\n");
 	sleep(1);
	
}*/

/*#include <sys/time.h>
#include <stdio.h>

int main() {
  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  printf("working\n");
        sleep(1);
  printf("seconds : %f\n micro seconds : %ld\n",
    (double)current_time.tv_sec/1000000000, current_time.tv_usec);

  return 0;
}
*/

/* Program to demonstrate time taken by function fun() */
/*
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

// A function that terminates when enter key is pressed
void fun()
{
	int i;
    printf("fun() starts \n");
    for( i = 0; i < 10; i++) 
    {
        printf("working\n");
	sleep(1);
           
    }
    printf("fun() ends \n");
}

// The main program calls fun() and measures time taken by fun()
int main()
{
    // Calculate the time taken by fun()
    clock_t t;
    t = clock();
    fun();
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("fun() took %f seconds to execute \n", time_taken);
    return 0;
}*/

/*#include <stdlib.h>
#include <stdio.h>
#include <time.h>       // for time()
#include <unistd.h>     // for sleep()

// main function to find the execution time of a C program
int main(int argc, char *argv[])
{
    time_t begin = time(NULL);
	int i;
	int n = atoi(argv[2]);
	int opt;
	int sec = 100; // default value

	while ((opt = getopt(argc, argv, "t:")) != -1) {
		switch (opt) {
			case 't':
				sec = atoi(optarg);
				time_t end = time(NULL);
				// calculate elapsed time by finding difference (end - begin)
				printf("The elapsed time is %d seconds\n", (end - begin));


				break;
			default:
				perror("runsim: Error: getopt");
				exit(1);
		}
	}

   // do some stuff here
    	for(i = 0; i < n; i++){
		if(n > 20){
                        printf("greater than 20");
                        exit(0);
                }

     	    printf("working\n");
    		sleep(1);
	}
    
    time_t end = time(NULL);


    // calculate elapsed time by finding difference (end - begin)
    printf("The elapsed time is %d seconds\n", (end - begin));

    return 0;
}*/

/*#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void sig_handler(int signum){

  printf("Inside handler function\n");
}

int main(){

  signal(SIGALRM,sig_handler); // Register signal handler

  alarm(2);  // Scheduled alarm after 2 seconds

  for(int i=1;;i++){

    printf("%d : Inside main function\n",i);
    sleep(1);  // Delay for 1 second
}
return 0;
}*/

/* catch_SIGHUP.c

   Catch the SIGHUP signal and display a message.

   Usage: catch_SIGHUP [x] [ > logfile 2>&1 ]
*/
#if ! defined(_XOPEN_SOURCE) || _XOPEN_SOURCE < 500
#define _XOPEN_SOURCE 500
#endif
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>  /* Type definitions used by many programs */
#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */
#include <stdbool.h>    /* 'bool' type plus 'true' and 'false' constants */

static void
handler(int sig)
{
}
int
main(int argc, char *argv[])
{
    pid_t childPid;
    struct sigaction sa;

    setbuf(stdout, NULL);       /* Make stdout unbuffered */

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGHUP, &sa, NULL) == -1)
        perror("sigaction");

    childPid = fork();
    if (childPid == -1)
        perror("fork");

    if (childPid == 0 && argc > 1)
        if (setpgid(0, 0) == -1)       /* Move to new process group */
            perror("setpgid");

    printf("PID=%ld; PPID=%ld; PGID=%ld; SID=%ld\n", (long) getpid(),
            (long) getppid(), (long) getpgrp(), (long) getsid(0));

    alarm(10);                  /* An unhandled SIGALRM ensures this process
                                   will die if nothing else terminates it */
    for (;;) {                  /* Wait for signals */
        pause();
        printf("%ld: caught SIGHUP\n", (long) getpid());
    }
}
