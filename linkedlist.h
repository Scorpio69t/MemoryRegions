#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H


// Linked list node definition
typedef struct Node node;
typedef struct linkedList *LinkedList;

struct Node
{
	//char *name;
	void *region;
  	char *name;
  	int blockTotalSize;
  	int usedBlocks;

  	node *next;
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

