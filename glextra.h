#ifndef GLEXTRA_H
#define GLEXTRA_H

#include "gl.h"
#include "thermalCamera.h"

struct Line{
  int x1;
  int y1;
  int x2;
  int y2;
};

struct Circle{
  int xCenter;
  int yCenter;
  int radius;
};

/*

 */
void drawStickFigure();
  /* To be implemented in glextra.c */

/*

 */
struct Circle* calculateHead(const char* data);
  /* To be implemented in glextra.c */


/*

 */
void drawCircle(int xCenter, int yCenter, int radius);
  /* To be implemented in glextra.c */

/*

 */
void projectInfraredDataToMonitor(short* infraredData, int rowSize);

#endif
