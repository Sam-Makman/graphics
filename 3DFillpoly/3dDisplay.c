#include <FPT.h>
#include <D3d_matrix.h>

#define WINDOW_WIDTH 600
#define ROTATE_SPEED .05 

typedef
struct {
  int objnum;
  int polynum;
  double dist;
}
POLYGON;

double x[20][15000], y[20][10000], z[20][10000], colors[20][10000][3];
int numpoints[20], numpolys[20], poly_sizes[20][10000], polygons[20][10000][100];
POLYGON polyLoc[200000];
int plsize;




int compare (const void *p, const void *q)
{
  POLYGON *a, *b ;

  a = (POLYGON*)p ;
  b = (POLYGON*)q ;

  if  (((*a).dist) < ((*b).dist)) return -1 ;
  else if (((*a).dist) > ((*b).dist)) return 1 ;
  else return 0 ;
}

void setUp(){
  G_init_graphics(WINDOW_WIDTH,WINDOW_WIDTH + 30);
  G_rgb(0,0,0);
  G_clear();
  G_clear(1,1,1);
}

double dot_product( double a[3], double b[3]){
 return((a[0]*b[0]) + (a[1]*b[1]) + (a[2]*b[2]) );
}


void loadFiles(int argc, char ** argv){
int i,j,k, m;
FILE * f;
m=0;
for(i=1; i<argc; i++){
	f = fopen(argv[i], "r");
		if(f == NULL){
			printf("Cannot open file %s \n", argv[i]);
		}
	fscanf(f , "%d", &numpoints[i -1]);
	for(j=0; j< numpoints[i-1]; j++){
		fscanf(f, "%lf %lf %lf", &x[i - 1][j], &y[i - 1][j], &z[i-1][j]);
		// printf( "points %lf %lf  \n", x[i - 1][j], y[i - 1][j]);
	}
	fscanf( f, "%d", &numpolys[i -1]);
		for(k = 0; k < numpolys[i -1]; k++){
			fscanf( f, "%d", &poly_sizes[i -1][k]);
			for(j=0; j< poly_sizes[i -1][k];j++){
				fscanf(f, "%d", &polygons[i -1][k][j]);
				polyLoc[m].objnum=i-1;
				polyLoc[m].polynum=k;
				polyLoc[m].dist=z[i-1][polygons[i -1][k][j]];
				m++;
			}
		}
		for(k=0; k<numpolys[i -1]; k++){
      		fscanf(f,"%lf %lf %lf", &colors[i -1][k][0], &colors[i -1][k][1],  &colors[i -1][k][2]);
    	}
	}
	qsort(polyLoc, m,sizeof(POLYGON),compare);
	plsize = m;
	fclose(f);
}


void scaleNfit(int argc){
int i,j;
double scale[4][4] ,iscale[4][4];
for(i=0; i<argc-1;i++){
	double xmax, xmin, ymax, ymin, xrad, yrad, xcenter, ycenter, zmax,zmin,zrad,zcenter;
			xmin = x[i][0];
			xmax = x[i][0];
			ymin = y[i][0];
			ymax = y[i][0];
			zmin = z[i][0];
			zmax = z[i][0];
	for(j = 0; j<numpoints[i];j++){
		if(x[i][j] < xmin){
			xmin = x[i][j];
		}
		if(x[i][j] > xmax){
			xmax = x[i][j];
		}
		if(y[i][j] < ymin){
			ymin = y[i][j];
		}
		if(y[i][j] > ymax){
			ymax = y[i][j];
		}
		if(z[i][j] < zmin){
			zmin = z[i][j];
		}
		if(z[i][j] > zmax){
			zmax = z[i][j];
		}
	}
	xrad = (xmax - xmin)/2;
	 // printf("xmax = %lf xmin = %lf \n",xmax, xmin );
	yrad = (ymax - ymin)/2;
	zrad = (zmax - zmin)/2;
	 // printf("ymax = %lf ymin = %lf \n",ymax, ymin );
	xcenter = xmax - xrad;
	ycenter = ymax - yrad;
	zcenter = zmax - zrad;
	// printf("Xcenter = %lf Ycenter = %lf \n", xcenter, ycenter);
	double s;
	
	if(xrad > yrad){
		s = xrad;
	}else{
		s = yrad;
	}
	if(zrad > s){
		s = zrad;
	}
	s = (WINDOW_WIDTH/2)/s;
	D3d_make_identity(scale);
	D3d_make_identity(iscale);
	D3d_translate(scale, iscale, -xcenter, -ycenter, -zcenter);
	// D3d_scale(scale, iscale,1/s,1/s,1/s);r
	D3d_mat_mult_points(x[i],y[i],z[i],scale,x[i],y[i],z[i], numpoints[i]);
}
}

