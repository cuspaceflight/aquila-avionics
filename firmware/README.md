#### Important:
Copy the "aquila_interface" folder into your Arduino/libraries directory

Only copy one of (aquila_interface.cpp, aquila_interface.h) OR (aquila_hil_interface.cpp, aquila_hil_interface.h) into the Arduino libriaries folder. Code will not compile if both are in the libraries folder.

Make sure aquila_flight.ino is including the correct file.

#### Guide to files
* aquila_flight - actual flight program
* aquila_interface - library for interacting with Aquila hardware
* individual_sensor_tests - a small program for each sensor, used to test protocols
* inertial_calibration - calculates two-point calibrations for accelerometers and gyroscopes by having you hold the board in different orientations
* sensor_dump - reads all sensors using aquila_interface and prints their values to serial