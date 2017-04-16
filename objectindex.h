#ifndef _OBJINDEX_H
#define _OBJINDEX_H


typedef struct ObjectNode objNode;
typedef struct ObjectList *ObjList;



struct ObjectNode
{
	char *beginBlock; 
	char *endBlock;
	unsigned short blockSize;
	objNode *next;
};


struct ObjectList
{
	int size;
	objNode *first;
	objNode *currentObjNode;
};



ObjList newObjList();
int getNumBlocks(ObjList list);
ObjList newObjNode(ObjList currentList, void *blockPtr, unsigned short block_size);
ObjList freePointers(ObjList currentObjList);
void printPointers(ObjList list);

#endif