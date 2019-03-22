#ifndef GAME_H
#define GAME_H

#include "stickFigure.h"

static struct Circle balls[3];
static int numOfBounds = 4;

//Player Bounds
struct Rectangle headBounds;
struct Rectangle lArmBounds;
struct Rectangle rArmBounds;
struct Rectangle torsoBounds;
//Obstacle Bounds
struct Rectangle obstacleBounds[3];

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
void setGamePieces();

/*

 */
void updateGamePieces();

/*

 */
void updateObstacleBounds();

/*

 */
void drawGamePieces();

/*

 */
int hasCollided();

/*

 */
void gameOver();

#endif
