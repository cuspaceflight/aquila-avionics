/*
 * Teensy 4.1
 * 
 * MS5607 on SPI1 port:
 * MOSI - 26
 * MISO - 1
 * SCLK - 27
 * CS - 4
 * 
 */

 #include <SPI.h>

const bool loop_mode = true;

const int cs = 4;
const int MOSI2 = 26;
const int MISO2 = 1;
const int SCLK2 = 27;

float c1;
float c2;
float c3;
float c4;
float c5;
float c6;

uint32_t D1;
uint32_t D2;

float smoothed = 0;

void setup() {
  
  Serial.begin(9600);
  
  SPI1.begin();

  

  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);

  delay(500);

  if(loop_mode) {
    send_baro_command(0x1E);
    delay(500);
    c1 = read_baro_register(0xA2, 2);
    c2 = read_baro_register(0xA4, 2);
    c3 = read_baro_register(0xA6, 2);
    c4 = read_baro_register(0xA8, 2);
    c5 = read_baro_register(0xAA, 2);
    c6 = read_baro_register(0xAC, 2);
  } else {
    // send reset command
    Serial.println("Sending reset:");
    Serial.println(send_baro_command(0x1E));
    delay(500);
  
    
  
    // read 16 bit PROM value
    Serial.println("Requesting PROM calibration values:");
    c1 = read_baro_register(0xA2, 2);
    c2 = read_baro_register(0xA4, 2);
    c3 = read_baro_register(0xA6, 2);
    c4 = read_baro_register(0xA8, 2);
    c5 = read_baro_register(0xAA, 2);
    c6 = read_baro_register(0xAC, 2);
    Serial.print(c1);
    Serial.print(", ");
    Serial.print(c2);
    Serial.print(", ");
    Serial.print(c3);
    Serial.print(", ");
    Serial.print(c4);
    Serial.print(", ");
    Serial.print(c5);
    Serial.print(", ");
    Serial.println(c6);
  
    delay(2000);
  
    Serial.println("Sending pressure conversion command and reading ADC");
    send_baro_command(0x48);
    D1 = read_baro_register(0x00, 3);
    D1 = 6472300;
    Serial.println(D1);
    Serial.println("Sending temperature conversion command and reading ADC");
    send_baro_command(0x58);
    D2 = read_baro_register(0x00, 3);
    D2 = 8370462;
    Serial.println(D2);
  
    Serial.println("Calculating temperature:");
    int64_t dT = D2 - (c5*256);
    Serial.println(dT);
    int64_t temp = 2000 + ((dT*c6)/8388608);
    Serial.println(temp/100.0);
  
    Serial.println("Calculating pressure:");
    float off = (c2*131072) + (c4 * dT)/64;
    Serial.println(off);
    int64_t sens = c1*65536 + (c3 * dT)/128;
    Serial.println(sens);
    int32_t p = (((D1 * sens)/2097152) - off)/32768;
    Serial.println(p/100.0);

  }
}

void loop() {
  send_baro_command(0x48);
  D1 = read_baro_register(0x00, 3);
  send_baro_command(0x58);
  D2 = read_baro_register(0x00, 3);

  int64_t dT = D2 - (c5*256);
  int64_t temp = 2000 + ((dT*c6)/8388608);

  float off = (c2*131072) + (c4 * dT)/64;
  int64_t sens = c1*65536 + (c3 * dT)/128;
  int32_t p = (((D1 * sens)/2097152) - off)/32768;

  // conditioning to make nice plots
  int32_t dp = p - 99100;
  smoothed = smoothed * 0.9 + p*0.1;
  Serial.println(smoothed);
}

unsigned int send_baro_command(byte baro_command){
  SPI1.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);
  unsigned int result = SPI1.transfer(baro_command);
  delay(10);
  digitalWrite(cs, HIGH);
  SPI1.endTransaction();

  return result;
}

unsigned int read_baro_register(byte target_register, int num_bytes) {
  SPI1.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);
  SPI1.transfer(target_register);
  unsigned int result = SPI1.transfer(0x00);
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
