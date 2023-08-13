#### Important:
Copy the `aquila_interface` folder into your `Arduino/libraries` directory before compiling. If you wish to run Hardware-In-Loop (HIL) testing, also copy `aquila_hil_interface.h` and `aquila_hil_interface.cpp` into this libraries folder.


#### Guide to files
* aquila_flight - actual flight program
* aquila_interface - library for interacting with Aquila hardware
* individual_sensor_tests - a small program for each sensor, used to test protocols
* inertial_calibration - calculates two-point calibrations for accelerometers and gyroscopes by having you hold the board in different orientations
* sensor_dump - reads all sensors using aquila_interface and prints their values to serial

#### HIL Testing
To run an HIL test on the flight computer with imitated sensor readings from a simulated flight, uncomment the indicated line at the top of `aquila_flight.ino`. The "liftoff" will occur automatically 30 seconds after startup, so make sure to issue the "unlock" command within this time.