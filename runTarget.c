#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "graphBuilder.h"
#include "cmdLine.h"

void checkDependencies(graphNode** gN, graphNode* curGN) {
        int i = 0;
	int target = 0;
	int done = 0;
	struct stat statBuf;
	int newestUpdate;
	int noDependencies = 0;
	listNode* curLN = NULL;

	do{
		printf("%s\n", curGN->name);
		if(curGN->childListStart != NULL) {
			curLN = curGN->childListStart;

			//Cycle through nodes.
        		while(gN[i] != NULL) {
				//Check if dependencies is a target.
        			if(strcmp(gN[i]->name, curLN->string) == 0) {
					//Get dependencies.
                        		checkDependencies(gN, gN[i]);

					stat(gN[i]->name, &statBuf);
                        		if(newestUpdate > statBuf.st_mtime) {
                		               	newestUpdate = statBuf.st_mtime;
		                        }
					
					target = 1;
					break;
                		}
                		i++;
        		}

			//If target is not a node.
			if(target == 0) {
				//printf("Checking file: %s\n", curLN->string);
				int err;
				err = stat(curLN->string, &statBuf);
				if(err == -1) {
					perror("No file found.");
					exit(0);
				}
				//printf("Before time check.\n");
				if(newestUpdate > statBuf.st_mtime) {
					newestUpdate = statBuf.st_mtime;
				}
			}
		}else{
			for(int z = 0; z < gN[i]->commandSize; z++) {
				execute(gN[i]->command[z]);
			}
			noDependencies = 1;
			done = 1;
			continue;
		}
		
		if(strcmp(curGN->childListEnd->string, curLN->string) != 0) {
			curLN = curLN->child;
		}else{
			done = 1;
		}
		
	}while(done != 1);
	
	if(noDependencies == 0) {
		FILE* fp = fopen(curGN->name, "r");
                if(fp == NULL) {
                  	int z = 0;
                        while(curGN->command[z] != NULL) {
                             	execute(gN[i]->command[z]);
                        	z++;
                	}
		}else{
			stat(curGN->name, &statBuf);

			if(newestUpdate < statBuf.st_mtime) {
				int y = 0;
				while(curGN->command[y]) {
					execute(curGN->command[y]);
				}
			}
		}
	}
}


void runTarget(graphNode** gN, char* target) {
	graphNode* curGN;

	//Find target node
	if(target != NULL) {
		int i = 0;
		while(gN[i] != NULL) {
			if(strcmp(gN[i]->name, target) == 0) {
				curGN = gN[i];
				break;
			}
			i++;
		}
		if(curGN == NULL) {
			perror("Error: target does not exist.");
			exit(0);
		}
	}else{
		curGN = gN[0];
	}

	checkDependencies(gN, curGN);
}
