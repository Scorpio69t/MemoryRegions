// linked list taken from lecture notes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#include <malloc/malloc.h>

#include "linkedlist.h"



static int listSize = 0;
static node *top = NULL;
 
// used to track where we are for the list traversal methods
static node *traverseNode = NULL;
    
// "destroy" will deallocate all nodes in a linked list object
// and will set "top" to NULL.
void destroy()
{
  node *curr = top;
  node *temp = NULL;

  while ( curr != NULL )
  {
    // flip order to see it blow up...
    temp = curr;
    curr = curr->next;

    free( temp );
  }

  top = NULL;
}


// returns number of nodes in list
int getSize()
{
  return listSize;
}




char *currentName()
{
  char *temp;

  if(traverseNode != NULL)
  {
    temp = malloc(strlen(traverseNode->data) + 1);
    strncpy(temp, traverseNode->data, strlen(traverseNode->data));
  }
  else
  {
    temp = NULL;
  }
  //printf("%lu###\n", strlen(traverseNode->data));
  return temp;
}



// "build" will create an ordered linked list consisting
// of the first "size" even integers.
void addNode(const char *region_name, unsigned short region_size)
{
  node *newNode = NULL;


  newNode = malloc( sizeof( node ) );
  newNode->data = (char *)malloc(sizeof(char) * strlen(region_name));  
  strncpy(newNode->data, region_name, strlen(region_name));

  newNode->region = (char *)malloc(region_size * sizeof(char));

  /*if(newNode->region != NULL)
  {
    printf("malloc worked for: %s\n", region_name);
  }
  else
  {
    printf("malloc failed for: %s\n", region_name);
  }*/
  assert(newNode->region != NULL);
  newNode->usedBlocks = 0;
  printf("%i\n",newNode->usedBlocks);
  newNode->blockTotalSize = region_size;

  //int n = sizeof(newNode->region);
  printf("%hu sizetestfor: %s\n", region_size, region_name);
  //printf("%zu sizeoftest\n\n", malloc_size(newNode->region));
  newNode->next = top;
  top = newNode;

  //printf("%s", top->name); //remove after.  prints extra square character so i changed it to for loop


  //make sure strings being copied are equal
  //assert(strcmp(top->data, region_name) == 0);

  //increment list size after each node is added
  listSize++;
  
}



/*void newList(const char *region_name, r_size_t region_size)
{
  node *newNode = NULL;
  data = malloc(sizeof(char) * region_size);
}*/


// starts a list traversal by getting the data at top.
// returns false if top == NULL.
int firstNode()
{
  int result = 0;
  
  if ( top )
  {
    //*item = top->data;
    
    traverseNode = top;
    
    result = 1;
  }  
  
  return result;
}


// gets the data at the current traversal node and increments the traversal.
// returns false if we're at the end of the list.
int nextNode()
{
  int result = 0;
  
  if ( traverseNode )
  {
    //*item = traverseNode->number;
    
    traverseNode = traverseNode->next;
    result = 1;
  }
  
  return result;
}


//go through list to find a region called region_name
int chooseNode(const char *region_name)
{
  int result;
  traverseNode = top;

  result = 0;

  //this block used for top node
  if(traverseNode != NULL && getSize() > 0)
  {
    if(strcmp(region_name, traverseNode->data) == 0)
    {
      result = 1;
    }
  }

  //go through rest of nodes until end of list if region_name didn't match the first node
  while(traverseNode != NULL && result == 0 && getSize() > 0)
  {
    traverseNode = traverseNode->next;
    if(traverseNode != NULL)
    {
      if(strcmp(region_name, traverseNode->data) == 0)
      {
        result = 1;
      }
    }
  }

  return result;
}

// "print" will output an object's entire linked list 
// to the standard output device -- one "number" per line.
/*void print()
{
  int value;
  
  if ( firstNode( &value ) )
  {
    do
    {
      printf( "%d\n", value );
    } while ( nextNode( &value ) );
  }
}*/


