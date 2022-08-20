/*
 * Teensy 4.1
 * 
 * ADXL375 on SPI1 port:
 * MOSI - 11
 * MISO - 12
 * SCLK - 13
 * CS - 2
 * DRDY - 30
 * 
 */

 /* Settings 
  *  filter settings - 0x28: 00000010 - no high pass filter, output data rate 1kHz with lowpass corner at 250Hz
  *  range settings - 0x2C: 10000011 - I2C and interrup settings default, range to +/- 40g
  *  power control - 0x2D: 00000000 - drdy and temp on, mode from standby to measurement
  */

#include <SPI.h>

const int cs = 2;
const int drdy = 30;

const byte filter_settings = 0b00000010;
const byte range_settings = 0b10000011;
const byte power_settings = 0b00000000;

float vel = 0;
int last_t = 0;

void setup() {
  Serial.begin(9600);
  SPI.begin();

  pinMode(drdy, INPUT);
  pinMode(cs, OUTPUT);

  //writeRegister(adress, value);

  delay(1000);

  // read manufacturer and device codes
  Serial.println(read_adxl_register(0x00, 1));
  Serial.println(read_adxl_register(0x01, 1));
  // Write - read test
  /*Serial.println(read_adxl_register(0x1F, 1));
  Serial.println(write_adxl_register(0x1F, 0xF0, 1));
  Serial.println(read_adxl_register(0x1F, 1));*/

  Serial.println("**** Read Temperature ****");
  int temp_bits = read_adxl_register(0x06, 2);
  Serial.println(temp_bits);
  float temp = 25 + (1885 - temp_bits) / 9.05;
  Serial.print("Converts to ");
  Serial.print(temp);
  Serial.println(" degC");
  Serial.println("**** Setting up for measurement ****");
  Serial.println(write_adxl_register(0x28, filter_settings));
  Serial.println(write_adxl_register(0x2C, range_settings));
  Serial.println(write_adxl_register(0x2D, power_settings));
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(drdy)){
   int32_t reading = read_adxl_register(0x0E, 3)<<8;
   float accel = (reading/16.0/256.0 - 1244)/12144.0;
   Serial.println(accel, 4);
  }
}

unsigned int read_adxl_register(byte target_register, int num_bytes){
  byte r_command = (target_register << 1) + 0x01; // shifts left 1 bit and sets last bit to 1 as per ADXL specs
  //Serial.print("Reading address ");
  //Serial.println(target_register);
  
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);
  SPI.transfer(r_command);
  unsigned int result = SPI.transfer(0x00);
  num_bytes--;
  while(num_bytes > 0){
    result = result << 8;
    result = result | SPI.transfer(0x00);
    num_bytes--;
  }
  digitalWrite(cs, HIGH);
  SPI.endTransaction();
  
  //Serial.print("Received: ");
  return result;
}

unsigned int write_adxl_register(byte target_register, byte data){
  byte w_command = target_register << 1;
  
  Serial.print("Writing data ");
  Serial.print(data);
  Serial.print(" to address ");
  Serial.println(target_register);
  
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);
  SPI.transfer(w_command);
  unsigned int result = SPI.transfer(data);
  digitalWrite(cs, HIGH);
  SPI.endTransaction();

  Serial.print("Received: ");
  return result;
}
