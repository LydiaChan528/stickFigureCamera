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
  char * infraredData = malloc(64);

  //Default address is 0x69

 
  
}



