#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "regions.h"
#include "linkedlist.h"


r_size_t roundSize(r_size_t);


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


	if(region_size >= 1)
	{
		// round if size isn't zero
		region_size = roundSize(region_size); 
	}
	else //if region_size is 0
	{
		result = false;
	}


	//put loop here to check for unique name
	for(int i = 0; i < getSize(); i++)
	{

	}


	//initialize memory region if size and name test pass
	if(result)
	{
		addNode(region_name, region_size);
	}

	
	return result;
}




const char *rchosen()
{
	return currentName();
}




Boolean rchoose(const char *region_name)
{
	Boolean result;

	result = chooseNode(region_name);

	return result;
}

