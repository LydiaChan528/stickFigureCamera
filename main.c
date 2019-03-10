#include "printf.h"
#include "uart.h"
#include "i2c.h"
#include "gl.h"
#include "malloc.h"
#include "thermalCamera.h"


/* This function assigns a different color based on subjective threshholds on infrared data values
 */
void projectInfraredDataOntoMonitor(){

}

void main(void) 
{
  uart_init();
  printf("Hello, world!\n");
  gl_init(50,50,0);
  //i2c_init();

  char* infraredData = malloc(64);
  *infraredData = 'c';
  getDataFromInfraredSensor(infraredData);
  for(int i = 0; i < 64; i++){
    printf("%c",*infraredData);
    infraredData++;
  }

  //Default address is 0x69

 
  
}



