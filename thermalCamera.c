#include "thermalCamera.h"
#include "i2c.h"
#include "strings.h"

/* This function calls upon the i2c driver to read in the 8x8 temperature array that is given by the AMG88xx Thermal Camera.
 */
void getDataFromInfraredSensor(short* data){
  char regL= 0x80;
  char regH= 0x81;
  char lowerByte = 0;
  char upperByte = 0;
  int i = 0;
  
  while (i < 64) {
    //Read lower byte
    i2c_write(0x69, (void *)&regL, 1);
    i2c_read(0x69, &lowerByte, 1); //2
      
    //Read higher byte;
    i2c_write(0x69, (void *)&regH, 1);
    i2c_read(0x69, &upperByte, 1); //2

    //Store bitshifted short
    data[i] = ((lowerByte | ((upperByte & 0x7) << 8)));
    
    regL+=2;
    regH+=2;
    i++;
  }  
  return;
}

/* This function prints out to the user the inputted infrared Data(in Celsius) 
in a n x n grid.
 */
void printInfraredData(short *infraredData, int size){
  //display values in 2D array
  for(int i = 0; i < size; i++){
    if (i % 8 == 0) {
      printf("\n");
    }
    printf("[%d.%02d]", (infraredData[i]/4), (infraredData[i]%4)*25);
  }
  printf("\n\n\n");
}

/*

 */
void interpolateSensorData(){
  return;
}
