// s = 1^3 - 2^3 + 3^3 - 4^3 + 5^3 - 6^3 ... n^3
// unusual solution due to Autumn Cool
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
  double n,s,i ;

  printf("Enter a positive whole number ") ;
  scanf("%lf",&n) ;

  printf("The alternating sum of cubes to %.0lf",n) ;
  
  s = 0 ;
  while (n > 0) {
    s = n*n*n - s ;
    n = n - 1 ;
  }

  printf(" is %.0lf\n",s) ;
}


