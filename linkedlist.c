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


int getSize(LinkedList list)
{
  return list->size;
}



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



