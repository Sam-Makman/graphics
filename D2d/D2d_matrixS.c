
#include <D2d_matrix.h>
#include <math.h>


/*

 ( x')          (x)
 ( y')  =   M * (y)  
 ( 1 )          (1)

instead of (x',y',1) = (x,y,1) * M  

*/



int D2d_print_mat (double a[3][3])
{
  int r,c ;
  for (r = 0 ; r < 3 ; r++ ) {
      for (c = 0 ; c < 3 ; c++ ) {
           printf(" %12.4lf ",a[r][c]) ;
      }
      printf("\n") ;
  }

  return 1 ;
} 




int D2d_copy_mat (double a[3][3], double b[3][3])
// a = b
{
  int r,c ;
  for (r = 0 ; r < 3 ; r++ ) {
      for (c = 0 ; c < 3 ; c++ ) {
           a[r][c] = b[r][c] ;
      }
  }

  return 1 ;
} 

int D2d_mat_mult (double res[3][3], double a[3][3], double b[3][3]){
  int i, j, k;
  double tres[3][3];
  for(i=0; i<3;i++){
    for(k=0; k<3;k++){
      tres[i][k] = 0;
      for(j=0;j<3;j++){
      tres[i][k] += a[i][j] * b[j][k];
      }
    //  printf("%lf ",tres[i][k]);
    }
  //  printf("\n");
  }
  for(i=0; i<3;i++){
    for(k=0; k<3;k++){
  res[i][k] = tres[i][k];
}
}
}






int D2d_make_identity (double a[3][3])
// a = I
{
  int r,c ;
  for (r = 0 ; r < 3 ; r++ ) {
      for (c = 0 ; c < 3 ; c++ ) {
           if (r == c) a[r][c] = 1.0 ;
               else    a[r][c] = 0.0 ;
      }
  }

  return 1 ;
} 






/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////


int D2d_translate (double a[3][3], double b[3][3], double dx, double dy)
// a = translation*a  
// b = b*translation_inverse  
{
  double t[3][3] ;

  D2d_make_identity(t) ;

  t[0][2] =  dx ;  t[1][2] = dy ;  
  D2d_mat_mult(a,  t,a) ;

  t[0][2] = -dx ;  t[1][2] = -dy ;
  D2d_mat_mult(b,  b,t) ;

  return 1 ;
}

int D2d_scale (double a[3][3], double b[3][3], double sx, double sy){
  double scale[3][3] ;
  D2d_make_identity(scale);
  scale[0][0] = sx;
  scale[1][1] = sy;
  D2d_mat_mult(a, scale, a);
  scale[0][0] = 1/sx;
  scale[1][1] = 1/sy;
  D2d_mat_mult(b, b, scale);
return 1;
}
// a = scale*a  
// b = b*scale_inverse 

int D2d_rotate (double a[3][3], double b[3][3], double radians){
  double rotate[3][3], r2[3][3] ;
  D2d_make_identity(rotate);
  D2d_make_identity(r2);
  rotate[0][0] = cos(radians);
  rotate[0][1] = -sin(radians);
  rotate[1][0] = sin(radians);
  rotate[1][1] = cos(radians);
  D2d_mat_mult(a, rotate, a);
  r2[0][0] = cos(-radians);
  r2[0][1] = -sin(-radians);
  r2[1][0] = sin(-radians);
  r2[1][1] = cos(-radians);
    D2d_mat_mult(b,b,r2 );
  return 1;
}
// a = rotate*a  
// b = b*rotate_inverse  

int D2d_negate_x (double a[3][3], double b[3][3]){
 double neg[3][3] ;
  D2d_make_identity(neg);
  neg[0][0]=-1;
  D2d_mat_mult(a,neg,a);
  D2d_mat_mult(b,b, neg);
  return 1;
}
// negate the x....reflects in the y-axis
// a = reflect*a 
// b = b*reflect_inverse  

int D2d_negate_y (double a[3][3], double b[3][3]){
   double neg[3][3] ;
  D2d_make_identity(neg);
  neg[1][1]=-1;
  D2d_mat_mult(a,neg,a);
  D2d_mat_mult(b,b, neg);
return 1;
}
// negate the y....reflects in the x-axis
// a = reflect*a 
// b = b*reflect_inverse  

int D2d_mat_mult_points (double *X, double *Y, double m[3][3], double *x, double *y, int numpoints){
double xres[numpoints], yres[numpoints];
int i;
for(i=0; i<numpoints; i++){
  X[i] = m[0][0] * x[i] + m[0][1] * y[i] + m[0][2];
  Y[i] = m[1][0] * x[i] + m[1][1] * y[i] + m[1][2];
}
return 1;
}
// |X0 X1 X2 ...|       |x0 x1 x2 ...|
// |Y0 Y1 Y2 ...| = m * |y0 y1 y2 ...|
// | 1  1  1 ...|       | 1  1  1 ...|