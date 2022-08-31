/* Daniel Fearn
 *  20/08/22
 *  
 *  Eventually this will contain the flight program for the Aquila-only test flight.
 *  For now it's just testing bits as they are implemented.
 *  
 * 
 */

#define SEA_LEVEL 1029

#include "aquila_interface.h"

AQUILA aquila;


void setup() {
  Serial.begin(19200);
  aquila.begin();
}

void loop() {
  aquila.update_accel();
  aquila.update_imu();
  aquila.poll_baro_ext();
  aquila.poll_baro_int();

  char timestamp[32];
  aquila.rtc_datetime(timestamp);
  Serial.println(timestamp);

  Serial.print("Accelerations (ADXL357): ");
  Serial.print(aquila.get_accel_x(), 4);
  Serial.print(", ");
  Serial.print(aquila.get_accel_y(), 4);
  Serial.print(", ");
  Serial.println(aquila.get_accel_z(), 4);

  Serial.print("Accelerations (MPU6050): ");
  Serial.print(aquila.get_imu_accel_x(), 4);
  Serial.print(", ");
  Serial.print(aquila.get_imu_accel_y(), 4);
  Serial.print(", ");
  Serial.println(aquila.get_imu_accel_z(), 4);

  Serial.print("Gyroscopes: ");
  Serial.print(aquila.get_imu_gyro_x(), 4);
  Serial.print(", ");
  Serial.print(aquila.get_imu_gyro_y(), 4);
  Serial.print(", ");
  Serial.println(aquila.get_imu_gyro_z(), 4);

  Serial.print("External barometer: ");
  Serial.print(aquila.get_ext_temperature());
  Serial.print(", ");
  Serial.print(aquila.get_ext_pressure());
  Serial.print(", ");
  Serial.println(abs_altitude(aquila.get_ext_pressure()));
  
  Serial.print("Internal barometer: ");
  Serial.print(aquila.get_int_temperature());
  Serial.print(", ");
  Serial.print(aquila.get_int_pressure());
  Serial.print(", ");
  Serial.println(abs_altitude(aquila.get_int_pressure()));

  Serial.print("Battery voltage: ");
  Serial.println(aquila.get_batt_voltage());

  Serial.println();

}

float abs_altitude(float pressure) {
  return 44330*(1-pow((pressure/SEA_LEVEL), (1/5.255)));
}