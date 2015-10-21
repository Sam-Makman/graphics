#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main()
{
  int n ;
  double decimal,r[100] ;

  scanf("%lf",&decimal) ;
  n = 0 ;
  while (decimal > 0) {
    r[n] = fmod(decimal,2) ;
    n = n+ 1 ;
    decimal = floor(decimal/2) ;
  }

  while (n > 0) {
    n = n - 1 ;
    printf("%.0lf",r[n]) ;
  }
  printf("\n") ;
}
