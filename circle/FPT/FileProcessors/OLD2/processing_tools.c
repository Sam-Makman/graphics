
#include <stdio.h>
#include <stdlib.h>



int make_double_indices_legal(FILE *fin, FILE *fout)
// process a "C" program, looking for all non-comment
// occurrences of [...] and replace them with 
//   [(int)(  ...  ) + 0.5]

// test cases should include things like
// var[x+3]
// var[x][y-7]
// var[[a+b]], although this wouldn't actually be a legal item in "C"
{
  int c ;
  int q, err ;
  int prevc ;
  int inside_a_string ;
  int inside_C_comment ;
  int inside_Cpp_comment ;


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








int before_and_after (FILE *fin, FILE *fout,
                      char *before,  char *after)
{
  int i ;
  int c ;


  // copy the before string into the outputs stream
  i = 0 ;
  while (before[i] != 0) {
    c = before[i] ;
    fputc(c,fout) ;
    i++ ;
  }



  // copy the file into the output stream
  c = fgetc(fin) ;
  while (c != EOF) {

    fputc(c,fout) ;
    c = fgetc(fin) ;
  }





  // copy the after string into the outputs stream
  i = 0 ;
  while (after[i] != 0) {
    c = after[i] ;
    fputc(c,fout) ;
    i++ ;
  }

}

