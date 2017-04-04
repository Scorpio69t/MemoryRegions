#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "regions.h"
#include "linkedlist.h"  //might not need to include this for main/test



int main()
{
	Boolean rc;


	rc = rinit("OmgWtfBbq", 756);
	assert(rc);
	rc = rinit("Heartstone", 8956);
	assert(rc);
	rc = rinit("abcdefghij", 1026);
	assert(rc);

	printf("%i list size\n", getSize()); //remove after
	printf("Chosen: %s\n\n", rchosen());


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


	rc = rchoose("abcdefghij");
	if(rc == 0)
	{
		printf("cant find name abcdefghij\n");
	}
	else
	{
		printf("found name abcdefghij\n");
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





	return EXIT_SUCCESS;
}
