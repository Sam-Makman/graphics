#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main()
{
  char first[100], second[100], nword[100] ;
  int flen,slen,i,j,k ;

  printf("Enter first word ") ;
  scanf("%s",first) ;
  flen = 0 ;  while (first[flen] != '\0'){ flen = flen + 1 ; }

  printf("Enter second word ") ;
  scanf("%s",second) ;
  slen = 0 ;  while (second[slen] != '\0'){ slen = slen + 1 ; }


  i = 0 ; j = 0 ; k = 0 ;

  while ( (i < flen) && (i+1 < flen) && (j < slen)) {

    nword[k] = first[i]    ; k = k + 1 ; i = i + 1 ;
    nword[k] = first[i]    ; k = k + 1 ; i = i + 1 ;
    nword[k] = second[j]   ; k = k + 1 ; j = j + 1 ;

  }

  nword[k] = '\0' ;

  printf("The new word is %s\n",nword) ;

}


