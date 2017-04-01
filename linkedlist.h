#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H


// Linked list node definition
typedef struct Node node;


struct Node
{
	char *name;
  	char *data;
  	node *next;
};


void destroy();
void build(const char *region_name, unsigned short region_size);
//void newList(const char *region_name, r_size_t region_size);
int getSize();
int firstNode(int *item);
int nextNode(int *item);
void print();


#endif

