#ifndef THERMALCAMERA_H
#define THERMALCAMERA_H


/*Set up the necessary functions to test and display the basic input that 
   we get from the infrared thermal sensor.
 */
void getDataFromInfraredSensor(short* data);
  //To be implemented in thermalCamera.c


/*Interpolate the 8x8 array that we get from the infrared data in order to 
faciliate more precise calculations
 */
void interpolateSensorData2(short* irData, short* ipData, int originalRowSize, int newRowSize);

void interpolateSensorData(short* irData, short* ipData, int originalRowSize, int newRowSize);

void printInfraredData(short *infraredData, int rowSize);
#endif
