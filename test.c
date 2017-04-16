#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "regions.h"
//#include "linkedlist.h"  //might not need to include this for main/test



int main()
{
	Boolean rc;
	char batman[7] = "Batman";
	/*char DatBoi[7] = "DatBoi";
	char qwerty[6] = "qwerty";
	char omg[13] = "OmgwTfbbQ";*/
	char *ca1, *ca2, *ca3;

	//assert(rc);
	//rc = rinit("unicycle frog", 8956);
	//assert(rc);
	//rc = rinit("qwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiop", 1026);
	//assert(rc);
	rc = rinit(batman, 756);  
	assert(rc);

	ca3 = ralloc(300);
	ca2 = ralloc(61);
	ca1 = ralloc(100);
	printf("ALLOCATING PTR %p, %p, %p\n", ca3, ca2, ca1);
	/*rc = rinit(batman, 420);
	assert(!rc);
	rc = rinit(omg, 222); 
	assert(rc);
	rc = rinit(qwerty, 987); 
	assert(rc);
	rc = rinit(DatBoi, 456); 
	assert(rc);
	rc = rinit(omg, 100);
	assert(!rc);
	rc = rinit(qwerty, 421);
	assert(!rc);
	rc = rchoose(DatBoi);
	rdestroy(DatBoi);
	rc = rinit(DatBoi, 333);
	assert(rc);
	rdestroy(batman);
	rc = rinit(batman, 111);  
	assert(rc);
	
	printf("CHOSEN REGION: %s\n", rchosen());
	rc = rchoose(batman);
	printf("CHOSEN REGION: %s\n", rchosen());
	rc = rchoose("awdawdawdawd");
	printf("CHOSEN REGION: %s\n", rchosen());
	rc = rchoose(DatBoi);
	printf("CHOSEN REGION: %s\n", rchosen());
	rc = rchoose(omg);
	rdestroy(omg);
	printf("CHOSEN REGION: %s\n", rchosen());*/


	rdump();

	printf("\n\nProgram completed normally.\n");
	return EXIT_SUCCESS;
}


