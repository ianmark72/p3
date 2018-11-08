#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parsing1.h"

char** stringSplit(char* string) {
	char** stringArray = calloc(20, sizeof(char*));
	size_t counter1 = 0;
	size_t counter2 = 0;
	size_t counter3 = 0;
	const int BUF_SIZE = 1024;
	const char space = ' ';
	char* tmpStr;
	char previousChar = space;

	while(counter1 < (unsigned)strnlen(string, BUF_SIZE)) {
		if(string[counter1] != space) {
			if(counter3 == 0) {
				tmpStr = calloc(50, sizeof(char*));
			}
			tmpStr[counter3] = string[counter1];
			counter3++;
		}else if(previousChar != space){
			stringArray[counter2] = tmpStr;
			counter2++;
			counter3 = 0;
		}
		previousChar = string[counter1];
		counter1++;

		if(counter1 == (unsigned)strnlen(string, BUF_SIZE)) {
			stringArray[counter2] = tmpStr;
                }
	}

	//int i = 0;
	//while(stringArray[i] != NULL) {
        //	printf("%i: %s\n", i, stringArray[i]);
	//	i++;
        //}

	return stringArray;
}
void execute(char* cmd ) {
    pid_t pid;
    int status;
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