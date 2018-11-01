/***********************************************************************
* FILENAME: parsing.c 
*
* DESCRIPTION:
*       This is the file that parse through the makefile and triggers approptiate behavior
* 
* AUTHORS: Matthew Derzay, CS Login: derzay
*          Ian Mark, CS Login: imark
*
***********************************************************************/

#include "reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include <pthread.h>

/**
 *  This method reads in lines from make and parse through them.
 *  
 *
 *  Return: void* - NULL, nothing of value.
 */
void* read(void* q) {
        //Buffer max size.
        const int BUF_SIZE = 1024;
        //String pointer.
        char* string;
        //Next character input from std input.
        char input;
        //Counter for the buffer entries.
        int ctr = 0;
        //Character to cycle through excess lines that are too long.
        char c;
        //Whether or not there is a newline at the end of a string.
        int noNewLine = 1;

        //Allocate memory for the buffer.
        char* buffer = (char*)calloc(BUF_SIZE, sizeof(char));
        if(buffer == NULL) { fprintf(stderr, "error with calloc");}

        //Loop until the end of the file.
	do {
                //Check for line that is larger than the buffer size.
                if ( ctr >= BUF_SIZE - 1 ) {
                        //Cycle through the rest of the line.
                        do{
                                c = getchar();
                        }while( c != '\n');
                        //Print to std error.
                        fprintf(stderr, "Line longer than %i\n", BUF_SIZE);
                        //Clear buffer memory and set counter to zero.
                        memset(buffer, 0, BUF_SIZE);
                        if( buffer == NULL) { fprintf(stderr, "error with memset");}
                        ctr = 0;
                        noNewLine = 1;
                }
                //Get the next character.
                input = getchar();
                //Check for newlines or end of file characters.
                if ( input != '\n' && input != EOF) {
                        //Put the character into the buffer and increment counter.
                        if(buffer != NULL) {
                                buffer[ctr] = input;
                        }
                        ctr++;
                                                  
                        noNewLine = 1;
                } else {
                        //Check if newline or end of file.
                        if(input != EOF) {
                                //Allocate memory for string pointer.
                                string = (char*)calloc(BUF_SIZE, sizeof(char));
                                if(string == NULL) { fprintf(stderr, "error calloc");}

                                //Copy string from buffer and enqueue.
                                if(buffer != NULL && string != NULL) {
                                        strncpy(string, buffer, BUF_SIZE);
                                }
                                if(string == NULL) { fprintf(stderr, "error strncpy");}

                                if(buffer != NULL) {
                                        memset(buffer, 0, BUF_SIZE);
                                }

                                if( buffer == NULL) { fprintf(stderr, "error with memset");}

                                //Reset values.
                                ctr = 0;
                                noNewLine = 0;
                        } else{
                                //Check if there is something in the buffer but no newline.
                                if(noNewLine == 1) {
                                        //Allocate memory and enqueue.
                                        string = (char*)calloc(BUF_SIZE, sizeof(char));
                                        if(string == NULL) { fprintf(stderr, "error with calloc");}

                                        if(string != NULL && buffer != NULL) {
                                                strncpy(string, buffer, BUF_SIZE);
                                        }
                                        if(string == NULL) { fprintf(stderr, "error strncpy");
                                }
                        }
                }
        } while ( input != EOF);

        //Exit thread when nothing left.
        pthread_exit(0);
        return NULL;

