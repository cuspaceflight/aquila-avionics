#include "SPI.h"
#include "Wire.h"

#define spi_speed 10000000
#define adxl357_cs 2


#define mpu6050 0x68

uint32_t num_runs = 200;

void setup() {
  pinMode(adxl357_cs, OUTPUT);

  SPI.begin();
  Wire.begin();
  Serial.begin(19200);
  Serial.println("starting up");
  delay(500);

  // setup adxl357
  write_adxl357_reg(0x28, 0b00000010);
  write_adxl357_reg(0x2C, 0b10000011);
  write_adxl357_reg(0x2D, 0b00000000);
  delay(100);
  // clear any preset offsets
  write_adxl357_reg(0x1E, 0b00000000);
  write_adxl357_reg(0x1F, 0b00000000);
  write_adxl357_reg(0x20, 0b00000000);
  write_adxl357_reg(0x21, 0b00000000);
  write_adxl357_reg(0x22, 0b00000000);
  write_adxl357_reg(0x23, 0b00000000);
  delay(500);

  // mpu6050 setup
  write_mpu6050_reg(0x6B, 0);
  delay(100);
  // +/- 16g mode
  write_mpu6050_reg(0x1C, 3<<3);
  // +/- 2000deg/s mode
  write_mpu6050_reg(0x1B, 3<<3);

  char adxl_adresses[6] = {0x08, 0x08, 0x0B, 0x0B, 0x0E, 0x0E};
  char mpu6050_addresses[6] = {0x3D, 0x3D, 0x3B, 0x3B, 0x3F, 0x3F};
  float adxl_values[6];
  float mpu6050_values[6];

  float adxl_total = 0;
  float mpu6050_total = 0;
  for (uint8_t i = 0; i < 6; i++) {
    
    Serial.print("Press any key to calibrate point ");
    Serial.println(i);
    Serial.println(test_description(i));
    while(Serial.available() == 0){}
    Serial.read();
    Serial.println("Running");

    byte adxl_address = adxl_adresses[i];
    byte mpu6050_address = mpu6050_addresses[i];

    for (uint32_t j = 0; j < num_runs; j++) {
      int32_t raw_reading = (read_adxl357_reg(adxl_address, 3)<<8);
      adxl_total += raw_reading/4096;

      int16_t raw_reading2 = read_mpu6050_reg(mpu6050_address, 2);
      mpu6050_total += raw_reading2;
      delay(20);      
    }
    
    adxl_values[i] = adxl_total/num_runs;
    Serial.print("ADXL357 esult: ");
    Serial.println(adxl_values[i]);

    mpu6050_values[i] = mpu6050_total/num_runs;
    Serial.print("MPU6050 result: ");
    Serial.println(mpu6050_values[i]);

    adxl_total = 0;
    mpu6050_total = 0;

  }
  

  Serial.print("Press any key to calibrate gyroscopes");
  while(Serial.available() == 0){}
  Serial.read();

  float gyro_x_total = 0;
  float gyro_y_total = 0;
  float gyro_z_total = 0;
  for (uint8_t i = 0; i < num_runs; i++) {
    Wire.beginTransmission(mpu6050);
    Wire.write(0x43);
    Wire.endTransmission();
    Wire.requestFrom(mpu6050, 6, true);

    int16_t gyro_x_reading = (Wire.read() << 8) | Wire.read();
    int16_t gyro_y_reading = (Wire.read() << 8) | Wire.read();
    int16_t gyro_z_reading = (Wire.read() << 8) | Wire.read();

    gyro_x_total += gyro_x_reading;
    gyro_y_total += gyro_y_reading;
    gyro_z_total += gyro_z_reading;
    delay(20);
  }

  float gyro_x_offset = gyro_x_total / num_runs;
  float gyro_y_offset = gyro_y_total / num_runs;
  float gyro_z_offset = gyro_z_total / num_runs;

  Serial.println("----- ADXL357 -----");
  Serial.print("x sensitivity: ");
  Serial.println((adxl_values[0] - adxl_values[1]) / 2);
  Serial.print("x offset: ");
  Serial.println((adxl_values[0] + adxl_values[1]) / 2);
  Serial.print("y sensitivity: ");
  Serial.println((adxl_values[2] - adxl_values[3]) / 2);
  Serial.print("y offset: ");
  Serial.println((adxl_values[2] + adxl_values[3]) / 2);
  Serial.print("z sensitivity: ");
  Serial.println((adxl_values[4] - adxl_values[5]) / 2);
  Serial.print("z offset: ");
  Serial.println((adxl_values[4] + adxl_values[5]) / 2);

  Serial.println("----- MPU6050 Acceleromter -----");
  Serial.print("x sensitivity: ");
  Serial.println((mpu6050_values[2] - mpu6050_values[3]) / 2);
  Serial.print("x offset: ");
  Serial.println((mpu6050_values[2] + mpu6050_values[3]) / 2);
  Serial.print("y sensitivity: ");
  Serial.println((mpu6050_values[1] - mpu6050_values[0]) / 2);
  Serial.print("y offset: ");
  Serial.println((mpu6050_values[1] + mpu6050_values[0]) / 2);
  Serial.print("z sensitivity: ");
  Serial.println((mpu6050_values[4] - mpu6050_values[5]) / 2);
  Serial.print("z offset: ");
  Serial.println((mpu6050_values[4] + mpu6050_values[5]) / 2);

  Serial.println("----- MPU6050 Gyroscopes -----");
  Serial.print("x offset: ");
  Serial.println(gyro_x_offset);
  Serial.print("y offset: ");
  Serial.println(gyro_y_offset);
  Serial.print("z offset: ");
  Serial.println(gyro_z_offset);

  Serial.println("All offsets in LSB, accelerometer sensitivities in LSB /g");

  while(true){}

}

