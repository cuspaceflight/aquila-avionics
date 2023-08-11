#include "Arduino.h"
#include "SPI.h"

#include "rfm95w.h"

RFM95W radio;

enum FlightState {LOCKED, PAD, BURN, COAST, APOGEE, DESCENT, LAND};
const char *StateNames[] = {"LOCKED", "PAD", "BURN", "COAST", "APOGEE", "DESCENT", "LAND"};

struct FlightParams {
  uint32_t unix_time;
  byte  flight_state;
  float accel_x;
  float accel_y;
  float accel_z;

  float int_pressure;
  float int_temperature;

  float imu_accel_x;
  float imu_accel_y;
  float imu_accel_z;
  float imu_gyro_x;
  float imu_gyro_y;
  float imu_gyro_z;

  float est_altitude;
  float est_velocity;

};

FlightParams data;

void setup(){
    Serial.begin(19200);

    radio.begin(4);
    radio.init_receive();
}

void loop(){
    radio.check_received((char*)&data, 64);

    Serial.println(data.unix_time);

    Serial.print("State: ");
    Serial.println(StateNames[(data.flight_state & 0b00000111)]);

    Serial.print("Accelerations (ADXL357): ");
    Serial.print(data.accel_x, 4);
    Serial.print(", ");
    Serial.print(data.accel_y, 4);
    Serial.print(", ");
    Serial.println(data.accel_z, 4);

    Serial.print("Accelerations (MPU6050): ");
    Serial.print(data.imu_accel_x, 4);
    Serial.print(", ");
    Serial.print(data.imu_accel_y, 4);
    Serial.print(", ");
    Serial.println(data.imu_accel_z, 4);

    Serial.print("Pyro armed: ");
    Serial.println(data.flight_state >> 7);
    Serial.print("Pyro continuities: ");
    Serial.print((data.flight_state & 0b01000000) >> 6);
    Serial.print(", ");
    Serial.print((data.flight_state & 0b00100000) >> 5);
    Serial.print(", ");
    Serial.print((data.flight_state & 0b00010000) >> 4);
    Serial.print(", ");
    Serial.println((data.flight_state & 0b00001000) >> 3);

    Serial.print("Gyroscopes: ");
    Serial.print(data.imu_gyro_x, 4);
    Serial.print(", ");
    Serial.print(data.imu_gyro_y, 4);
    Serial.print(", ");
    Serial.println(data.imu_gyro_z, 4);
    
    Serial.print("Internal barometer: ");
    Serial.print(data.int_pressure);
    Serial.print(", ");
    Serial.println(data.int_temperature);

    Serial.print("Velocity estimate: ");
    Serial.println(data.est_velocity, 4);
    Serial.print("Altitude estimate: ");
    Serial.println(data.est_altitude, 4);

    Serial.println();
    Serial.println();

    delay(50);
}