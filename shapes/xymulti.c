#include <FPT.h>
#define WINDOW_WIDTH 600
#define ROTATE_SPEED .05
int numpoints[10], numpolys[10], poly_sizes[10][600], polygons[10][600][20];
double colors[10][600][3], xy[2][20][600];


void setUp(){
  G_init_graphics(WINDOW_WIDTH,WINDOW_WIDTH + 30);
  G_rgb(0,0,0);
  G_clear();
  G_clear(1,1,1);
}


void scaleNfit(int argc){
printf("entering scaleNfit \n");
int i, j, k;
for(i= 0; i< argc -1; i++){
	double xmax, xmin, ymax, ymin, xrad, yrad, xcenter, ycenter;
			xmin = xy[0][i][0];
			xmax = xy[0][i][0];
			ymin = xy[1][i][0];
			ymax = xy[1][i][0];
			printf("finding endpoints\n");
	for(j = 0; j<numpoints[i];j++){
		if(xy[0][i][j] < xmin){
			xmin = xy[0][i][j];
		}
		if(xy[0][i][j] > xmax){
			xmax = xy[0][i][j];
		}
		if(xy[1][i][j] < ymin){
			ymin = xy[1][i][j];
		}
		if(xy[1][i][j] > ymax){
			ymax = xy[1][i][j];
		}
	}
	xrad = (xmax - xmin)/2;
	// printf("xmax = %lf xmin = %lf \n",xmax, xmin );
	yrad = (ymax - ymin)/2;
	// printf("ymax = %lf ymin = %lf \n",ymax, ymin );
	xcenter = xmax - xrad;
	ycenter = ymax - yrad;
	double scale;
	if(xrad > yrad){
		scale = xrad;
	}else{scale = yrad;}
	//printf(" xrad = %lf yrad = %lf xcenter = %lf ycenter = %lf", xrad, yrad, xcenter, ycenter);
	// printf("about to rescale \n numpoints = %d \n", numpoints[i]);
	for(j = 0; j<numpoints[i];j++){
		//printf("Before x = %lf  y = %lf \n", xy[0][i][j], xy[1][i][j]);
		xy[0][i][j] = xy[0][i][j] - xcenter;
		xy[1][i][j] = xy[1][i][j] - ycenter;
		//printf("centered  x = %lf  y = %lf \n", xy[0][i][j], xy[1][i][j]);
		xy[0][i][j] = xy[0][i][j] * ((WINDOW_WIDTH/3)/scale);
		xy[1][i][j] = xy[1][i][j] * ((WINDOW_WIDTH/3)/scale);
		//printf("after x = %lf  y = %lf \n", xy[0][i][j], xy[1][i][j]);
		xy[0][i][j] = xy[0][i][j] + (WINDOW_WIDTH/2);
		xy[1][i][j] = xy[1][i][j] + (WINDOW_WIDTH/2);
	}

}
}


//int argc, char ** argv, double *** xys; int * numpoints, int * numpolys, int ** poly_sizes, int *** polygons, int *** colors
void loadFiles(int argc, char ** argv){
	int i, k, j;
	FILE * f;

	for(i = 1; i<argc; i++){
		f = fopen(argv[i], "r");
		if(f == NULL){
			printf("Cannot open file %s \n", argv[i]);
		}
		fscanf(f , "%d", &numpoints[i -1]);
		for(k=0; k < numpoints[i -1]; k++){
			fscanf(f, "%lf %lf ", &xy[0][i - 1][k], &xy[1][i - 1][k]);
			//printf("x = %lf y = %lf k = %d \n", xy[0][i - 1][k], xy[1][i - 1][k], k);
		}
		fscanf( f, "%d", &numpolys[i -1]);
		for(k = 0; k < numpolys[i -1]; k++){
			fscanf( f, "%d", &poly_sizes[i -1][k]);
			//printf("poly sizes %d \n",poly_sizes[i][k]);
			for(j=0; j< poly_sizes[i -1][k];j++){
				fscanf(f, "%d", &polygons[i -1][k][j]);
				//printf("polygons %d\n", polygons[i][k][j]);
			}
		}
		for(k=0; k<numpolys[i -1]; k++){
      		fscanf(f,"%lf %lf %lf", &colors[i -1][k][0], &colors[i -1][k][1],  &colors[i -1][k][2]);
    	}
	}
	scaleNfit(argc);
}

void rotate(int pnum){
int i;
//printf(" numpoints %d \n",numpoints[pnum]);
  for(i = 0; i<numpoints[pnum]; i++){
    double xtc, ytc, angle, c;
    xtc = (WINDOW_WIDTH/2) - xy[0][pnum][i];
    ytc = (WINDOW_WIDTH/2) - xy[1][pnum][i];
    c = sqrt((xtc * xtc) + (ytc * ytc));
    angle = atan2(ytc, xtc) + M_PI;
    angle += ROTATE_SPEED;
  //  printf("xtc = %lf ytc = %lf cos = %lf sin = %lf angle = %lf \n",xtc , ytc, cos(angle), sin(angle), angle);
    xy[0][pnum][i] = (WINDOW_WIDTH/2) + (cos(angle) * c);
    xy[1][pnum][i] = (WINDOW_WIDTH/2) + (sin(angle) * c);
  }
}

void display(int pnum){
	int i, j, k;
	G_rgb(0,0,0);
  G_clear();
  G_clear(1,1,1);
// printf("enter disp\n");
for(i=0;i<numpolys[pnum];i++){
	double xtemp[poly_sizes[pnum][i]], ytemp[poly_sizes[pnum][i]];
	for(j=0; j<poly_sizes[pnum][i];j++){
 		xtemp[j] = xy[0][pnum][polygons[pnum][i][j]];
 		ytemp[j] = xy[1][pnum][polygons[pnum][i][j]];
	}
 	G_rgb(colors[pnum][i][0],colors[pnum][i][1],colors[pnum][i][2]);
 	G_fill_polygon(xtemp, ytemp ,poly_sizes[pnum][i]);
 	}
 	rotate(pnum);
}





int main(int argc, char ** argv){
int i, j, k;
//double *** xy;
if(argc == 1){
	printf("usage: pgm_name file1.xy file2.xy ... \n");
	exit(1);
}

setUp();
loadFiles(argc, argv);
int num;
while(1 == 1){
	num = G_wait_key();
	if( num >= 48 && num <= 57){
		num = num - 48;
		if(num < argc){
			display(num);
		}
	}
	if(num == 81 || num == 113){
		break;
	}
}
}