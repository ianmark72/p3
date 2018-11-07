#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "graph.h"

void checkDependencies(graphNode** gN, graphNode* curGN) {
        int i = 0;
	int target = 0;
	struct stat* statBuf;
	int newestUpdate;

	do{
		if(curGN->childListStart != NULL) {
			listNode* curLN = curGN->childListStart;

			//Cycle through nodes.
        		while(gN[i] != NULL) {
				//Check if dependencies is a target.
        			if(strcmp(gN[i]->name, curLN->string) == 0) {
					//Get dependencies.
                        		getDependencies(gN, gN[i]);

					FILE* fp = fopen(gN[i]->name, "r");
					if(fp == NULL) {
						int z = 0;
                				while(gN[i]->command[z] != NULL) {
                        				execute(gN[i]->command[z]);
                        				z++;
                				}
					}else{
						stat(gN[i]->name, &statBuf);
                        			if(newestUpdate > statBuf.st_mtime) {
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
				stat(curLN->string, &statBuf);
				if(newestUpdate > statBuf.st_mtime) {
					newestUpdate = statBuf.st_mtime;
				}
			}
		}else{
			int z = 0;
			while(gN[i]->command[z] != NULL) {
				execute(gN[i]->command[z]);
				z++;
			}
		}
		curLN = curLN->child;
	}while(curLN != NULL);
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
