#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parsing1.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	char Makefile[] = "Makefile";
	char makefile[] = "makefile";
	char* target;

	if(argc == 2) {
		strncpy(target, argv[1]);
	}else if(argc > 2) {
		perror("Too many arguments. Limit of one target.");
		exit(0);
	}

	fp = fopen(makefile, "r");
	if(fp == NULL) {
		fp = fopen(Makefile, "r");
		if(fp == NULL) {
			perror("No makefile found.");
			exit(0);
		}
	}

	//Pass to parsing.
	read(fp);
}

