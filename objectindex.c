
//-----------------------------------------
// NAME: Justin Mui
// STUDENT NUMBER: 7624249
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: assignment 4, QUESTION: 1
// 
// REMARKS: A linked list which holds the pointers to each block of
//          memory that is allocated to a region.  This linked list 
//          is stored in the nodes of the region's linked list.
//          Part of this code taken from course textbook.
//
//-----------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "objectindex.h"





//------------------------------------------------------
// createObjList
//
// PURPOSE: create a new linked list of pointers. 
//          called by addNode() when a new region is created
// OUTPUT PARAMETERS:
//      newObjList: new linked list for pointers that was created
//------------------------------------------------------
ObjList createObjList()
{
	ObjList newObjList;

	newObjList = (ObjList)malloc(sizeof(ObjList));
	assert(newObjList != NULL);

	if(newObjList != NULL)
	{
		newObjList->first = NULL;
		newObjList->size = 0;
		newObjList->blocksFilled = 0;
	}
	else
	{
		newObjList = NULL;
	}

	assert(newObjList != NULL);

	return newObjList;
}






//------------------------------------------------------
// newObjNode
//
// PURPOSE: add a new node with a pointer to a block of memory
// INPUT PARAMETERS:
//      currentList: linked list to add a node to
//      blockPtr: pointer of to a block of allocated memory
//      block_size: amount of memory allocated to that block
// OUTPUT PARAMETERS:
//      list: return list with pointer added to it
//------------------------------------------------------
ObjList newObjNode(ObjList currentList, void *blockPtr, unsigned short block_size)
{
	assert(currentList != NULL);
	assert(blockPtr != NULL);
	assert(block_size > 0);

	objNode *newNode;

	newNode = malloc(sizeof(objNode));
	assert(newNode != NULL);

	if(newNode != NULL)
	{
		newNode->beginBlock = blockPtr;
		newNode->blockSize = block_size;
		newNode->next = currentList->first;
		currentList->first = newNode;
		currentList->size++;
		currentList->blocksFilled += block_size;

		verifyObjIndex(currentList);
	}


	assert(currentList != NULL);
	assert(blockPtr != NULL);
	assert(block_size > 0);

	return currentList;
}






//------------------------------------------------------
// freePointers
//
// PURPOSE: free all nodes of pointers in this linked list
// INPUT PARAMETERS:
//      currentList: linked list to traverse and clear nodes
// OUTPUT PARAMETERS:
//      list: linked list with all nodes freed and removed
//------------------------------------------------------
ObjList freePointers(ObjList currentList)
{
	assert(currentList != NULL);

	objNode *current;
	objNode *prev;

	prev = NULL;
	current = currentList->first;


	while(current != NULL)
	{
		verifyObjIndex(currentList);

		prev = current;
		current = current->next;
		free(prev);
	}

	assert(currentList != NULL);

	return currentList;
}







//------------------------------------------------------
// printPointers
//
// PURPOSE: called by printRegions() to print out block pointers and the amount of memory they use
// INPUT PARAMETERS:
//      list: linked list containing pointers to print
//------------------------------------------------------
void printPointers(ObjList list)
{
	assert(list != NULL);

	objNode *currentNode;
	currentNode = list->first;

	verifyObjIndex(list);

	for(int i = 0; i < list->size; i++)
	{
		printf("Block: %p, Size: %i\n", currentNode->beginBlock, currentNode->blockSize);
		currentNode = currentNode->next;
	}

	assert(list != NULL);
}







//------------------------------------------------------
// findPtr
//
// PURPOSE: find the pointer block_ptr in the linked list and return its
//          size if it exists, and 0 if it doesn't
// INPUT PARAMETERS:
//      list: linked list to search for pointer in
//      block_ptr: pointer to block of memory
// OUTPUT PARAMETERS:
//      size: size of block of memory if it was found, otherwise return 0
//------------------------------------------------------
int findPtr(ObjList list, void *block_ptr)
{
	assert(list != NULL);
	assert(block_ptr != NULL);

	int found;
	int count;
	int size;
	objNode *current;

	found = 0;
	count = 0;
	size = 0;
	current = list->first;

	while(count < list->size && found == 0 && current != NULL)
	{
		if(block_ptr == current->beginBlock)
		{
			found = 1;
		}
		else
		{
			count++;
			current = current->next;
		}
	}

	verifyObjIndex(list); 

	if(found)
	{
		size = current->blockSize;
	}


	assert(list != NULL);
	assert(block_ptr != NULL);

	return size;
}






//------------------------------------------------------
// freeBlock
//
// PURPOSE: search for then free the memory used by block_ptr in the current region
// INPUT PARAMETERS:
//      list: linked list of pointers to search in
//      block_ptr: pointer to block of memory to search for and clear
// OUTPUT PARAMETERS:
//      list: list of pointers that was passed to this function
//------------------------------------------------------
ObjList freeBlock(ObjList list, void *block_ptr)
{
	assert(list != NULL);
	assert(block_ptr != NULL);

	int result;
	int count;
	objNode *previous;
	objNode *current;
	objNode *toRemove;

	result = 0;
	count = 0;
	previous = NULL;
	current = list->first;


	while(count < list->size && result == 0)
	{
	 	if(current->beginBlock == block_ptr)
	 	{
	 		result = 1;
	 	}
	 	else
	 	{
	 		previous = current;
	 		current = current->next;
	 		count++;
	 	}
	}

	verifyObjIndex(list);

	if(result == 1)
	{
	 	if(previous == NULL)
	 	{	
	 		toRemove = current;
	 		list->first = current->next;
	 	}
	 	else
	 	{
	 		toRemove = current;
	 		previous->next = current->next;
	 	}

	 	list->size--;
	 	list->blocksFilled -= toRemove->blockSize;
	}


	assert(list != NULL);
	assert(block_ptr != NULL);

	return list;
}







//------------------------------------------------------
// verifyObjIndex
//
// PURPOSE: invariants for checking the linked list of pointers in a region
// INPUT PARAMETERS:
//      list: linked list of pointers
//------------------------------------------------------
void verifyObjIndex(ObjList list)
{
	assert(list != NULL);
	assert(list->size >= 0);
	assert(list->blocksFilled >= 0);
}

