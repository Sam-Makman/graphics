
#include <FPT.h>
double cx[100], cy[100], center[2];
int cSize;

double sameSide(double ax, double ay, double bx, double by, double x1, double y1, double x2, double y2){
  return ((y1 - y2)*(ax - x1) + (x2 -x1)*(ay -y1))*((y1 - y2)*(bx - x1) + (x2 - x1)*(by - y1));
}

// void ssTest(){
//  double a = sameSide(1,1,1,1,2,2,10,10);
//  double b = sameSide(1,0,0,1,1,1,2,2);
//  double c = sameSide(10000,0,5.6,0,1,1,2,2);
//  double x = 60000000000000;
//  double d = sameSide(x,5000000000000,5000000000,6000000000000,1,1,2,2);
//  printf("Should be 0 a: %lf \n",a);
//     printf("should be negative b : %lf \n",b);
//    printf("should be positive c %lf \n",c);
//     printf("Negative d %lf \n", d);
// }


void intersect(double ret[2], double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4 ){
  if(sameSide(x1,y1,x2,y2,x3,y3,x4,y4) > 1){
      printf("Both points on the same side at begining\n");
      return;
    }
  double tx = x2;
  double ty = y2;
  double ox = x1;
  double oy = y1;
  printf("enter intersect\n");
  while(1==1){
    // printf("finding\n");
    double side = sameSide(x1,y1,tx,ty,x3,y3,x4,y4);
    if(sameSide(tx,ty,ox,oy,x3,y3,x4,y4) > 1){
      printf("both points on same side\n");
      break;
    }
    if(fabs((tx-ox)/2) < .000000001 && fabs((ty-oy)/2) <.0000000001 ) {
      ret[0]=tx;
      ret[1]=ty;
      // printf("tx : %lf , ty: %lf \n", tx, ty);
      return;
    }
    else if(side > 0){
      double tempx, tempy;
      
      tempx = tx - ((tx-ox)/2);
      tempy = ty - ((ty-oy)/2);
      if(sameSide(tx,ty,tempx,tempy,x3,y3,x4,y4) > 0){
        tx = tempx;
        ty = tempy;
      }else{
        ox = tempx;
        oy = tempy;
      }

    }else if(side < 0){
      double tempx, tempy;
      tempx = ox - ((ox-tx)/2);
      tempy = oy - ((oy-ty)/2);
      if(sameSide(ox,oy,tempx,tempy,x3,y3,x4,y4) > 0){
        ox = tempx;
        oy = tempy;
      }else{
        tx = tempx;
        ty = tempy;
      }
    
      // printf(" %lf  %lf \n", ((tx-ox)/2),((ty-oy)/2));
    }
    else if(side == 0 ){
      ret[0]=tx;
      ret[1]=ty;
      // printf("tx : %lf , ty: %lf \n", tx, ty);
      return;
    }
  }
}
void intersectTest(){
  double ret[2], x1,x2,x3,x4,y1,y2,y3,y4;
  x1 = 600;
  y1 = 600;
  x2 = 0;
  y2 = 0;
  x3 = 300;
  y3 = 500;
  x4 = 150;
  y4 = 200;
  intersect(ret, x1,y1,x2,y2,x3,y3,x4,y4);
  printf("Test x: %lf  , y: %lf  \n", ret[0], ret[1]);
}

