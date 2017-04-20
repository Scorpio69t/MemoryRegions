
//-----------------------------------------
// NAME: Justin Mui
// STUDENT NUMBER: 7624249
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: assignment 4, QUESTION: 1
// 
// REMARKS: A linked list which holds all the regions which
//          are assigned memory in this program.  Most of these
//          functions are called from regions.c to add, remove,
//          and modify regions and blocks of memory.
//          Part of this code taken from course textbook.
//
//-----------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "linkedlist.h"






//------------------------------------------------------
// createList
//
// PURPOSE: create a new linked list of regions if no list already exists
// OUTPUT PARAMETERS:
//      newList: new linked list that was created
//------------------------------------------------------
LinkedList createList()
{
  LinkedList newList;

  newList = (LinkedList) malloc(sizeof(LinkedList));
  assert(newList != NULL);

  if(newList != NULL)
  {
    newList->first = NULL;
    newList->size = 0;
    newList->allocResult = 0;
    newList->pickedRegion = 0;
  }
  else
  {
    newList = NULL;
  }

  assert(newList != NULL);
  assert(newList->size == 0);
  assert(newList->allocResult == 0);

  return newList;
}








//------------------------------------------------------
// addNode
//
// PURPOSE: add a new region to the linked list
// INPUT PARAMETERS:
//      list: linked list to add new region to
//      region_name: name of region to be created
//      region_size: amount of memory to allocate to this region
// OUTPUT PARAMETERS:
//      list: return list once new node is added to it
//------------------------------------------------------
LinkedList addNode(LinkedList list, const char *region_name, unsigned short region_size)
{
  assert(list != NULL);
  assert(region_size > 0);
  assert(strlen(region_name) > 0);

  node *newNode;

  newNode = malloc(sizeof(node));
  assert(newNode != NULL);
  newNode->name = malloc(sizeof(char) * strlen(region_name) + 1); 
  assert(newNode->name != NULL);

  newNode->region = malloc(sizeof(char) * region_size);  
  assert(newNode->region != NULL);


  if(newNode != NULL && newNode->name != NULL && newNode->region != NULL)
  {
    newNode->endRegion = newNode->region + region_size - 1;
    newNode->blockTotalSize = region_size;
    newNode->usedBlocks = 0;
    strncpy(newNode->name, region_name, strlen(region_name));
    newNode->name[strlen(region_name)] = '\0';
    newNode->next = list->first;
    newNode->myObjList = createObjList();  //creates object index for pointers to blocks
    newNode->myObjList->size = 0;

    //fill region with non zero
    for(int i = 0; i < newNode->blockTotalSize; i++)
    {
      newNode->region[i] = 'X';
    }


    list->first = newNode;
    list->size++;

    verifyLList(list);

  }
  else
  {
    list = NULL;
  }


  if(newNode->myObjList == NULL)
  {
    list = removeNode(list, region_name);
  }


  assert(list != NULL);
  assert(region_size > 0);
  assert(strlen(region_name) > 0);

  return list;
}








//------------------------------------------------------
// findNode
//
// PURPOSE: check if a node with name mathing region_name exists. add the node
//          to list->chosenRegion if it exists.
// INPUT PARAMETERS:
//      list: linked list to search in
//      region_name: name of region to find
// OUTPUT PARAMETERS:
//      result: return 1 if the region exists, and 0 if it doesn't
//------------------------------------------------------
int findNode(LinkedList list, const char *region_name)
{
  assert(list != NULL);
  assert(strlen(region_name) > 0);

  int result;
  int count;
  node *currentNode;

  result = 0;
  count = 0;
  list->pickedRegion = 0;
  list->foundNewRegion = 0;
  currentNode = list->first;

  verifyLList(list);

  while(count < list->size && result == 0) 
  {
    if(strcmp(region_name, currentNode->name) == 0)
    {
      result = 1;
      list->chosenRegion = currentNode;
      list->pickedRegion = 1;
      list->foundNewRegion = 1;
      verifyNodeOnly(*list->chosenRegion);
    }
    else
    {
      count++;
      currentNode = currentNode->next;
    }
    
  }

  assert(list != NULL);
  assert(strlen(region_name) > 0);
  assert((result == 1) || (result == 0));

  return result;
}








