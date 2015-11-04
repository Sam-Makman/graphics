#include <FPT.h>
#include <D3d_matrixS.c>

#define WINDOW_WIDTH 600
#define ROTATE_SPEED .05 
double x[20][15000], y[20][15000], z[20][15000], colors[20][15000][3];
int numpoints[20], numpolys[20], poly_sizes[20][15000], polygons[20][15000][100];

void setUp(){
  G_init_graphics(WINDOW_WIDTH,WINDOW_WIDTH + 30);
  G_rgb(0,0,0);
  G_clear();
  G_clear(1,1,1);
}



void loadFiles(int argc, char ** argv){
	printf("load files");
int i,j,k;
FILE * f;
for(i=1; i<argc; i++){
	f = fopen(argv[i], "r");
		if(f == NULL){
			printf("Cannot open file %s \n", argv[i]);
		}
	printf("loading file\n");
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
				// printf("polygons %d\n", polygons[i -1][k][j]);
			}
		}
		for(k=0; k<numpolys[i -1]; k++){
      		fscanf(f,"%lf %lf %lf", &colors[i -1][k][0], &colors[i -1][k][1],  &colors[i -1][k][2]);
    	}
	}
	fclose(f);
}


// void scaleNfit(int argc){
// int i,j;
// double scale[3][3] ,iscale[3][3];
// for(i=0; i<argc-1;i++){
// 	double xmax, xmin, ymax, ymin, xrad, yrad, xcenter, ycenter;
// 			xmin = x[i][0];
// 			xmax = x[i][0];
// 			ymin = y[i][0];
// 			ymax = y[i][0];
// 	for(j = 0; j<numpoints[i];j++){
// 		if(x[i][j] < xmin){
// 			xmin = x[i][j];
// 		}
// 		if(x[i][j] > xmax){
// 			xmax = x[i][j];
// 		}
// 		if(y[i][j] < ymin){
// 			ymin = y[i][j];
// 		}
// 		if(y[i][j] > ymax){
// 			ymax = y[i][j];
// 		}
// 	}
// 	xrad = (xmax - xmin)/2;
// 	 // printf("xmax = %lf xmin = %lf \n",xmax, xmin );
// 	yrad = (ymax - ymin)/2;
// 	 // printf("ymax = %lf ymin = %lf \n",ymax, ymin );
// 	xcenter = xmax - xrad;
// 	ycenter = ymax - yrad;
// 	// printf("Xcenter = %lf Ycenter = %lf \n", xcenter, ycenter);
// 	double s;
// 	if(xrad > yrad){
// 		s = xrad;
// 	}else{
// 		s=yrad;
// 	}
// 	s = (WINDOW_WIDTH/2)/s;
// 	D2d_make_identity(scale);
// 	D2d_make_identity(iscale);
// 	D2d_translate(scale, iscale, -xcenter, -ycenter);
// 	D2d_scale(scale, iscale,s,s);
// 	D2d_translate(scale, iscale, WINDOW_WIDTH/2, WINDOW_WIDTH/2);
// 	D2d_mat_mult_points(x[i],y[i],scale,x[i],y[i], numpoints[i]);
// }
// }

void rotate(int pnum, int axis){
	double a[4][4], b[4][4];
 	D3d_make_identity(a);
 	D3d_make_identity(b);
 	// D3d_translate(a, b, -WINDOW_WIDTH/2, -WINDOW_WIDTH/2, 0);
 	if(axis == 0){
		D3d_rotate_x(a,b, ROTATE_SPEED);
 	}else if(axis == 1){
		D3d_rotate_y(a,b, ROTATE_SPEED);
 	}else if(axis == 2){
 		D3d_rotate_z(a,b, ROTATE_SPEED);
 	}
 	
 	// D3d_translate(a, b, WINDOW_WIDTH/2, WINDOW_WIDTH/2,0);
 	D3d_mat_mult_points(x[pnum], y[pnum],z[pnum], a, x[pnum], y[pnum],z[pnum], numpoints[pnum]);
}

void display(int pnum){
	int i, j, k;
	G_rgb(0,0,0);
  G_clear();
  G_clear(1,1,1);
// printf("enter disp\n");
for(i=0;i<numpolys[pnum];i++){
	double xtemp[poly_sizes[pnum][i]], ytemp[poly_sizes[pnum][i]],ztemp[poly_sizes[pnum][i]];
	// printf("New display\n");
	for(j=0; j<poly_sizes[pnum][i];j++){
 		xtemp[j] = x[pnum][polygons[pnum][i][j]];
 		ytemp[j] = y[pnum][polygons[pnum][i][j]];
 		ztemp[j] = z[pnum][polygons[pnum][i][j]];
 		// printf("X = %lf Y = %lf  Z = %lf \n",xtemp[j],ytemp[j], ztemp[j] );
	}
	for(j=0; j<poly_sizes[pnum][i];j++){
		xtemp[j] = xtemp[j]/ztemp[j];
		ytemp[j] = ytemp[j]/ztemp[j];
		// xtemp[j] = xtemp[j] + 300;
		// ytemp[j] = ytemp[j] + 300;
		// printf("x, y %lf %lf ",xtemp[j], ytemp[j]);
		}


 	// G_rgb(colors[pnum][i][0],colors[pnum][i][1],colors[pnum][i][2]);
 	G_rgb(1,0,0);
 	G_polygon(xtemp, ytemp, poly_sizes[pnum][i]);
 	// G_fill_polygon(xtemp, ytemp ,poly_sizes[pnum][i]);
 	}
 	// double a[3][3], b[3][3];
 	// D2d_make_identity(a);
 	// D2d_make_identity(b);
 	// D2d_translate(a, b, -WINDOW_WIDTH/2, -WINDOW_WIDTH/2);
 	// D2d_rotate(a,b, ROTATE_SPEED);
 	// D2d_translate(a, b, WINDOW_WIDTH/2, WINDOW_WIDTH/2);
 	// D2d_mat_mult_points(x[pnum], y[pnum], a, x[pnum], y[pnum],numpoints[pnum]);

}


int main(int argc, char ** argv){

	if(argc == 1){
	printf("usage: pgm_name file1.xy file2.xy ... \n");
	exit(1);
}
setUp();
loadFiles(argc, argv);
// scaleNfit(argc);
display(0);
G_wait_key();
int num, file, axis;
file = 0;
axis = 0;
while(1 == 1){
	num = G_wait_key();
	if(num == 114){
		rotate(file, axis);
			display(file);
	}
	else if(num == 81 || num == 113){
		break;
	}
	else if(num ==120){
		axis = 0;
	}
	else if(num == 121){
		axis = 1;
	}
	else if(num = 122){
		axis = 2;
	}
	else if( num >= 48 && num <= 57){
		file = num - 48;
		if(file < argc){
			display(file);
		}
	}
	
}
}