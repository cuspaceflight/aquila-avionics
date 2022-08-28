/* Daniel Fearn
 *  27/08/2022
 *  
 *  This class interacts with the Real-Time Clock on the Teensy 4.1 board
 *  The library refers to Teensy3 but its the same on the Teensy 4.1
 * 
 *  This code does not include a way to sync the real time clock from a PC. For that, use the Teensy3Clock example sketch.
 *  
 */

#include "rtc.h"

bool TEENSY_RTC::begin(){
    setSyncProvider(get_time);
    return timeStatus() == timeSet;
}

void TEENSY_RTC::get_datetime(char* outstr) {
    snprintf_P(outstr, 32, PSTR("%u-%02u-%02u--%02u-%02u-%02u"),
               year(), month(), day(), hour(),
               minute(), second());
}

time_t TEENSY_RTC::get_unix() {
    return now();
}

time_t TEENSY_RTC::get_time() {
    return Teensy3Clock.get();
}