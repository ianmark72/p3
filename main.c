#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fp;
	char Makefile[] = "Makefile";
	char makefile[] = "makefile";
	
	fp = fopen(Makefile, "r");
	if(fp == NULL) {
		fp = fopen(makefile, "r");
		if(fp == NULL) {
			perror("No makefile found.");
			exit(0);
		}
	}

	//Pass to parsing.
}

