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

double x[20][10000], y[20][10000], z[20][10000], colors[20][10000][3];
int numpoints[20], numpolys[20], poly_sizes[20][10000], polygons[20][10000][100];
POLYGON polyLoc[200000];
int plsize;
double red, green, blue, intensity;




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
 return((a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]) );
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
			}
				polyLoc[m].objnum=i-1;
				polyLoc[m].polynum=k;
				polyLoc[m].dist=z[i-1][polygons[i -1][k][0]];
				// printf(" objnum %d , polynum %d , dist %lf \n", polyLoc[m].objnum, polyLoc[m].polynum, polyLoc[m].dist);
				m++;
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
	x[i][numpoints[i]+1] = xmax - xrad;
	y[i][numpoints[i]+1] = ymax - yrad;
	z[i][numpoints[i]+1] = zmax - zrad;
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
	D3d_translate(a,b,-x[pnum][numpoints[pnum]+1],-y[pnum][numpoints[pnum]+1],-z[pnum][numpoints[pnum]+1]);
 	if(axis == 0){
		D3d_rotate_x(a,b, sign* ROTATE_SPEED);
 	}else if(axis == 1){
		D3d_rotate_y(a,b, sign*ROTATE_SPEED);
 	}else if(axis == 2){
 		D3d_rotate_z(a,b,sign*ROTATE_SPEED);
 	}
 	D3d_translate(a,b,x[pnum][numpoints[pnum]+1],y[pnum][numpoints[pnum]+1],z[pnum][numpoints[pnum]+1]);
 	D3d_mat_mult_points(x[pnum], y[pnum],z[pnum], a, x[pnum], y[pnum],z[pnum], numpoints[pnum]);
}

void translate(int pnum, int axis, int direction){
	double a[4][4], b[4][4];
 	D3d_make_identity(a);
 	D3d_make_identity(b);
 	int sign = 1;
 	if(direction == 0){
 		sign = -1;
 	}
 	if(axis == 0){
 		x[pnum][numpoints[pnum]+1] = x[pnum][numpoints[pnum]+1] + (sign * 1);
		D3d_translate(a , b, 1 *sign, 0, 0);
 	}else if(axis == 1){

 	y[pnum][numpoints[pnum]+1] = y[pnum][numpoints[pnum]+1] + (sign * 1);
		D3d_translate(a , b, 0,1*sign ,0);
 	}else if(axis == 2){
 		z[pnum][numpoints[pnum]+1] = z[pnum][numpoints[pnum]+1] + (sign * 1);
 		D3d_translate(a , b, 0,0,1*sign );
 	}
 	
 	
 	D3d_mat_mult_points(x[pnum], y[pnum],z[pnum], a, x[pnum], y[pnum],z[pnum], numpoints[pnum]);
}

