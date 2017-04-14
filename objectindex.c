//linked list for holding pointers to blocks in a region

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "objectindex.h"
#include "linkedlist.h"








ObjList newObjList()
{
	ObjList newObjList;

	newObjList = (ObjList)malloc(sizeof(ObjList));
	assert(newObjList != NULL);

	if(newObjList != NULL)
	{
		newObjList->first = NULL;
		newObjList->size = 0;
	}
	else
	{
		newObjList = NULL;
	}

	return newObjList;
}



//number of points to blocks
int getNumBlocks(ObjList currentList)
{
	return currentList->size;
}



//add new node to object index
ObjList newObjNode(ObjList currentList)
{
	objNode *newNode;

	newNode = malloc(sizeof(objNode));
	assert(newNode != NULL);

	return currentList;
}



