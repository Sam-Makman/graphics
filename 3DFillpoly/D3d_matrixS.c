
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
  double t[4][4]; 
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
  rotate[1][1] = cos(radians);
  rotate[1][2] = -sin(radians);
  rotate[2][1] = sin(radians);
  rotate[2][2] = cos(radians);
  D3d_mat_mult(a, rotate, a);
  r2[1][1] = cos(-radians);
  r2[1][2] = -sin(-radians);
  r2[2][1] = sin(-radians);
  r2[2][2] = cos(-radians);
    D3d_mat_mult(b,b,r2 );
  return 1;
}//finished
// a = rotate*a  
// b = b*rotate_inverse 


int D3d_rotate_y (double a[4][4], double b[4][4], double radians){
  double rotate[4][4], r2[4][4] ;
  D3d_make_identity(rotate);
  D3d_make_identity(r2);
  rotate[0][0] = cos(radians);
  rotate[0][2] = sin(radians);
  rotate[2][0] = -sin(radians);
  rotate[3][3] = cos(radians);
  D3d_mat_mult(a, rotate, a);
  r2[0][0] = cos(-radians);
  r2[0][2] = -sin(-radians);
  r2[2][0] = sin(-radians);
  r2[3][3] = cos(-radians);
  D3d_mat_mult(b,b,r2 );
  return 1;
}//finished

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
}//finished



int D3d_cs_rotate_x (double a[4][4], double b[4][4], double cs, double sn){
  return 0;
}
// a = rotate*a  
// b = b*rotate_inverse  


int D3d_cs_rotate_y (double a[4][4], double b[4][4], double cs, double sn){
  return 0;
}
// a = rotate*a  
// b = b*rotate_inverse  


int D3d_cs_rotate_z (double a[4][4], double b[4][4], double cs, double sn){
    double rotate[4][4], r2[4][4] ;
  D3d_make_identity(rotate);
  D3d_make_identity(r2);
  rotate[0][0] = cs;
  rotate[0][1] = -sn;
  rotate[1][0] = sn;
  rotate[1][1] = cs;
  D3d_mat_mult(a, rotate, a);
  r2[0][0] = -cs;
  r2[0][1] = sn;
  r2[1][0] = -sn;
  r2[1][1] = -cs;
    D3d_mat_mult(b,b,r2 );
  return 1;
}
// a = rotate*a  
// b = b*rotate_inverse  

int D3d_negate_x (double a[4][4], double b[4][4]){
 double neg[4][4] ;
  D3d_make_identity(neg);
  neg[0][0]=-1;
  D3d_mat_mult(a,neg,a);
  D3d_mat_mult(b,b, neg);
  return 1;
}//finished
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
}//finished
// negate the y....reflects in the x-axis
// a = reflect*a 
// b = b*reflect_inverse  


int D3d_negate_z (double a[4][4], double b[4][4]){
   double neg[4][4] ;
  D3d_make_identity(neg);
  neg[2][2]=-1;
  D3d_mat_mult(a,neg,a);
  D3d_mat_mult(b,b, neg);
return 1;
}//finished


int D3d_mat_mult_points (double *X, double *Y,double  *Z, double m[4][4], double *x, double *y,double *z, int numpoints){
double xres[numpoints], yres[numpoints], zres[numpoints];
int i;
// printf("Mat mult points\n");
for(i=0; i<numpoints; i++){
  xres[i] = m[0][0] * x[i] + m[0][1] * y[i] + m[0][2] * z[i] + m[0][3] ;
  yres[i] = m[1][0] * x[i] + m[1][1] * y[i] + m[1][2] * z[i] + m[1][3];
  zres[i] = m[2][0] * x[i] + m[2][1] * y[i] + m[2][2] * z[i] + m[2][3];
  // printf("X = %lf, Y = %lf \n", xres[i], yres[i]);

}
for(i=0; i<numpoints; i++){
  X[i] = xres[i];
  Y[i] = yres[i];
  Z[i] = zres[i];
}
return 1;
}
// |X0 X1 X2 ...|       |x0 x1 x2 ...|
// |Y0 Y1 Y2 ...| = m * |y0 y1 y2 ...|
// | 1  1  1 ...|       | 1  1  1 ...|



int D3d_mat_mult_pt (double P[3],
                     double m[4][4],
                     double Q[3]) {
  return 0;
}
// multiplies a SINGLE point by a matrix
// | P[0] |       | Q[0] |
// | P[1] | = m * | Q[1] |
// | P[2] |       | Q[2] |
// |  1   |       |  1   |

// SAFE, user may make a call like 
// D3d_mat_mult_pt (q,  m,q) ;



int D3d_x_product (double res[3], double a[3], double b[3]){
  return 0;
}
// res = a x b  , cross product of two vectors
// SAFE: it is ok to make a call such as
// D3d_x_product (a,  a,b) or
// D3d_x_product (b,  a,b) or
// D3d_x_product (a,  a,a) 




int D3d_make_movement_sequence_matrix (
                              double mat[4][4],
                              double inv[4][4],
                              int num_movements,
                              int *movement_type_list,
                              double *parameter_list ){
  return 0;
}

     // create a matrix (mat) and its inverse (inv)
     // that specify a sequence of movements....

     // movement_type_list[k] is an integer that
     // specifies the type of matrix to be used in the
     // the k-th movement.  the parameter that each
     // matrix needs is supplied in parameter_list[k].

     // return 1 if successful, 0 if error


     // the codes for movement_type_list are :
     // 0 - scale x
     // 1 - scale y
     // 2 - scale z

     // 3 - rotate x
     // 4 - rotate y
     // 5 - rotate z
   
     // 6 - translate x
     // 7 - translate y
     // 8 - translate z

     // 9  - negate x...reflect in the yz plane
     // 10 - negate y...relfect in the xz plane
     // 11 - negate z...reflect in the zy plane





int D3d_view (double view[4][4],  double view_inverse[4][4],
              double eye_x, double eye_y, double eye_z ,
              double coi_x, double coi_y, double coi_z ,
              double up_x,  double up_y,  double up_z ){
  return 0;
}
// Construct the view matrix and its inverse given the location
// of the eye, the center of interest, and an up point.
// return 1 if successful, 0 otherwise.

// int main(){

// }