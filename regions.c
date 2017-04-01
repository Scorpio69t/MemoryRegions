#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "regions.h"
//#include "linkedlist.h"


r_size_t roundSize(r_size_t);

int listSize = 0;

//round region_size up to nearest multiple of 8
r_size_t roundSize(r_size_t region_size)
{
	r_size_t remainder;

	remainder = region_size % 8;
	remainder = 8 - remainder;
	region_size += remainder;
	return region_size;
}



Boolean rinit(const char *region_name, r_size_t region_size)
{
	Boolean result;

	result = true;

	if(region_size == 0)
	{
		result = false;
	}
	else
	{
		// round if size isn't zero
		region_size = roundSize(region_size); 
	}

	//put loop here to check for unique name


	//initialize memory region
	for(int i = 0; i < region_size; i++)
	{
		
	}


	return result;
}


