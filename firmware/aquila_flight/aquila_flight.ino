/* Daniel Fearn
 *  09/10/22
 *  
 *  This will be the flight program running on the Aquila-only test flight.
 *  
 * 
 */



#define pin_accel_int 30
//#define HIL_mode // uncomment to run HIL simulation of flight

#include <SD.h>

#ifdef HIL_mode
  #include <aquila_hil_interface.h>
  AQUILA_HIL aquila;
#else
  #include <aquila_interface.h>
  AQUILA aquila;
#endif


// flight state variables 
// REQ[1]
enum FlightState {LOCKED, PAD, BURN, COAST, APOGEE, DESCENT, LAND};
const char *StateNames[] = {"LOCKED", "PAD", "BURN", "COAST", "APOGEE", "DESCENT", "LAND"};
#ifdef HIL_mode
  FlightState state = PAD;
#else
  FlightState state = LOCKED; // REQ[2]
#endif
FlightState prevState = state;

// whether system parameters are being printed to serial when on the pad 
bool printing_params = false; // REQ[37][38]

// structure for encoding flight parameters for telemetry
struct FlightParams {
  uint32_t unix_time;
  byte flight_state;
  float accel_x;
  float accel_y;
  float accel_z;

  float int_pressure;
  float int_temperature;

  float imu_accel_x;
  float imu_accel_y;
  float imu_accel_z;
  float imu_gyro_x;
  float imu_gyro_y;
  float imu_gyro_z;

  float est_altitude;
  float est_velocity;

};

// timers for 10Hz and 100Hz loops
uint32_t hz10_time; // REQ[27][28]
uint32_t hz100_time; // REQ[25][26][29]
uint32_t curr_time;

// system parameters
// REQ[41]
constexpr uint8_t servo_unlocked = 0; 
constexpr uint8_t servo_locked = 70;
uint8_t servo_pos = servo_locked;
// REQ[7]
float parachute_altitude = 500; // m

// REQ[32][34][49]
float pad_pressure = 1020;

// REQ[8]
constexpr uint8_t baro_num_samples = 10; // number of samples to store
constexpr uint16_t baro_sample_period = 100; // number of 100hz loops between samples
uint16_t baro_sample_count = 0; // counts 100hz loops to know when to take samples
uint16_t baro_sample_index = 0; // the index in which to store the next sample
float baro_samples[baro_num_samples]; // array to store the samples

// REQ[52]
char last_cmd = '0';

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
  aquila.move_all_servos(servo_locked);

  // REQ[30]
  pinMode(pin_accel_int, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin_accel_int), accel_integration, RISING);

  // REQ[32]
  if(!SD.begin(BUILTIN_SDCARD)){
    Serial.println("Critical SD card error");
    while(!SD.begin(BUILTIN_SDCARD)){}
  }
  //SD.remove("aquila_log.csv");
  datafile = SD.open("aquila_log.csv", FILE_WRITE);
  datafile.seek(EOF);

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

byte loop_count = 0; // REQ[33][52]
// things to do at 10Hz
// REQ[27][28]
void hz10(){
  uint32_t loop_time = micros();
  if (printing_params /*& (state == LOCKED || state == PAD)*/){print_serial_state();}

  // every other loop either check if a command is received, or send a packet.
  // can't do both bc of async timing of the radio REQ[21][33][52]
  loop_count++;
  if (loop_count & 0b00000001) {
    handle_radio_command();
    send_telemetry();
  } else {
    aquila.start_listening();
  }

  // REQ[11]
  if (state == LAND) {
    // REQ[32]
    log_sd_state(loop_time);
  }
}

// things to do at 100Hz
// REQ[25][26][29]
void hz100(){
  uint32_t loop_time = micros();
  // REQ[31]
  aquila.update_imu();
  aquila.poll_baro_int();

  // REQ[11]
  if (state != LAND) {
    // REQ[32]
    log_sd_state(loop_time);
  }

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
      if (abs_altitude(aquila.get_int_pressure(), pad_pressure) < parachute_altitude) {state = DESCENT;} // REQ[7]
      break;
    case DESCENT:
      // REQ[8]
      if (++baro_sample_count > baro_sample_period) {
        baro_sample_count = 0;
        if (++baro_sample_index > baro_num_samples) {baro_sample_index = 0;}
        baro_samples[baro_sample_index] = aquila.get_int_pressure();

        if (abs(baro_samples[baro_sample_index]-baro_samples[ (baro_sample_index+1)%baro_num_samples ]) < 1 ) {
          state = LAND;
        }
      }

      

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
        // deploy nosecone
        safely_arm_pyro();
        aquila.fire_pyro(1);
        aquila.fire_pyro(2);
        aquila.fire_pyro(3);
        aquila.fire_pyro(4);
        break;
      case DESCENT: // REQ[10]
        // deploy parachutes
        servo_pos = servo_unlocked;
        aquila.move_all_servos(servo_pos);
        break;

      case LAND: // REQ[51]
        aquila.disarm_pyro();
        break;

      default:
        break;
    }
  }
  prevState = state;
}

