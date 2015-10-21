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
	double xtemp[1000], ytemp[1000];
	// printf("New display\n");
	for(j=0; j<poly_sizes[pnum][i];j++){
 		xtemp[j] = x[pnum][polygons[pnum][i][j]];
 		ytemp[j] = y[pnum][polygons[pnum][i][j]];
 		// printf("X = %lf Y = %lf \n",xtemp[j],ytemp[j] );
	}
	int tsize = clip(xtemp,ytemp,poly_sizes[pnum][i]);
 	G_rgb(colors[pnum][i][0],colors[pnum][i][1],colors[pnum][i][2]);
 	G_fill_polygon(xtemp, ytemp ,tsize);
 	}
 	double a[3][3], b[3][3];
 	D2d_make_identity(a);
 	D2d_make_identity(b);
 	D2d_translate(a, b, -WINDOW_WIDTH/2, -WINDOW_WIDTH/2);
 	D2d_rotate(a,b, ROTATE_SPEED);
 	D2d_translate(a, b, WINDOW_WIDTH/2, WINDOW_WIDTH/2);
 	
 	D2d_mat_mult_points(x[pnum], y[pnum], a, x[pnum], y[pnum],numpoints[pnum]);

for(i=0; i<cSize;i++){//show clipping box
	G_rgb(255,255,255);
	G_line(cx[i], cy[i], cx[(i+1)%cSize], cy[(i+1)%cSize]);
}

}

double sameSide(double ax, double ay, double bx, double by, double x1, double y1, double x2, double y2){
	return ((y1 - y2)*(ax - x1) + (x2 -x1)*(ay -y1))*((y1 - y2)*(bx - x1) + (x2 - x1)*(by - y1));
}

// void ssTest(){
// 	double a = sameSide(1,1,1,1,2,2,10,10);
// 	double b = sameSide(1,0,0,1,1,1,2,2);
// 	double c = sameSide(10000,0,5.6,0,1,1,2,2);
// 	double x = 60000000000000;
// 	double d = sameSide(x,5000000000000,5000000000,6000000000000,1,1,2,2);
// 	printf("Should be 0 a: %lf \n",a);
// 		 printf("should be negative b : %lf \n",b);
// 		printf("should be positive c %lf \n",c);
// 		 printf("Negative d %lf \n", d);
// }


void intersect(double ret[2], double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4 ){
	if(sameSide(x1,y1,x2,y2,x3,y3,x4,y4) > 0){
		printf("x1 : %lf, y1: %lf \n x2 : %lf , y2 %lf \n", x1, y1, x2, y2);

			printf("Both points on the same side at begining\n");
			// exit(1);
			// return;
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
		printf("Startpoint : %lf, endpoint : %lf \n", spointSide, epointSide);
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
		}
		else if(spointSide == 0 && epointSide == 0){//both on the line
			printf("zero zero\n");
			// clipx[tcount] = tempx[j];	
			// clipy[tcount] = tempy[j];
			// tcount++;
			clipx[tcount] = tempx[(j+1)%count];	
			clipy[tcount] = tempy[(j+1)%count];
			tcount++;
		}
		else if(epointSide == 0 && spointSide > 0){//end on line start inside 
			//add end point to array
			printf("end is 0\n");
			clipx[tcount] = tempx[(j+1)%count];	
			clipy[tcount] = tempy[(j+1)%count];
			tcount++; 
		}

		else if(epointSide == 0 && spointSide < 0){//end on line start outside 
			printf("end is 0\n");
			clipx[tcount] = tempx[(j+1)%count];	
			clipy[tcount] = tempy[(j+1)%count];
			tcount++; 
		}

		else if(spointSide == 0 && epointSide > 0){//start on line end inside
			//add start and end point to array
			clipx[tcount] = tempx[j];
			clipy[tcount] = tempy[j];
			tcount++;

			clipx[tcount] = tempx[(j+1)%count];	
			clipy[tcount] = tempy[(j+1)%count];
			tcount++; 
		}
		else if(spointSide == 0 && epointSide < 0){//start on line end outside
			// add start point to array 
			clipx[tcount] = tempx[j];	
			clipy[tcount] = tempy[j];
			tcount++; 
		}
		else{
			printf("nothing works and everything is terrible \n");
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
	// printf("coords x:%lf y:%lf", coords[0], coords[1]);
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
//intersectTest();
display(0);
getClippingWindow();
// cx[0]=100;
// cy[0]=200;
// cx[1]=200;
// cy[1]=200;
// cx[2]=500;
// cy[2]=500;
// cx[3]= 200;
// cy[3] = 500;
// cSize=4;
// center[0] = 300;
// center[1] = 400;
// G_rgb(255,0,0);
// G_fill_rectangle(300,400,5,5);
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