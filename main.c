#include "printf.h"
#include "uart.h"
#include "i2c.h"
#include "gl.h"
#include "glextra.h"
#include "malloc.h"
#include "thermalCamera.h"
#include "timer.h"
#include "game.h"
#include "stickFigure.h"


void main(void) 
{
  //initialize 
  uart_init();
  gl_init(29, 29, GL_DOUBLEBUFFER);
  // gl_clear(GL_WHITE);
  i2c_init();

  //storage for infraredData
  short* infraredData = malloc(sizeof(short)*64);
 
  
  //This is the janky working implementation to get data and interpolate it
  while(1){
    getDataFromInfraredSensor(infraredData);
    short* interpolatedData15 = malloc(sizeof(short)*15*15);
    interpolateSensorData(infraredData,interpolatedData15,8,15);
    
    short* interpolatedData29 = malloc(sizeof(short)*29*29);
    interpolateSensorData(interpolatedData15,interpolatedData29,15,29);

    // printInfraredData(infraredData,8);
    // printInfraredData(interpolatedData15,15);
    projectInfraredDataToMonitor(interpolatedData29,29);
    }

  
  /*
  //sucessfully tested beginning implementation of balls falling
  setGamePieces();
  while(1){
    drawGamePieces();
    updateGamePieces();
    timer_delay(2);
  }
  */

}