//------------------------------------------------------
// findRegion
//
// PURPOSE: similar to findNode except it returns the list instead of a boolean
// INPUT PARAMETERS:
//      list: linked list to search in
//      region_name: name of region to find
// OUTPUT PARAMETERS:
//      list: return list with list->foundNewRegion for whether the region was found or not
//------------------------------------------------------
LinkedList findRegion(LinkedList list, const char *region_name)
{
  assert(strlen(region_name) > 0);

  int result;
  int count;
  node *currentNode;

  result = 0;
  count = 0;
  list->foundNewRegion = 0;
  currentNode = list->first;


  while(count < list->size && result == 0) 
  {
    if(strcmp(region_name, currentNode->name) == 0)
    {
      result = 1;
      list->chosenRegion = currentNode;
      list->pickedRegion = 1;
      list->foundNewRegion = 1;
    }
    else
    {
      count++;
      currentNode = currentNode->next;
    }
  }

  verifyLList(list);

  if(result == 0)
  {
    list->foundNewRegion = 0;
  }

  assert(strlen(region_name) > 0);
  return list;
}








//------------------------------------------------------
// removeNode
//
// PURPOSE: remove a region from linked list if it exists
// INPUT PARAMETERS:
//      list: linked list to remove node from
//      region_name: name of region to find and remove
// OUTPUT PARAMETERS:
//      list: linked list that was passed to this function
//------------------------------------------------------
LinkedList removeNode(LinkedList list, const char *region_name)
{
  assert(list != NULL);
  assert(strlen(region_name) > 0);

  int result;
  int count;
  node *previousNode;
  node *currentNode;
  node *toRemove;

  result = 0;
  count = 0;
  previousNode = NULL;
  currentNode = list->first;

  verifyLList(list);  


  while(count < list->size && result == 0) 
  {
    if(strcmp(region_name, currentNode->name) == 0)
    {
      // unchoose region to be destroyed if it is currently chosen
      if(list->pickedRegion == 1)
      {
        if(strcmp(list->chosenRegion->name, currentNode->name) == 0)
        {
          list->chosenRegion = NULL;
          list->pickedRegion = 0;
        }
        else
        {
          list->pickedRegion = 1;
        }
      }


      result = 1;
      if(previousNode == NULL) //first node
      {
        toRemove = currentNode;
        list->first = currentNode->next;  
      }
      else
      {
        toRemove = currentNode;
        previousNode->next = currentNode->next;
      }

      free(toRemove->region);
      free(toRemove->name);
      toRemove->myObjList = freePointers(toRemove->myObjList);  //free every node in object index linked list
      free(toRemove->myObjList);
      free(toRemove);
      
    }
    else
    {
      count++;
      previousNode = currentNode;
      currentNode = currentNode->next;
    }
  }

  verifyLList(list);  

  if(result)
  {
    list->size--;
  }


  assert(list != NULL);
  assert(strlen(region_name) > 0);

  return list;
}








//------------------------------------------------------
// printRegions
//
// PURPOSE: prints out region names, blocks of memory and their size, and percentage of free space remaining.
//          calls printPointers to print out memory blocks and free space
// INPUT PARAMETERS:
//      list: linked list to print data from
//------------------------------------------------------
void printRegions(LinkedList list)
{
  assert(list != NULL);

  double percentFree;
  node *currentNode;

  currentNode = list->first;
  
  if(list->size > 0)
  {
    for(int i = 0; i < list->size; i++)
    {
      percentFree = currentNode->blockTotalSize - currentNode->usedBlocks; 
      percentFree = (percentFree / currentNode->blockTotalSize) * 100;

      printf("\nRegion name: %s\n", currentNode->name);
      if(currentNode->myObjList->size > 0)
      {
        printPointers(currentNode->myObjList);
      }
      printf("Free blocks: %.2f%%\n", percentFree); 
      currentNode = currentNode->next;
    }
    printf("\nEnd of regions list.\n\n");

    verifyLList(list);
  }
  else
  {
    printf("Empty list.\n\n");
  }


  assert(list != NULL);
}







