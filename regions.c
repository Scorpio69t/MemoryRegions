
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


//create and select that region if it doesn't already exist 
Boolean rinit(const char *region_name, r_size_t region_size)
{
	assert(nodeCount >= 0); //-------------------------------------------------------------------------------------
	//printf("REGION NAME: %s\n", region_name);
	//assert(strlen(region_name) > 0);
	//assert(region_size > 0);

	Boolean result;

	result = true;

	if(region_name != NULL && region_size > 0)
	{

		if(nodeCount == 0)
		{			
			myList = newList();

			if(myList != NULL)
			{
				//printf("RINIT WORKS + %d\n", getSize(myList));
				//myList = addNode(myList, "", 1);
				result = true;
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
		if(result == true)
		{
			if(nodeCount == 0)
			{
				myList = addNode(myList, region_name, region_size);
				//printf("ADDED NODE %s, list size: %d\n", region_name, getSize(myList));	
				nodeCount = myList->size;
				rchoose(region_name);
				//printf("REGION NAME: %s, LIST NAME: %s\n", region_name, myList->chosenRegion->name);
				//printf("ADDED NODE %s, size: %d\n", rchosen(), getSize(myList));	
			}
			else if(nodeCount > 0)
			{	
				if(findNode(myList, region_name)) //if name already exists
				{
					//printf("Region with name %s already exists\n", region_name);
					result = false;
				}
				else
				{
					myList = addNode(myList, region_name, region_size);
					//printf("ADDED NODE %s, list size: %d\n", region_name, getSize(myList));	
					nodeCount = myList->size;
					rchoose(region_name);
					//printf("CHOSEN REGION: %s, LISTSIZE: %i\n", myList->chosenRegion->name, myList->size);
					//printf("REGION NAME: %s, LIST NAME: %s\n", region_name, myList->chosenRegion->name);

					verifyRegion(myList, myList->pickedRegion, nodeCount);
					verifyLList(myList);

					//printf("ADDED NODE %s, size: %d\n", rchosen(), getSize(myList));	
				}
			}
			else
			{
				//printf("Cannot add region.\n");
				result = false;
			}
			//result = addNode(region_name, region_size);
			//rchoose(region_name);
		}
	}
	else
	{
		result = false;
	}
	//printf("number of regions: %i, result: %i\n", nodeCount, result);
//printf("%s ######### chosen name\n", myList->chosenRegion->name);

	//assert(strlen(region_name) > 0);
	//assert(region_size > 0);
	assert((result == true) || (result == false));
	assert(nodeCount >= 0); //-------------------------------------------------------------------------------------
	return result;
}




// return name of currently chosen node and null if a node isn't chosen
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
			//printf("RCHOSEN: %s structlength: %lu, currentNAme length: %lu", currentName, strlen(myList->chosenRegion->name), strlen(currentName));  
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
				//printf("Malloc failed!\n");
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




// choose a region matching the name from region_name
// returns true if it exists and false if it doesn't
Boolean rchoose(const char *region_name)
{
	assert(nodeCount >= 0); //-------------------------------------------------------------------------------------
	//assert(strlen(region_name) > 0);

	Boolean result; // remove = true later
//printf("%s #########\n", region_name);
	if(region_name != NULL)
	{
		if(nodeCount > 0)
		{
			myList->foundNewRegion = 0;

			myList = findRegion(myList, region_name);

			verifyLList(myList);
			verifyRegion(myList, myList->pickedRegion, nodeCount);
			//printf("%s CHOEENESNN REGION\n", myList->chosenRegion->name);
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

	//assert(strlen(region_name) > 0);
	assert(nodeCount >= 0); //-------------------------------------------------------------------------------------
	assert((result == true) || (result == false));

	return result;
}







//remove a region from list
void rdestroy(const char *region_name)
{
	assert(nodeCount >= 0); //-------------------------------------------------------------------------------------
	//assert(strlen(region_name) > 0);
	/*if(strcmp(region_name, "r5001") == 0)
	{
		//rdump();
		printf("***************** %i\n", myList->size);

	}*/
	if(region_name != NULL)//--------------------------------------------------------------------------------------
	{
		if(strlen(region_name) > 0)//------------------------------------------------------------------------------
		{
			if(nodeCount > 0)
			{
				verifyRegion(myList, myList->pickedRegion, nodeCount);
				verifyLList(myList);

				myList = removeNode(myList, region_name);
		//printf("############## %i\n", nodeCount);
				//if(strcmp(region_name, "r5001") == 0){printf("^^^^^^^^^^^^^^^^\n");}

				nodeCount = myList->size;
				//printf("nodecount: %i, regionname: %s\n", nodeCount, region_name);
				//printf("SIZE: %i\n", myList->size);

				/*if(myList->chosenRegion == NULL)
				{
					myList->pickedRegion = 0;
				}*/


			}
			else //if(nodeCount == 0) //this hasn't been tested yet. try by removing everyone node with redestroy in test.c ---------------------------------------------------------------------------------------------
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

	assert(nodeCount >= 0); //-------------------------------------------------------------------------------------
	//assert(strlen(region_name) > 0);
}




void rdump()
{
	assert(myList >= 0);

	if(nodeCount > 0 )//&& myList != NULL)
	{
		//printf("%s REGION NAME \n", myList->first->name);
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



//allocate block of memory in chosen region if there are enough contiguous bytes
void *ralloc(r_size_t block_size)
{
	//assert(myList != NULL);
	//assert(block_size > 0);
	assert(nodeCount >= 0); //-------------------------------------------------------------------------------------

	void *blockPtr;
	int freeBlocks;

	if(nodeCount > 0) // maybe move noceCount > 0 here instead of checking for NULL list ---------------------------------
	{
		if(myList->pickedRegion == 1 && block_size > 0)  //removed nodecount check ----------------------------------- 
		{
			block_size = roundSize(block_size);
			freeBlocks = myList->chosenRegion->blockTotalSize - myList->chosenRegion->usedBlocks;
			//printf("\nBLOCKS FREE %i, ALLOCATING %i\n", freeBlocks, block_size);
			//check that region to allocate is larger than 0 and less than the amount of free memory remaining

			if(block_size > 0 && block_size <= freeBlocks)
			{

				//this can still return NULL if not enough contiguous empty blocks are found
				myList = allocateBlock(myList, block_size);  //might need to return list and add struct variable for new blockPtr
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


	//assert(block_size > 0);
	//assert(myList != NULL);
	assert(nodeCount >= 0); //-------------------------------------------------------------------------------------
	return blockPtr;
}





Boolean rfree(void *block_ptr)
{
	//assert(block_ptr != NULL);
	assert(nodeCount >= 0); //------------------------------------

	Boolean result;
	int beforeUsed;

	if(nodeCount > 0)
	{
		if(myList->pickedRegion == 1 && block_ptr != NULL)
		{
			//verifyRegion(myList, myList->pickedRegion, nodeCount);
			//verifyLList(myList);

			beforeUsed = myList->chosenRegion->usedBlocks;
			myList = rfreeHelper(myList, block_ptr);
			myList->chosenRegion->usedBlocks = myList->chosenRegion->myObjList->blocksFilled;
			//printf("############ %i\n", myList->chosenRegion->myObjList->blocksFilled);
			//if less used blocks after calling rfreeHelper
			
			//maybe move assertions here

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

	//assert(block_ptr != NULL);
	assert((result == true) || (result == false));

	return result;
}





r_size_t rsize(void *block_ptr)
{
	//assert(block_ptr != NULL);

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
	//assert(block_ptr != NULL);

	return size;
}


