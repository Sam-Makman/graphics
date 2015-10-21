#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main()
{
  char first[100], second[100], nword[100] ;
  int i,j,k ;

  printf("Enter first word ") ;
  scanf("%s",first) ;

  printf("Enter second word ") ;
  scanf("%s",second) ;

  i = 0 ; j = 0 ; k = 0 ;

  while ( (first[i] != '\0') && (first[i+1] != '\0') &&
           (second[j] != '\0')) {

    nword[k] = first[i]    ; k = k + 1 ; i = i + 1 ;
    nword[k] = first[i]    ; k = k + 1 ; i = i + 1 ;
    nword[k] = second[j]   ; k = k + 1 ; j = j + 1 ;

  }

  nword[k] = '\0' ;

  printf("The new word is %s\n",nword) ;

}


