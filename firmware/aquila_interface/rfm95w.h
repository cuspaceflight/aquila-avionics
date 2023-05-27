#pragma once


#include "Arduino.h"
#include "SPI.h"

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
const byte regRxNumBytes = 0x13; // number of bytes received

// power amplifier
const byte regPaConfig = 0x09;
const byte pa_config = 0b11111111; // max power
const byte pa_low_power = 0b01001111; // low power for short range testing

// IRQ interrupts
const byte regIRQflags = 0x12;

// end registers

class RFM95W {
  public:
    byte begin(byte pin_cs);
    void init_receive();
    void check_received(char* outstr, uint8_t max_length);
    void transmit(uint8_t size, char* data);
  private:
    byte cs;
    uint32_t read_reg(byte address, uint8_t num_bytes);
    uint32_t write_reg(byte addres, byte data);
    uint32_t spi_speed;
};
