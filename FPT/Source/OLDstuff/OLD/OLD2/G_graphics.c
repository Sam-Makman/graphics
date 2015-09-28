
#include <G_graphics.h>

#include <X_graphics.h> 



int  G_init_graphics (int w, int h)
// G_init_graphics has the task of connecting this interface
// with actual routines that can do the work in a
// specific environment, e.g. X11 or Windows or whatever
{
 int s ;

 G_close = Close_Down_X ;

 // G_display_image = Copy_Buffer_X ;
 G_display_image = Copy_Buffer_And_Flush_X ;

 Gi_events = Get_Events_X ;

 G_events = Get_Events_DX ;

 G_change_pen_dimensions =  Change_Pen_Dimensions_X ;

 Gi_get_current_window_dimensions = Get_Current_Dimensions_X ;

 G_get_current_window_dimensions = Get_Current_Dimensions_DX ;

 Gi_rgb = Set_Color_Rgb_X ;

 G_rgb = Set_Color_Rgb_DX ;

 G_pixel = Point_X ;

 G_point = Safe_Point_X ;

 G_circle = Circle_X ;

 G_unclipped_line = Line_X ;

 // G_line = Line_X ;
 G_line = Safe_Line_X ;

 Gi_polygon = Polygon_X ; 

 G_polygon = Polygon_DX ;

 G_triangle = Triangle_X ; 

 G_rectangle = Rectangle_X ; 

 G_single_pixel_horizontal_line = Horizontal_Single_Pixel_Line_X ;

 G_clear = Clear_Buffer_X ;

 G_fill_circle =  Fill_Circle_X ;

 G_unclipped_fill_polygon =  Fill_Polygon_X ; 

 Gi_fill_polygon = Fill_Polygon_X ; 

 G_fill_polygon = Fill_Polygon_DX ; 

 G_fill_triangle = Fill_Triangle_X ;

 G_fill_rectangle = Fill_Rectangle_X ;

 G_font_pixel_height = Font_Pixel_Height_X ;

 G_string_pixel_width = String_Pixel_Width_X ;

 G_draw_string = Draw_String_X ;

 G_draw_text = Draw_Text_X ;

 G_save_image_to_file = Save_Image_To_File_X ;

 s = Init_X(w,h) ;

 return s ;
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


// The following functions are built on top of G
// not directly on top of the underlying
// video system


int Gi_wait_click(int p[2])
{
  int sig ;

  G_display_image();  
  do {
    sig = Gi_events(p) ;
  }  while (sig != -3) ;

  return sig ;
}



int G_wait_click(double p[2])
{
  int sig ;
  int pi[2] ;

  sig = Gi_wait_click(pi) ;
  p[0] = pi[0] ;
  p[1] = pi[1] ;
  
  return sig ;
}



int G_wait_key()
{
  int p[2] ;
  int sig ;

  G_display_image();  
  do {
    sig = Gi_events(p) ;
  }  while (sig < 0) ;

  return sig ;
}

