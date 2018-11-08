#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsing1.h"
#include "graphBuilder.h"
#include "runTarget.h"
#include "checkCycles.h"

int main(int argc, char *argv[]) {
	FILE *fp;
	char Makefile[] = "Makefile";
	char makefile[] = "testmakefile2";
	struct graphNode** depenGraph;
	int arg = 0;
	
	if(argc == 2) {
		arg = 1;
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
	depenGraph = reader(fp);
	
	//Check for cycles.
	checkCycles(depenGraph);

	//Pass the specific target to build.
	if(argc == 2) {
		runTarget(depenGraph, argv[arg]);
	}else{
		runTarget(depenGraph, NULL);
	}

	//Testing graph, DO NOT DELETE
	int a = 0;
	while(depenGraph[a] != NULL) {
		//Print the node name.
		printf("Node name: %s\n", depenGraph[a]->name);

		//Print the node commands.
		int b = 0;
		while(depenGraph[a]->command[b] != NULL){
			printf("	Command %i: %s\n", b, depenGraph[a]->command[b]);
			b++;
		}

		//Print the children of the node.
		int c = 0;
		if(depenGraph[a]->childListStart != NULL) {
			listNode* lN = depenGraph[a]->childListStart;
			printf("        Child %i: %s\n", c, lN->string);
			c++;

                	while(lN->child != NULL){
				lN = lN->child;
                        	printf("        Child %i: %s\n", c, lN->string);
                        	c++;
                	}
		}

		//Print the parents of the node.
                int d = 0;
                if(depenGraph[a]->parentListStart != NULL) {
                        listNode* lN = depenGraph[a]->parentListStart;
                        printf("        Parent %i: %s\n", d, lN->string);
                        d++;

                        while(lN->child != NULL){
                                lN = lN->child;
                                printf("        Parent %i: %s\n", d, lN->string);
                                d++;
                        }
                }

		a++;	
	}
}

