#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "regions.h"
#include "linkedlist.h"



int main()
{
	Boolean rc;

	rc = rinit("hello", 2016);

	printf("%i\n", rc);

	return EXIT_SUCCESS;
}
