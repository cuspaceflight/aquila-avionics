/* Daniel Fearn
 *  10/05/23
 *  
 *  This class handles communication with an RFM95W LoRa module
 *  It is connected to the baro_ext port, which is SPI1 with cs 4
 *  
 */

#include "rfm95w.h"

byte RFM95W::begin(byte pin_cs){
    cs = pin_cs;

    SPI1.begin();

    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);

    delay(500);

    // set frequency
    uint32_t num_steps = 868e6 / 61; // convert frequency to PLL steps and write (datasheet p13)
    write_reg(0x08, num_steps & 0xFF);
    num_steps = num_steps >> 8;
    write_reg(0x07, num_steps & 0xFF);
    num_steps = num_steps >> 8;
    write_reg(0x06, num_steps & 0xFF);

    

    write_reg(regPaConfig, pa_config);

    write_reg(regOpMode, operation_mode | SLEEP);
    
    // set packet length (as per aquila_flight this is currently 64 bytes)
    write_reg(0x22, 0x40);

    write_reg(regOpMode, operation_mode | STDBY);

    return read_reg(0x08, 1); // return a byte of the frequency setting to prove life
}

void RFM95W::init_receive(){
    write_reg(regOpMode, operation_mode | RX_CONT); // start listening for packets continuously
};

void RFM95W::check_received(char* outstr, uint8_t max_length){
    byte flags = read_reg(regIRQflags, 1); // interrupt flags
  
    if (flags != 0) { // something has happened
        
        //Serial.println(flags, BIN);

        byte location = read_reg(regRxCurrentAddr, 1); // get location of received payload
        write_reg(regFifoPtrAddr, location); // move pointer there
        
        
        uint8_t length = read_reg(regRxNumBytes, 1); // get length of received payload

        // read all bytes
        for (int i = 0; i < max_length; i++) {
            outstr[i] = read_reg(regFifo, 1);
            //Serial.println(read_reg(regFifo, 1), BIN);
        }


        //byte payload = read_reg(regFifo, 1); // read out firsty byte of payload
        //Serial.println(payload);


        write_reg(regIRQflags, 0xFF); // clear all flags
    }
};

void RFM95W::transmit(uint8_t size, char* data){

    write_reg(regFifoPtrAddr, txBaseAddr);

    for (int i = 0; i < size; i++) {
        write_reg(regFifo, data[i]);
    }

    write_reg(regOpMode, operation_mode | TX);
};

uint32_t RFM95W::read_reg(byte address, uint8_t num_bytes) {
  SPI1.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);

  address = address & 0b01111111; // set first bit to 0 for read   

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

uint32_t RFM95W::write_reg(byte address, byte data) {
  SPI1.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);

  address = address | 0b10000000; // set first bit to 1 for write   

  SPI1.transfer(address);
  uint32_t result = SPI1.transfer(data);

  digitalWrite(cs, HIGH);
  SPI1.endTransaction();

  return result;
}