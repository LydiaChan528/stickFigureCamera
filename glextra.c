#include "glextra.h"
#include "gl.h"
#include "timer.h"

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
void drawCircle(int xCenter, int yCenter, int radius) 
{ 
    int x = 0, y = radius; 
    int d = 3 - 2 * radius; 
    drawOctave(xCenter, yCenter, x, y, GL_BLUE); 
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
	drawOctave(xCenter, yCenter, x, y,GL_BLUE); 
        timer_delay_us(50); 
      }
    } 
}

/*

 */
void drawStickFigure(){
  /* To be implemented in glextra.c */
}

struct Circle* calculateHead(const char* data){
  struct Circle* head;
  return head;
  /* To be implemented in glextra.c */
}

void projectInfraredDataToMonitor(short* infraredData, int size){

}

