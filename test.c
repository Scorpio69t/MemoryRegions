#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "regions.h"
#include "linkedlist.h"  //might not need to include this for main/test



int main()
{
	Boolean rc;


	rc = rinit("Batman", 756);
	//assert(rc);
	//rc = rinit("unicycle frog", 8956);
	//assert(rc);
	//rc = rinit("qwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiop", 1026);
	//assert(rc);

	rc = rinit("Batman", 420);
	rc = rinit("qwerty", 987);
	rc = rinit("datboi", 456);
	rc = rinit("qwerty", 421);
	rc = rinit("datboi", 456);
	//printf("%i list size\n", getSize()); //remove after
	//printf("Chosen: %s\n\n", rchosen());


	/*rc = rchoose("Batman");
	if(rc == 0)
	{
		printf("cant find name Batman\n");
	}
	else
	{
		printf("found name Batman\n");
	}
	printf("Chosen: %s\n\n", rchosen());


	rc = rchoose("qwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiop");
	if(rc == 0)
	{
		printf("cant find name qwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiop\n");
	}
	else
	{
		printf("found name qwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiop\n");
	}
	printf("Chosen: %s\n\n", rchosen());


	rc = rchoose("unicycle frog");
	if(rc == 0)
	{
		printf("cant find name unicycle frog\n");
	}
	else
	{
		printf("found name unicycle frog\n");
	}
	printf("Chosen: %s\n\n", rchosen());




	rc = rchoose("thisdoesntexist");
	if(rc == 0)
	{
		printf("cant find name thisdoesntexist\n");
	}
	else
	{
		printf("found name thisdoesntexist\n");
	}
	printf("Chosen: %s\n\n", rchosen()); */




	/*printf("-------------------------\n");
	destroyList();
	printf("-------------------------\n");*/


	printf("Program completed normally.");
	return EXIT_SUCCESS;
}
