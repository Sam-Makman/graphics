
#include <D3d_matrix.h>
#include <math.h>


/*

 ( x')          (x)
 ( y')  =   M * (y)  
 ( 1 )          (1)

instead of (x',y',1) = (x,y,1) * M  

*/



int D3d_print_mat (double a[4][4])
{
  int r,c ;
  for (r = 0 ; r < 4 ; r++ ) {
      for (c = 0 ; c < 4 ; c++ ) {
           printf(" %12.4lf ",a[r][c]) ;
      }
      printf("\n") ;
  }

  return 1 ;
} //Finished 




int D3d_copy_mat (double a[4][4], double b[4][4])
// a = b
{
  int r,c ;
  for (r = 0 ; r < 4 ; r++ ) {
      for (c = 0 ; c < 4 ; c++ ) {
           a[r][c] = b[r][c] ;
      }
  }

  return 1 ;
} //Finished 

int D3d_mat_mult (double res[4][4], double a[4][4], double b[4][4]){
  int i, j, k;
  double tres[4][4];
  for(i=0; i<4;i++){
    for(k=0; k<4;k++){
      tres[i][k] = 0;
      for(j=0;j<4;j++){
      tres[i][k] += a[i][j] * b[j][k];
      }
    //  printf("%lf ",tres[i][k]);
    }
  //  printf("\n");
  }
  for(i=0; i<4;i++){
    for(k=0; k<4;k++){
  res[i][k] = tres[i][k];
}
}
}//Finished 






int D3d_make_identity (double a[4][4])
// a = I
{
  int r,c ;
  for (r = 0 ; r < 4 ; r++ ) {
      for (c = 0 ; c < 4 ; c++ ) {
           if (r == c) a[r][c] = 1.0 ;
               else    a[r][c] = 0.0 ;
      }
  }

  return 1 ;
} //Finished 






/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////


int D3d_translate (double a[4][4], double b[4][4], double dx, double dy, double dz)
// a = translation*a  
// b = b*translation_inverse  
{
  double t[4][4] ;

  D3d_make_identity(t) ;

  t[0][3] =  dx ;  t[1][3] = dy ;  t[2][3] = dz;
  D3d_mat_mult(a,  t,a) ;

  t[0][3] = -dx ;  t[1][3] = -dy ;t[2][3] = -dz;
  D3d_mat_mult(b,  b,t) ;

  return 1 ;
}//Finished

int D3d_scale (double a[4][4], double b[4][4], double sx, double sy, double sz){
  double scale[4][4] ;
  D3d_make_identity(scale);
  scale[0][0] = sx;
  scale[1][1] = sy;
  scale[2][2] = sz;
  D3d_mat_mult(a, scale, a);
  scale[0][0] = 1/sx;
  scale[1][1] = 1/sy;
  scale[2][2] = 1/sz;
  D3d_mat_mult(b, b, scale);
return 1;
}//Done
// a = scale*a  
// b = b*scale_inverse 

int D3d_rotate_x (double a[4][4], double b[4][4], double radians){
  double rotate[4][4], r2[4][4] ;
  D3d_make_identity(rotate);
  D3d_make_identity(r2);
  rotate[0][0] = cos(radians);
  rotate[0][1] = -sin(radians);
  rotate[1][0] = sin(radians);
  rotate[1][1] = cos(radians);
  D3d_mat_mult(a, rotate, a);
  r2[0][0] = cos(-radians);
  r2[0][1] = -sin(-radians);
  r2[1][0] = sin(-radians);
  r2[1][1] = cos(-radians);
    D3d_mat_mult(b,b,r2 );
  return 1;
}
// a = rotate*a  
// b = b*rotate_inverse  
int D3d_rotate_y (double a[4][4], double b[4][4], double radians){
  double rotate[4][4], r2[4][4] ;
  D3d_make_identity(rotate);
  D3d_make_identity(r2);
  rotate[0][0] = cos(radians);
  rotate[0][1] = -sin(radians);
  rotate[1][0] = sin(radians);
  rotate[1][1] = cos(radians);
  D3d_mat_mult(a, rotate, a);
  r2[0][0] = cos(-radians);
  r2[0][1] = -sin(-radians);
  r2[1][0] = sin(-radians);
  r2[1][1] = cos(-radians);
    D3d_mat_mult(b,b,r2 );
  return 1;
}

int D3d_rotate_z (double a[4][4], double b[4][4], double radians){
  double rotate[4][4], r2[4][4] ;
  D3d_make_identity(rotate);
  D3d_make_identity(r2);
  rotate[0][0] = cos(radians);
  rotate[0][1] = -sin(radians);
  rotate[1][0] = sin(radians);
  rotate[1][1] = cos(radians);
  D3d_mat_mult(a, rotate, a);
  r2[0][0] = cos(-radians);
  r2[0][1] = -sin(-radians);
  r2[1][0] = sin(-radians);
  r2[1][1] = cos(-radians);
    D3d_mat_mult(b,b,r2 );
  return 1;
}

int D3d_negate_x (double a[4][4], double b[4][4]){
 double neg[4][4] ;
  D3d_make_identity(neg);
  neg[0][0]=-1;
  D3d_mat_mult(a,neg,a);
  D3d_mat_mult(b,b, neg);
  return 1;
}
// negate the x....reflects in the y-axis
// a = reflect*a 
// b = b*reflect_inverse  

int D3d_negate_y (double a[4][4], double b[4][4]){
   double neg[4][4] ;
  D3d_make_identity(neg);
  neg[1][1]=-1;
  D3d_mat_mult(a,neg,a);
  D3d_mat_mult(b,b, neg);
return 1;
}
// negate the y....reflects in the x-axis
// a = reflect*a 
// b = b*reflect_inverse  


int D3d_negate_y (double a[4][4], double b[4][4]){
   double neg[4][4] ;
  D3d_make_identity(neg);
  neg[2][2]=-1;
  D3d_mat_mult(a,neg,a);
  D3d_mat_mult(b,b, neg);
return 1;
}


int D3d_mat_mult_points (double *X, double *Y, double m[4][4], double *x, double *y, int numpoints){
double xres[numpoints], yres[numpoints];
int i;
// printf("Mat mult points\n");
for(i=0; i<numpoints; i++){
  xres[i] = m[0][0] * x[i] + m[0][1] * y[i] + m[0][2];
  yres[i] = m[1][0] * x[i] + m[1][1] * y[i] + m[1][2];
  // printf("X = %lf, Y = %lf \n", xres[i], yres[i]);

}
for(i=0; i<numpoints; i++){
  X[i] = xres[i];
  Y[i] = yres[i];
}
return 1;
}
// |X0 X1 X2 ...|       |x0 x1 x2 ...|
// |Y0 Y1 Y2 ...| = m * |y0 y1 y2 ...|
// | 1  1  1 ...|       | 1  1  1 ...|

int main(){

}