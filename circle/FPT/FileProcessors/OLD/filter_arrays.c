
// process a "C" program, looking for all non-comment
// occurrences of [...] and replace them with 
//   [(int)(  ...  ) + 0.5]

// test cases should include things like
// var[x+3]
// var[x][y-7]
// var[[a+b]], although this wouldn't actually be a legal item in "C"



#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  FILE *fin, *fout ;
  int c ;
  int q, err ;
  int prevc ;
  int inside_a_string ;
  int inside_C_comment ;
  int inside_Cpp_comment ;
 
  if (argc != 3) {
    printf("Usage : pgm   input_C_file   output_C_file_name\n") ;
    exit(0) ;
  }


  fin = fopen (argv[1],"r") ;
  if (fin == NULL) {
    printf("can't open file %s\n",argv[1]) ;
    exit(0) ;
  }


  fout = fopen (argv[2],"w") ;
  if (fout == NULL) {
    printf("can't open file %s\n",argv[2]) ;
    exit(0) ;
  }


  inside_C_comment = 0 ;
  inside_Cpp_comment = 0 ;
  inside_a_string = 0 ; // no, we are not yet inside a string

  prevc = 0 ;
  c = fgetc(fin) ;

  while (c != EOF) {


    if (inside_C_comment == 1) {

         if ( (prevc == '*') && (c == '/') ) { inside_C_comment = 0 ; }
         fputc(c,fout) ;

    } else if (inside_Cpp_comment == 1) {

         if ( (prevc != '\\') && (c == '\n') ) { inside_Cpp_comment = 0 ; }
         fputc(c,fout) ;

    } else if (inside_a_string == 1) {

         if (c == '"') { inside_a_string = 0 ; }
         fputc(c,fout) ;

    } else if ((prevc == '/') && (c == '*')) {

         inside_C_comment = 1 ;
         fputc(c,fout) ;
         c = 0 ; // this eliminates the possibility that
        	 // the next pair might be */
	         // it turns out that /*/ is NOT a legit comment

    } else if ((prevc == '/') && (c == '/')) {

         inside_Cpp_comment = 1 ;
         fputc(c,fout) ;


    } else if (c == '"') {

         inside_a_string = 1 ;
         fputc(c,fout) ;


    } else if (c == '[') {

       fputc('[',fout) ;
       fputc('(',fout) ;
       fputc('i',fout) ;
       fputc('n',fout) ;
       fputc('t',fout) ;
       fputc(')',fout) ;
       fputc('(',fout) ;
       fputc('(',fout) ;

    } else if (c == ']') {

       fputc(')',fout) ;
       fputc('+',fout) ;
       fputc('0',fout) ;
       fputc('.',fout) ;
       fputc('5',fout) ;
       fputc(')',fout) ;
       fputc(']',fout) ;

    } else {

       fputc(c,fout) ;

    }





    prevc = c ;    
    c = fgetc(fin) ;
  }




}
