#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parsing1.h"

void execute(char* cmd ) {
    pid_t pid;
    pid = fork();
    int status = 0;
    char** split = stringSplit(cmd);
    if (pid == -1) {     /* fork a child process           */
          fprintf(stderr, "*** ERROR: forking child process failed\n");
          exit(1);
     }
    else if ( pid > 0) {
        wait(NULL);
    }
    else {
        status = execvp(split[0], split);
	if( status == -1){ 
		fprintf(stderr, "Error executing %s\n", split);
		exit(1);
	}
    }
}