// REQ[52]
void handle_radio_command(){
  char cmd = '0';
  aquila.receive_telec((char*)&cmd);
  if (cmd != '0' && cmd != last_cmd) {
    execute_command(cmd);
    last_cmd = cmd;
  }
}

// reads and performs single character commands from Serial. All characters after the first are discarded.
// REQ[35]
void handle_serial_command(){
  if (Serial.available() == 0){ return; }

  // read first character
  char cmd = Serial.read();

  // empty buffer of any other characters
  while (Serial.available() > 0){Serial.read();}

  execute_command(cmd);

}

void execute_command(char cmd) {
  if (cmd == 'N') { // REQ[36]
    print_serial_state();
  } else if (cmd == 'S') { // REQ[37]
    printing_params = true;
  } else if (cmd == 'P') { // REQ[38]
    printing_params = false;
  } else if (cmd == 'L') { // REQ[39]
    state = LOCKED; // REQ[45]
  } else if (cmd == 'U') { // REQ[40]
    state = PAD; // REQ[3]
  } else if (cmd == 'V') { // REQ[41]
    if (state == LOCKED && aquila.pyro_is_armed()) { // REQ[44]
      servo_pos = (servo_pos == servo_unlocked) ? servo_locked : servo_unlocked;
      aquila.move_all_servos(servo_pos);
    }
  } else if (cmd == 'A') { // REQ[42]
    safely_arm_pyro();

  } else if (cmd == 'D') { // REQ[43]
    aquila.disarm_pyro();
  } else if (cmd == 'C') { // REQ[49]
    pad_pressure = aquila.get_int_pressure();
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
  
  Serial.print("Internal barometer: ");
  Serial.print(aquila.get_int_temperature());
  Serial.print(", ");
  Serial.print(aquila.get_int_pressure());
  Serial.print(", ");
  Serial.println(abs_altitude(aquila.get_int_pressure(), pad_pressure));

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

  Serial.print("Servo position: ");
  Serial.println((servo_pos == servo_locked) ? "LOCKED" : "RELEASE");

  Serial.print("Velocity estimate: ");
  Serial.println(velocity, 4);
  Serial.print("Altitude estimate: ");
  Serial.println(altitude, 4);

  for (uint8_t i = 0; i < baro_num_samples; i++) {
    Serial.print(baro_samples[i]);
    Serial.print(",");
  }
  Serial.println();

  Serial.println();
}

// prints all data to a line in the SD file
void log_sd_state(uint32_t loop_time){

  // time
  char time[21];
  snprintf_P(time, sizeof(time), PSTR("%i,%i"), aquila.rtc_unix(), loop_time);
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
    aquila.pyro_continuity(2),
    aquila.pyro_continuity(3),
    aquila.pyro_continuity(4),
    servo_pos
  );
  

  
  char line[168];
  snprintf_P(line, sizeof(line), PSTR("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"), 
            time, StateNames[state], 
            vel, alt, ax, ay, az, 
            mp_ax, mp_ay, mp_az, mp_gx, mp_gy, mp_gz,
            int_t, int_p,
            b_v, rec
  );

  datafile.println(line);
  datafile.flush();
}

// handles accelerometer interrupt
// REQ[30]
void accel_integration() {
  if (state == LOCKED || state == LAND) {return;} // REQ[18]

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
// REQ[32][34][49]
float abs_altitude(float pressure, float sea_level) {
  return 44330*(1-pow((pressure/sea_level), (1/5.255)));
}

// arms pyro channels with safeguards
// REQ[48]
void safely_arm_pyro() {
  servo_pos = servo_locked;
  aquila.move_all_servos(servo_pos);
  aquila.arm_pyro();
}

// REQ[33]
void send_telemetry() {
  FlightParams data;

  byte flight_state = (state & 0b00000111)
   + (aquila.pyro_continuity(1) << 6)
   + (aquila.pyro_continuity(2) << 5)
   + (aquila.pyro_continuity(3) << 4)
   + (aquila.pyro_continuity(4) << 3)
   + (aquila.pyro_is_armed() << 7);

  data.unix_time = micros();
  data.flight_state = flight_state;
  data.accel_x = aquila.get_accel_x();
  data.accel_y = aquila.get_accel_y();
  data.accel_z = aquila.get_accel_z();
  data.int_pressure = aquila.get_int_pressure();
  data.int_temperature = aquila.get_int_temperature();

  data.imu_accel_x = aquila.get_imu_accel_x();
  data.imu_accel_y = aquila.get_imu_accel_y();
  data.imu_accel_z = aquila.get_imu_accel_z();
  data.imu_gyro_x = aquila.get_imu_gyro_x();
  data.imu_gyro_y = aquila.get_imu_gyro_y();
  data.imu_gyro_z = aquila.get_imu_gyro_z();

  data.est_altitude = altitude;
  data.est_velocity = velocity;

  aquila.transmit_telem((uint8_t)(sizeof data), (char*)&data);
  
}