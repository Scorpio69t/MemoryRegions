// linked list taken from lecture notes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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

  // make sure we don't have a list yet
  //destroy();
  newNode = malloc( sizeof( node ) );
  newNode->data = malloc(strlen(region_name) + 1);  
  strncpy(newNode->data, region_name, strlen(region_name));


  newNode->next = top;
  top = newNode;

  //printf("%s", top->name); //remove after.  prints extra square character so i changed it to for loop


  //make sure strings being copied are equal
  assert(strcmp(top->data, region_name) == 0);

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
  node *temp = NULL;

  result = 0;

  if(traverseNode != NULL && getSize() > 0)
  {
    if(strcmp(region_name, traverseNode->data) == 0)
    {
      result = 1;
    }
  }

  while ( traverseNode != NULL && result == 0 && getSize() > 0)
  {
    // flip order to see it blow up...
    temp = traverseNode;
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


