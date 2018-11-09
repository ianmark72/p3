#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphBuilder.h"

void getChildren(graphNode** gN, graphNode** sA, listNode* curLN, int ctr) {
	int i = 0;
	
	//for(int k = 0; k < ctr; k++) {
	//	printf("%i: %s\n", k, sA[k]->name);
	//}

        while(gN[i] != NULL) {
		//printf("%i: %s\n", i, gN[i]->name);
        	if(strcmp(gN[i]->name, curLN->string) == 0) {
			for(int j = 0; j < ctr; j++) {
                        	if(strcmp(curLN->string, sA[j]->name) == 0) {
					//printf("%s\n", curLN->string);
					fprintf(stderr, "Error: Cycle Detected.\n");
					exit(0);					
				}	
                        }
			sA[ctr] = gN[i];
			//printf("StringArray entry: %s\n", sA[ctr]->name);
			ctr++;
			if(gN[i]->childListStart != NULL) {
				getChildren(gN, sA, gN[i]->childListStart, ctr);
			}
			break;
                }
        	i++;
        }
	
	while(curLN->child != NULL) {
		i = 0;
		curLN = curLN->child;

        	while(gN[i] != NULL) {
                	if(strcmp(gN[i]->name, curLN->string) == 0) {
                        	for(int j = 0; j < ctr; j++) {
                                	if(strcmp(curLN->string, sA[j]->name) == 0) {
                                        	fprintf(stderr, "Error: Cycle Detected.\n");                                     
                                        	exit(0);
                                	}       
                        	}

                        	sA[ctr] = gN[i];
				//printf("StringArray entry: %s\n", sA[ctr]->name);
                        	ctr++;
				if(gN[i]->childListStart != NULL) {
                        		getChildren(gN, sA, gN[i]->childListStart, ctr);
				}
				break;
                	}
                	i++;
        	}
        }
}

int checkCycles(graphNode** gN) {
	int ctr = 0;
	int i = 0;
	while(gN[i] != NULL) {
		if(gN[i]->childListStart != NULL) {
			graphNode** stackArray = calloc(50, sizeof(graphNode*));
			ctr = 0;
	
			stackArray[ctr] = gN[i];
			ctr++;

			getChildren(gN, stackArray, gN[i]->childListStart, ctr);

			free(stackArray);
		}
		i++;
	}

	return 0;
}
