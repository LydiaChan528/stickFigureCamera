#include "thermalCamera.h"
#include "i2c.h"
#include "strings.h"
#include "math.h"

static short bilinearInterpolation(short q11, short q12, short q21, short q22, double x1, double x2, double y1, double y2, double x, double y);

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
in a n x n grid. The inputted size must be a perfect Square!!
 */
void printInfraredData(short *infraredData, int rowSize){
  //display values in 2D array
  for(int i = 0; i < rowSize*rowSize; i++){
    if (i % rowSize == 0) {
      printf("\n");
    }
    printf("[%d.%02d]", (infraredData[i]/4), (infraredData[i]%4)*25);
  }
  printf("\n\n\n");
}

void interpolateSensorData(short* irData, short* ipData, int originalRowSize, int newRowSize){
  short* stretchWide = malloc(originalRowSize * newRowSize);
  //stretchWide
  int irIndex = 0;
  int col = 1;
  for(int i = 0; i < originalRowSize * (newRowSize); i+=2){
    stretchWide[i] = irData[irIndex];
    if(!(col == newRowSize)){
      stretchWide[i+1] = (irData[irIndex] + irData[irIndex+1])/2;
    }
    else{
      col = -1;
      i -= 1;
    }
    col+=2;
    irIndex++;
  }

  //place in values from stretchWide
  int onCol = 1;
  int placeIn = 0;
  for(int i = 0; i < originalRowSize * newRowSize; i++){
    if(onCol % (newRowSize + 1) == 0){
      onCol = 1;
      placeIn += newRowSize;
    }
    ipData[placeIn] = stretchWide[i];
    onCol++;
    placeIn++;
  }
  
  //stretchtall
  int colOn = 1;
  for(int i = newRowSize; i < newRowSize * newRowSize; i++){
    if(colOn % (newRowSize + 1) == 0){
      colOn = 1;
      i += newRowSize;
    }
    ipData[i] = (ipData[i-newRowSize] + ipData[i + newRowSize])/2;
    colOn++;
  }
			      
}


/*

 */
void interpolateSensorData2(short* irData, short* ipData, int originalRowSize, int newRowSize){
  int ipInitializeIndex = 2;
  int placedNums = 1;
  ipData[0] = irData[0];
  //place into interpolated Data the already existing values
  for(int i = 1; i < originalRowSize*originalRowSize; i++){
    if(placedNums == originalRowSize){
      placedNums = 0;
      ipInitializeIndex += newRowSize - 1;
    }
    placedNums++;
    ipData[ipInitializeIndex] = irData[i];
    ipInitializeIndex += 2;
  }
  int rowOn = 0;
  //interpolate data points on the rows that already have existing values
  for(int i = 1; i < newRowSize*newRowSize; i+=2){
    if(i % newRowSize == 0){
      i += newRowSize + 1;
      rowOn += 2;
    }
    short q12;
    short q11;
    short q22;
    short q21;
    short irPoint;
    if(rowOn == newRowSize){
      q12 = ipData[i-1-newRowSize*2];
      q11 = ipData[i-1];
      q22 = ipData[i+1-newRowSize*2];
      q21 = ipData[1+1];
      irPoint = bilinearInterpolation(q11,q12,q21,q22,0.0,2.0,0.0,2.0,1.0,0.0);
    }
    else{
      q11 = ipData[i-1+newRowSize*2];
      q12 = ipData[i-1];
      q21 = ipData[i+1+newRowSize*2];
      q22 = ipData[1+1];
      irPoint = bilinearInterpolation(q11,q12,q21,q22,0.0,2.0,0.0,2.0,1.0,2.0);
    }
    ipData[i] = irPoint;
  }

  int colOn = 1;
  //interpolate data points on remaining gap rows
  for(int i = newRowSize; i < newRowSize*newRowSize; i++){
    if(colOn % (newRowSize + 1) == 0){
      i += newRowSize;
      colOn = 1;
    }
    short q12;
    short q11;
    short q22;
    short q21;
    short irPoint;
    //if on last col
    if(colOn == newRowSize){
      q11 = ipData[i - 2 + newRowSize];
      q12 = ipData[i - 2 - newRowSize];
      q21 = ipData[i + newRowSize];
      q22 = ipData[i - newRowSize];
      irPoint = bilinearInterpolation(q11,q12,q21,q22,0,2,0,2,2,1);
    }
    //do left most interpolation on cubic grid
    else if(i % 2 == 0){
      q11 = ipData[i + newRowSize];
      q12 = ipData[i - newRowSize];
      q21 = ipData[i + 2 + newRowSize];
      q22 = ipData[i + 2 - newRowSize];
      irPoint = bilinearInterpolation(q11,q12,q21,q22,0,2,0,2,0,1);
    }
    else{
      q11 = ipData[i - 1 + newRowSize];
      q12 = ipData[i - 1 - newRowSize];
      q21 = ipData[i + 1 + newRowSize];
      q22 = ipData[i + 1 - newRowSize];
      irPoint = bilinearInterpolation(q11,q12,q21,q22,0,2,0,2,1,1);
    }
    ipData[i] = irPoint;
    colOn++;
  }
  
}

/*

 */
static short bilinearInterpolation(short q11, short q12, short q21, short q22, double x1, double x2, double y1, double y2, double x, double y) 
{
    double delta_X2X1 = x2 - x1;
    double delta_Y2Y1 = y2 - y1;
    double delta_X2X = x2 - x;
    double delta_Y2Y = y2 - y;
    double delta_YY1 = y - y1;
    double delta_XX1 = x - x1;
    return (short) (1.0 / (delta_X2X1 * delta_Y2Y1) * (q11 * delta_X2X * delta_Y2Y +  q21 * delta_XX1 * delta_Y2Y +
        q12 * delta_X2X * delta_YY1 + q22 * delta_XX1 * delta_YY1));
}
