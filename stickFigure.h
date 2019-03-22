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

/*
  Draw a stick figure by its components: head, torso, legs, and arms.
 */
void drawStickFigure();

/*
  Update dimensions and location of stick figure on screen, 
  based on thermal camera inputs and head location.

  @param personHead   head location on which to base stick figure location
  @param screenSize   size of frame that stick figure is drawn in
 */
void updateStickFigure();

void stickFigure_init(struct Circle* personHead, int screenSize);

#endif
