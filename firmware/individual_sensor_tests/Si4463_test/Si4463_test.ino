/*
 * Teensy 4.1
 * 
 * Si4463 on SPI1 port:
 * MOSI - 26
 * MISO - 1
 * SCLK - 27
 * CS - 5
 * 
 */

 #include <SPI.h>

const bool loop_mode = true;

const int cs = 5;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
  
  SPI1.begin();
  
  Serial.println(read_radio_register(0x44, 1));
}

void loop() {
  // put your main code here, to run repeatedly:

}

unsigned int read_radio_register(byte target_register, int num_bytes) {
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
