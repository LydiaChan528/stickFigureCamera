#include "game.h"
#include "glextra.h"
#include "stickFigure.h"
#include "gl.h"


void updatePlayerBounds(){
  //Calculate Bounds for Head
  headBounds = calculateBoundsForCircle(player.head);
  //Calculate Bounds for Arms
  lArmBounds = calculateBoundsForRect(player.leftArm);
  rArmBounds = calculateBoundsForRect(player.rightArm);
  //Calculate Bounds for Torso
  torsoBounds = calculateBoundsForRect(player.torso);

  allBounds[0] = headBounds;
  allBounds[1] = lArmBounds;
  allBounds[2] = rArmBounds;
  allBounds[3] = torsoBounds;
}

void updateObstacleBounds(){
  obstacleBounds = calculateBoundsForCircle(ball);
}

struct Rectangle calculateBoundsForCircle(struct Circle c){

  struct Rectangle circleB;
  circleB.one.x = c.center.x - c.radius;
  circleB.one.y = c.center.y - c.radius;
  circleB.two.x = c.center.x - c.radius;
  circleB.two.y = c.center.y + c.radius;
  circleB.three.x = c.center.x + c.radius;
  circleB.three.y = c.center.y - c.radius;
  circleB.four.x = c.center.x + c.radius;
  circleB.four.y = c.center.y + c.radius;

  return circleB;
}

struct Rectangle calculateBoundsForRect(struct Line line){

  struct Rectangle bounds;
  bounds.one.x = line.one.x;
  bounds.one.y = line.one.y - 1;
  bounds.two.x = line.one.x;
  bounds.two.y = line.one.y + 1;

  bounds.three.x = line.two.x;
  bounds.three.y = line.two.y - 1;
  bounds.four.x = line.two.x;
  bounds.four.y = line.two.y + 1;
 
  return bounds;
}

void setGamePieces(){
  ball.center.x = gl_get_width()/2;
  ball.center.y = 0;
}

void updateGamePieces(){
  ball.center.y += 1;
  //if the ball goes to the bottom of the screen, reset it
  if(ball.center.y >= gl_get_height()){
    ball.center.y = 0;
  }
}

void drawGamePieces(){
  //Draw balls 
  drawCircle(ball.center.x,ball.center.y,ball.radius);
  gl_swap_buffer();
  gl_clear(GL_WHITE);
}

int hasCollided(){
  //iterate through the boundary boxes for collision with game pieces
  for(int i = 0; i < numOfBounds; i++){
    if(hasRectangleCollided(allBounds[i],obstacleBounds)){
      return 1;
    }
  }
  return 0;
}

int hasRectangleCollided(struct Rectangle r1, struct Rectangle r2){
  //test if one rectangle is to the left of another(two is upperLeft, three is   //bottom right)
  if(r1.two.x > r2.three.x || r1.three.x > r2.two.x){
    return 0;
  }
  else if(r1.two.y < r2.three.y || r2.two.y < r1.three.y){
    return 0;
  }
  return 1;
}
