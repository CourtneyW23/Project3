#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


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


int main() {
	const char *name = "logfile.txt";


	 logmsg(name);

 

	 return 0;

}