void loop() {
  Serial.println(read_mpu6050_reg(0x3B, 2));
  delay(100);
}

uint32_t read_adxl357_reg(byte address, uint8_t num_bytes) {
  byte r_command = (address << 1) + 1;
  SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE0));
  digitalWrite(adxl357_cs, LOW);
  SPI.transfer(r_command);
  uint32_t result = SPI.transfer(0x00);
  num_bytes--;
  while(num_bytes > 0){
    result = result << 8;
    result = result | SPI.transfer(0x00);
    num_bytes--;
  }
  digitalWrite(adxl357_cs, HIGH);
  SPI.endTransaction();
  return result;
}

uint32_t write_adxl357_reg(byte address, byte data){
  byte w_command = address << 1;
  SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE0));
  digitalWrite(adxl357_cs, LOW);
  SPI.transfer(w_command);
  uint32_t result = SPI.transfer(data);
  digitalWrite(adxl357_cs, HIGH);
  SPI.endTransaction();
  return result;
}

uint32_t read_mpu6050_reg(byte address, uint8_t num_bytes) {
    Wire.beginTransmission(mpu6050);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(mpu6050, num_bytes, true);

    uint32_t reading = Wire.read();
    num_bytes--;
    while (num_bytes > 0) {
        reading = (reading << 8) | Wire.read();
        num_bytes--;
    }
    return reading;
}

uint32_t write_mpu6050_reg(byte address, byte data) {
    Wire.beginTransmission(mpu6050);
    Wire.write(address);
    Wire.write(data);
    Wire.endTransmission();
}

String test_description(uint8_t index) {
  switch (index)
  {
  case 0:
    return "x-axis up (pwr switch corner up)";
    break;
  case 1:
    return "x-axis down (usb connctor corner up)";
    break;
  case 2:
    return "y-axis up (SD card corner up)";
    break;
  case 3:
    return "y-axis down (pyro switch corner up)";
    break;
  case 4:
    return "z-axis up (board flat)";
    break;
  case 5:
    return "z-axis down (board inverted)";
    break;
  
  default:
    return "invalid index";
    break;
  }
}