#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include "objectindex.h"
// Linked list node definition
typedef struct Node node;
typedef struct linkedList *LinkedList;



struct Node
{
	char *region;  //might need to be void?
	char *name;
	char *newBlock;
  	int blockTotalSize;
  	int usedBlocks;
  	node *next;
  	ObjList myObjList;
};



struct linkedList
{
	int size;  //number of regions in list
	int allocResult; //result of whether rinit() was successful
	node *first;
	node *chosenRegion;
};



LinkedList newList();
LinkedList addNode(LinkedList list, const char *region_name, unsigned short region_size);
int findNode(LinkedList list, const char *region_name);
LinkedList findRegion(LinkedList list, const char *region_name);
LinkedList removeNode(LinkedList list, const char *region_name);
void printRegions(LinkedList list);
LinkedList allocateBlock(LinkedList list, unsigned short block_size);
char *findFreeBlocks(node currentNode, unsigned short block_size);
LinkedList rfreeHelper(LinkedList list, void *block_ptr);
unsigned short getPtrSize(LinkedList list, void *block_ptr);
void verifyLList(LinkedList list);
void verifyNodeOnly(node currentNode);

#endif

