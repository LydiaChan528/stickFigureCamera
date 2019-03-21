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
#define THERMAL_BACKGROUND_COLOR GL_BLACK

#define CANVAS_SCREEN_SIZE 150
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
    // timer_delay_ms(500);
    struct Circle* head = calculateHead(interpolatedData29, 29); 
    // printf("HEAD cntr (%d,%d), rad=%d\n", head->center.x, head->center.y, head->radius);
    gl_clear(THERMAL_BACKGROUND_COLOR);
    drawCircle((THERMAL_SCREEN_SIZE - head->center.x), head->center.y, head->radius, GL_AMBER);
    gl_swap_buffer();


    //draw Stick Figure
    // gl_clear(GL_WHITE);
    // struct Circle* head = calculateHead(interpolatedData29, 29); 
    // struct Point figureHeadCenter = { (THERMAL_SCREEN_SIZE - head->center.x), ((2*THERMAL_SCREEN_SIZE/3) + head->center.y - head->radius)};
    // struct Circle figureHead = { figureHeadCenter, head->radius };
    // // drawCircle(figureHead.center.x, figureHead.center.y, figureHead.radius, CANVAS_DRAW_COLOR);

    // int axis = figureHead.center.x;
    // int head_ctr = figureHead.center.y;
    // int head_rad = figureHead.radius;//3
    // int body_lng = (4*figureHead.radius);//12
    // int leg_wid = (figureHead.radius+1);//4
    // int leg_lng = (2*figureHead.radius);//6
    // drawCircle(axis, head_ctr, head_rad, GL_BLACK);
    // gl_draw_line(axis, (head_ctr+head_rad), axis, (head_ctr+head_rad+body_lng), GL_BLACK);//torso
    // gl_draw_line(axis, (head_ctr+head_rad+body_lng), axis-leg_wid, (head_ctr+head_rad+body_lng+leg_lng), GL_BLACK);//left leg
    // gl_draw_line(axis, (head_ctr+head_rad+body_lng), axis+leg_wid, (head_ctr+head_rad+body_lng+leg_lng), GL_BLACK);//right leg
    // gl_draw_line(axis, (head_ctr+head_rad)+(body_lng/4), axis-leg_wid, (head_ctr+head_rad)+(body_lng/2)+1, GL_BLACK);//left arm
    // gl_draw_line(axis, (head_ctr+head_rad)+(body_lng/4), axis+leg_wid, (head_ctr+head_rad)+(body_lng/2)+1, GL_BLACK);//right arm
    // gl_swap_buffer();

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



