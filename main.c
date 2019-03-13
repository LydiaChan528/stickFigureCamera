#include "printf.h"
#include "uart.h"
#include "i2c.h"
#include "gl.h"
// #include "fb.h"
#include "malloc.h"
#include "thermalCamera.h"


/* This function assigns a different color based on subjective threshholds on infrared data values
 */
void projectInfraredDataOntoMonitor(){

}

void main(void) 
{
  //initialize 
  //uart_init();
  //gl_init(50, 50, GL_SINGLEBUFFER);
  i2c_init();
  //printf("Hello, world!\n");

  short* infraredData = malloc(sizeof(short)*64);

  //TEST read one value
  //while (1) {
    char regL= 0x80;
    char regH= 0x81;
    int i = 0;

    while (i < 64) {
      //i2c_read(0x69, infraredData, 2);
      //printf("after read\n");
      char data1 = 0;
      i2c_write(0x69, (void *)&regL, 1);
      i2c_read(0x69, &data1, 1); //2

      

  // char* infraredDataH = malloc(64);
      char data2 = 0;
      i2c_write(0x69, (void *)&regH, 1);
      i2c_read(0x69, &data2, 1); //2
      // i2c_read(0x80 + 1, infraredData + 1, 2);

      infraredData[i] = ((data1 | ((data2 & 0x7) << 8)));

      // printf("Read: %x\n", *((unsigned int *)infraredData)); 

      regL+=2;
      regH+=2;
      i++;
    } 

  // //access data from thermal camera over I2C
  // char* infraredData = malloc(64);
  // // *infraredData = 'c';
  // getDataFromInfraredSensor(infraredData);

  //display values in 2D array
  for(int i = 0; i < 64; i++){
    if (i % 8 == 0) {
      printf("\n");
    }
    // printf("[%d]",*infraredData);
    // infraredData++;
    printf("[%d.%02d]", (infraredData[i]/4), (infraredData[i]%4)*25);
  }

  printf("\n\n\n");
  // //Default address is 0x69

 
  //printf("\n\nAccess complete!\n");
}



