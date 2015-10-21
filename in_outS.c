#include <FPT.h>

int swidth, sheight ;

int click_and_save (double *x, double *y)
{
  int n ;
  double P[2] ;

  G_rgb(0,1,0.5) ;
  G_fill_rectangle(0,0,swidth,20) ;

  G_rgb(1,0,0) ;
  G_wait_click(P);

  n = 0 ;
  while (P[1] > 20) {
    x[n] = P[0] ;
    y[n] = P[1] ;
    G_circle(x[n],y[n],2) ;
    if (n > 0) { G_line(x[n-1],y[n-1], x[n],y[n]) ;}
    n++ ;
    G_wait_click(P) ;
  }

  return n ;
}



int in_out (double *x, double *y, int n, double P[2]){
// return 1 if point P is inside the convex polygon
// else return 0
int i;
double centerx,centery;
for(i=0;i<n;i++){
centerx+=x[i];
centery+=y[i];
}
centerx/=i;
centery/=i;
for(i=0;i<n;i++){
 double side =((y[i] - y[(i+1)%n])*(P[0] - x[i]) + (x[(i+1)%n] -x[i])*(P[1] -y[i]))*((y[i] - y[(i+1)%n])*(centerx - x[i]) + (x[(i+1)%n] - x[i])*(centery -y[i]));
if(side < 0)return 0;
}
return 1;

}



int main()
{
  double xp[1000],yp[1000] ;
  int n,q ;
  double P[2] ;


  swidth = 700 ; sheight = 700 ;
  G_init_graphics(swidth, sheight) ;
  G_rgb(0,0,0) ;
  G_clear() ;

  G_rgb(1,0,0) ;
  n = click_and_save(xp,yp) ;
  G_rgb(0,1,0) ;
  G_fill_polygon(xp,yp,n) ;
while(1==1){
  G_wait_click(P) ;
  if(P[1] < 40){
    break;
  }
  int r = in_out(xp,yp,n,P);
  if(r==1){
    G_rgb(1,0,0);
  }else{
  G_rgb(0,0,1) ;
}
  G_fill_circle(P[0],P[1],2) ;
}

  q = G_wait_key() ;
}
