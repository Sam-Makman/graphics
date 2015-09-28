#include <FPT.h>
#define WINDOW  600



    void mypolygon(double x[], double y[], int length ){
    int i;
G_rgb(1,1,1);
    for(i = 0; i< length; i++){
      if(i+1 < length){
      G_line(x[i], y[i], x[i+1], y[i+1]);
      }
      else{
	G_line(x[i], y[i], x[0], y[0]);
      }
      
}

  }

  int clickandsave(double x[], double y[]){
    double coords[2];
    int length;
    int i;
    for(i = 0; i< 100; i++){
    G_wait_click(coords);
    if(coords[0] < 44 && coords[1] > 580){
      break;
    }
    else{
      x[i] = coords[0];
      y[i] = coords[1];
G_fill_rectangle(coords[0] -1, coords[1] -1 , 3, 3 );
      length = i;
    }
    }
    return i;
  }


void sort(double *d, int m){
	int i,j, small;
	double temp;
	
	for(j=0; j< m;j++){
		small = j;
		for(i=j;i<m;i++){
			if(d[small] > d[i]){
				small = i;
			}
		}

		temp = d[j];
		d[j] = d[small];
		d[small] = temp;
	}
}

my_fill_polygon(double x[], double y[], int length){
int i,j,k;
//
printf("length %d \n", length);
if(length ==2){
G_line(x[1], y[1], x[0], y[0]);
}else{
   for(i=0;i<WINDOW; i++){
	double points[length];
	int pcount=0;
	for(j=0; j<length; j++){
		if((y[j] > i && y[(j+1)%length] > i) || (y[j] <= i && y[(j+1)%length] <= i)){}
		else{
			double rise, run, b, slope, xcord;
			rise = y[j] - y[(j+1)%length];
			run = x[j] - x[(j+1)%length];
			slope = rise/run;
			xcord = (i - y[j])/slope + x[j];
			//printf("xcord: %lf , slope %lf , y[j] : %lf , x[j]: %lf , y: %d \n ", xcord, slope, y[j], x[j], i);

			points[pcount] = xcord;
			pcount++;		
}
}
int k;
sort(points, pcount);

for(k=0; k < pcount; k+=2){
	//printf("line x1 %lf, x2 %lf pcount: %d , y: %d \n", points[k], points[k+1], pcount, i);
	G_line(points[k], i, points[k+1], i);
	
}
}
}
}
int main(){
  double ax[100], ay[100], bx[100], by[100];
  int anum, bnum;
  G_init_graphics(WINDOW,WINDOW);
  G_rgb(0,0,0);
  G_clear();
  G_clear(1,1,1);
  G_rgb(1,1,1);
  G_draw_string("Save", 0,585);
  G_rgb(0,1,0);
  anum = clickandsave(ax,ay);
  my_fill_polygon(ax, ay, anum);
  G_rgb(1,0,0);
  bnum = clickandsave(bx, by);
//printf("anum: %d bnum %d \n", anum, bnum);
  my_fill_polygon(bx,by,bnum);
 
G_wait_key();
   }
