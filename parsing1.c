/***********************************************************************
* FILENAME: parsing1.c 
*
* DESCRIPTION:
*       This is a file where we are trying to reformat old code to read in a fiel 
* 
* AUTHORS: Matthew Derzay, CS Login: derzay
*          Ian Mark, CS Login: imark
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "graph.h"

/**
 *  This method reads in lines from make and parse through them.
 *  
 *
 *  Return: void* - NULL, nothing of value.
 */
typedef struct lines {
	int type;
	char* line;
} lines;

lines* read(FILE* q) {
	const int BUF_SIZE = 1024;
	int type = -1; //type of line, 0 if cmd 1 if target, 2 if blank

	// First, read through line and store as string
       	char input  = ' ';
       	char* line = calloc(BUF_SIZE, sizeof(char));
       	char* buffer = calloc(BUF_SIZE, sizeof(char));
       	lines* linesArray = (lines*)calloc(50, sizeof(lines)); 
       	input = getc(q);

       	int ctr = 0;
       	int lineNum =0;
	graphNode* curGN;
	graphNode** nodeArray = calloc(20, sizeof(graphNode*));
	graphArrayCtr = 0;
	char* nextString;
	char colon = ':';
	char* substringBC;
	char* substringAC;
	char** dependencies = calloc(20, sizeof(char*));

       	while (lineNum < 50 && input != EOF) {
       		while( input != EOF && input != '\n' ) {
			if(ctr == 1024) {
				perror("%i: Invalid Line: %s", lineNum, buffer);
				exit(0);
			}
			buffer[ctr] = input;
			input = getc(q);
			ctr++;
      		}
      		ctr = 0;
      		strncpy(line, buffer, 100);
      		if (line[0] == '\t') {
			type = 0; 
      		}
      		else if ( isalpha(line[0]) || isdigit(line[0])) {
			type = 1;
      		}
      		else if ( line[0] == '\n' ) {
			type = 2;
      		}
      		else { fprintf(stderr, "error typing\n"); }
      		struct lines tmp;
		tmp.type = type;
		tmp.line = line;
      		linesArray[lineNum] = tmp;
      		printf("%i",lineNum);
      		printf("struct content: %i,%s\n",linesArray[lineNum].type,linesArray[lineNum].line);
      		lineNum++;
      		memset(buffer, 0, BUF_SIZE);
      		input = getc(q);
       	}

	for(int i = 0; i < lineNum; i++) {
		if(linesArray[i]->type == 0) {
			//Create new node in the array.
			nodeArray[graphArrayCtr] = (graphNode*)calloc(1, sizeof(graphNode*));
			nextString = calloc(50, sizeof(char*));
			substringBC = calloc(50, sizeof(char*));
			substringAC = calloc(50, sizeof(char*));
			int ssctr = 0;

			//Read through the string of the make file.
			for(int j = 0; j < strlen(nextString); j++){
				//Read until colon marker.
				while(nextString[j] != colon) {
					substringBC[j] = nextString[j]; 
					j++;
				}
				//Read the rest into another string.
				if(nextString[j] != colon){
					substringAC[ssctr];
					ssctr++;
				}
			}
			
			//Split the second part of the string into an array.
			dependencies = strtok(substringAC);

			nodeArray[graphArrayCtr] = CreateGraphNode(substring);

			//Add dependencies to child list of node.
			for(int k = 0; k < sizeof(dependencies)/sizeof(dependencies[0]); k++) {
				addChild(nodeArray[graphArrayCtr], dependencies[k]);
			}

			curGN = nodeArray[graphArrayCtr];
			graphArrayCtr++;
		}else{
			//Get rid of the tab.
			linesArray[i]->line++;
			//Check to make sure that the first line isn't a command.
			if(curGN == NULL) {
				perror("Command without a target.");
				exit(0);
			}
			addCommand(curGN, linesArray[i]);
		}
	}

	return linesArray;
}
