typedef struct listNode {
        struct listNode* child;
        char* string;
}listNode;

typedef struct graphNode {
        char* name;
        int arrayPos;
        char** command;
        struct listNode* parentListStart;
        struct listNode* parentListEnd;
        struct listNode* childListStart;
        struct listNode* childListEnd;
}graphNode;

struct graphNode* CreateGraphNode(char* nameP);
void addCommand(struct graphNode* gn, char* commandP);
void addParent(struct graphNode* gn, char* newParent);
void addChild(struct graphNode* gn, char* newChild);