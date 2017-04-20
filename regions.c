
//-----------------------------------------
// NAME: Justin Mui
// STUDENT NUMBER: 7624249
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: assignment 4, QUESTION: 1
// 
// REMARKS: This is called by main.c to accept all the input
//          for building the regions.  Most of these functions
//          take and verify the input from main.c then call
//          linked.c to create, modify, or destroy regions
//          of memory.
//
//-----------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "regions.h"
#include "regiontools.h"
#include "linkedlist.h"


static int nodeCount = 0;  //number of regions in the program. should be 0 when no list or regions exist
static LinkedList myList;  //linked list object





//------------------------------------------------------
// rinit
//
// PURPOSE: create and select a new region if a region with that name doesn't already exist
// INPUT PARAMETERS:
//			region_name: name of region to create
//          region_size: amount of memory to allocate in region
// OUTPUT PARAMETERS:
// 			result: boolean of whether the region was successfully created
//------------------------------------------------------
Boolean rinit(const char *region_name, r_size_t region_size)
{
	assert(nodeCount >= 0); 

	Boolean result;

	result = true;

	if(region_name != NULL && region_size > 0)
	{

		//create new linked list if nodeCount is 0
		if(nodeCount == 0)
		{			
			myList = createList();

			if(myList != NULL)
			{
				result = true;
			}
			else
			{
				result = false;
			}
		}

		if(region_size >= 1)
		{
			// round if size isn't zero
			region_size = roundSize(region_size); 
		}
		else 
		{
			result = false;
		}


		//initialize memory region if size >0 and name isn't NULL
		if(result == true)
		{
			if(nodeCount == 0)
			{
				myList = addNode(myList, region_name, region_size);

				nodeCount = myList->size;
				rchoose(region_name);
			}
			else if(nodeCount > 0)
			{	
				if(findNode(myList, region_name)) //if name already exists
				{
					result = false;
				}
				else
				{
					myList = addNode(myList, region_name, region_size);
					nodeCount = myList->size;
					rchoose(region_name);

					verifyRegion(myList, myList->pickedRegion, nodeCount);
					verifyLList(myList);

				}
			}
			else
			{
				result = false;
			}

		}
	}
	else
	{
		result = false;
	}


	assert((result == true) || (result == false));
	assert(nodeCount >= 0); 
	return result;
}







//------------------------------------------------------
// rchosen
//
// PURPOSE: return name of the region that was chosen
// OUTPUT PARAMETERS:
// 			currentName: name of chosen region, NULL if no region is currently chosen
//------------------------------------------------------
const char *rchosen()
{
	assert(nodeCount >= 0);

	char *currentName;

	if(nodeCount > 0)
	{
		if(myList->pickedRegion == 0)
		{
			currentName = NULL;
		}
		else
		{
			currentName = malloc(sizeof(char) * strlen(myList->chosenRegion->name) + 1); // +1
			assert(currentName != NULL);

			if(currentName != NULL)
			{
				strncpy(currentName, myList->chosenRegion->name, strlen(myList->chosenRegion->name));
				currentName[strlen(myList->chosenRegion->name)] = '\0';

				verifyRegion(myList, myList->pickedRegion, nodeCount);
				verifyLList(myList);
			}
			else
			{
				currentName = NULL;
			}
		}
	}
	else
	{
		currentName = NULL;
	}

	assert(nodeCount >= 0);
	
	return currentName;
}






//------------------------------------------------------
// rchoose
//
// PURPOSE: choose a region if there is one that matches the name given by reigon_name
// INPUT PARAMETERS:
//			region_name: name of region to search for
// OUTPUT PARAMETERS:
// 			result: boolean of whether that region was found
//------------------------------------------------------
Boolean rchoose(const char *region_name)
{
	assert(nodeCount >= 0);


	Boolean result; 

	if(region_name != NULL)
	{
		if(nodeCount > 0)
		{
			myList->foundNewRegion = 0;
			myList = findRegion(myList, region_name);

			verifyLList(myList);
			verifyRegion(myList, myList->pickedRegion, nodeCount);

			if(myList->foundNewRegion == 0)
			{
				result = false;
			}
			else //myList->foundNewRegion == 1
			{
				result = true;
			}
		}
		else
		{
			result = false;
		}
	}
	else
	{
		result = false;
	}


	assert(nodeCount >= 0); 
	assert((result == true) || (result == false));

	return result;
}








