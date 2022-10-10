/* Daniel Fearn
 *  09/10/22
 *  
 *  This will be the flight program running on the Aquila-only test flight.
 *  
 * 
 */

#define SEA_LEVEL 1020

#include <aquila_interface.h>

AQUILA aquila;

// flight state variables 
// REQ[1]
enum FlightState {LOCKED, PAD, BURN, COAST, APOGEE, DESCENT, LAND};
const char *StateNames[] = {"LOCKED", "PAD", "BURN", "COAST", "APOGEE", "DESCENT", "LAND"};
FlightState state = LOCKED; // REQ[2]
FlightState prevState = state;

// whether system parameters are being printed to serial when on the pad 
bool printing_params = false; // REQ[37][38]

// timers for 10Hz and 100Hz loops
uint32_t hz10_time; // REQ[27][28]
uint32_t hz100_time; // REQ[25][26][29]
uint32_t curr_time;

// system parameters
// REQ[41]
uint8_t servo_open = 0; 
uint8_t servo_closed = 180;
uint8_t servo_pos = 0;

void setup() {
  Serial.begin(19200);
  aquila.begin();

  hz10_time = hz100_time = micros(); // REQ[25][26][27][28][29]
}

// main loop
void loop() {
  curr_time = micros();
  if (curr_time - hz10_time > 1e5) { // REQ[27][28]
    hz10_time = curr_time;
    hz10();
  }
  if (curr_time - hz100_time > 1e4) { // REQ[25][26][29]
    hz100_time = curr_time;
    hz100();
  }
}

// things to do at 10Hz
// REQ[27][28]
void hz10(){
  if (printing_params && (state == LOCKED || state == PAD)){print_serial_state();}
}

// things to do at 100Hz
// REQ[25][26][29]
void hz100(){
  // REQ[31]
  aquila.update_accel();
  aquila.update_imu();
  aquila.poll_baro_ext();
  aquila.poll_baro_int();

  // state switching
  switch(state) {
    case LOCKED:
      handle_serial_command(); // REQ[35][23]
      break;
    case PAD:
      handle_serial_command(); // REQ[35][23]
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
  
  // state entry actions
  if (state != prevState) {
    switch (state) {
      case LOCKED: // REQ[46]
        // reset altitude/velocity
        break;
      case APOGEE: // REQ[9]
        // deploy nosecone
        break;
      case DESCENT: // REQ[10]
        // deploy parachutes
        break;
    }
  }
  prevState = state;
}

// reads and performs single character commands from Serial. All characters after the first are discarded.
// REQ[35]
void handle_serial_command(){
  if (Serial.available() == 0){ return; }

  // read first character
  char cmd = Serial.read();

  // empty buffer of any other characters
  while (Serial.available() > 0){Serial.read();}

  if (cmd == 'N') { // REQ[36]
    Serial.println(">> print system state");
    print_serial_state();

  } else if (cmd == 'S') { // REQ[37]
    Serial.println(">> start printing system state");
    printing_params = true;

  } else if (cmd == 'P') { // REQ[38]
    Serial.println(">> stop printing system state");
    printing_params = false;

  } else if (cmd == 'L') { // REQ[39]
    Serial.println(">> put system in LOCKED state");
    state = LOCKED; // REQ[45]

  } else if (cmd == 'U') { // REQ[40]
    Serial.println(">> put system in PAD state");
    state = PAD; // REQ[3]

  } else if (cmd == 'V') { // REQ[41]
    if (state != LOCKED) {
      Serial.println(">> must be in LOCKED state to move servos");
    } else if(!aquila.pyro_is_armed()) { // REQ[44]
      Serial.println(">> pyro must be armed to move servos");
    } else {
      Serial.println(">> toggle servo position");
      servo_pos = (servo_pos == servo_open) ? servo_closed : servo_open;
      aquila.move_all_servos(servo_pos);
    }

  } else if (cmd == 'A') { // REQ[42]
    Serial.println(">> arm pyro");
    aquila.arm_pyro();

  } else if (cmd == 'D') { // REQ[43]
    Serial.println(">> disarm pyro");
    aquila.disarm_pyro();
  } else {
    Serial.println(">> command not recognised");
  }

}

// prints timestamp, all sensor values to serial
// REQ[34][36][37][38]
void print_serial_state(){
  char timestamp[32];
  aquila.rtc_datetime(timestamp);
  Serial.println(timestamp);

  Serial.print("State: ");
  Serial.println(StateNames[state]);

  Serial.print("Accelerations (ADXL357): ");
  Serial.print(aquila.get_accel_x(), 4);
  Serial.print(", ");
  Serial.print(aquila.get_accel_y(), 4);
  Serial.print(", ");
  Serial.println(aquila.get_accel_z(), 4);

  Serial.print("Accelerations (MPU6050): ");
  Serial.print(aquila.get_imu_accel_x(), 4);
  Serial.print(", ");
  Serial.print(aquila.get_imu_accel_y(), 4);
  Serial.print(", ");
  Serial.println(aquila.get_imu_accel_z(), 4);

  Serial.print("Gyroscopes: ");
  Serial.print(aquila.get_imu_gyro_x(), 4);
  Serial.print(", ");
  Serial.print(aquila.get_imu_gyro_y(), 4);
  Serial.print(", ");
  Serial.println(aquila.get_imu_gyro_z(), 4);

  Serial.print("External barometer: ");
  Serial.print(aquila.get_ext_temperature());
  Serial.print(", ");
  Serial.print(aquila.get_ext_pressure());
  Serial.print(", ");
  Serial.println(abs_altitude(aquila.get_ext_pressure(), SEA_LEVEL));
  
  Serial.print("Internal barometer: ");
  Serial.print(aquila.get_int_temperature());
  Serial.print(", ");
  Serial.print(aquila.get_int_pressure());
  Serial.print(", ");
  Serial.println(abs_altitude(aquila.get_int_pressure(), SEA_LEVEL));

  Serial.print("Battery voltage: ");
  Serial.println(aquila.get_batt_voltage());

  Serial.print("Pyro armed: ");
  Serial.println(aquila.pyro_is_armed());

  Serial.print("Pyro continuities: ");
  if (aquila.pyro_is_armed()){
    Serial.print(aquila.pyro_continuity(1));
    Serial.print(", ");
    Serial.print(aquila.pyro_continuity(2));
    Serial.print(", ");
    Serial.print(aquila.pyro_continuity(3));
    Serial.print(", ");
    Serial.println(aquila.pyro_continuity(4));
  } else {
    Serial.println("pyrotechnics must be armed to test continuity");
  }

  Serial.println();
}

float abs_altitude(float pressure, float sea_level) {
  return 44330*(1-pow((pressure/sea_level), (1/5.255)));
}