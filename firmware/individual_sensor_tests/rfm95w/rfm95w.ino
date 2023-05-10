// read and write tests for rfm95w LoRa module plugged into baro_ext socket

/*
 * Teensy 4.1
 * 
 * RFM95W on SPI1 port:
 * MOSI - 26
 * MISO - 1
 * SCLK - 27
 * CS - 4
 * 
 * tx:
 * mode request standby
 * tx init
 * write data fifo  <-----------------+
 * mode request tx                    |
 * wait for irq txdone                |
 * automatic mode change standby      |
 * new tx? --- yes -------------------+
 * 
 * rx single:
 * mode request standby
 * rx init
 * mode request rx single <--+
 * wait for IRQ              |
 *     /      \              |
 * rx done    rx timeout ----+
 *    |                      |
 * IRQ crc error? --- yes ---+
 *    |                      |
 *   no                      |
 *    |                      |
 * read rx data -------------+
 * 
 * rx continuous:
 * mode request standby
 * rx init
 * mode request rx cont   
 * check IRQ  <--------------+
 *     /     \               |
 * rx done    empty ---- ----+
 *    |                      |
 * IRQ crc error? --- yes ---+
 *    |                      |
 *   no                      |
 *    |                      |
 * read rx data -------------+
 * 
 */

#define RXCODE // changes whether this code is for the receiver or the transmitter

#include <SPI.h>

const int cs = 4;
const uint32_t frequency = 868e6;


// registers - datasheet p103 - p109
const byte regFifo = 0x00;

const byte regOpMode = 0x01;
const byte operation_mode = 0b10000000; // LoRa mode, high frequency mode, sleep
// modes to be ORed with above
const byte SLEEP = 0b00000000;
const byte STDBY = 0b00000001;
const byte TX = 0b00000011;
const byte RX_CONT = 0b00000101;
const byte RX_SING = 0b00000110;

// fifo reading in and out
const byte regFifoPtrAddr = 0x0D; // set where the 0x00 regFifo register should point in memory
const byte txBaseAddr = 0x80; // default starting point for tx part of memory
const byte regRxCurrentAddr = 0x10; // location of last rx packet

// power amplifier
const byte regPaConfig = 0x09;
const byte pa_config = 0b11111111; // max power
const byte pa_low_power = 0b01001111; // low power for short range testing

// IRQ interrupts
const byte regIRQflags = 0x12;

// end registers

void setup() {

    Serial.begin(9600);
  
    SPI1.begin();

    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);

    delay(500);

    Serial.println(read_rfm_register(0x06, 1)); // should return 108 (0x6C) after reset (must manually power cycle)

    write_rfm_register(0x06, 110);

    Serial.println(read_rfm_register(0x06, 1)); // should return 110 now that we've written to it
    

    // set frequency
    uint32_t num_steps = 868e6 / 61; // convert frequency to PLL steps and write (datasheet p13)
    Serial.println(num_steps);
    write_rfm_register(0x08, num_steps & 0xFF);
    num_steps = num_steps >> 8;
    write_rfm_register(0x07, num_steps & 0xFF);
    num_steps = num_steps >> 8;
    write_rfm_register(0x06, num_steps & 0xFF);


    Serial.println(read_rfm_register(0x06, 1));
    Serial.println(read_rfm_register(0x07, 1));
    Serial.println(read_rfm_register(0x08, 1));

    write_rfm_register(regPaConfig, pa_config); // change to pa_config for long range!

    write_rfm_register(regOpMode, operation_mode | SLEEP); // must be put in sleep to switch on LoRa mode
    delay(10);
    write_rfm_register(regOpMode, operation_mode | STDBY); // set into LoRa standby
  
#ifdef RXCODE
    write_rfm_register(regOpMode, operation_mode | RX_CONT); // start listening for packets
#endif

}

void loop() {
  
#ifdef RXCODE
  byte flags = read_rfm_register(regIRQflags, 1); // interrupt flags
  
  if (flags != 0) { // something has happened
    
    Serial.println(flags, BIN);

    byte location = read_rfm_register(regRxCurrentAddr, 1); // get location of received payload
    write_rfm_register(regFifoPtrAddr, location);
    
    byte payload = read_rfm_register(regFifo, 1); // read out payload
    Serial.println(payload);


    write_rfm_register(regIRQflags, 0xFF); // clear all flags
  }

  delay(100);


#else
  write_rfm_register(regFifoPtrAddr, txBaseAddr);
  write_rfm_register(regFifo, 42);

  write_rfm_register(regOpMode, operation_mode | TX);

  delay(500);

#endif
  
}

unsigned int read_rfm_register(byte target_register, int num_bytes) {
  SPI1.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);

  target_register = target_register & 0b01111111; // set first bit to 0 for read   

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

unsigned int write_rfm_register(byte target_register, byte data) {
  SPI1.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);

  target_register = target_register | 0b10000000; // set first bit to 1 for write   

  SPI1.transfer(target_register);
  unsigned int result = SPI1.transfer(data);

  digitalWrite(cs, HIGH);
  SPI1.endTransaction();

  return result;
}