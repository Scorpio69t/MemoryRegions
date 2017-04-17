// linked list taken from textbook

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "linkedlist.h"
#include "objectindex.h"
//#include <malloc/malloc.h>



//create a new list if list is empty
LinkedList newList()
{
  LinkedList newList;

  newList = (LinkedList) malloc(sizeof(LinkedList));
  assert(newList != NULL);

  if(newList != NULL)
  {
    newList->first = NULL;
    newList->size = 0;
    newList->allocResult = 0;
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




//add a new node to beginning of list
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
  //newNode->region = (unsigned char *)malloc(sizeof(char) * region_size);
  newNode->region = malloc(sizeof(char) * region_size);
  assert(newNode->region != NULL);


  if(newNode != NULL && newNode->name != NULL && newNode->region != NULL)
  {
    newNode->blockTotalSize = region_size;
    newNode->usedBlocks = 0;
    strncpy(newNode->name, region_name, strlen(region_name));
    newNode->next = list->first;
    newNode->myObjList = newObjList();  //creates object index for pointers to blocks

    //fill region with non zero
    for(int i = 0; i < newNode->blockTotalSize; i++)
    {
      newNode->region[i] = '1';
      //printf("%c ", newNode->region[i]);
    }
    //printf("\n");

    list->first = newNode;
    list->size++;

    verifyLList(list);
    verifyNodeOnly(*list->first);
  }
  else
  {
    //printf("Malloc failed!\n");
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



//check if a node with name matching region_name exists then return 1 if found and 0 if not found
int findNode(LinkedList list, const char *region_name)
{
  assert(list != NULL);
  assert(strlen(region_name) > 0);

  int result;
  int count;
  node *currentNode;

  result = 0;
  count = 0;
  currentNode = list->first;

  verifyLList(list);

  while(count < list->size && result == 0) //might need to be <= list->size
  {
    if(strcmp(region_name, currentNode->name) == 0)
    {
      result = 1;
      list->chosenRegion = currentNode;

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




//check if a node with name matching region_name exists then return list
LinkedList findRegion(LinkedList list, const char *region_name)
{
  assert(strlen(region_name) > 0);

  int result;
  int count;
  node *currentNode;

  result = 0;
  count = 0;
  currentNode = list->first;


  while(count < list->size && result == 0) //might need to be <= list->size
  {
    if(strcmp(region_name, currentNode->name) == 0)
    {
      result = 1;
      list->chosenRegion = currentNode;

      verifyNodeOnly(*list->chosenRegion);
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
    list->chosenRegion = NULL;
  }

  assert(strlen(region_name) > 0);
  return list;
}




//remove a region from list if it exists
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
  verifyNodeOnly(*currentNode);

  while(count < list->size && result == 0) //might need to be <= list->size
  {
    if(strcmp(region_name, currentNode->name) == 0)
    {

      // unchoose region to be destroyed if it is currently chosen
      if(strcmp(list->chosenRegion->name, currentNode->name) == 0)
      {
        list->chosenRegion = NULL;
      }


      result = 1;
      //printf("#########1\n");
      if(previousNode == NULL)
      {
        toRemove = currentNode;
        list->first = currentNode->next;  
        //printf("#########2\n");
      }
      else
      {
        toRemove = currentNode;
        previousNode->next = currentNode->next;
        //printf("#########3\n");
      }
      //printf("Destroying region: %s\n\n", region_name);
      verifyNodeOnly(*toRemove);

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
     
      //printf("#########5\n");
    }
  }


  if(result)
  {
    list->size--;
    //printf("#########6\n");
  }
  //printf("#########7\n");


  assert(list != NULL);
  assert(strlen(region_name) > 0);

  return list;
}





// print of block addresses, amount of memory used by that block, and percentage of free memory left in that region
void printRegions(LinkedList list)
{
  assert(list != NULL);

  double percentFree;
  int intPercent;
  node *currentNode;

  currentNode = list->first;
  
  if(list->size > 0)
  {
    verifyNodeOnly(*currentNode);

    for(int i = 0; i < list->size; i++)
    {
      percentFree = currentNode->blockTotalSize - currentNode->usedBlocks; 
      percentFree = (percentFree / currentNode->blockTotalSize) * 100;
      intPercent = percentFree;

      printf("\nRegion name: %s\n", currentNode->name);
      printPointers(currentNode->myObjList);
      printf("Free blocks: %i%%\n", intPercent);  //need to add blocks allocated and block sizes.  %p for block pointers
      currentNode = currentNode->next;
    }
    printf("End of regions list.\n\n");

    verifyLList(list);
  }
  else
  {
    printf("Empty list.\n\n");
  }

  /*char *ptr1;
  for(ptr1 = list->chosenRegion->region; ptr1 < list->chosenRegion->region + list->chosenRegion->blockTotalSize; ptr1++)
  {
    printf("%c", (*ptr1));
  }*/

  assert(list != NULL);
}





LinkedList allocateBlock(LinkedList list, unsigned short block_size)
{
  assert(list->chosenRegion != NULL);
  assert(block_size > 0);

  void *blockPtr = NULL; // remove null
  char *ptr1;

  //look for contiguous blocks of free bytes in list->chosenRegion
  blockPtr = findFreeBlocks(*list->chosenRegion, block_size); //maybe remove asterisk *


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
    verifyNodeOnly(*list->chosenRegion);
    //list->chosenRegion->usedBlocks += block_size;
  }
  else
  {
    blockPtr = NULL;
    list->allocResult = 0;

    verifyLList(list);
  }


  //print whole region to test
  /*for(ptr1 = list->chosenRegion->region; ptr1 < list->chosenRegion->region + list->chosenRegion->blockTotalSize; ptr1++)
  {
    printf("%c", (*ptr1));
  }*/

  //printf("\n");

  assert(list->chosenRegion != NULL);
  assert(block_size > 0);

  return list;
}




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
    if(*currentPtr != '0') //might need to initialise all spaces in region to something other than '0' either in linkedlist.c or regions.c
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

  //pointer arthmetic to traverse region and find block space
  // http://www.cs.umanitoba.ca/~fbristow/lectures/comp2160/lecture23-mar22/lecture23-mar22.html?print-pdf#/

  if(found == 0)
  {
    startPtr = NULL;
  }

  assert(block_size > 0);
  return startPtr;
}




LinkedList rfreeHelper(LinkedList list, void *block_ptr)
{
  assert(list != NULL);
  assert(block_ptr != NULL);

  char *ptr1;
  char *ptr2;
  int size;
  //printf("%p %p \n", block_ptr, list->chosenRegion->region);
  size = findPtr(list->chosenRegion->myObjList, block_ptr);

  if(size > 0)
  {
    ptr2 = block_ptr + size;
    for(ptr1 = block_ptr; ptr1 < ptr2; ptr1++)
    {
      (*ptr1) = '1';
    }
    verifyLList(list);
  }



  list->chosenRegion->myObjList = freeBlock(list->chosenRegion->myObjList, block_ptr);

  verifyNodeOnly(*list->chosenRegion);
  verifyLList(list);
//printf("********************\n");

  /*for(ptr1 = list->chosenRegion->region; ptr1 < list->chosenRegion->region + list->chosenRegion->blockTotalSize; ptr1++)
  {
    printf("%c", (*ptr1));
  }*/


  assert(list != NULL);
  assert(block_ptr != NULL);
  return list;
}



unsigned short getPtrSize(LinkedList list, void *block_ptr)
{
  assert(list != NULL);
  assert(block_ptr != NULL);

  unsigned short size;

  size = findPtr(list->chosenRegion->myObjList, block_ptr);

  assert(size > 0);
  verifyNodeOnly(*list->chosenRegion);
  verifyLList(list);

  assert(list != NULL);
  assert(block_ptr != NULL);
  return size;
}



//invariants for linkedlist
void verifyLList(LinkedList list)
{
  assert(list != NULL);
  assert(list->first != NULL);
  assert(list->size > 0);
  assert(list->allocResult >= 0);
  assert(list->allocResult <= 1);
}


//invariants for nodes currently selected
void verifyNodeOnly(node currentNode)
{
  assert(currentNode.region != NULL);
  assert(currentNode.name != NULL);
  assert(strlen(currentNode.name) > 0);
  assert(currentNode.blockTotalSize > 0);
  assert(currentNode.usedBlocks >= 0);
  assert(currentNode.usedBlocks <= currentNode.blockTotalSize);
}