void rotate(int pnum, int axis, int direction){
	double a[4][4], b[4][4];
 	D3d_make_identity(a);
 	D3d_make_identity(b);
 	int sign = 1;
 	if(direction == 0){
 		sign = -1;
 	}
 	double xmax, xmin, ymax, ymin, xrad, yrad, xcenter, ycenter, zmax,zmin,zrad,zcenter;
			xmin = x[pnum][0];
			xmax = x[pnum][0];
			ymin = y[pnum][0];
			ymax = y[pnum][0];
			zmin = z[pnum][0];
			zmax = z[pnum][0];
			int j;
	for(j = 0; j<numpoints[pnum];j++){
		if(x[pnum][j] < xmin){
			xmin = x[pnum][j];
		}
		if(x[pnum][j] > xmax){
			xmax = x[pnum][j];
		}
		if(y[pnum][j] < ymin){
			ymin = y[pnum][j];
		}
		if(y[pnum][j] > ymax){
			ymax = y[pnum][j];
		}
		if(z[pnum][j] < zmin){
			zmin = z[pnum][j];
		}
		if(z[pnum][j] > zmax){
			zmax = z[pnum][j];
		}
	}
	xrad = (xmax - xmin)/2;
	yrad = (ymax - ymin)/2;
	zrad = (zmax - zmin)/2;
	xcenter = xmax - xrad;
	ycenter = ymax - yrad;
	zcenter = zmax - zrad;
	D3d_translate(a,b,-xcenter,-ycenter,-zcenter);
 	if(axis == 0){
		D3d_rotate_x(a,b, sign* ROTATE_SPEED);
 	}else if(axis == 1){
		D3d_rotate_y(a,b, sign*ROTATE_SPEED);
 	}else if(axis == 2){
 		D3d_rotate_z(a,b,sign*ROTATE_SPEED);
 	}
 	D3d_translate(a,b,xcenter,ycenter,zcenter);
 	D3d_mat_mult_points(x[pnum], y[pnum],z[pnum], a, x[pnum], y[pnum],z[pnum], numpoints[pnum]);
}

void translate(int pnum, int axis, int direction){
	printf("begin translate \n");
	double a[4][4], b[4][4];
 	D3d_make_identity(a);
 	D3d_make_identity(b);
 	int sign = 1;
 	if(direction == 0){
 		sign = -1;
 	}
 	if(axis == 0){
		D3d_translate(a , b, 1 *sign, 0, 0);
 	}else if(axis == 1){
		D3d_translate(a , b, 0,1*sign ,0);
 	}else if(axis == 2){
 		D3d_translate(a , b, 0,0,1*sign );
 	}
 	D3d_mat_mult_points(x[pnum], y[pnum],z[pnum], a, x[pnum], y[pnum],z[pnum], numpoints[pnum]);
 	printf("end translate \n");
}

void display(int pnum, int sign){
	int i, j, k, m;
	G_rgb(0,0,0);
	G_clear();
	G_clear(1,1,1);
	if(sign == 0){
			sign = -1;
		}else{
			sign=1;
		}
		for(pnum = 0; pnum<20; pnum++){
// printf("enter disp\n");

int n=0;

for(n=0; n<plsize; n++){
double xtemp[poly_sizes[polyLoc[n].objnum][polyLoc[n].polynum]];
double ytemp[poly_sizes[polyLoc[n].objnum][polyLoc[n].polynum]];
double ztemp[poly_sizes[polyLoc[n].objnum][polyLoc[n].polynum]];
	printf("New display\n");
	for(j=0; j<poly_sizes[pnum][i];j++){
 		xtemp[j] = x[polyLoc[n].objnum][polygons[polyLoc[n].objnum][polyLoc[n].polynum][j]];
 		ytemp[j] = y[polyLoc[n].objnum][polygons[polyLoc[n].objnum][polyLoc[n].polynum][j]];
 		ztemp[j] = z[polyLoc[n].objnum][polygons[polyLoc[n].objnum][polyLoc[n].polynum][j]];
 		printf("X = %lf Y = %lf  Z = %lf \n",xtemp[j],ytemp[j], ztemp[j] );
	}
	for(j=0; j<poly_sizes[pnum][i];j++){
		xtemp[j] = xtemp[j]/ztemp[j];
		ytemp[j] = ytemp[j]/ztemp[j];
		xtemp[j] = (xtemp[j] * (300/tan(M_PI/3))) + 300;
		ytemp[j] = (ytemp[j] * (300/tan(M_PI/3))) + 300;
		printf("X = %lf Y = %lf  Z = %lf \n",xtemp[j],ytemp[j], ztemp[j] );
		}
		G_rgb(pnum%2,pnum%3, 1);
 		G_fill_polygon(xtemp, ytemp, poly_sizes[pnum][i]);
 	
}
}
}



