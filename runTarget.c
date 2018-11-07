#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void checkDependencies(graphNode** gN, graphNode** sA, listNode* curLN, int ctr) {
        int i = 0;
	int target = 0;

	//Cycle through nodes.
        while(gN[i] != NULL) {
		//Check if depencies is a target.
        	if(strcmp(gN[i]->name, curLN->string) == 0) {
			//Get depencies.
                        getDependencies(gN, sA, gN[i]->childListStart, ctr);
			target = 1;
			break;
                }
                i++;
        }

	//
	if(target == 1) {
		//Check stat
	}

        while(curLN->child != NULL) {
                i = 0;
                curLN = curLN->child;

                while(gN[i] != NULL) {
                        if(strcmp(gN[i]->name, curLN->string) == 0) {
                                for(int j = 0; j < ctr; j++) {
                                        if(strcmp(curLN->string, sA[j]->name) == 0) {
                                                perror("Error: Cycle Detected.\n");
                                                exit(0);
                                        }
                                }

                                sA[ctr] = gN[i];
                                ctr++;
                                getChildren(gN, sA, gN[i]->childListStart, ctr);
                        }
                        i++;
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
}
