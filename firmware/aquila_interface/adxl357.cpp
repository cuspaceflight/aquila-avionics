/* Daniel Fearn
 *  20/08/22
 *  
 *  This class handles communication with and calculations for ADXL357 accelerometer.
 *  The accelerometer is connected to SPI - the first SPI bus on the controller.
 *  The accelerometer is locked in it's highest range setting of +/-40g
 *  Changing the range on the fly makes the code more complex and may introduce calibration issues so I haven't done that
 * 
 *  Calibration values in the header file must be determined separately.
 */

#include "adxl357.h"

byte ADXL357::begin(byte pin_cs, int32_t cals[6]) {
  cs = pin_cs;
  calibrations[0] = cals[0];
  calibrations[1] = cals[1];
  calibrations[2] = cals[2];
  calibrations[3] = cals[3];
  calibrations[4] = cals[4];
  calibrations[5] = cals[5];

  spi_speed = 10000000;
  write_reg(0x28, 0b00000010);
  write_reg(0x2C, 0b10000011);
  write_reg(0x2D, 0b00000000);
  return read_reg(0x00, 1);
}

void ADXL357::read_measurement() {
  int32_t raw_x = (read_reg(0x08, 3)<<8);
  int32_t raw_y = (read_reg(0x0B, 3)<<8);
  int32_t raw_z = (read_reg(0x0E, 3)<<8);
  
  x_g = (raw_x/4096.0 - calibrations[1]) / (float)calibrations[0];
  y_g = (raw_y/4096.0 - calibrations[3]) / (float)calibrations[2];
  z_g = (raw_z/4096.0 - calibrations[5]) / (float)calibrations[4];
}

uint32_t ADXL357::read_reg(byte address, uint8_t num_bytes) {
  byte r_command = (address << 1) + 1;
  SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);
  SPI.transfer(r_command);
  uint32_t result = SPI.transfer(0x00);
  num_bytes--;
  while(num_bytes > 0){
    result = result << 8;
    result = result | SPI.transfer(0x00);
    num_bytes--;
  }
  digitalWrite(cs, HIGH);
  SPI.endTransaction();
  return result;
}

uint32_t ADXL357::write_reg(byte address, byte data){
  byte w_command = address << 1;
  SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);
  SPI.transfer(w_command);
  uint32_t result = SPI.transfer(data);
  digitalWrite(cs, HIGH);
  SPI.endTransaction();
  return result;
}
