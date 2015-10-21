// Is a number prime?
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
  double n,flag,d ;

  printf("Enter a positive whole number ") ;
  scanf("%lf",&n) ;

  flag = 1 ; // start out believing it is prime
  d = 2 ;
  while (d*d <= n) {
    if (fmod(n,d) == 0) { flag = 0 ; break ; }
    d = d + 1 ;
  }


  printf("%.0lf ",n) ;
  if (flag == 1) {
    printf("is prime\n") ;
  } else {
    printf("is not prime\n") ;
  }

  // this code treats 1 as prime but the mathematicians
  // don't include 1-easily fixed
}
