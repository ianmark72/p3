#ifndef PARSING1_H
#define PARSING1_H

#include <stdio.h>
typedef struct lines {
        int type;
        char* line;
} lines;
char** stringSplit(char* string);
struct graphNode** reader(FILE*);

#endif /* PARSING1_H */
