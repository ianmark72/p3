#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

typedef struct listNode {
        struct listNode* child;
        char* string;
}listNode;

typedef struct graphNode {
        char* name;
        int arrayPos;
        char** command;
	int commandSize;
        struct listNode* childListStart;
        struct listNode* childListEnd;
}graphNode;

struct graphNode* CreateGraphNode(char* nameP);
void addCommand(struct graphNode* gn, char* commandP);
void addChild(struct graphNode* gn, char* newChild);

#endif /* GRAPHBUILDER_H */
