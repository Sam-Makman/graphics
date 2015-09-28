
#ifndef GENERIC_GRAPHICS_DEF
#define GENERIC_GRAPHICS_DEF


// the G_ routines are graphics related and should
// not be called unless G_init_graphics has been called first


int  G_init_graphics (int w, int h) ;
// G_init_graphics has the task of connecting this interface
// with actual routines that can do the work in a
// specific environment, e.g. X11 or Windows or whatever

int Gi_wait_click(int p[2]) ;

int G_wait_click(double p[2]) ;

int G_wait_key() ;


/////////////////////////////////////////////////////////////////////
// ALL of the following are merely pointers
// which are initialized by G_Init
//
// Note that this include file is indeed the source of
// the actuall allocation of storage for these pointers...
// you certainly want these global pointers included 
// in the compilation process and you want them 
// included only once.
/////////////////////////////////////////////////////////////////////


int (* G_close) () ;
// terminate the graphics


int (* G_display_image) () ;
// make drawing visible if it already isn't
// in some environments, this might not do anything
// in others it might copy a buffer and/or do other
// synchronizing tasks


int (* Gi_events) (int *d) ;

int (* G_events) (double *d) ;


int (* G_change_pen_dimensions) (int w, int h) ;
// return 0 if illegal w,h specified, otherwise 1


int (* Gi_get_current_window_dimensions) (int *dimentsions) ;
// return 1 if successful
// needs to be passed an array of two ints


int (* G_get_current_window_dimensions) (double *dimentsions) ;
// return 1 if successful
// needs to be passed an array of two doubles


int (* Gi_rgb) (int r, int g, int b) ;
// assumes r,g,b are ints in [0,255]

int (* G_rgb) (double r, double g, double b) ;
// assumes r,g,b are doubles in [0, 1]


/////////////////////////////////////////////////////////////////////
// The next batch are based on the ability to repeatedly
//  plot a single pixel
/////////////////////////////////////////////////////////////////////

int (* G_pixel) (int x, int y) ;
// return 1 always
// This is not guaranteed to be safe


int (* G_point) (int x, int y) ;
// return 1 always
// This is SAFE.
// Draws a thick point whose dimensions are controlled by
// int G_change_pen_dimensions (int w, int h).

int (* G_circle) (int a, int b, int r) ;
// always return 1
// capable of drawing a circle with thick outline

int (* G_unclipped_line) (int ixs, int iys, int ixe, int iye) ;
// return 1 always
// This is SAFE.
// Capable of drawing a thick line.
// This is safe because it depends on G_point (which is SAFE)
// but because it is unclipped, this code could waste a great
// deal of time trying to plot lots of points outside the window.


int (* G_line) (int ixs, int iys, int ixe, int iye) ;
// return 0 if line clipped away entirely, else return 1
// This is SAFE.
// Capable of drawing a thick line.
// This also clips
// Note that the clipping occurs only for a thin, "perfect"
// line, not for a possibly thick line, but the safety feature
// of G_point that will actually plot a thick point, keeps the
// entire code safe.


int (* Gi_polygon) (int *x, int *y, int numpts) ; 
// return 1 always
// capable of drawing a polygon with thick outline

int (* G_polygon) (double *x, double *y, int numpts) ;
// provided as an alternative for passing arrays of doubles
// return 1 always
// capable of drawing a polygon with thick outline


int (* G_triangle) (int x0, int y0, int x1, int y1, int x2, int y2) ; 
// return value it inherits from G_polygon
// capable of drawing a triangle with thick outline


int (* G_rectangle) (int xleft, int yleft, int width, int height) ; 
// return value it inherits from G_polygon
// capable of drawing a rectangle with thick outline



/////////////////////////////////////////////////////////////////////
// This batch are based on the ability to repeatedly
// draw single pixel horizontal lines
/////////////////////////////////////////////////////////////////////


int (* G_single_pixel_horizontal_line) (int x0, int x1, int y) ;
// return 1 always
// This is not guaranteed to be safe


int (* G_clear) () ; 
// return 1 always


int (* G_fill_circle) (int a, int b, int r) ;
// always return 1


int (* G_unclipped_fill_polygon) (int *xx, int *yy, int n) ;
// return 0 if size needs to be truncated (unusual), else 1 
// This is SAFE


int (* Gi_fill_polygon) (int *xx, int *yy, int n) ;
// return 0 if size needs to be truncated (unusual), 
// or if clipping is used,  otherwise return 1
// This is SAFE
// AND it clips


int (* G_fill_polygon) (double *xx, double *yy, int n) ;
// provided as an alternative for passing arrays of doubles
// return 0 if size needs to be truncated (unusual), 
// or if clipping is used,  otherwise return 1
// This is SAFE
// AND it clips


int (* G_fill_triangle) (int x0, int y0, int x1, int y1, int x2, int y2) ; 
// return value it inherits from G_fill_polygon


int (* G_fill_rectangle) (int xleft, int yleft, int width, int height) ;
// return value it inherits from G_fill_polygon


int (* G_font_pixel_height) () ;
// return the font height in pixels






// the void * pointers below allow for passing in 
// either an array of characters (usual usage)
// but also, perhaps, an double array of packed 
// characters

int (* G_string_pixel_width) (void *s) ;
// return the length in pixles of the string s

int (* G_draw_string) (void *one_line_of_text, int LLx, int LLy) ;
// draw a single line of text beginning at (LLx,LLy) wihc specifies
// the coordinates of the lower left corner of the bounding box
// of the text


int (* G_draw_text) (
               int num_lines_of_text,
               void  *lines_of_text, // an array of pointers
               double startx, 
               double starty,
               double height,
               double x_over_y_ratio,
               double extra_space_between_letters_fraction,
               double extra_space_between_lines_fraction) ;


int (* G_save_image_to_file) (void *filename) ;
// return 1 if successful, else 0


#endif
