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

    //[STICK FIGURE]
    stickFigure_init(calculateHead(interpolatedData29, 29), calculateArms(interpolatedData29, 29));
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




