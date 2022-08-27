#include "TimeLib.h"

void setup() {
  // put your setup code here, to run once:
  setSyncProvider(get_time);

  Serial.begin(9600);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  delay(100);

  char outStr[32];
  snprintf_P(outStr, 32, PSTR("%u-%02u-%02u--%02u-%02u-%02u"),
               year(), month(), day(), hour(),
               minute(), second());    
  Serial.println(outStr);
}

time_t get_time(){
  return Teensy3Clock.get();
}
