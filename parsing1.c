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

char* trim(char* string) {
	size_t oldCtr = 0;
	size_t newCtr = 0;
	const int BUF_SIZE = 1024;
	char* newString = calloc(50, sizeof(char));

	while(oldCtr < (unsigned)strnlen(string, BUF_SIZE)) {
		if(string[oldCtr] == ' ') {
			oldCtr++;
		}else{
			newString[newCtr] = string[oldCtr];
			newCtr++;
			oldCtr++;
		}
	}

	return newString;
}

char** stringSplit(char* string) {
	char** stringArray = calloc(50, sizeof(char*));
	size_t counter1 = 0;
	size_t counter2 = 0;
	size_t counter3 = 0;
	const int BUF_SIZE = 1024;
	const char space = ' ';
	char previousChar = space;
	char* tmpStr = NULL;

	while(counter1 < (unsigned)strnlen(string, BUF_SIZE)) {
		if(string[counter1] != space) {
			if(counter3 == 0) {
				free(tmpStr);
				tmpStr = calloc(BUF_SIZE, sizeof(char));
			}
			tmpStr[counter3] = string[counter1];
			counter3++;
		}else if(previousChar != space){
			stringArray[counter2] = calloc(BUF_SIZE, sizeof(char));
                        strncpy(stringArray[counter2], tmpStr, BUF_SIZE);
			
			counter2++;
			counter3 = 0;
		}
		previousChar = string[counter1];
		counter1++;

		if(counter1 == (unsigned)strnlen(string, BUF_SIZE) && previousChar != space) {
			stringArray[counter2] = calloc(BUF_SIZE, sizeof(char));
			strncpy(stringArray[counter2], tmpStr, BUF_SIZE);
                }
	}

	free(tmpStr);

	return stringArray;
}

struct graphNode** reader(FILE* q) {
	const int BUF_SIZE = 1024;
	int type = -1; //type of line, 0 if cmd 1 if target, 2 if blank

	// First, read through line and store as string
       	char input  = ' ';
       	char* line;
       	char* buffer = calloc(BUF_SIZE, sizeof(char));
       	lines* linesArray = (lines*)calloc(100, sizeof(lines)); 
	input = getc(q);

       	int ctr = 0;
       	int lineNum =0;
	graphNode* curGN = NULL;
	graphNode** nodeArray = calloc(100, sizeof(graphNode*));
	int graphArrayCtr = 0;
	char* nextString;
	char colon = ':';
	char* substringBC;
	char* substringAC;
	char** dependencies;

       	while (input != EOF) {
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
		if( type == 1 || type == 0 ) {
      			struct lines tmp;

			tmp.line = calloc(BUF_SIZE, sizeof(char));
			strncpy(tmp.line, line, BUF_SIZE);

			tmp.type = type;
      			linesArray[lineNum] = tmp;
			lineNum++;
		}

		free(line);
		
      		memset(buffer, 0, BUF_SIZE);
      		input = getc(q);
		type = -1;
	}
	
	for(int i = 0; i < lineNum; i++) {
		if(linesArray[i].type == 1) {
			//Create new node in the array.
			nodeArray[graphArrayCtr] = calloc(1, sizeof(graphNode));
			nextString = linesArray[i].line;
			
			substringBC = calloc(50, sizeof(char));
			substringAC = calloc(50, sizeof(char));
			int ssCtr = 0;
			int strCtr = 0;
			int strLength = (unsigned)strnlen(nextString, BUF_SIZE);

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

			//Split the second part of the string into an array.
			dependencies = stringSplit(substringAC);
			free(substringAC);

			nodeArray[graphArrayCtr] = CreateGraphNode(trim(substringBC));
			free(substringBC);

			//Add dependencies to child list of node.
			int k = 0;
			while(dependencies[k] != NULL) {
				addChild(nodeArray[graphArrayCtr], dependencies[k]);
				k++;	
			}
			
			free(dependencies);
			free(nextString);

			curGN = nodeArray[graphArrayCtr];
			graphArrayCtr++;
		}else if(linesArray[i].type == 0) {
			//Get rid of the tab.
			linesArray[i].line++;
			//Check to make sure that the first line isn't a command.
			if(curGN == NULL) {
				perror("Command without a target.\n");
				exit(0);
			}
			addCommand(curGN, linesArray[i].line);
			//free(linesArray[i].line);
		}
	}

	free(linesArray);
	free(buffer);

	return nodeArray;
}
