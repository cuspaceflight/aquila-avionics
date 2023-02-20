#include "si4463.h"
extern "C" {
#include "si4463_lib.h"
}

void SI4463_WriteRead(const uint8_t * pTxData, uint8_t * pRxData, const uint16_t txSize) {

}

void SI4463::SetShutdown() {}

void SI4463_ClearShutdown() {}

void SI4463::Select() {
    digitalWrite(pin_cs, LOW);
}

void SI4463::Deselect() {
    digitalWrite(pin_cs, HIGH);
}

void SI4463::DelayMs(uint32_t delayMs) {
    delay(delayMs);
}

uint8_t SI4463::IsClearToSend() {
    return 1;
}

bool SI4463::begin(byte pin_cs) {
    this->pin_cs = pin_cs;

    pinMode(pin_cs, OUTPUT);
}