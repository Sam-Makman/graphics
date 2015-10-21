#include <FPT.h>
#include <D2d_matrix.h>

#define WINDOW_WIDTH 600
#define ROTATE_SPEED .05 
double x[20][1000], y[20][1000], colors[20][1000][3];
int numpoints[20], numpolys[20], poly_sizes[20][1000], polygons[20][1000][40];
double cx[100], cy[100], center[2];
int cSize;
void setUp(){
  G_init_graphics(WINDOW_WIDTH,WINDOW_WIDTH + 30);
  G_rgb(0,0,0);
  G_clear();
  G_clear(1,1,1);
}



void loadFiles(int argc, char ** argv){
int i,j,k;
FILE * f;
for(i=1; i<argc; i++){
	f = fopen(argv[i], "r");
		if(f == NULL){
			printf("Cannot open file %s \n", argv[i]);
		}
	// printf("loading file");
	fscanf(f , "%d", &numpoints[i -1]);
	for(j=0; j< numpoints[i-1]; j++){
		fscanf(f, "%lf %lf ", &x[i - 1][j], &y[i - 1][j]);
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


void scaleNfit(int argc){
int i,j;
double scale[3][3] ,iscale[3][3];
for(i=0; i<argc-1;i++){
	double xmax, xmin, ymax, ymin, xrad, yrad, xcenter, ycenter;
			xmin = x[i][0];
			xmax = x[i][0];
			ymin = y[i][0];
			ymax = y[i][0];
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
	}
	xrad = (xmax - xmin)/2;
	 // printf("xmax = %lf xmin = %lf \n",xmax, xmin );
	yrad = (ymax - ymin)/2;
	 // printf("ymax = %lf ymin = %lf \n",ymax, ymin );
	xcenter = xmax - xrad;
	ycenter = ymax - yrad;
	// printf("Xcenter = %lf Ycenter = %lf \n", xcenter, ycenter);
	double s;
	if(xrad > yrad){
		s = xrad;
	}else{
		s=yrad;
	}
	s = (WINDOW_WIDTH/2)/s;
	D2d_make_identity(scale);
	D2d_make_identity(iscale);
	D2d_translate(scale, iscale, -xcenter, -ycenter);
	D2d_scale(scale, iscale,s,s);
	D2d_translate(scale, iscale, WINDOW_WIDTH/2, WINDOW_WIDTH/2);
	D2d_mat_mult_points(x[i],y[i],scale,x[i],y[i], numpoints[i]);
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
	// printf("New display\n");
	for(j=0; j<poly_sizes[pnum][i];j++){
 		xtemp[j] = x[pnum][polygons[pnum][i][j]];
 		ytemp[j] = y[pnum][polygons[pnum][i][j]];
 		// printf("X = %lf Y = %lf \n",xtemp[j],ytemp[j] );
	}
	int tSize = 5;// clip(xtemp, ytemp ,poly_sizes[pnum][i]);
	if(tSize > 2){
 	G_rgb(colors[pnum][i][0],colors[pnum][i][1],colors[pnum][i][2]);
 	G_fill_polygon(xtemp, ytemp ,tSize);
 	}}
 	double a[3][3], b[3][3];
 	D2d_make_identity(a);
 	D2d_make_identity(b);
 	D2d_translate(a, b, -WINDOW_WIDTH/2, -WINDOW_WIDTH/2);
 	D2d_rotate(a,b, ROTATE_SPEED);
 	D2d_translate(a, b, WINDOW_WIDTH/2, WINDOW_WIDTH/2);

 	D2d_mat_mult_points(x[pnum], y[pnum], a, x[pnum], y[pnum],numpoints[pnum]);

for(i=0; i<cSize;i++){
	G_rgb(255,255,255);
	G_line(cx[i], cy[i], cx[(i+1)%cSize], cy[(i+1)%cSize]);
}
}

double sameSide(double ax, double ay, double bx, double by, double x1, double y1, double x2, double y2){
	return ((y1 - y2)*(ax - x1) + (x2 -x1)*(ay -y1))*((y1 - y2)*(bx - x1) + (x2 - x1)*(by -y1));
}

int clip(double xp[], double yp[], int size){
	// printf("enter clip");
int i, j;
int count = 0;
double tempx[100], tempy[100];
for(i=0;i<=cSize;i++){


	double m = cy[i] -cy[(i+1)%cSize] /cx[i] -cx[(i+1)%cSize];
	double b = m * cx[i] - cy[i];	
	for(j=0;j<=size;j++){
		// printf("Center : %lf , %lf \n", center[0], center[1]);
		// double sideY = center[1] - (center[0] * m + b);
		// double sideX = center[0] - (b+center[1] /m);
		// double startSideX = yp[j] - (xp[j] * m + b);
		// double startSideY = xp[j] - (b+yp[j] /m);
		// double endSideX =  yp[(j+1)%size] - (xp[(j +1)%size] * m + b);
		// double endSideY = xp[(j+1)%size] - (b+yp[(j+1)%size] /m);
		double spointSide = sameSide(center[0], center[1], xp[j], yp[j], cx[i], cy[i],cx[(i+1)%cSize] ,cy[(i+1)%cSize]);
		double epointSide = sameSide(center[0], center[1], xp[(j+1)%size], yp[(j+1)%size], cx[i], cy[i],cx[(i+1)%cSize] ,cy[(i+1)%cSize]);

		// printf("sideX,Y: %lf,%lf \n startSide : %lf, endSide %lf \n", sideX, sideY, startSide, endSide);
		if(spointSide > 0 && epointSide > 0){
			// tempx[count] = xp[(j+1)%size];
			// tempy[count] = yp[(j+1)%size];
			// count++;
			//printf("in-in\n");
		}//both points are inside. 
		else if(spointSide < 0 && epointSide <0){
			// printf("out-out\n");
		}//both points are outside
		else if(spointSide > 0 && epointSide < 0){
			// double slope = yp[j] - yp[(j+1)%size] /xp[j] - xp[(j+1)%size];
			// double offset = slope * xp[j] - yp[j];
			// double xIntersect = (b - offset) / (m*slope);
			// double yIntesect = m * xIntersect + b;
			// tempx[count] = xIntersect;
			// tempy[count] = yIntesect;
			// count++;
			// printf("in-out\n");

		}//start is inside end is outside 
		else if(spointSide < 0 && epointSide > 0){
			// double slope = yp[j] - yp[(j+1)%size] /xp[j] - xp[(j+1)%size];
			// double offset = slope * xp[j] - yp[j];
			// double xIntersect = (b - offset) / (m*slope);
			// double yIntesect = m * xIntersect + b;
			// tempx[count] = xIntersect;
			// tempy[count] = yIntesect;
			// count++;
			// tempx[count] = xp[(j+1)%size];
			// tempy[count] = yp[(j+1)%size];
			// count++;
			// printf("out-in\n");
		}//start is outside end is inside
		int k;
	// 	for(k=0; k<count;k++){
	// 	 printf("(X,Y) , (%lf , %lf)\n", tempx[i], tempy[i]);
	// 	xp[k] = tempx[k];
	// 	yp[k] = tempy[k];
	// }

	
	// size = count;

	count = 0;
	if(size <= 0){
		break;
	}
	}
	// printf("count : %d \n", count);
	
	
}
return count;
}

void getClippingWindow(){
	double coords[2];
	int i = 0;
while(1==1){
G_wait_click(coords);
if(coords[0] < 40 && coords[1] < 40){
	break;}
else{
	cx[i] = coords[0];
	cy[i] = coords[1];
	printf("coords x:%lf y:%lf", coords[0], coords[1]);
	G_rgb(255,255,255);
	G_fill_rectangle(coords[0],coords[1], 5,5);
	center[0] += cx[i];
	center[1] += cy[i];
	i++;
}
}

center[0] /=i;
center[1] /=i;
cSize = i;
}

int main(int argc, char ** argv){

	if(argc == 1){
	printf("usage: pgm_name file1.xy file2.xy ... \n");
	exit(1);
}
setUp();
loadFiles(argc, argv);
scaleNfit(argc);


int num;
// getClippingWindow();
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