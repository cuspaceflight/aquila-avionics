/* Daniel Fearn
 *  09/10/22
 *  
 *  This will be the flight program running on the Aquila-only test flight.
 *  
 * 
 */

// REQ[32][34]
#define SEA_LEVEL 1020

#define pin_accel_int 30

#include <aquila_interface.h>
#include <SD.h>

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
uint8_t servo_closed = 70;
uint8_t servo_pos = 0;
// REQ[7]
uint32_t descent_delay_millis = 2000;
uint32_t time_to_descent = 0;

// data logging
// REQ[32]
File datafile;

// altitude and velocity
// REQ[30]
volatile float altitude = 0;
volatile float velocity = 0;
volatile float acceleration = 0;
volatile uint32_t last_integ_micros = 0;
float g_cal = 9.81; // g used for acceloremeter calibration
float g_local = 9.81; // constant for low altitude, must computed at high altitudes. Mid latitude value used

void setup() {
  Serial.begin(19200);
  aquila.begin();
  aquila.move_all_servos(servo_closed);

  // REQ[30]
  pinMode(pin_accel_int, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin_accel_int), accel_integration, RISING);

  // REQ[32]
  if(!SD.begin(BUILTIN_SDCARD)){
    Serial.println("Critical SD card error");
    while(!SD.begin(BUILTIN_SDCARD)){}
  }
  SD.remove("aquila_log.csv");
  datafile = SD.open("aquila_log.csv", FILE_WRITE);

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
  aquila.update_imu();
  aquila.poll_baro_ext();
  aquila.poll_baro_int();

  // REQ[32]
  log_sd_state();

  // state switching
  switch(state) {
    case LOCKED:
      handle_serial_command(); // REQ[35][23]
      break;
    case PAD:
      handle_serial_command(); // REQ[35][23]
      if (velocity > 0.5) {state = BURN;} // REQ[4]
      break;
    case BURN:
      if (acceleration < 0) {state = COAST;} // REQ[5]
      break;
    case COAST:
      if (velocity < 0) {state = APOGEE;} // REQ[6]
      break;
    case APOGEE:
      if (time_to_descent != 0 && millis() > time_to_descent) {state = DESCENT;} // REQ[7]
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
        altitude = 0;
        velocity = 0;
        last_integ_micros = 0;
        break;
      case APOGEE: // REQ[9]
        time_to_descent = millis() + descent_delay_millis; // REQ[7]
        // deploy nosecone
        break;
      case DESCENT: // REQ[10]
        // deploy parachutes
        break;

      default:
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
      Serial.print(">> toggle servo position to ");
      Serial.println(servo_pos == servo_open ? "closed" : "open");
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

  Serial.print("Velocity estimate: ");
  Serial.println(velocity, 4);
  Serial.print("Altitude estimate: ");
  Serial.println(altitude, 4);

  Serial.println();
}

// prints all data to a line in the SD file
void log_sd_state(){

  // time
  char time[21];
  snprintf_P(time, sizeof(time), PSTR("%i,%i"), aquila.rtc_unix(), micros());
  // velocity/altitude estimates
  char alt[12]; // 4 dp + point + 6 digits + minus sign = 12
  char vel[12];
  dtostrf(altitude, 1, 4, alt);
  dtostrf(velocity, 1, 4, vel);
  // ADXL357
  char ax[9]; // 5 dp + p + 2 digits + minus sign = 9
  char ay[9];
  char az[9];
  dtostrf(aquila.get_accel_x(), 1, 5, ax);
  dtostrf(aquila.get_accel_y(), 1, 5, ay);
  dtostrf(aquila.get_accel_z(), 1, 5, az);
  // MPU6050
  char mp_ax[8]; // 4 dp + p + 2 digits + minus sign = 8
  char mp_ay[8];
  char mp_az[8];
  dtostrf(aquila.get_imu_accel_x(), 1, 4, mp_ax);
  dtostrf(aquila.get_imu_accel_y(), 1, 4, mp_ay);
  dtostrf(aquila.get_imu_accel_z(), 1, 4, mp_az);
  char mp_gx[8]; // 2 dp + p + 4 digits + minus sign = 8
  char mp_gy[8];
  char mp_gz[8];
  dtostrf(aquila.get_imu_gyro_x(), 1, 2, mp_gx);
  dtostrf(aquila.get_imu_gyro_y(), 1, 2, mp_gy);
  dtostrf(aquila.get_imu_gyro_z(), 1, 2, mp_gz);
  // External barometer
  char ext_t[6]; // 2 dp + p + 2 digits + minus sign = 6
  char ext_p[7]; // 2 dp + p + 4 digits = 7
  dtostrf(aquila.get_ext_temperature(), 1, 2, ext_t);
  dtostrf(aquila.get_ext_pressure(), 1, 2, ext_p);
  // Internal barometer
  char int_t[6]; // 2 dp + p + 2 digits + minus sign = 6
  char int_p[7]; // 2 dp + p + 4 digits = 7
  dtostrf(aquila.get_int_temperature(), 1, 2, int_t);
  dtostrf(aquila.get_int_pressure(), 1, 2, int_p);
  // Battery voltage
  char b_v[5]; // 2 dp + p + 1 digit + minus sign = 5
  dtostrf(aquila.get_batt_voltage(), 1, 2, b_v);
  // Pyros
  char rec[14]; // 5 bools + 3 digits + 6 commas = 14
  snprintf_P(rec, sizeof(rec), PSTR("%d,%d,%d,%d,%d,%i"),
    aquila.pyro_is_armed(),
    aquila.pyro_continuity(1),
    aquila.pyro_continuity(1),
    aquila.pyro_continuity(1),
    aquila.pyro_continuity(1),
    servo_pos
  );
  

  
  char line[185];
  snprintf_P(line, sizeof(line), PSTR("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"), 
            time, StateNames[state], 
            vel, alt, ax, ay, az, 
            mp_ax, mp_ay, mp_az, mp_gx, mp_gy, mp_gz,
            ext_t, ext_p, int_t, int_p,
            b_v, rec
  );

  datafile.println(line);
  datafile.flush();
}
void sep(){
  datafile.print(',');
}

// handles accelerometer interrupt
// REQ[30]
void accel_integration() {
  if (state == LOCKED) {return;} // REQ[18]

  aquila.update_accel();

  uint32_t now = micros();
  if (last_integ_micros == 0) {
    last_integ_micros = now;
    return;
  }

  float accel = aquila.get_accel_z(); // g

  if (abs(accel - 1) < 0.01 && (state == PAD)) { // REQ[47]
    accel = 1;
  } 

  acceleration = accel * g_cal; // m/s/s

  float dt = (now - last_integ_micros)*1e-6;
  velocity += (acceleration - g_local) * dt;
  altitude += velocity * dt;

  last_integ_micros = now;

}

// roughly converts pressure reading to altitude
// REQ[32][34]
float abs_altitude(float pressure, float sea_level) {
  return 44330*(1-pow((pressure/sea_level), (1/5.255)));
}