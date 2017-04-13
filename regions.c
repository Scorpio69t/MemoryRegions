#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "regions.h"
#include "linkedlist.h"


r_size_t roundSize(r_size_t);
static int nodeCount = 0;
LinkedList myList;



//round region_size up to nearest multiple of 8
r_size_t roundSize(r_size_t region_size)
{
	r_size_t remainder;

	remainder = region_size % 8;

	if(remainder > 0)
	{
		remainder = 8 - remainder;
		region_size += remainder;
	}
	
	return region_size;
}



Boolean rinit(const char *region_name, r_size_t region_size)
{
	Boolean result;

	result = true;

	if(nodeCount == 0)
	{	
		//printf("RINIT WORKS + %d\n", getSize(list)):
		
		myList = newList();
		
		if(newList != NULL)
		{
			printf("RINIT WORKS + %d\n", getSize(myList));
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
	if(result)
	{
		myList = addNode(myList, region_name, region_size);
		printf("ADDED A NODE + %d\n", getSize(myList));
		//result = addNode(region_name, region_size);
		//rchoose(region_name);
	}

	
	return result;
}



// return name of currently chosen node and null if a node isn't chosen
/*const char *rchosen()
{
	return currentName();
}*/



// choose a region matching the name from region_name
// returns true if it exists and false if it doesn't
Boolean rchoose(const char *region_name)
{
	Boolean result = true; // remove = true later

	//result = chooseNode(region_name);

	return result;
}


/*void destroyList()
{
	destroy();
}*/


