#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main()
{
  int n, decimal, r[100] ;

  scanf("%d",&decimal) ;
  n = 0 ;
  while (decimal > 0) {
    r[n] = decimal % 2 ;
    n = n+ 1 ;
    decimal = decimal/2 ;
  }

  while (n > 0) {
    n = n - 1 ;
    printf("%d",r[n]) ;
  }
  printf("\n") ;
}