//------------------------------------------------------
// rdestroy
//
// PURPOSE: remove a region from the linked list and free any memory allocated inside that region
// INPUT PARAMETERS:
//			region_name: name of region to remove
//
//------------------------------------------------------
void rdestroy(const char *region_name)
{
	assert(nodeCount >= 0); 

	if(region_name != NULL)
	{
		if(strlen(region_name) > 0)
		{
			if(nodeCount > 0)
			{
				verifyRegion(myList, myList->pickedRegion, nodeCount);
				verifyLList(myList);

				myList = removeNode(myList, region_name);
				nodeCount = myList->size;

			}
			else //if(nodeCount == 0) 
			{
				if(myList != NULL)
				{
					free(myList);
				}
				nodeCount = 0;
			}
		}
	}

	if(nodeCount == 0 && myList != NULL)
	{
		free(myList);
	}

	assert(nodeCount >= 0); 
}







//------------------------------------------------------
// rdump
//
// PURPOSE: print out the name every region that exists, each block of
//          memory allocated in that region, and the percentage of 
//          free space remaining
//------------------------------------------------------
void rdump()
{
	assert(myList >= 0);

	if(nodeCount > 0 )//&& myList != NULL)
	{
		verifyRegion(myList, myList->pickedRegion, nodeCount);
		verifyLList(myList);

		printRegions(myList);
	}
	else
	{
		printf("No regions exist.\n\n");
	}

	assert(myList >= 0);
}








//------------------------------------------------------
// ralloc
//
// PURPOSE: allocate a block of memory in chosen region if there are enough contiguous bytes
// INPUT PARAMETERS:
//			block_size: amount of memory to allocate
// OUTPUT PARAMETERS:
// 			blockPtr: pointer to block of memory if it was allocated, NULL if it was not
//------------------------------------------------------
void *ralloc(r_size_t block_size)
{

	assert(nodeCount >= 0);

	void *blockPtr;
	int freeBlocks;

	if(nodeCount > 0) 
	{
		if(myList->pickedRegion == 1 && block_size > 0) 
		{
			block_size = roundSize(block_size);
			freeBlocks = myList->chosenRegion->blockTotalSize - myList->chosenRegion->usedBlocks;

			if(block_size > 0 && block_size <= freeBlocks)
			{
				//this can still return NULL if not enough contiguous empty blocks are found
				myList = allocateBlock(myList, block_size); 
				if(myList->allocResult == 1)
				{
					verifyRegion(myList, myList->pickedRegion, nodeCount);
					verifyLList(myList);

					blockPtr = myList->chosenRegion->newBlock;
					myList->chosenRegion->usedBlocks += block_size;
				}
				else
				{
					blockPtr = NULL;
				}
			}
			else
			{
				blockPtr = NULL;
			}
		}
		else
		{
			blockPtr = NULL;
		}
	}
	else
	{
		blockPtr = NULL;
	}



	assert(nodeCount >= 0);
	return blockPtr;
}








//------------------------------------------------------
// rfree
//
// PURPOSE: frees a block of memory given by block_ptr if it exists in current region
// INPUT PARAMETERS:
//			block_ptr: pointer to a block of memory
// OUTPUT PARAMETERS:
// 			result: boolean of whether the memory was freed
//------------------------------------------------------
Boolean rfree(void *block_ptr)
{
	assert(nodeCount >= 0); 

	Boolean result;
	int beforeUsed;

	if(nodeCount > 0)
	{
		if(myList->pickedRegion == 1 && block_ptr != NULL)
		{
			beforeUsed = myList->chosenRegion->usedBlocks;
			myList = rfreeHelper(myList, block_ptr);
			myList->chosenRegion->usedBlocks = myList->chosenRegion->myObjList->blocksFilled;

			if(beforeUsed > myList->chosenRegion->usedBlocks)
			{
				result = true;
			}
			else
			{
				result = false;
			}
		}
		else
		{
			result = false;
		}
	}
	else
	{
		result = false;
	}


	assert(nodeCount >= 0);
	assert((result == true) || (result == false));

	return result;
}






//------------------------------------------------------
// rsize
//
// PURPOSE: return size of a block of memory given by block_ptr if it exists in current region
// INPUT PARAMETERS:
//			block_ptr: the pointer to a block of memory
// OUTPUT PARAMETERS:
// 			size: size of that block of memory. 0 if there's an error.
//------------------------------------------------------
r_size_t rsize(void *block_ptr)
{
	assert(nodeCount >= 0); 

	r_size_t size;

	if(block_ptr != NULL && myList != NULL && nodeCount > 0)
	{
		size = getPtrSize(myList, block_ptr);

		verifyRegion(myList, myList->pickedRegion, nodeCount);
		verifyLList(myList);
	}
	else
	{
		size = 0;
	}


	assert(nodeCount >= 0); 
	assert(size >= 0); 

	return size;
}


