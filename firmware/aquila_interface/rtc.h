#pragma once

#include "Arduino.h"
#include "SPI.h"
#include "TimeLib.h"


class TEENSY_RTC {
    public:
        bool begin();
        void get_datetime(char* outstr);
        time_t get_unix();
    private:
        static time_t get_time();
};