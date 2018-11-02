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

/**
 *  This method reads in lines from make and parse through them.
 *  
 *
 *  Return: void* - NULL, nothing of value.
 */
void read(FILE* q) {
	const int BUF_SIZE = 1024;
	int type = -1; //type of line, 0 if cmd 1 if target, 2 if blank
       // First, read through line and store as string
       char input  = ' ';
       char* line = calloc(sizeof(char), BUF_SIZE);
       char* buffer = calloc(sizeof(char), BUF_SIZE);
       input = getc(q);
       int ctr = 0;
       while( input != EOF && input != '\n' ) {
		buffer[ctr] = input;
		input = getc(q);
		ctr++;
      }
      strncpy(line, buffer, 100);
      printf("%s\n",buffer);
      if (line[0] == '\t') {
		type = 0; 
      }
      else if ( isalpha(line[0]) || isdigit(line[0])) {
		type = 1;
      }
      else if ( line[0] == '\n' ) {
		type = 2;
      }
      else { printf("error\n"); }

	printf("%i\n", type);
}
