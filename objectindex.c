
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
//#include "linkedlist.h"



ObjList newObjList()
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





//add new node to object index
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
		//check whether there is space to allocate memory 
		//put size of allocated memory into newNode->blockSize
		newNode->beginBlock = blockPtr;
		newNode->blockSize = block_size;
		newNode->next = currentList->first;
		currentList->first = newNode;
		currentList->size++;
		currentList->blocksFilled += block_size;

		verifyObjIndex(currentList);
		//currentList->currentObjNode = currentList->first;
	}


	assert(currentList != NULL);
	assert(blockPtr != NULL);
	assert(block_size > 0);

	return currentList;
}






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


//find a pointer and return its size
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

	verifyObjIndex(list); //---------------------------------------------------------------------------------------------------

	if(found)
	{
		size = current->blockSize;
	}


	assert(list != NULL);
	assert(block_ptr != NULL);

	return size;
}



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
	 		//printf("************* %i %p\n", list->size, current->beginBlock);
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



//invariants
void verifyObjIndex(ObjList list)
{
	assert(list != NULL);
	assert(list->size >= 0);
	assert(list->blocksFilled >= 0);
	//assert(list->first->blockSize >= 0);
}

