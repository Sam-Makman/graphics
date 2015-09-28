#include <FPT.h>

int main(){
int numpoints, numpolys, poly_sizes[1000], polygons[1000][20];
double x[1000], y[1000];
double colors[1000][3];
scanf("%d", &numpoints);
int i;
G_init_graphics(1000,1000);
  G_rgb(0,0,0);
  G_clear();
  G_clear(1,1,1);


for(i = 0; i< numpoints; i++){
  scanf("%lf %lf ", &x[i], &y[i]);
}
scanf("%d", &numpolys);
for(i= 0; i< numpolys; i++){
	int size;
 	scanf("%d", &size);
	int j;
	poly_sizes[i]=size;
	for(j=0; j<size; j++){
		scanf("%d", &polygons[i][j]);
	}	
 }

    for(i=0; i<numpolys; i++){
      scanf("%lf %lf %lf", &colors[i][0], &colors[i][1],  &colors[i][2]);
    }

for(i=0;i<numpolys;i++){
	int j;
	double xtemp[poly_sizes[i]], ytemp[poly_sizes[i]];

	for(j=0; j<poly_sizes[i];j++){

//printf("x: %lf  y: %lf \n", x[polygons[i][j]], y[polygons[i][j]]);
//G_wait_key();
		xtemp[j] = x[polygons[i][j]];
		ytemp[j] = y[polygons[i][j]];
	//printf("polygons: %d , polysize %d \n", polygons[i][j],poly_sizes[i] );
	}

	G_rgb(colors[i][0],colors[i][1],colors[i][2]);

//for(j=0; j<poly_sizes[i];j++){
//	printf("x %lf y %lf \n", xtemp[j], ytemp[j]);
//}
	//printf("r %lf g %lf b %lf",colors[i][0],colors[i][1],colors[i][2]);
	G_fill_polygon(xtemp, ytemp ,poly_sizes[i] );
	//G_fill_rectangle(xtemp[0], ytemp[0], 100,100);
	//printf("Draw \n");
 	}
G_wait_key();
}
