/* Daniel Fearn
 *  09/10/22
 *  
 *  This will be the flight program running on the Aquila-only test flight.
 *  
 * 
 */


#include <aquila_interface.h>

AQUILA aquila;


void setup() {

}

void loop() {

}

float abs_altitude(float pressure, float sea_level) {
  return 44330*(1-pow((pressure/sea_level), (1/5.255)));
}