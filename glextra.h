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

 */
struct Circle* calculateHead(const char* data);
  /* To be implemented in glextra.c */


/*
 Draw a circle with a given center, radius, and color.
 */
void drawCircle(int xCenter, int yCenter, int radius, color_t c);
  /* To be implemented in glextra.c */

/*

 */
void projectInfraredDataToMonitor(short* infraredData, int rowSize);

#endif