int clip(double xp[], double yp[], int size){
  int i, j;
  int count = 0;
  double tempx[1000], tempy[1000];
  printf("init\n");
  for(i=0; i<size;i++){
    tempx[i]=xp[i];
    tempy[i]=yp[i];
    printf(" x: %lf y: %lf \n", tempx[i],tempy[i]);
    count++;
  }

  printf("\n\n");
  for(i=0;i<cSize;i++){
    double clipx[1000],clipy[1000];
    int tcount = 0;
    int f;
    // printf("Coords \n");
    for(f=0; f<count; f++){
      printf("x : %lf , y: %lf \n", tempx[f], tempy[f]);
    }
    for(j=0;j<count;j++){

    double spointSide = sameSide(center[0], center[1], tempx[j], tempy[j], cx[i], cy[i], cx[(i+1)%cSize] ,cy[(i+1)%cSize]);
    double epointSide = sameSide(center[0], center[1], tempx[(j+1)%count], tempy[(j+1)%count], cx[i], cy[i],cx[(i+1)%cSize] ,cy[(i+1)%cSize]);
    // printf("Startpoint : %lf, endpoint : %lf \n", spointSide, epointSide);
    if(spointSide > 0 && epointSide > 0){//both inside 
      printf("start in end in\n");
      clipx[tcount] = tempx[(j+1)%count];
      clipy[tcount] = tempy[(j+1)%count];
      tcount++; 
    }
    else if(spointSide < 0 && epointSide < 0){//both outside 
      printf("start out end out\n");
    }
    else if(spointSide > 0 && epointSide < 0){//start in end out 
      printf("start in end out \n");
      double point[2];
      intersect(point,tempx[j],tempy[j],tempx[(j+1)%count],tempy[(j+1)%count],cx[i],cy[i],cx[(i+1)%count],cy[(i+1)%count] );
      clipx[tcount] = point[0];
      clipy[tcount] = point[1];
      tcount++; 
    }else if(spointSide < 0 && epointSide > 0){//start out end in 
      printf("start out end in \n");//broken
      double point[2];
      intersect(point,tempx[(j+1)%count],tempy[(j+1)%count],tempx[j],tempy[j],cx[i],cy[i],cx[(i+1)%count],cy[(i+1)%count] );

      clipx[tcount] = point[0];
      clipy[tcount] = point[1];
      tcount++; 

      clipx[tcount] = tempx[(j+1)%count]; 
      clipy[tcount] = tempy[(j+1)%count];
      tcount++; 
    }else if(spointSide == 0 && epointSide == 0){//both on the line
      printf("zero zero\n");
      // clipx[tcount] = tempx[j];  
      // clipy[tcount] = tempy[j];
      // tcount++;
      clipx[tcount] = tempx[(j+1)%count]; 
      clipy[tcount] = tempy[(j+1)%count];
      tcount++;
    }
    else if(epointSide == 0 && spointSide > 0){//end on line start inside 
      printf("end is 0\n");
      clipx[tcount] = tempx[(j+1)%count]; 
      clipy[tcount] = tempy[(j+1)%count];
      tcount++; 
    }

    else if(epointSide == 0 && spointSide < 0){//end on line start outside 
      // printf("end is 0\n");
      // clipx[tcount] = tempx[(j+1)%count];  
      // clipy[tcount] = tempy[(j+1)%count];
      // tcount++; 
    }

    else if(spointSide == 0 && epointSide > 0){
      clipx[tcount] = tempx[j];
      clipy[tcount] = tempy[j];
      tcount++;

      clipx[tcount] = tempx[(j+1)%count]; 
      clipy[tcount] = tempy[(j+1)%count];
      tcount++; 
    }
    else if(spointSide == 0 && epointSide < 0){
      clipx[tcount] = tempx[j]; 
      clipy[tcount] = tempy[j];
      tcount++; 
    }
    else{
      printf("SHITS FUCKED \n");
    }
    }
    int k;
    count = tcount;
    for(k=0;k<count;k++){
      tempx[k] = clipx[k];
      tempy[k] = clipy[k];

    } 
  }
  printf("final result \n");
  for(i=0; i<count;i++){
    xp[i]=tempx[i];
    yp[i]=tempy[i];
    printf("x: %lf y: %lf \n", xp[i], yp[i]);
  }
  return count;

}

int main()
// this tests clipping of polygon to convex window
{
  int pn, wn ;
  double pt[2],u,v,q ;

  double px[100] = {  70,460,400} ;
  double py[100] = { 350, 25,550} ;
  pn = 3 ;

  cx[0] = 100;
  cx[1] = 600;
  cx[2] = 550;
  cx[3] = 150;
  cy[0] = 150 ;
  cy[1] = 200; 
  cy[2] = 450;
  cy[3] = 500;
  cSize = 4 ;

  srand48(100) ;

  G_init_graphics (700, 700) ;
  G_rgb (0,0,0) ;
  G_clear() ;

  G_rgb (1,0,0) ;
  G_polygon(cx,cy,cSize) ;

  G_rgb (0,0,1) ;
  G_polygon(px,py,pn) ;


  q = G_wait_key() ;


  pn =  clip(px, py, pn);//, wx, wy, wn) ;  

  G_rgb (1,1,0) ;
  G_fill_polygon(px,py,pn) ;
  q = G_wait_key() ;
}




