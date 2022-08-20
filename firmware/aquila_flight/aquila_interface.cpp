/* Daniel Fearn
 *  20/08/22
 *  
 *  This class organises all the sensors and actuators on the Aquila Flight Computer into a single interface.
 *  This has a few benefits:
 *  - Calculations and communication protocols are abstracted away so main flight code is super clean
 *  - Individual sensor classes can be copy-pasted into new projects
 *  - The interface can be swapped for one with dummy sensors to run hardware-in-the-loop (HIL) tests against simulated flights
 */

#include "aquila_interface.h"

void AQUILA::begin(){
  SPI.begin();
  SPI1.begin();

  pinMode(pin_accel_cs, OUTPUT);
  pinMode(pin_accel_drdy, INPUT);

  pinMode(pin_baro_ext_cs, OUTPUT);

  // initialise sensors and simply check they are alive
  if(accel.begin(pin_accel_cs) != 173){
    Serial.println("Accelerometer error");
    while(1){}
  }
  if(baro_ext.begin(pin_baro_ext_cs) == 0){
    Serial.println("Barometer error");
    while(1){}
  }
  
}

void AQUILA::update_accel() { accel.read_measurement(); }
float AQUILA::get_accel_x() { return accel.x_g; }
float AQUILA::get_accel_y() { return accel.y_g; }
float AQUILA::get_accel_z() { return accel.z_g; }

bool AQUILA::poll_baro_ext() { return baro_ext.poll_measurement(); }
float AQUILA::get_ext_temperature() { return baro_ext.temperature/100.0; }
float AQUILA::get_ext_pressure() { return baro_ext.pressure/100.0; }
