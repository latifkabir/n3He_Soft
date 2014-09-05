#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std; 
int main(void)
{
  char hex[] = "ff";
 
  //printf("%ld\n", strtol(hex, NULL, 16));
  long int k=strtol(hex, NULL, 16);
  cout<<k;
  return 0;
}
