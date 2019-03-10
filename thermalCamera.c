#include "thermalCamera.h"
#include "i2c.h"
#include "strings.h"

/*

 */
void getDataFromInfraredSensor(char* data){
  i2c_init();
  i2c_read(0x69, data,5);
}

/*

 */
void interpolateSensorData(){

}
