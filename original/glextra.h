#ifndef GLEXTRA_H
#define GLEXTRA_H

#include "gl.h"
#include "thermalCamera.h"

struct Point{
  int x;
  int y;
};

struct Line{
  struct Point one;
  struct Point two;
};

struct Circle{
  struct Point center;
  int radius;
};

struct Rectangle{
  struct Point one;
  struct Point two;
  struct Point three;
  struct Point four;
};

/*
  Calculate the center of the head from thermal camera data

  @param data     thermal camera data as a pointer to short
  @param rowSize  size of rows and columns
  @return         reference to circle representing the head    
 */
struct Circle* calculateHead(const short* data, int rowSize);
  /* To be implemented in glextra.c */

/*
  Draw circles using the Mid-Point Circle Drawing Algorithm, given
  center coordinates, radius length, and color.

  @param xCenter  x-coordinate of circle center
  @param yCenter  y-coordinate of circle center
  @param radius   length of radius of circle
  @param color    color to draw circle        
 */
void gl_draw_circle(int xCenter, int yCenter, int radius, color_t c);
  /* To be implemented in glextra.c */

/*
  Draw a circle given a Circle struct.

  @param circle   struct for circle data
  @param color    color of circle
 */
void drawCircle(struct Circle circle, color_t color);

/*
  Draw a line given a Line struct.

  @param line     struct for line data
  @param color    color of line
 */
void drawLine(struct Line line, color_t color);

/*
  Display the thermal camera data with colors based on temperature

  @param infraredData   thermal camera data as a pointer to short
  @param rowSize  size of rows and columns
 */
void projectInfraredDataToMonitor(short* infraredData, int rowSize);

#endif
