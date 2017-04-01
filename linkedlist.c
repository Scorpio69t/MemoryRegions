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


// "build" will create an ordered linked list consisting
// of the first "size" even integers.
void build(const char *region_name, unsigned short region_size)
{

  node *newNode = NULL;

  // make sure we don't have a list yet
  //destroy();


  newNode = malloc( sizeof( node ) );
  newNode->name = malloc(sizeof(region_name));
  strcpy(newNode->name, region_name);
  newNode->data = malloc(sizeof(char) * region_size);

  //(*newNode).data[5] = 'w';
  newNode->next = top;

  top = newNode;
  printf("%s\n", newNode->name);

  listSize++;
}



/*void newList(const char *region_name, r_size_t region_size)
{
  node *newNode = NULL;
  data = malloc(sizeof(char) * region_size);
}*/


// starts a list traversal by getting the data at top.
// returns false if top == NULL.
int firstNode( int *item )
{
  int result = 0;
  
  if ( top )
  {
    //*item = top->number;
    
    traverseNode = top->next;
  
    result = 1;
  }  
  
  return result;
}


// gets the data at the current traversal node and increments the traversal.
// returns false if we're at the end of the list.
int nextNode( int *item )
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


// "print" will output an object's entire linked list 
// to the standard output device -- one "number" per line.
void print()
{
  int value;
  
  if ( firstNode( &value ) )
  {
    do
    {
      printf( "%d\n", value );
    } while ( nextNode( &value ) );
  }
}


