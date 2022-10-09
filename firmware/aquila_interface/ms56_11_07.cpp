/* Daniel Fearn
 *  20/08/2022
 *  
 *  This class handles communication with and calculations for a MS5607 or MS5611 barometer
 *  (theres one slight difference in calculating a reading)
 *  The sensor is connected to SPI1 - the second SPI bus on the controller.
 *  The sensor has a unique way of outputting data. You must:
 *  0. request a temperature reading
 *  1. wait for up to 9ms
 *  2. read temperature reading, request a pressure reading
 *  3. wait for up to 9ms
 *  4. read pressure reading, calculate actual pressure using the two readings and the six factory calibration values
 *  
 *  To make this work without blocking anything, I've made single function that can be polled every loop of the main program
 *  The loop advances the process to the next step if ready, and does nothing otherwise
 *  The function returns true once the final stage is complete and a new pressure/altitude value is available.
 */


#include "Arduino.h"
#include "SPI.h"
#include "ms56_11_07.h"



uint32_t MS56_11_07::begin(byte pin_cs, MS56_type sensor_type) {
  cs = pin_cs;
  spi_speed = 4000000;
  type = sensor_type;

  // reset
  send_command(0x1E);
  uint32_t end_time = millis() + 10;
  while(millis() < end_time){}

  measurement_stage = 0;

  // load factory calibration values
  c[1] = read_reg(0xA2, 2);
  c[2] = read_reg(0xA4, 2);
  c[3] = read_reg(0xA6, 2);
  c[4] = read_reg(0xA8, 2);
  c[5] = read_reg(0xAA, 2);
  c[6] = read_reg(0xAC, 2);

  // return something non-zero to check the chip is alive
  return c[6];
}

bool MS56_11_07::poll_measurement() {
  if (measurement_stage == 0){ // request temp reading
    
    send_command(0x48);
    wait_time = millis() + 9;
    measurement_stage = 1;
    
  } else if (measurement_stage == 1) { // wait for temp reading
    
    if (millis() > wait_time) {measurement_stage = 2;}
    
  } else if (measurement_stage == 2) { // read temp and request pressure
    
    D1 = read_reg(0x00, 3);
    send_command(0x58);
    wait_time = millis() + 9;
    measurement_stage = 3;
    
  } else if (measurement_stage == 3) { // wait for pressure
    
    if (millis() > wait_time) {measurement_stage = 4;}
    
  } else if (measurement_stage == 4) { // read pressure, calculate result
    D2 = read_reg(0x00, 3);
    measurement_stage = 0;

    int64_t dT = D2 - (c[5]*256);
    temperature = 2000 + ((dT*c[6])/8388608);
    float off;
    int64_t sens;

    if (type == MS5607) {
      off = (c[2]*131072) + (c[4] * dT)/64;
      sens  = c[1]*65536 + (c[3] * dT)/128;
    } else { // MS5611
      off = (c[2]*65536) + (c[4] * dT)/128;
      sens = c[1]*32768 + (c[3] * dT)/256;
    }

    pressure = (((D1 * sens)/2097152) - off)/32768;
    return true;
  }

  return false;
}

uint32_t MS56_11_07::read_reg(byte address, uint8_t num_bytes) {
  SPI1.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);
  SPI1.transfer(address);
  uint32_t result = SPI1.transfer(0x00);
  num_bytes--;
  while(num_bytes > 0){
    result = result << 8;
    result = result | SPI1.transfer(0x00);
    num_bytes--;
  }
  digitalWrite(cs, HIGH);
  SPI1.endTransaction();
  return result;
}

uint32_t MS56_11_07::send_command(byte command) {
  SPI1.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);
  unsigned int result = SPI1.transfer(command);
  delay(10);
  digitalWrite(cs, HIGH);
  SPI1.endTransaction();
  return result;
}
