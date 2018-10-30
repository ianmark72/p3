#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode {
	listNode* child;
	char* string;
}

typedef struct graphNode {
	char* name;
	char* command;
	listNode* parentListStart;
	listNode* parentListEnd;
	listNode* childListStart;
	listNode* childListEnd;
}graphNode;

graphNode CreateGraphNode(char* nameP, char* commandP) {
	const int numOfNodes = 1;

	graphNode* gn = calloc(numOfNodes, sizeof(graphNode));

	graphNode->name = nameP;
	graphNode->command = commandP;

	return gn;
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
