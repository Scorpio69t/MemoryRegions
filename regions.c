#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "regions.h"
#include "linkedlist.h"


r_size_t roundSize(r_size_t);
static int nodeCount = 0;
int pickedRegion;
LinkedList myList;



//round region_size up to nearest multiple of 8
r_size_t roundSize(r_size_t region_size)
{
	r_size_t remainder;

	remainder = region_size % 8;

	if(remainder > 0)
	{
		remainder = 8 - remainder;
		region_size += remainder;
	}
	
	return region_size;
}



//create and select that region if it doesn't already exist 
Boolean rinit(const char *region_name, r_size_t region_size)
{
	Boolean result;

	result = true;

	if(nodeCount == 0)
	{			
		myList = newList();

		if(myList != NULL)
		{
			//printf("RINIT WORKS + %d\n", getSize(myList));
			//myList = addNode(myList, "", 1);

		}
		else
		{
			result = false;
		}
		//addNode("", 1); //first node added will be empty
	}

	if(region_size >= 1)
	{
		// round if size isn't zero
		region_size = roundSize(region_size); 
	}
	else //if region_size is 0
	{
		result = false;
	}

	//check if name already exists in list
	//result = chooseNode(region_name);
	//result = !result;

	//initialize memory region if size and name test pass
	if(result)
	{
		if(nodeCount == 0)
		{
			myList = addNode(myList, region_name, region_size);
			//printf("ADDED NODE %s, list size: %d\n", region_name, getSize(myList));	
			nodeCount = myList->size;
			rchoose(region_name);
			//printf("ADDED NODE %s, size: %d\n", rchosen(), getSize(myList));	
		}
		else if(nodeCount > 0)
		{	
			if(findNode(myList, region_name)) //if name already exists
			{
				printf("Region with name %s already exists\n", region_name);
				result = false;
			}
			else
			{
				myList = addNode(myList, region_name, region_size);
				//printf("ADDED NODE %s, list size: %d\n", region_name, getSize(myList));	
				nodeCount = myList->size;
				rchoose(region_name);
				//printf("ADDED NODE %s, size: %d\n", rchosen(), getSize(myList));	
			}
		}
		else
		{
			printf("Cannot add region.\n");
			result = false;
		}
		//result = addNode(region_name, region_size);
		//rchoose(region_name);
	}

	//printf("number of regions: %i, result: %i\n", nodeCount, result);

	return result;
}




// return name of currently chosen node and null if a node isn't chosen
const char *rchosen()
{
	char *currentName;

	if(pickedRegion == 0)
	{
		currentName = NULL;
	}
	else
	{
		currentName = malloc(sizeof(char) * strlen(myList->chosenRegion->name) + 1);
		assert(currentName != NULL);
		if(currentName != NULL)
		{
			strncpy(currentName, myList->chosenRegion->name, strlen(myList->chosenRegion->name));
		}
		else
		{
			printf("Malloc failed!\n");
			currentName = NULL;
		}
	}

	return currentName;
}




// choose a region matching the name from region_name
// returns true if it exists and false if it doesn't
Boolean rchoose(const char *region_name)
{
	Boolean result; // remove = true later

	myList = findRegion(myList, region_name);
	//printf("%s CHOEENESNN REGION\n", myList->chosenRegion->name);
	if(myList->chosenRegion == NULL)
	{
		pickedRegion = 0;
		result = false;
	}
	else
	{
		pickedRegion = 1;
		result = true;
	}

	return result;
}







//remove a region from list
void rdestroy(const char *region_name)
{
	if(nodeCount > 0)
	{
		myList = removeNode(myList, region_name);
		nodeCount = myList->size;
		//printf("SIZE: %i\n", myList->size);

		if(myList->chosenRegion == NULL)
		{
			pickedRegion = 0;
			
		}
	}
	else //if(nodeCount == 0) //this hasn't been tested yet. try by removing everyone node with redestroy in test.c ---------------------------------------------------------------------------------------------
	{
		if(myList != NULL)
		{
			free(myList);

		}
		pickedRegion = 0;
	}


	if(nodeCount == 0 && myList != NULL)
	{
		free(myList);
	}
}




void rdump()
{
	
	if(nodeCount > 0)
	{
		//printf("%s REGION NAME \n", myList->first->name);
		printRegions(myList);
	}
	else
	{
		printf("No regions exist.\n\n");
	}
}



//allocate block of memory in chosen region if there are enough contiguous bytes
void *ralloc(r_size_t block_size)
{
	void *blockPtr;
	int freeBlocks;

	freeBlocks = myList->chosenRegion->blockTotalSize - myList->chosenRegion->usedBlocks;
	//printf("\nBLOCKS FREE %i, ALLOCATING %i\n", freeBlocks, block_size);
	//check that region to allocate is larger than 0 and less than the amount of free memory remaining
	if(block_size > 0 && block_size < freeBlocks)
	{
		//this can still return NULL if not enough contiguous empty blocks are found
		myList = allocateBlock(myList, block_size);  //might need to return list and add struct variable for new blockPtr
		if(myList->allocResult == 1)
		{
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


	return blockPtr;
}





Boolean rfree(void *block_ptr)
{
	Boolean result;
	int beforeUsed;

	beforeUsed = myList->chosenRegion->usedBlocks;
	myList = rfreeHelper(myList, block_ptr);

	myList->chosenRegion->usedBlocks = myList->chosenRegion->myObjList->blocksFilled;
	//printf("############ %i\n", myList->chosenRegion->myObjList->blocksFilled);
	//if less used blocks after calling rfreeHelper

	if(beforeUsed > myList->chosenRegion->usedBlocks)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}





r_size_t rsize(void *block_ptr)
{
	r_size_t size;

	size = getPtrSize(myList, block_ptr);

	return size;
}

