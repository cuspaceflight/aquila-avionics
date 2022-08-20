/* Daniel Fearn
 *  20/08/22
 *  
 *  Eventually this will contain the flight program for the Aquila-only test flight.
 *  For now it's just testing bits as they are implemented.
 *  
 * 
 */

#include "aquila_interface.h"

AQUILA aquila;

void setup() {
  Serial.begin(9600);
  aquila.begin();
}

void loop() {
  //aquila.update_accel();
  //Serial.println(aquila.get_accel_z(), 4);
  
  if(aquila.poll_baro_ext()){
    Serial.print(aquila.get_ext_temperature());
    Serial.print(", ");
    Serial.println(aquila.get_ext_pressure());
  }
}
