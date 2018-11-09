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
	struct stat statBuf;
	int newestUpdate = 0;
	listNode* curLN = NULL;
	int firstNode = 1;

	if(curGN->childListStart != NULL) {
		curLN = curGN->childListStart;
		do{
			//Progress to next node
			if(firstNode != 1) {
				curLN = curLN->child;
			}else{
				firstNode = 0;
			}

			//Cycle through nodes.
			i = 0;
        		while(gN[i] != NULL) {
				//Check if dependencies is a target.
        			if(strcmp(gN[i]->name, curLN->string) == 0) {
					//Get dependencies.
                       			checkDependencies(gN, gN[i]);
					if (gN[i] != NULL) {	
						stat(gN[i]->name, &statBuf);
						if(newestUpdate < statBuf.st_mtime) {
                	               			newestUpdate = statBuf.st_mtime;
		                		}
					}
					target = 1;
					break;
                		}
                		i++;
			}

			//If target is not a node.
			if(target == 0) {
				int err;
				err = stat(curLN->string, &statBuf);
				if(err == -1) {
					fprintf(stderr, "No file found.");
					exit(1);
				}

				if(newestUpdate < statBuf.st_mtime) {
					newestUpdate = statBuf.st_mtime;
				}
			}
		}while(strcmp(curGN->childListEnd->string, curLN->string) != 0);
	}else{
		for(int z = 0; z < curGN->commandSize; z++) {
			execute(curGN->command[z]);
		}
		return;
	}
	
	//Find file and run if necessary.
	FILE* fp = fopen(curGN->name, "r");
        if(fp == NULL) {
		for(int z = 0; z < curGN->commandSize; z++) {
                        execute(curGN->command[z]);
                }
	}else{
		stat(curGN->name, &statBuf);
		if(newestUpdate > statBuf.st_mtime) {
				
			for(int y = 0; y < curGN->commandSize; y++) {
				execute(curGN->command[y]);
			}
		}
	}
}


void runTarget(graphNode** gN, char* target) {
	graphNode* curGN = NULL;

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
			fprintf(stderr,"Error: target does not exist.");
			exit(1);
		}
	}else{
		curGN = gN[0];
	}

	checkDependencies(gN, curGN);
}
