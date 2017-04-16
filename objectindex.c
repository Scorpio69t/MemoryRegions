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

	if(newNode != NULL)
	{
		//check whether there is space to allocate memory 
		//put size of allocated memory into newNode->blockSize
	}

	return currentList;
}


//free list of pointers to blocks in object index
ObjList freePointers(ObjList currentObjList)
{
	objNode *current = currentObjList->first;
	objNode *temp = NULL;


	//free every node in object index
	while(current != NULL)
	{
		temp = current;
		current = current->next;

		free(temp->beginBlock);
		free(temp->endBlock);
		free(temp);
	}

	free(currentObjList->first); //might need to remove this

	return currentObjList;
}