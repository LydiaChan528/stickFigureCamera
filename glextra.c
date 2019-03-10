#include "glextra.h"
#include "gl.h"

/* Helper function to drawCircle(). This function draws in all 8 octaves of a 
circle derived from Bresenham's Circle Algorithm.
 */
static void drawOctave(int xc, int yc, int x, int y, color_t c) 
{ 
    gl_draw_pixel(xc+x, yc+y, c); 
    gl_draw_pixel(xc-x, yc+y, c); 
    gl_draw_pixel(xc+x, yc-y, c); 
    gl_draw_pixel(xc-x, yc-y, c); 
    gl_draw_pixel(xc+y, yc+x, c); 
    gl_draw_pixel(xc-y, yc+x, c); 
    gl_draw_pixel(xc+y, yc-x, c); 
    gl_draw_pixel(xc-y, yc-x, c); 
} 
  
// Function for circle-generation 
// using Bresenham's algorithm 
void drawCircle(int x_center, int y_center, int radius) 
{ 
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    drawOctave(xCenter, yCenter, x, y); 
    while (y >= x) 
    { 
      // for each pixel we will 
      // draw all eight pixels 
      x++; 
      // check for decision parameter 
      // and correspondingly  
      // update d, x, y 
      if (d > 0) 
        { 
	  y--;  
	  d = d + 4 * (x - y) + 10; 
        } 
      else{
	d = d + 4 * x + 6; 
	drawCircle(xc, yc, x, y); 
        delay(50); 
      }
    } 
} 
