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
	rc = rinit("Heartstone", 2010);
	assert(rc);
	printf("%i list size\n", getSize()); //remove after



	rc = rchoose("Heartstone");
	if(rc == 0)
	{
		printf("cant find name Heartstone\n");
	}
	else
	{
		printf("found name Heartstone\n");
	}
	printf("Chosen: %s\n\n", rchosen());




	rc = rchoose("OmgWtfBbq");
	if(rc == 0)
	{
		printf("cant find name OmgWtfBbq\n");
	}
	else
	{
		printf("found name OmgWtfBbq\n");
	}
	printf("Chosen: %s\n\n", rchosen());




	rc = rchoose("kappa");
	if(rc == 0)
	{
		printf("cant find name kappa\n");
	}
	else
	{
		printf("found name kappa\n");
	}
	printf("Chosen: %s\n\n", rchosen()); 


	rc = rchoose("KappaKeepo");
	if(rc == 0)
	{
		printf("cant find name KappaKeepo\n");
	}
	else
	{
		printf("found name KappaKeepo\n");
	}
	printf("Chosen: %s\n\n", rchosen());


	return EXIT_SUCCESS;
}
