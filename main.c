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
	char makefile[] = "makefile";
	struct graphNode** depenGraph;
	int arg = 0;
	char* f = "-f";
	char* customMakefile = NULL;
	int custom = 0;
	
	//Parse arguments
	if(argc == 2) {
		if(strcmp(argv[1], f) != 0) {
			arg = 1;
		}else{
			fprintf(stderr, "Need argument for -f.");
			exit(1);
		}
	}else if(argc == 3){
		if(strcmp(argv[1], f) == 0) {
			customMakefile = argv[2];
			custom = 1;
		}else if(strcmp(argv[2], f) == 0) {
			fprintf(stderr, "Need argument for -f.");
			exit(1);
		}else{
			fprintf(stderr, "Arguments not valid.");
			exit(1);
		}
	}else if(argc == 4) {
		if(strcmp(argv[1], f) == 0) {
                        fprintf(stderr, "Invalid arguments.");
                }else if(strcmp(argv[2], f) == 0) {
                        customMakefile = argv[3];
			arg = 1;
			custom = 1;
                }else{
                        fprintf(stderr, "Arguments not valid.");
                        exit(1);
                }
	}else if(argc > 4) {
		fprintf(stderr,"Too many arguments.");
		exit(1);
	}

	if(custom == 0) {
		fp = fopen(makefile, "r");
		if(fp == NULL) {
			fp = fopen(Makefile, "r");
			if(fp == NULL) {
				fprintf(stderr,"No makefile found.");
				exit(1);
			}
		}
	}else{
		fp = fopen(customMakefile, "r");
                if(fp == NULL) {
                	fprintf(stderr,"No makefile found.");
                        exit(1);
                }
	}

	//Pass to parsing.
	depenGraph = reader(fp);
		
	//Check for cycles.
	checkCycles(depenGraph);
	
	//Pass the specific target to build.
	if(argc == 2 || argc == 4) {
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

