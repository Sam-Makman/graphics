// Is a number prime?
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
  double n,flag,d ;

  printf("Enter a positive whole number ") ;
  scanf("%lf",&n) ;

  d = 2 ;
  while (fmod(n,d) != 0) {
    d = d + 1 ;
  }


  printf("%.0lf ",n) ;
  if (d == n) {
    printf("is prime\n") ;
  } else {
    printf("is not prime\n") ;
  }

  // an input of 1 puts the code in an infinite loop
  // otherwise the code is ok...easy to fix.

}
