#include "printf.h"
#include "uart.h"
#include "i2c.h"
#include "gl.h"
#include "glextra.h"
// #include "fb.h"
#include "malloc.h"
#include "thermalCamera.h"
#include "timer.h"


void main(void) 
{
  //initialize 
  uart_init();
  gl_init(29, 29, GL_DOUBLEBUFFER);
  i2c_init();

  //storage for infraredData
  short* infraredData = malloc(sizeof(short)*64);
 
  
  while(1){
    getDataFromInfraredSensor(infraredData);
    //printInfraredData(infraredData,8);
    short* interpolatedData15 = malloc(sizeof(short)*15*15);
    interpolateSensorData(infraredData,interpolatedData15,8,15);
    // printInfraredData(infraredData,8);
    // printInfraredData(interpolatedData15,15);

    short* interpolatedData29 = malloc(sizeof(short)*29*29);
    interpolateSensorData(interpolatedData15,interpolatedData29,15,29);

    projectInfraredDataToMonitor(interpolatedData29,29);
    //timer_delay(5);
    //projectInfraredDataToMonitor(interpolatedData15,15);
    }
  

  //drawCircle(20,20,5);
  //gl_swap_buffer();
}



