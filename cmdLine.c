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
    char** split = stringSplit(cmd);
    if (pid == -1) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
    else if ( pid > 0) {
        wait(NULL);
    }
    else {
        execvp(split[0], split);
    }
}
