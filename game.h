#ifndef GAME_H
#define GAME_H

#include "stickFigure.h"

static struct Circle ball;
static int numOfBounds = 4;

//Player Bounds
struct Rectangle headBounds;
struct Rectangle lArmBounds;
struct Rectangle rArmBounds;
struct Rectangle torsoBounds;
//Obstacle Bounds
struct Rectangle obstacleBounds;

struct Rectangle allBounds[4];


/*

 */
int hasRectangleCollided(struct Rectangle one, struct Rectangle two);

/*

 */
struct Rectangle calculateBoundsForCircle(struct Circle c);

/*

 */
struct Rectangle calculateBoundsForRect(struct Line line);

/*

 */
void updatePlayerBounds();

/*

 */
void updateGamePieces();

/*

 */
void drawGamePieces();

/*

 */
void hasCollided();


#endif
