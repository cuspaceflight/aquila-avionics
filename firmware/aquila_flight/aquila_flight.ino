/* Daniel Fearn
 *  09/10/22
 *  
 *  This will be the flight program running on the Aquila-only test flight.
 *  
 * 
 */


#include <aquila_interface.h>

AQUILA aquila;

enum FlightState {LOCKED, PAD, BURN, COAST, APOGEE, DESCENT, LAND};
FlightState state;

// timers for 10Hz and 100Hz loops
uint32_t hz10_time;
uint32_t hz100_time;
uint32_t curr_time;

void setup() {
  state = LOCKED;

  Serial.begin(19200);

  hz10_time = hz100_time = micros();
}

void loop() {
  curr_time = micros();
  if (curr_time - hz10_time > 1e5) {
    hz10_time = curr_time;
    hz10();
  }
  if (curr_time - hz100_time > 1e4) {
    hz100_time = curr_time;
    hz100();
  }
}

void hz10(){
  Serial.println("10");
}

void hz100(){
  Serial.println("100");
  // state switching
  switch(state) {
    case LOCKED:

      break;
    case PAD:

      break;
    case BURN:

      break;
    case COAST:

      break;
    case APOGEE:

     break;
    case DESCENT:

      break;
    case LAND:

      break;
  }
}