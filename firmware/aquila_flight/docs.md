# Aquila Flight Software Documentation

## Contents

**Requirement-to-Code Tracking**

**Hardware Interface**

**Design**

- System States
- Background Operations
- Serial Interface


## Requirement-to-Code Tracking

To ensure the software meets all high-level requirements and does not contain any unused code, sections of the requirements are linked to sections of the source code. These are indicated by square brackets containing a number. The source code is commented with corresponding numbers to indicate where these requirements are implemented. For example a requirement may say “When X is true, Y should occur \[42]” and the corresponding section of code will have a comment “// REQ\[42]”. Where a single section of code serves to implement several requirements, the comment contains all of them e.g. “// REQ\[42]\[45]\[51]”. These should be standalone comments at the beginning of blocks of code or at the end of specific lines.


## Hardware Interface

A library called ‘aquila\_interface’ has been written to interface with the sensors and peripherals on the board. This is bare-bones protocol level code, and does not have a set of formal requirements associated with it at this time.


## High-Level Requirements

The architecture of the Aquila Flight program comprises two types of code: mode based; and background. The system state represents the current stage of flight, with transitions occurring when specific conditions are met. The transition from one mode to another may be associated with one or more actions such as actuation of a vehicle system. Background functions are run repeatedly at set rates to update sensor readings or log data. Some background functions may run only when the system is in specific modes.


### System States

There are seven total flight stages, represented by a mode. \[1]

| **Num** | **Name** | **Criteria to enter**                            | **Actions** |
| ------- | -------- | ------------------------------------------------ | ------------------------------------------------- |
| 0       | LOCKED   | Startup \[2], lock command received \[45]        | Set altitude and velocity estimates to zero \[46] |
| 1       | PAD      | unlock command received \[3]                     |                                                   |
| 2       | BURN     | velocity > 10m/s \[4]                            |                                                   |
| 3       | COAST    | acceleration < 0 \[5]                            |                                                   |
| 4       | APOGEE   | velocity < 0 \[6]                                | Activate bottle burst pyro \[9]                   |
| 5       | DESCENT  | barometric altitude below 500m \[7]              | Release parachute servos \[10]                    |
| 6       | LAND     | Barometric pressure constant for 10 seconds \[8] | Reduce logging rate to 10Hz \[11]                 |


### Background Operations



| **Operation**            | **Modes**               | **Rate**    | **Description** |
| ------------------------ | ----------------------- | ----------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Acceleration integration | all except LOCKED \[18] | \~1kHz\[24] | The ADXL357 raises an interrupt when it has a new reading. The handler updates the velocity and altitude estimates \[30]. When in PAD state, accelerations < 0.01g are discarded \[47]. |
| Sensor updates           | All \[19]               | 100Hz \[25] | All sensors are read and readings stored \[31]                                                                                                                                          |
| Data logging             | All \[20]               | 100Hz\[26]  | Write all sensor readings and system parameters to SD card \[32]                                                                                                                        |
| Telemetry transmission\* | All \[21]               | 10Hz\[27]   | Transmit packet of sensor readings and system parameters over radio \[33]                                                                                                               |
| Serial write             | LOCKED and PAD \[22]    | 10Hz\[28]   | Send sensor readings and system parameters over Serial \[34]                                                                                                                            |
| Serial read              | LOCKED and PAD \[23]    | 100Hz\[29]  | Read serial port for commands \[35]                                                                                                                                                     |


### Serial Interface

It is desirable to have a serial interface available in flight software to monitor parameters and send commands from a computer on the launch pad.

This is a work in progress but may look something like the following.


| **Command** | **Action** |
| ----------- | ------------------------------------------------------------------ |
| N           | Print system state to console \[36]                                |
| S           | Start printing system state at a rate of 10Hz \[37]                |
| P           | Stop printing system state \[38]                                   |
| L           | Put system into LOCKED state and reset altitude and velocity \[39] |
| U           | Put system into PAD state \[40]                                    |
| V\*         | Toggle servo position - LOCKED state only \[41]                    |
| A           | Arm pyrotechnics \[42]                                             |
| D           | Disarm pyrotechnics \[43]                                          |
| C           | Calibrate launch pad barometric pressure \[49]                     |

\* requires pyrotechnics to be armed \[44]


### Recovery Safety

To prevent unintentional release of the spring loaded recovery system, the servos should be set to the latched position whenever the pyro channels are armed \[48].