void display(int pnum, int sign, int specpow, double diffusepro, double ambient, int lightx, int lighty, int lightz){
	int i, j, k, m;
	G_rgb(0,0,0);
	G_clear();
	G_clear(1,1,1);
	if(sign == 0){
			sign = -1;
		}else{
			sign=1;
		}
int n=0;
// printf("plsize = %d \n", plsize );
for(n=0; n<plsize; n++){
		// printf("n = %d \n",n);
double xtemp[poly_sizes[polyLoc[n].objnum][polyLoc[n].polynum]];
double ytemp[poly_sizes[polyLoc[n].objnum][polyLoc[n].polynum]];
double ztemp[poly_sizes[polyLoc[n].objnum][polyLoc[n].polynum]];
	// printf("New display\n");
	// printf("polysize = %d \n", poly_sizes[polyLoc[n].objnum][polyLoc[n].polynum]);
	for(j=0; j<poly_sizes[polyLoc[n].objnum][polyLoc[n].polynum];j++){
 		xtemp[j] = x[polyLoc[n].objnum][polygons[polyLoc[n].objnum][polyLoc[n].polynum][j]];
 		ytemp[j] = y[polyLoc[n].objnum][polygons[polyLoc[n].objnum][polyLoc[n].polynum][j]];
 		ztemp[j] = z[polyLoc[n].objnum][polygons[polyLoc[n].objnum][polyLoc[n].polynum][j]];
 	
	}
		double perpendicular[3], first[3], second[3], eye[3], light[3],reflection[3];
		first[0] = xtemp[0]-xtemp[1];
		first[1] = ytemp[0]-ytemp[1];
		first[2] = ztemp[0]-ztemp[1];
		second[0] = xtemp[0]-xtemp[2];
		second[1] = ytemp[0]-ytemp[2];
		second[2] = ztemp[0]-ztemp[2];
		eye[0] = xtemp[0];
		eye[1] = ytemp[0];
		eye[2] = ztemp[0];
		light[0]= xtemp[0] - lightx;
		light[1]= ytemp[0] - lighty;
		light[2]= ztemp[0] - lightz;


for(j=0; j<poly_sizes[polyLoc[n].objnum][polyLoc[n].polynum];j++){
		xtemp[j] = xtemp[j]/ztemp[j];
		ytemp[j] = ytemp[j]/ztemp[j];
		xtemp[j] = (xtemp[j] * (300/tan(M_PI/3))) + 300;
		ytemp[j] = (ytemp[j] * (300/tan(M_PI/3))) + 300;
 		// printf("X = %lf Y = %lf  Z = %lf \n",xtemp[j],ytemp[j], ztemp[j] );
}

		D3d_x_product(perpendicular, first, second);
		double length = sqrt(perpendicular[0]*perpendicular[0] + perpendicular[1]*perpendicular[1] + perpendicular[2]*perpendicular[2]);
		perpendicular[0] = perpendicular[0]/length;
		perpendicular[1] = perpendicular[1]/length;
		perpendicular[2] = perpendicular[2]/length;
		double lightLength =  sqrt(light[0]*light[0] + light[1]*light[1] + light[2]*light[2]);
		light[0] = light[0]/lightLength;
		light[1] = light[1]/lightLength;
		light[2] = light[2]/lightLength;
		double eyelength =  sqrt(eye[0]*eye[0] + eye[1]*eye[1] + eye[2]*eye[2]);
		eye[0] = eye[0]/eyelength;
		eye[1] = eye[1]/eyelength;
		eye[2] = eye[2]/eyelength;
		if(dot_product(perpendicular, light) < 0){
			perpendicular[0] = -1 * perpendicular[0];
			perpendicular[1] = -1 * perpendicular[1];
			perpendicular[2] = -1 * perpendicular[2];
		}
		double diffuse = diffusepro * dot_product(perpendicular, light);

		reflection[0] = ((2 * dot_product(perpendicular, light)) * perpendicular[0]) - light[0];
		reflection[1] = ((2 * dot_product(perpendicular, light)) * perpendicular[1]) - light[1];
		reflection[2] = ((2 * dot_product(perpendicular, light)) * perpendicular[2]) - light[2];
		double specular;
		if(dot_product(eye, reflection) < 0){ 
			specular = 0;
		}else {
			specular = (1 - ambient - diffusepro) * pow((dot_product(eye, reflection)),specpow);	
		}
		double redt, greent, bluet;
		if(ambient + diffuse <= ambient + diffusepro){
			double yt = green;
			double xt = red;
			double zt = blue;
			redt = ((ambient + diffuse)/(ambient + diffusepro))*red + specular;
			greent = ((ambient + diffuse)/(ambient + diffusepro))*green + specular;
			bluet = ((ambient + diffuse)/(ambient + diffusepro))*blue + specular;
		}
		else{
			double yt = 1 - green;
			double xt = 1 - red;
			double m = xt/yt;
			double b = green - (m * red);
			redt = red + (((ambient + diffuse)-(ambient + diffusepro))/(ambient + diffusepro))*red + specular;
			greent = green + (((ambient + diffuse)-(ambient + diffusepro))/(ambient + diffusepro))*green + specular;
			bluet = blue + (((ambient + diffuse)-(ambient + diffusepro))/(ambient + diffusepro))*blue + specular;
		}
		double color = ambient + diffuse + specular;
		// printf("ambient = %lf , diffues = %lf , specuar =%lf\n",ambient, diffuse, specular);
		G_rgb(redt,greent,bluet);
 		G_fill_polygon(xtemp, ytemp, poly_sizes[polyLoc[n].objnum][polyLoc[n].polynum]);
 		G_rgb(0,0,0);
 		G_polygon(xtemp, ytemp, poly_sizes[polyLoc[n].objnum][polyLoc[n].polynum]);
}
}

int resize(){
	int i=0;
	for(i=0;i<plsize;i++){
		polyLoc[i].dist = z[polyLoc[i].objnum][polygons[polyLoc[i].objnum][polyLoc[i].polynum][0]];
	}
	qsort(polyLoc, plsize,sizeof(POLYGON),compare);
}


int main(int argc, char ** argv){

	if(argc == 1){
	printf("usage: pgm_name file1.xy file2.xy ... \n");
	exit(1);
}
int specpow;
double diffusepro, ambient;
 diffusepro = .4;
 ambient = .2;
// double x = 100;
// double y=200;
// double z=-50;
 specpow = 70;
red = 0;
green = 0;
blue = 1;
intensity = .4;
printf("enter ambeint  > ");
scanf("%lf", &ambient);
printf("enter Diffuse  > ");
scanf("%lf", &diffusepro);
printf("enter specular  > ");
scanf("%d", &specpow);
int x,y,z;
printf("enter light coordinates \n");
scanf("%d %d %d", &x, &y, &z);
printf("enter inital color");
scanf("%lf %lf %lf", &red, &green, &blue);
// printf("enter intensity");
// scanf("%lf", &intensity);
setUp();
loadFiles(argc, argv);
scaleNfit(argc);
display(0, 1, specpow, diffusepro, ambient, x ,y,z);
int num, file, axis;
file = 0;
axis = 0;
int sign = 0;
int direction = 0;
while(1 == 1){
	num = G_wait_key();

	if(num == 114){
		rotate(file, axis, direction);
		resize();
		display(file, sign, specpow, diffusepro, ambient, x , y, z);
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
		translate(file, axis, direction);
		resize();
		display(file,sign, specpow, diffusepro, ambient, x , y, z);
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
			display(file, sign, specpow, diffusepro, ambient, x , y, z);
		}
	}else if(num == 115){
		sign = (sign+1)%2;

		display(file, sign, specpow, diffusepro, ambient, x , y, z);
	}else{
		printf("no command");
	}
}
}