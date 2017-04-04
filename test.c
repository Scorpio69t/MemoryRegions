#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "regions.h"
#include "linkedlist.h"



int main()
{
	Boolean rc;

	rc = rinit("KappaKeepo", 2010);
	assert(rc);
	rc = rinit("OmgWtfBbq", 2010);
	assert(rc);

	printf("%s\n", rchosen()); //maybe remove

	return EXIT_SUCCESS;
}
