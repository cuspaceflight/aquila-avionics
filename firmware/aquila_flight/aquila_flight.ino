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
  Serial.begin(19200);
  aquila.begin();
}

void loop() {
  char timestamp[32];
  aquila.rtc_datetime(timestamp);
  Serial.println(timestamp);
  Serial.println(aquila.rtc_unix());
  delay(500);
  /*
  aquila.update_accel();
  Serial.print(aquila.get_accel_x(), 4);
  Serial.print(", ");
  Serial.print(aquila.get_accel_y(), 4);
  Serial.print(", ");
  Serial.println(aquila.get_accel_z(), 4);
  delay(10);
  */
  
  /*
  if(aquila.poll_baro_ext()){
    Serial.print(aquila.get_ext_temperature());
    Serial.print(", ");
    Serial.print(aquila.get_ext_pressure());
    Serial.print(", ");

    float abs_altitude = 44330*(1-pow((aquila.get_ext_pressure()/1013.25), (1/5.255)));
    Serial.println(abs_altitude);
  }*/
  
  /*
  if(aquila.poll_baro_int()){
    Serial.print(aquila.get_int_temperature());
    Serial.print(", ");
    Serial.print(aquila.get_int_pressure());
    Serial.print(", ");

    float abs_altitude = 44330*(1-pow((aquila.get_int_pressure()/1013.25), (1/5.255)));
    Serial.println(abs_altitude);
  }*/
}
