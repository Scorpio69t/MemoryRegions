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
	int blocksFilled;
	objNode *first;
};



ObjList createObjList();
ObjList newObjNode(ObjList currentList, void *blockPtr, unsigned short block_size);
ObjList freePointers(ObjList currentList);
void printPointers(ObjList list);
ObjList freeBlock(ObjList list, void *block_ptr);
int findPtr(ObjList list, void *block_ptr);
void verifyObjIndex(ObjList list);

#endif

