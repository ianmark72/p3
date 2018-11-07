#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void execute( ) {

    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
    execvp(cmd, argv);

}