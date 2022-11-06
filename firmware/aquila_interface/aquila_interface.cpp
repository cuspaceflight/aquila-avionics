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
  Wire.begin();

  pinMode(pin_accel_cs, OUTPUT);
  pinMode(pin_accel_drdy, INPUT);

  pinMode(pin_baro_ext_cs, OUTPUT);
  pinMode(pin_baro_cs, OUTPUT);

  pinMode(pin_batt_v, INPUT);
  pinMode(pin_pyro_arm, OUTPUT);
  digitalWrite(pin_pyro_arm, HIGH);

  pinMode(pin_pyro_cont1, INPUT);
  pinMode(pin_pyro_cont2, INPUT);
  pinMode(pin_pyro_cont3, INPUT);
  pinMode(pin_pyro_cont4, INPUT);

  pinMode(pin_pyro1, OUTPUT);
  pinMode(pin_pyro2, OUTPUT);
  pinMode(pin_pyro3, OUTPUT);
  pinMode(pin_pyro4, OUTPUT);
  digitalWrite(pin_pyro1, LOW);
  digitalWrite(pin_pyro2, LOW);
  digitalWrite(pin_pyro3, LOW);
  digitalWrite(pin_pyro4, LOW);

  sv1.attach(pin_servo1);
  sv2.attach(pin_servo2);
  sv3.attach(pin_servo3);
  sv4.attach(pin_servo4);

  int32_t adxl357_calibration[] = {accel_x_sens, accel_x_offset, accel_y_sens, accel_y_offset, accel_z_sens, accel_z_offset};
  int32_t mpu6050_calibration[] = {imu_ax_sens, imu_ax_offset, imu_ay_sens, imu_ay_offset, imu_az_sens, imu_az_offset, imu_gx_offset, imu_gy_offset, imu_gz_offset};

  // initialise Teensy 4.1 Real-Time Clock
  if(!rtc.begin()) {
    Serial.println("Real-Time Clock not set");
    //while(1){}
  }

  // initialise sensors and simply check they are alive
  if(accel.begin(pin_accel_cs, adxl357_calibration) != 0xAD){
    Serial.println("Accelerometer error");
    //while(1){}
  }

  if(baro_ext.begin(pin_baro_ext_cs, MS5607) == 65535){
    Serial.println("External barometer error");
    //while(1){}
  }

  if(baro.begin(pin_baro_cs, MS5611) == 65535){
    Serial.println("Onboard barometer error");
    //while(1){}
  }

  if(imu.begin(mpu6050_calibration) != 104) {
    Serial.println("MPU6050 error");
    // while(1){}
  }
  
}

// ---------- Real-Time Clock ----------
void AQUILA::rtc_datetime(char* outstr) { rtc.get_datetime(outstr); }
uint32_t AQUILA::rtc_unix() { return rtc.get_unix(); }

// ---------- ADXL357 accelerometer ----------
void AQUILA::update_accel() { accel.read_measurement(); }
float AQUILA::get_accel_x() { return accel.x_g; }
float AQUILA::get_accel_y() { return accel.y_g; }
float AQUILA::get_accel_z() { return accel.z_g; }

// ---------- External and onboard barometers ----------
bool AQUILA::poll_baro_ext() { return baro_ext.poll_measurement(); }
float AQUILA::get_ext_temperature() { return baro_ext.temperature/100.0; }
float AQUILA::get_ext_pressure() { return baro_ext.pressure/100.0; }

bool AQUILA::poll_baro_int() { return baro.poll_measurement(); }
float AQUILA::get_int_temperature() { return baro.temperature/100.0; }
float AQUILA::get_int_pressure() { return baro.pressure/100.0; }

// ---------- MPU6050 IMU ----------
void AQUILA::update_imu() { imu.read(); }
float AQUILA::get_imu_accel_x() { return imu.accel_x; }
float AQUILA::get_imu_accel_y() { return imu.accel_y; }
float AQUILA::get_imu_accel_z() { return imu.accel_z; }
float AQUILA::get_imu_gyro_x() { return imu.gyro_x; }
float AQUILA::get_imu_gyro_y() { return imu.gyro_y; }
float AQUILA::get_imu_gyro_z() { return imu.gyro_z; }

// ---------- Battery voltage measurement ----------
float AQUILA::get_batt_voltage() { return analogRead(pin_batt_v)/1024.0 * 3.2 * 3; }

// ---------- Pyrotechnics ----------
void AQUILA::arm_pyro() { 
  digitalWrite(pin_pyro_arm, LOW); 
  pyro_armed = true;
}
void AQUILA::disarm_pyro() {
  digitalWrite(pin_pyro_arm, HIGH);
  digitalWrite(pin_pyro1, LOW);
  digitalWrite(pin_pyro2, LOW);
  digitalWrite(pin_pyro3, LOW);
  digitalWrite(pin_pyro4, LOW);
  pyro_armed = false;
}
bool AQUILA::pyro_is_armed() { return pyro_armed; }

bool AQUILA::pyro_continuity(uint8_t pyro_number) {
  if (!pyro_armed) { return false; }
  switch (pyro_number) {
  case 1:
    return !digitalRead(pin_pyro_cont1);
    break;
  case 2:
    return !digitalRead(pin_pyro_cont2);
    break;
  case 3:
    return !digitalRead(pin_pyro_cont3);
    break;
  case 4:
    return !digitalRead(pin_pyro_cont4);
    break;
  default:
    return false;
    break;
  }
}

bool AQUILA::fire_pyro(uint8_t pyro_number) {
  if (!pyro_armed) { return false; }
  switch (pyro_number) {
  case 1:
    digitalWrite(pin_pyro_cont1, HIGH);
    break;
  case 2:
    digitalWrite(pin_pyro_cont2, HIGH);
    break;
  case 3:
    digitalWrite(pin_pyro_cont3, HIGH);
    break;
  case 4:
    digitalWrite(pin_pyro_cont4, HIGH);
    break;
  default:
    return false;
    break;
  }
  return true;
}

void AQUILA::move_all_servos(uint8_t angle) {
  sv1.write(angle);
  sv2.write(angle);
  sv3.write(angle);
  sv4.write(angle);
}