#include "glextra.h"
#include "gl.h"
#include "timer.h"
#include "math.h"

/* Helper function to drawCircle(). This function draws in all 8 octaves of a 
circle derived from Bresenham's Circle Algorithm.
 */
static void drawOuterPoints(int xc, int yc, int x, int y, color_t color) {
  gl_draw_pixel(xc+x, yc+y, color);
  gl_draw_pixel(xc-x, yc+y, color);
  gl_draw_pixel(xc+x, yc-y, color);
  gl_draw_pixel(xc-x, yc-y, color);
  gl_draw_pixel(xc+y, yc+x, color);
  gl_draw_pixel(xc-y, yc+x, color);
  gl_draw_pixel(xc+y, yc-x, color);
  gl_draw_pixel(xc-y, yc-x, color);
}

/*Draw circles using Bresenham's algorithm*/
void drawCircle(int xCenter, int yCenter, int radius, color_t c) {
  int x = 0;
  int y = radius;
  int decision = 3 - (2*radius);
  drawOuterPoints(xCenter, yCenter, x, y, c);

  while (y > x) {
    x++;
    if (decision > 0) {
      y--;
      decision += (4*(x-y) + 10);
    } else {
      decision += ((4*x) + 6);
    }
    drawOuterPoints(xCenter, yCenter, x, y, c);
  } 
}


/*

 */
struct Circle* calculateHead(const char* data){
  struct Circle* head;
  return head;
  /* To be implemented in glextra.c */
}

void projectInfraredDataToMonitor(short* infraredData, int rowSize){
  gl_clear(GL_WHITE);
  int row = 0;
  //TO:DO GET MATH LIB TO WORK SO THIS BECOMES MORE DYNAMIC, not(col % constant)
  for(int col = 0; col < rowSize*rowSize; col++){
    if(col % rowSize == 0 && col > 0){
      row++;
    }
    //Quik maths
    unsigned char red = 0;
    unsigned char blue = 0;
    if(*infraredData/4 > 22){
      red = *infraredData;
    }
    else{
      blue = *infraredData;
    }
    gl_draw_pixel(col%rowSize,row,gl_color(red,0,blue));
    infraredData++; 
  }
  gl_swap_buffer();
}

