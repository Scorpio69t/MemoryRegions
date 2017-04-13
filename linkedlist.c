// linked list taken from lecture notesd

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#include <malloc/malloc.h>

#include "linkedlist.h"




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
  newNode->name = (char *)malloc(sizeof(char) * strlen(region_name));
  assert(newNode->name != NULL);
  newNode->region = malloc(sizeof(char) * region_size);
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
    list = NULL;
  }


  return list;
}



//check if a node with name matching region_name exists
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


