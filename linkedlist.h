#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include "objectindex.h"
// Linked list node definition
typedef struct Node node;
typedef struct linkedList *LinkedList;



struct Node
{
	void *region;
	char *name;
  	int blockTotalSize;
  	int usedBlocks;
  	node *next;
  	ObjList myObjList;
};



struct linkedList
{
	int size;
	node *first;
	node *chosenRegion;
};



LinkedList newList();
int getSize(LinkedList list);
LinkedList addNode(LinkedList list, const char *region_name, short region_size);
int findNode(LinkedList list, const char *region_name);
LinkedList findRegion(LinkedList list, const char *region_name);
LinkedList removeNode(LinkedList list, const char *region_name);
void printRegions(LinkedList list);

#endif