//------------------------------------------------------
// allocateBlock
//
// PURPOSE: allocate a block of memory with size given by block_size. calls findFreeBlocks
//          to find enough contiguous free memory in the region
// INPUT PARAMETERS:
//      list: linked list to allocate new memory to
//      block_size: amount of memory to search for and allocate
// OUTPUT PARAMETERS:
//      list: return list containing pointer if memory was allocated, NULL pointer if 
//            not enough contiguous memory was found
//------------------------------------------------------
LinkedList allocateBlock(LinkedList list, unsigned short block_size)
{
  assert(list->chosenRegion != NULL);
  assert(block_size > 0);

  void *blockPtr = NULL; 
  char *ptr1;

  //look for contiguous blocks of free bytes in list->chosenRegion
  blockPtr = findFreeBlocks(*list->chosenRegion, block_size); 


  if(blockPtr != NULL)
  {
    list->chosenRegion->newBlock = blockPtr;
    list->chosenRegion->myObjList = newObjNode(list->chosenRegion->myObjList, blockPtr, block_size);
    list->allocResult = 1;

    for(ptr1 = list->chosenRegion->newBlock; ptr1 < list->chosenRegion->newBlock + block_size; ptr1++)
    {
      (*ptr1) = '0';
    }

    verifyLList(list);
  }
  else
  {
    blockPtr = NULL;
    list->allocResult = 0;

    verifyLList(list);
  }
 

  assert(list->chosenRegion != NULL);
  assert(block_size > 0);

  return list;
}






//------------------------------------------------------
// findFreeBlocks
//
// PURPOSE: called by allocateBlock to find enough contiguous memory in the currently chosen region
// INPUT PARAMETERS:
//      currentNode: node that is currently chosen
//      block_size: amount of free memory to search for then allocate
// OUTPUT PARAMETERS:
//      startPtr: pointer to memory location that has enough free space, NULL if not
//                enough contiguous memory was found
//------------------------------------------------------
char *findFreeBlocks(node currentNode, unsigned short block_size)
{
  assert(block_size > 0);

  char *startPtr; 
  char *currentPtr;
  int emptyCount;
  int traverseCount;
  int found;

  currentPtr = currentNode.region;
  startPtr = currentPtr;
  emptyCount = 0;
  traverseCount = 0;
  found = 0;


  while(traverseCount < currentNode.blockTotalSize && found == 0)
  {
    if(*currentPtr == 'X') 
    {
      emptyCount++;
    }
    else
    {
      startPtr = currentPtr + 1;
      emptyCount = 0;
    }

    if(emptyCount == block_size)
    {
      found = 1;
    }

    currentPtr = currentPtr + 1;
    traverseCount++;
  }

  // verifyLList() is not called since this function is only passed a node, not a linked list
  verifyNodeOnly(currentNode);

  if(found == 0)
  {
    startPtr = NULL;
  }

  assert(block_size > 0);
  return startPtr;
}






//------------------------------------------------------
// rfreeHelper
//
// PURPOSE: called by rfree() to search for pointer block_ptr in current region then free that
//          block of memory if it exists
// INPUT PARAMETERS:
//      list: linked list with a chosen region
//      block_ptr: pointer to memory block to find and clear
// OUTPUT PARAMETERS:
//      list: linked list containing the current region
//------------------------------------------------------
LinkedList rfreeHelper(LinkedList list, void *block_ptr)
{
  assert(list != NULL);
  assert(block_ptr != NULL);

  char *ptr1;
  char *ptr2;
  int size;
  
  size = findPtr(list->chosenRegion->myObjList, block_ptr);

  if(size > 0)
  {
    ptr2 = block_ptr + size;
    for(ptr1 = block_ptr; ptr1 < ptr2; ptr1++)
    {
      (*ptr1) = 'X';
    }
    verifyLList(list);
  }


  if(list->pickedRegion == 1)
  {
    list->chosenRegion->myObjList = freeBlock(list->chosenRegion->myObjList, block_ptr);
  }

  verifyLList(list);


  assert(list != NULL);
  assert(block_ptr != NULL);

  return list;
}




//------------------------------------------------------
// getPtrSize
//
// PURPOSE: find a pointer if the current region and return the amount of memory that it's using
// INPUT PARAMETERS:
//      list: linked list containing the current region to search in
//      block_ptr: pointer to block of memory to search for
// OUTPUT PARAMETERS:
//      size: amount of memory taken up by block_ptr, and 0 if it wasn't found
//------------------------------------------------------
unsigned short getPtrSize(LinkedList list, void *block_ptr)
{
  assert(list != NULL);
  assert(block_ptr != NULL);

  unsigned short size;

  size = findPtr(list->chosenRegion->myObjList, block_ptr);
  verifyLList(list);

  assert(list != NULL);
  assert(block_ptr != NULL);
  return size;
}





