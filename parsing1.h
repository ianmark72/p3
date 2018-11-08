#include <stdio.h>
typedef struct lines {
        int type;
        char* line;
} lines;
char** stringSplit(char* string);
struct graphNode** reader(FILE*);
