#ifndef _OBJINDEX_H
#define _OBJINDEX_H


typedef struct ObjectNode objNode;
typedef struct ObjectList *ObjList;



struct ObjectNode
{
	char *beginBlock; 
	char *endBlock;
	int blockSize;
	objNode *next;
};


struct ObjectList
{
	int size;
	objNode *first;
};



ObjList newObjList();
int getNumBlocks(ObjList list);
ObjList newObjNode(ObjList list);
ObjList freePointers(ObjList currentObjList);


#endif