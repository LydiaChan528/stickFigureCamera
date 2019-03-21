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
#define THERMAL_BACKGROUND_COLOR GL_WHITE
#define CANVAS_SCREEN_SIZE 100
#define CANVAS_BACKGROUND_COLOR GL_WHITE
#define CANVAS_DRAW_COLOR GL_BLACK

void main(void) 
{
  //initialize 
  uart_init();
  gl_init(THERMAL_SCREEN_SIZE, THERMAL_SCREEN_SIZE, GL_DOUBLEBUFFER);
  gl_clear(THERMAL_BACKGROUND_COLOR);
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
    // printInfraredData(interpolatedData29,29);
    projectInfraredDataToMonitor(interpolatedData29,29);

    // [GRAPHICS] Test calculate and draw head
    struct Circle* head = calculateHead(interpolatedData29, 29); 
    // printf("HEAD cntr (%d,%d), rad=%d\n", head->center.x, head->center.y, head->radius);
    gl_clear(THERMAL_BACKGROUND_COLOR);
    drawCircle((THERMAL_SCREEN_SIZE - head->center.x), head->center.y, head->radius, GL_AMBER);
    gl_swap_buffer();
    // timer_delay_ms(500);

    }
  
  /*
  //[GAME] sucessfully tested beginning implementation of balls falling
  setGamePieces();
  while(1){
    drawGamePieces();
    updateGamePieces();
    timer_delay(2);
  }
  */

  /*
  //[GRAPHICS] TEST struct for head
  char* testString = "abcd";
  struct Circle* head = calculateHead(testString);
  printHead();

  //TEST amber square with two circles
  gl_clear(GL_AMBER);
  gl_draw_rect(3, 3, 23, 23, GL_RED);
  drawCircle(8, 8, 5, GL_BLACK);
  drawBetterCircle(18, 18, 5, GL_BLACK);
  gl_swap_buffer();
  */
}



