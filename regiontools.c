
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "regions.h"
#include "regiontools.h"
//#include "linkedlist.h"



//round region_size up to nearest multiple of 8
r_size_t roundSize(r_size_t region_size)
{
	assert(region_size > 0);

	r_size_t remainder;

	remainder = region_size % 8;

	if(remainder > 0)
	{
		remainder = 8 - remainder;
		region_size += remainder;
	}
	
	assert(region_size > 0);
	return region_size;
}




// invariants for regions
void verifyRegion(LinkedList myList, int pickedRegion, int nodeCount)
{
	assert(myList != NULL);
	assert(nodeCount >= 0);
	assert(pickedRegion >= 0);
	assert(pickedRegion <= 1);
}



//invariants for linkedlist
void verifyLList(LinkedList list)
{
  assert(list != NULL);
  //assert(list->first != NULL);
  assert(list->size > 0);
  assert(list->allocResult >= 0);
  assert(list->allocResult <= 1);

  if(list->pickedRegion == 1)
  {
    verifyNodeOnly(*list->chosenRegion);
  }
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

