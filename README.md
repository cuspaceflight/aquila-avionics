# Aquila Avionics
Schematics and firmware for Aquila flight computer.

## Functions
* **Altimetry** - Accurately estimate altitude with barometer, GPS and accelerometer
* **Recovery** - Activate pyrotechnics to deploy parachute stages at appropriate points during descent
*  **Data logging** - Log altitude data and other parameters for post-flight analysis
* **Telemetry** - Transmit data to a ground station during flight as a backup should the vehicle be lost
* **Location** - Continually transmit location after landing to aid finding the vehicle

## Specifications
* **Mass** -  2kg
* **Acceleration** - 30g
* **Altitude** - 150km
* **Speed** - 1500m/s
* **Flexibility** - Exact flight and recovery profile is TBC
*  **Budget** - £150

# Overview
What follows here is a very brief overview of the design, broken down by component. It's aim is to familiarise the reader with what this project includes and some of the decisions made.
## Batteries
The computer is designed to run from two 18650 Li-Ions in series. A battery management chip monitors the cell voltages and automatically balances them if necessary. There is no onboard charger, so batteries must be charged separately before installation/flights. Ideally cells with built-in under-volt protection should be used. The battery holders are physically mounted to the board (but will be mechanically supported by additional hardware). Power can be switched on and off via a screw terminal.  To connect the batteries to the rest of the board, a jumper is secured between the two terminals. A potential divider allows the microcontroller to directly monitor the battery voltages.

Additionally, a 3V CR2032 type cell is mounted to the board. This maintains real time clocks in the microcontroller and GPS receiver, improving resilience against power cycle events during flight.
## Power supplies
The board has two power supplies: 3.3V 3A and 5V 3A. The 3.3V supply powers most of the electronics on the board and is permanently on. The 5V supply is dedicated to pyrotechnics and servos as required by the recovery system. It is switched on and off by the microcontroller to conserve power when not needed and as a safety layer. A safety pin (in the form of a 2.5 mm audio jack) can be inserted into a socket on the board to physically disconnect the pyro channels from the power supply, eliminating the risk of unintentionally activating pyrotechnics during any activities leading up to launch. 
## Sensors
### Barometer
A barometer is mounted on the board to measure atmospheric pressure. This is particularly useful during descent to deploy parachute stages at appropriate altitudes close to the ground. The model used is a MS5611-01BA03. It has a resolution on the order of tenths of millibar, but a minimum pressure of 10 millibar limits it's usefulness to below 30 km altitude.
### GPS
A U-blox MAX-M8Q receiver is included for completeness. CoCom regulations limit the operation of civilian GPS chips faster than 1000 knots (~500 m/s) and above 18 km, both of which will be exceeded early in Griffin's flight profile. Therefore the GPS will not be relied on for navigational purposes, but purely for data collection. It may be the case that once the rocket slows below 1000 knots near apogee, a fix can once again be acquired. This is uncertain as the manufacturer does not specify behaviour at these extremes.

An additional Low-Noise Amplifier and band-pass filter are included in the signal path as antenna challenges and telemetry radio interference will degrade signal quality.
### Accelerometer
The most important sensor for navigation and apogee deployment is the accelerometer. An inertial navigation system will be implemented to estimate the vehicle's velocity and altitude based on accelerometer readings. The double integration of acceleration to velocity leads to errors on the order of time squared, so it is imperative the accelerometer readings are low noise and very stable. Combined with this requirement, a high g range is required as the rocket will accelerate at up to 30g at some points.  An Analog Devices ADXL357 is chosen. It boasts 20 bit resolution, ultra-low noise and high bias stability with a range of +/- 40g.
## Telemetry
An Si4463 radio transceiver provides a bi-directional radio link with a ground station. This will be useful for configuring the computer during launch preparations as well as backing up as much data as possible should the vehicle be lost. A secondary purpose for the radio will be locating the vehicle after a successful recovery. The current setup is designed for operation in the 915 MHz ISM band, subject to regulatory compliance.
## Interfaces
Connectors on the board include: 
* **female SMA** for GPS antenna
* **female SMA** for telemetry antenna
* **6-way Molex Nano-Fit** for a separate, remote, barometer, in case structural limitations prevent the avionics bay being vented to the atmosphere
* **6-way Molex Nano-Fit** for up to four servo motors
* **4x 2-way screw terminal** for up to four pyrotechnics
* **Micro USB** for programming and serial communication

The pyro channels can provide 5V at 1A continuous as limited by the FETs, 3A peak as limited by the power supply. They also include individual continuity measurement by draining approximately 50uA through the pyro.
## Microcontroller
A Teensy 4.1 was selected as the microcontroller. It is based around an ARM Cortex-M7 running at 600MHz. The first reason for this choice is that it includes many features we would only have to implement ourselves such as a real time clock, MicroSD storage, USB interface etc. Secondly, it is compatible with the Arduino ecosystem, granting access to many existing libraries and improving access to the firmware for CUSF members.
## Antennas
Antennas are an area of ongoing research, hence nothing has been included in this repo yet. Carbon-fibre reinforced polymer (CFRP) construction precludes antennas being mounted inside the rocket body, and extreme aerodynamic and aerothermal loads make any kind of protruding antenna impossible. This leaves the only possible solution as conformal patch antenna arrays. Methods to design and optimise these antennas and feed networks are currently being developed.
