#include "printf.h"
#include "uart.h"
#include "i2c.h"
#include "gl.h"
// #include "fb.h"
#include "malloc.h"
#include "thermalCamera.h"


void main(void) 
{
  //initialize 
  uart_init();
  gl_init(50, 50, GL_DOUBLEBUFFER);
  i2c_init();

  //storage for infraredData
  short* infraredData = malloc(sizeof(short)*64);
   
  getDataFromInfraredSensor(infraredData);
  printInfraredData(infraredData,64);
 
}



