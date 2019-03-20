#include "glextra.h"
#include "gl.h"
#include "timer.h"
#include "printf.h"
#include "math.h"

struct Circle* head;


/*Draw circles with Mid-Point Algorithm*/
void drawCircle(int xCenter, int yCenter, int radius, color_t c) {
  int x = radius;
  int y = 0;

  //draw 4 outerpoints
  gl_draw_pixel(xCenter+x, yCenter+y, c);
  gl_draw_pixel(xCenter+y, yCenter+x, c);
  gl_draw_pixel(xCenter-x, yCenter-y, c);
  gl_draw_pixel(xCenter-y, yCenter-x, c);
  
  int P = (1-radius);
  while (x > y) {
    y++;

    if (P <= 0) {
      P += (2*y + 1);
    } else {
      x--;
      P += (2*y - 2*x + 1);
    }

    if (x < y) {
      break;
    }

    //draw point in all four quadrants
    gl_draw_pixel(xCenter+x, yCenter+y, c);
    gl_draw_pixel(xCenter-x, yCenter+y, c);
    gl_draw_pixel(xCenter+x, yCenter-y, c);
    gl_draw_pixel(xCenter-x, yCenter-y, c);

    if (x != y) {
      //draw reflected point over y=x in all four quadrants
      gl_draw_pixel(xCenter+y, yCenter+x, c);
      gl_draw_pixel(xCenter-y, yCenter+x, c);
      gl_draw_pixel(xCenter+y, yCenter-x, c);
      gl_draw_pixel(xCenter-y, yCenter-x, c);
    }

  }

}

/*

 */
struct Circle* calculateHead(const char* data){
  // struct Circle* head = (struct Circle*)malloc(sizeof(struct Circle)); //malloc
  head->radius = 0;
  struct Point headCenter = {15, 15};
  head->center = headCenter;
  return head;
  /* To be implemented in glextra.c */
}

void printHead() {
  printf("HEAD cntr (%d,%d), rad=%d\n", head->center.x, head->center.y, head->radius);
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
    unsigned char green = 0;//test
    unsigned char blue = 0;
    if(*infraredData/4 > 24) {
      green = *infraredData;
    } else if(*infraredData/4 > 22){
      red = *infraredData;
    } else{
      blue = *infraredData;
    }
    gl_draw_pixel(col%rowSize,row,gl_color(red,green,blue));
    infraredData++; 
  }
  gl_swap_buffer();
}



// /* Helper function to drawCircle(). This function draws in all 8 octaves of a 
// circle derived from Bresenham's Circle Algorithm.
//  */
// static void drawOuterPoints(int xc, int yc, int x, int y, color_t color) {
//   gl_draw_pixel(xc+x, yc+y, color);
//   gl_draw_pixel(xc-x, yc+y, color);
//   gl_draw_pixel(xc+x, yc-y, color);
//   gl_draw_pixel(xc-x, yc-y, color);
//   gl_draw_pixel(xc+y, yc+x, color);
//   gl_draw_pixel(xc-y, yc+x, color);
//   gl_draw_pixel(xc+y, yc-x, color);
//   gl_draw_pixel(xc-y, yc-x, color);
// }

// /*Draw circles using Bresenham's algorithm*/
// void drawCircle(int xCenter, int yCenter, int radius, color_t c) {
//   int x = 0;
//   int y = radius;
//   int decision = 3 - (2*radius);
//   drawOuterPoints(xCenter, yCenter, x, y, c);

//   while (y > x) {
//     x++;
//     if (decision > 0) {
//       y--;
//       decision += (4*(x-y) + 10);
//     } else {
//       decision += ((4*x) + 6);
//     }
//     drawOuterPoints(xCenter, yCenter, x, y, c);
//   } 
// }

