
#include <stdio.h>
#include <stdlib.h>




int main(int argc, char **argv)
{

  FILE *file1, *file2, *file3 ;

 
  if (argc != 4) {
    printf("Usage : pgm   input_C_file  tmp_file_name  output_C_file_name\n") ;
    exit(0) ;
  }


  file1 = fopen (argv[1],"r") ;
  if (file1 == NULL) {
    printf("can't open file %s to read\n",argv[1]) ;
    exit(0) ;
  }



  file2 = fopen (argv[2],"w") ;
  if (file2 == NULL) {
    printf("can't open file %s to write\n",argv[2]) ;
    exit(0) ;
  }






  /////////////////////////////////////////////////////
  before_and_after (file1,
                    file2,
                    "#include <FPT.h> \n int main() { ", 
                    "\n  }\n"
                   ) ;

  fclose(file1) ;
  fclose(file2) ;
  /////////////////////////////////////////////////////




  file2 = fopen (argv[2],"r") ;
  if (file2 == NULL) {
    printf("can't open file %s to read\n",argv[2]) ;
    exit(0) ;
  }


  file3 = fopen (argv[3],"w") ;
  if (file3 == NULL) {
    printf("can't open file %s\n",argv[3]) ;
    exit(0) ;
  }
  


  /////////////////////////////////////////////////////
  make_double_indices_legal(file2, file3) ;
  fclose(file2) ;
  fclose(file3) ;
  /////////////////////////////////////////////////////

}



