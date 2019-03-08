#include "printf.h"
#include "uart.h"
#include "i2c.h"
#include "gl.h"

 /*Set up the necessary functions to test and display the basic input that 
  we get from the infrared thermal sensor(Let's move these functions into it's
  own driver file when we finish it*/
void getDataFromInfraredSensor(){

  
}


/* This function assigns a different color based on subjective threshholds on infrared data values
 */
void projectInfraredDataOntoMonitor(){

}

void main(void) 
{
  uart_init();
  printf("Hello, world!\n");
  gl_init(50,50,0);

 
  
}



