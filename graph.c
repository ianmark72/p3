#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode {
	listNode* child;
	char* string;
}

typedef struct graphNode {
	char* name;
	int arrayPos;
	char** command;
	listNode* parentListStart;
	listNode* parentListEnd;
	listNode* childListStart;
	listNode* childListEnd;
}graphNode;

graphNode CreateGraphNode(char* nameP) {
	const int numOfNodes = 1;

	graphNode* gn = calloc(numOfNodes, sizeof(graphNode));
	
	gn->arrayPos = 0;
	graphNode->name = nameP;
	graphNode->command = calloc(10, sizeof(char*));

	return gn;
}

void addCommand(graphNode* gn, char* commandP) {
	gn->command[gn->arrayPos] = commandP;
	gn->arrayPos++;
}

void addParent(graphNode* gn, char* newParent) {
	const int numOfNodes = 1;

	listNode* newLN = calloc(numOfNodes, sizeof(graphNode));
	newLN->string = newParent;

	if(gn->parentListStart == NULL) {
		gn->parentListStart = newLN;
		gn->parentListEnd = newLN;
	}else{
		gn->parentListEnd->child = newLN;
		gn->parentListEnd = newLN;
	}
}

void addChild(graphNode* gn, char* newChild) {
	const int numOfNodes = 1;

        listNode* newLN = calloc(numOfNodes, sizeof(graphNode));
        newLN->string = newChild;

        if(gn->childListStart == NULL) {
                gn->childListStart = newLN;
                gn->childListEnd = newLN;
        }else{
                gn->childListEnd->child = newLN;
                gn->childListEnd = newLN;
        }
}