// for(i=0;i<numpolys[pnum];i++){
// 	double xtemp[poly_sizes[pnum][i]], ytemp[poly_sizes[pnum][i]],ztemp[poly_sizes[pnum][i]];
// 	// printf("New display\n");
// 	for(j=0; j<poly_sizes[pnum][i];j++){
//  		xtemp[j] = x[pnum][polygons[pnum][i][j]];
//  		ytemp[j] = y[pnum][polygons[pnum][i][j]];
//  		ztemp[j] = z[pnum][polygons[pnum][i][j]];
//  		// printf("X = %lf Y = %lf  Z = %lf \n",xtemp[j],ytemp[j], ztemp[j] );
// 	}
// 	for(j=0; j<poly_sizes[pnum][i];j++){
// 		xtemp[j] = xtemp[j]/ztemp[j];
// 		ytemp[j] = ytemp[j]/ztemp[j];
// 		xtemp[j] = (xtemp[j] * (300/tan(M_PI/3))) + 300;
// 		ytemp[j] = (ytemp[j] * (300/tan(M_PI/3))) + 300;
// 		// printf("X = %lf Y = %lf  Z = %lf \n",xtemp[j],ytemp[j], ztemp[j] );
// 		}

// 		double perpendicular[3], first[3], second[3], origin[3];
// 		first[0] = xtemp[0]-xtemp[1];
// 		first[1] = ytemp[0]-ytemp[1];
// 		first[2] = ztemp[0]-ztemp[1];
// 		second[0] = xtemp[0]-xtemp[2];
// 		second[1] = ytemp[0]-ytemp[2];
// 		second[2] = ztemp[0]-ztemp[2];
// 		origin[0] = 0 - xtemp[0];
// 		origin[1] = 0 - xtemp[1];
// 		origin[2] = 0 - xtemp[2];
		
	
//  	G_rgb(pnum%2,pnum%3, 1);
//  	G_fill_polygon(xtemp, ytemp, poly_sizes[pnum][i]);
 	
//  }
// }
//}


int main(int argc, char ** argv){

	if(argc == 1){
	printf("usage: pgm_name file1.xy file2.xy ... \n");
	exit(1);
}
setUp();
loadFiles(argc, argv);
scaleNfit(argc);
display(0, 1);
// G_wait_key();
int num, file, axis;
file = 0;
axis = 0;
int sign = 0;
int direction = 0;
while(1 == 1){
	num = G_wait_key();
	if(num == 114){
		rotate(file, axis, direction);
			display(file, sign);
	}
	else if(num == 81 || num == 113){//quit
		break;
	}
	else if(num ==120){//x-axis
		axis = 0;
	}
	else if(num == 121){//y-axis
		axis = 1;
	}
	else if(num == 122){//z-axis 
		axis = 2;
	}
	else if(num == 116){//translate 
		printf("pre translate \n");
		// translate(file, axis, direction);
		display(file,sign);
		printf("post translate \n");
	}
	else if(num == 99){//change translate direction
		if(direction == 0){
			direction = 1;
		}else{
			direction=0;
		}
	}
	else if( num >= 48 && num <= 57){//choose file
		file = num - 48;
		if(file < argc){
			display(file, sign);
		}
	}else if(num == 115){
		sign = (sign+1)%2;

		display(file, sign);
	}else{
		printf("no command");
	}
}
}