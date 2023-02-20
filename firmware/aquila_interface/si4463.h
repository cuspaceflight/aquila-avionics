#pragma once

#include "Arduino.h"

class SI4463 {
    private:
    byte pin_cs;

    void WriteRead(const uint8_t * pTxData, uint8_t * pRxData, const uint16_t txSize);
    void SetShutdown();
    void ClearShutdown();
    void Select();
    void Deselect();
    void DelayMs(uint32_t delayMs);
    uint8_t IsClearToSend();


    public:
    bool begin(byte pin_cs);


};