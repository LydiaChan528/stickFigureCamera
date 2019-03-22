#include "printf.h"
#include "uart.h"
#include "i2c.h"
#include "timer.h"
#include "malloc.h"
#include "gl.h"
#include "glextra.h"
#include "thermalCamera.h"
#include "stickFigure.h"
#include "game.h"

#define THERMAL_SCREEN_SIZE 29
#define THERMAL_BACKGROUND_COLOR GL_BLUE

#define CANVAS_SCREEN_SIZE 150
#define CANVAS_BACKGROUND_COLOR GL_WHITE
#define CANVAS_DRAW_COLOR GL_BLACK

void main(void) 
{
  //initialize 
  uart_init();

  // /*to test*/gl_init(THERMAL_SCREEN_SIZE, THERMAL_SCREEN_SIZE, GL_DOUBLEBUFFER);
  // /*to test*/gl_clear(THERMAL_BACKGROUND_COLOR);

  gl_init(CANVAS_SCREEN_SIZE, CANVAS_SCREEN_SIZE, GL_DOUBLEBUFFER);
  gl_clear(CANVAS_BACKGROUND_COLOR);
  // player_init();
  i2c_init();

  //storage for infraredData
  short* infraredData = malloc(sizeof(short)*64);
  
  setGamePieces();
  //This is the janky working implementation to get data and interpolate it
  while(1){
    //[GET DATA + INTERPOLATE]
    gl_clear(CANVAS_BACKGROUND_COLOR);
    // /*to test*/gl_clear(THERMAL_BACKGROUND_COLOR);


    getDataFromInfraredSensor(infraredData);
    short* interpolatedData15 = malloc(sizeof(short)*15*15);
    interpolateSensorData(infraredData,interpolatedData15,8,15);
    
    short* interpolatedData29 = malloc(sizeof(short)*29*29);
    interpolateSensorData(interpolatedData15,interpolatedData29,15,29);

    // projectInfraredDataToMonitor(interpolatedData29,29);

    // struct Circle* head = (calculateHead(interpolatedData29, 29));
    // printf("HEAD: (%d, %d)\n", head->center.x, head->center.y);
    // struct Circle realHead = { (struct Point){head->center.x, head->center.y}, 4};

    // struct Line* leftRight = (calculateArms(interpolatedData29, 29));
    // printf("LEFT ARM: (%d, %d)\nRIGHT ARM: (%d, %d)\n", leftRight->one.x, leftRight->one.y, leftRight->two.x, leftRight->two.y);
    // struct Circle leftArm = {leftRight->one, 3};
    // struct Circle rightArm = {leftRight->two, 3};

    // drawCircle(realHead, GL_AMBER);
    // drawCircle(leftArm, GL_GREEN);
    // drawCircle(rightArm, GL_GREEN);

    // ACTUAL IMPLEMENTATION OF PROGRAM
    //[STICK FIGURE]
    stickFigure_init(calculateHead(interpolatedData29, 29), calculateArms(interpolatedData29, 29));
    // void stickFigure_init(struct Circle* personHead, struct Line* armLength) {
    updatePlayerBounds();
    drawStickFigure();

    //[OBSTACLE]
    drawGamePieces();
    updateGamePieces();
    updateObstacleBounds();
    if(hasCollided()){
      gameOver();
      break;
    }
    timer_delay_ms(125);

    // // gl_clear(CANVAS_BACKGROUND_COLOR);
    gl_swap_buffer();

  }
}




