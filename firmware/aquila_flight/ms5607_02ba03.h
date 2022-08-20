#pragma once

#include "Arduino.h"
#include "SPI.h"

class MS5607 {
  public:
    uint32_t begin(byte pin_cs);
    bool poll_measurement();
    int32_t pressure;
    int32_t temperature;
  private:
    byte cs;
    float c[7];
    uint32_t D1;
    uint32_t D2;
    uint8_t measurement_stage;
    uint32_t wait_time;
    uint32_t read_reg(byte address, uint8_t num_bytes);
    uint32_t send_command(byte command);
    uint32_t spi_speed;
};
