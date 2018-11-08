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
#include "graphBuilder.h"

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

char** stringSplit(char* string) {
	char** stringArray = calloc(20, sizeof(char*));
	size_t counter1 = 0;
	size_t counter2 = 0;
	size_t counter3 = 0;
	const int BUF_SIZE = 1024;
	const char space = ' ';
	char* tmpStr;
	char previousChar = space;

	while(counter1 < (unsigned)strnlen(string, BUF_SIZE)) {
		if(string[counter1] != space) {
			if(counter3 == 0) {
				tmpStr = calloc(50, sizeof(char*));
			}
			tmpStr[counter3] = string[counter1];
			counter3++;
		}else if(previousChar != space){
			stringArray[counter2] = tmpStr;
			counter2++;
			counter3 = 0;
		}
		previousChar = string[counter1];
		counter1++;

		if(counter1 == (unsigned)strnlen(string, BUF_SIZE)) {
			stringArray[counter2] = tmpStr;
                }
	}

	//int i = 0;
	//while(stringArray[i] != NULL) {
        //	printf("%i: %s\n", i, stringArray[i]);
	//	i++;
        //}

	return stringArray;
}

struct graphNode** reader(FILE* q) {
	const int BUF_SIZE = 1024;
	int type = -1; //type of line, 0 if cmd 1 if target, 2 if blank

	// First, read through line and store as string
       	char input  = ' ';
       	char* line;
       	char* buffer = calloc(BUF_SIZE, sizeof(char));
       	lines* linesArray = (lines*)calloc(50, sizeof(lines)); 
       	input = getc(q);

       	int ctr = 0;
       	int lineNum =0;
	graphNode* curGN;
	graphNode** nodeArray = calloc(20, sizeof(graphNode*));
	int graphArrayCtr = 0;
	char* nextString;
	char colon = ':';
	char* substringBC;
	char* substringAC;
	char** dependencies;

       	while (lineNum < 50 && input != EOF) {
       		while( input != EOF && input != '\n' ) {
			if(ctr == 1024) {
				printf("%i: Invalid Line: %s", lineNum, buffer);
				exit(0);
			}
			buffer[ctr] = input;
			input = getc(q);
			ctr++;
      		}
      		ctr = 0;
		line = calloc(BUF_SIZE, sizeof(char));
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
			if( type != 2 ) {
      		struct lines tmp;
			tmp.type = type;
			tmp.line = line;
      		linesArray[lineNum] = tmp;
      		//printf("%i",lineNum);
      		//printf("struct content: %i,%s\n",linesArray[lineNum].type,linesArray[lineNum].line);
			}
			lineNum++;
      		memset(buffer, 0, BUF_SIZE);
      		input = getc(q);
       	}

	//for(int z = 0; z < 15; z++) {
	//	printf("struct content: %i,%s\n",linesArray[z].type,linesArray[z].line);
	//}

	//printf("Before graph creation.\n");

	for(int i = 0; i < lineNum; i++) {
		//printf("inside the line loop.\n");
		//printf("The line is of type: %i and contains string: %s\n", linesArray[i].type, linesArray[i].line);
		if(linesArray[i].type == 1) {
			//printf("Target line.\n");
			//Create new node in the array.
			nodeArray[graphArrayCtr] = (graphNode*)calloc(1, sizeof(graphNode*));
			nextString = linesArray[i].line;
			//printf("%s\n", nextString);
			substringBC = calloc(50, sizeof(char*));
			substringAC = calloc(50, sizeof(char*));
			int ssCtr = 0;
			int strCtr = 0;
			int strLength = (unsigned)strnlen(nextString, BUF_SIZE);

			//printf("After initialization.\n");

			//Read until colon marker.
                        while(nextString[strCtr] != colon && strCtr < strLength) {
                                substringBC[strCtr] = nextString[strCtr];
                        	strCtr++;
                        }
			if(nextString[strCtr] != colon && strCtr + 1 >= strLength){
				perror("Error: Invalid target line.\n");
                                exit(0);
			}

			//Pass over the colon.
			if(strCtr + 1 != strLength ) {
				strCtr++;
			}
			
			//printf("strCtr: %i, strLength: %i\n", strCtr, strLength);

			//printf("Colon split.\n");

			//Read through the rest of the string after the colon.
			while(nextString[strCtr] != colon && strCtr < strLength) {
				//Read the rest into another string.
				substringAC[ssCtr] = nextString[strCtr];
				strCtr++;
				ssCtr++;
			}
			if(nextString[strCtr] == colon && strCtr + 1 != strLength) {
				perror("Error: Too many targets.\n");
				exit(0);
			}	
			//printf("subString after colon: %s\n", substringAC);
			//printf("After string splitting.\n");
			
			//Split the second part of the string into an array.
			dependencies = stringSplit(substringAC);

			//for(int i = 0; i < sizeof(dependencies)/sizeof(dependencies[0]); i++){
			//	printf("%i: %s\n", i, dependencies[i]);
			//}
	
			//printf("After dependencies split.\n");

			nodeArray[graphArrayCtr] = CreateGraphNode(substringBC);

			//printf("After node creation.\n");

			//Add dependencies to child list of node.
			int k = 0;
			while(dependencies[k] != NULL) {
				addChild(nodeArray[graphArrayCtr], dependencies[k]);
				k++;	
			}
			
			//printf("After dependencies added.\n");

			//Search through graphnode's children to find parents.
			for(int l = 0; l < graphArrayCtr; l++) {
				struct listNode* curNode;
				if(nodeArray[l]->childListStart != NULL) {
					curNode = nodeArray[l]->childListStart;
				}
				if(strcmp(curNode->string, nodeArray[graphArrayCtr]->name) == 0) {
                                	addParent(nodeArray[graphArrayCtr], curNode->string);
                                }
				
				//Cycle through children and find matching names.
				while(curNode->child != NULL) {
					curNode = curNode->child;
					if(strcmp(curNode->string, nodeArray[graphArrayCtr]->name) == 0) {
						addParent(nodeArray[graphArrayCtr], curNode->string);
					}	
				}
			}

			//printf("After node parents are found.\n");

			curGN = nodeArray[graphArrayCtr];
			graphArrayCtr++;
		}else if(linesArray[i].type == 0) {
			//printf("Command Line.\n");

			//Get rid of the tab.
			linesArray[i].line++;
			//Check to make sure that the first line isn't a command.
			if(curGN == NULL) {
				perror("Command without a target.\n");
				exit(0);
			}
			addCommand(curGN, linesArray[i].line);
		}
	}

	return nodeArray;
}
