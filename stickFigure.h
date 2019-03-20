#ifndef STICKFIGURE_H
#define STICKFIGURE_H

#include "glextra.h"

struct Player{
  struct Circle head;
  struct Line torso;
  struct Line leftArm;
  struct Line rightArm;
  struct Line leftLeg;
  struct Line rightLeg;
};

struct Player player;

void drawStickFigure();
  //To be implemented in stickFigure.c

 /*Implementation to update stick figure:
   1) interrupt handler with interrupt as change in motion
   2) called like a "console_print" to refresh stick figure
  */
void updateStickFigure();

#endif
