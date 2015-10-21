// s = 1^3 - 2^3 + 3^3 - 4^3 + 5^3 - 6^3 ... n^3
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
  double n,s,i ;

  printf("Enter a positive whole number ") ;
  scanf("%lf",&n) ;
  
  s = 0 ;
  i = 1 ; 
  while (i <= n) {
    if (fmod(i,2) == 0) {
        s = s - i*i*i ;
    } else {
        s = s + i*i*i ;
    }

    i = i + 1 ;
  }

  printf("The alternating sum of cubes to %.0lf is %.0lf\n",n,s) ;
}


