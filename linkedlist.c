// linked list taken from lecture notesd

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linkedlist.h"
//#include <malloc/malloc.h>






LinkedList newList()
{
  LinkedList newList;

  newList = (LinkedList) malloc(sizeof(LinkedList));
  assert(newList != NULL);

  if(newList != NULL)
  {
  newList->first = NULL;
  newList->size = 0;
  }
  else
  {
    newList = NULL;
  }

  return newList;
}


//get number of nodes in list
int getSize(LinkedList list)
{
  return list->size;
}


//add a new node to beginning of list
LinkedList addNode(LinkedList list, const char *region_name, short region_size)
{
  node *newNode;

  newNode = malloc(sizeof(node));
  assert(newNode != NULL);
  newNode->name = (char *)malloc(sizeof(char) * strlen(region_name) + 1);
  assert(newNode->name != NULL);
  newNode->region = (unsigned char *)malloc(sizeof(char) * region_size);
  assert(newNode->region != NULL);


  if(newNode != NULL && newNode->name != NULL && newNode->region != NULL)
  {
    newNode->blockTotalSize = region_size;
    newNode->usedBlocks = 0;
    strncpy(newNode->name, region_name, strlen(region_name));
    newNode->next = list->first;
    list->first = newNode;
    list->size++;
  }
  else
  {
    printf("Malloc failed!\n");
    list = NULL;
  }


  return list;
}



//check if a node with name matching region_name exists then return 1 if found and 0 if not found
int findNode(LinkedList list, const char *region_name)
{
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
    }
    else
    {
      count++;
      currentNode = currentNode->next;
    }

  }

  return result;
}




//check if a node with name matching region_name exists then return list
LinkedList findRegion(LinkedList list, const char *region_name)
{
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
    }
    else
    {
      count++;
      currentNode = currentNode->next;
    }

  }

  if(result == 0)
  {
    list->chosenRegion = NULL;
  }

  return list;
}




//remove a region from list if it exists
LinkedList removeNode(LinkedList list, const char *region_name)
{
  int result;
  int count;
  node *previousNode;
  node *currentNode;
  node *toRemove;

  result = 0;
  count = 0;
  previousNode = NULL;
  currentNode = list->first;

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

      free(toRemove->region);
      free(toRemove->name);
      //add another free to free object index
      free(toRemove);
      
      //printf("#########4\n");
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

  return list;
}






void printRegions(LinkedList list)
{
  int percentFree;
  node *currentNode;

  currentNode = list->first;

  if(list->size > 0)
  {
    for(int i = 0; i < list->size; i++)
    {
      percentFree = currentNode->blockTotalSize - currentNode->usedBlocks;
      percentFree /= currentNode->blockTotalSize;
      percentFree *= 100;

      printf("%s\n", currentNode->name);
      printf(", Free blocks: %i%%\n", percentFree);  //need to add blocks allocated and block sizes.  %p for block pointers
      currentNode = currentNode->next;
    }
    printf("End of lists\n");
  }
  else
  {
    printf("Empty list.\n");
  }

}










//choose and return node matching region_name, else returns a NULL region
/*node chooseNode(LinkedList list, const char *region_name)
{
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
    }
    else
    {
      count++;
      currentNode = currentNode->next;
    }

  }

  if(result == 0)
  {
    currentNode = NULL;
  }

  return currentNode;
}*/


