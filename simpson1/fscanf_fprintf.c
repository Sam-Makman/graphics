
#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE *fin ;
   FILE *fout ;
   char name[100] ;
   int age ;
   int i ;

   fin = fopen ("sample_input", "r") ; // r for read
   if (fin == NULL) {
       printf("can't open file, sample_input") ;
       exit(1) ;
   }


   fout = fopen ("sample_output", "w") ; // w for write
   if (fout == NULL) {
       printf("can't open file, sample_output") ;
       exit(1) ;
   }


   // it should be noted that fscanf (and scanf)
   // also return the number of items successfully scanned
   // this can be useful in applications where the number of
   // items to be scanned is not marked beforehand or 
   // at the end by some kind of sentinel

   do {
       i = fscanf(fin, "%s %d", name, &age) ;   
       fprintf(fout, "num items successfully scanned = %d\n", i) ;
   } while (i > 0) ;

}
