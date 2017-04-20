
//-----------------------------------------
// NAME: Justin Mui
// STUDENT NUMBER: 7624249
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: assignment 4, QUESTION: 1
// 
// REMARKS: Test file for creating and destroying regions as well
//          as allocating a freeing memory.  Regions are checked
//          by using assertions and printing out regions using
//          rdump() and rchosen().
//
//-----------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "regions.h"





int main()
{
  Boolean res;
  char *pt1, *pt2, *pt3, *pt4, *pt5;

  printf("Chosen region: %s\n", rchosen()); //NULL since no regions have been created

  res = rinit("first region", 2000);
  assert(res);

  res = rinit("this shouldn't work", 0);
  assert(!res);

  rchoose("wasd");

  printf("Chosen region: %s\n", rchosen()); //should be "first region"

  res = rinit("DatBoi", 1111);
  assert(res);

  res = rinit("qwertyuiop", 567);
  assert(res);

  printf("Chosen region: %s\n", rchosen()); //should be "qwertyuiop"
  rchoose("DatBoi");
  printf("Chosen region: %s\n", rchosen()); //should be "DatBoi"

  pt1 = ralloc(0);
  assert(pt1 == NULL);

  pt1 = ralloc(420);
  pt2 = ralloc(333);
  pt3 = ralloc(800);
  assert(pt3 == NULL);

  printf("Size: %d\n", rsize(pt1));
  printf("Size: %d\n", rsize(pt2));
  assert(rsize(pt1) > 0);
  assert(rsize(pt2) > 0);
  assert(rsize(pt3) == 0); //this is 0 since it couldn't be created


  rdump(); 


  rchoose("qwertyuiop");
  printf("Chosen region: %s\n", rchosen()); 

  pt4 = ralloc(0);
  assert(pt4 == NULL);

  pt4 = ralloc(567);
  printf("Size: %d\n", rsize(pt4));
  assert(rsize(pt4) > 0);

  rchoose("first region");
  printf("Chosen region: %s\n", rchosen()); 

  pt3 = ralloc(1200);
  pt5 = ralloc(750);
  printf("Size: %d\n", rsize(pt3));
  printf("Size: %d\n", rsize(pt5));


  res = rfree(pt1);
  assert(!res);

  //pt1 and pt4 are 0 since they don't belong to the chosen region
  assert(rsize(pt4) == 0);
  assert(rsize(pt1) == 0);
  assert(rsize(pt3) > 0);

  rdump();

  //free blocks pt1 and pt2 in "DatBoi".  pt5 shouldn't be freed since it belongs to "first region"
  rchoose("DatBoi");
  printf("Chosen region: %s\n", rchosen()); 

  res = rfree(pt1);
  assert(res);

  res = rfree(pt2);
  assert(res);

  res = rfree(pt5);
  assert(!res);


  //free both blocks in "first region"
  rchoose("first region");
  printf("Chosen region: %s\n", rchosen()); 

  res = rfree(pt3);
  assert(res);
  res = rfree(pt5);
  assert(res);



  //free block pt4 but not pt1 since it belongs to another region
  rchoose("qwertyuiop");
  printf("Chosen region: %s\n", rchosen()); 

  res = rfree(pt1);
  assert(!res);

  res = rfree(pt4);
  assert(res);

  
  rdump(); //regions should exist here but empty


  rchoose("first region");
  rdestroy("first region");

  assert(rchosen() == NULL);
  printf("Chosen region: %s\n", rchosen());  //this should be NULL since chosen region was destroyed
  

  rdestroy("qwertyuiop");


  rdump(); //only region "DatBoi" exist
  rdestroy("DatBoi");

  
  rdump(); // no regions exist


  fprintf(stderr,"\nEnd of processing.\n");

  return EXIT_SUCCESS;
}




