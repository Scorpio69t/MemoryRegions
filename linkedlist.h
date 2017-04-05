#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H


// Linked list node definition
typedef struct Node node;


struct Node
{
	//char *name;
	void *region;
  	void *data;
  	int blockTotalSize;
  	int usedBlocks;

  	node *next;
};


void destroy();
int addNode(const char *region_name, unsigned short region_size);
char *currentName();
int getSize();
int firstNode();
int nextNode();
void print();
int chooseNode(const char *region_name);


#endif

