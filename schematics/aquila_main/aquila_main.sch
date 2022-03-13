EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Aquila Avionics Main Board"
Date "2022-03-02"
Rev ""
Comp "Cambridge University Spaceflight"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Daniel Fearn"
$EndDescr
$Comp
L RF_GPS:MAX-M8W U?
U 1 1 62143EF4
P 9450 2250
F 0 "U?" H 9450 1461 50  0000 C CNN
F 1 "MAX-M8W" H 9450 1370 50  0000 C CNN
F 2 "RF_GPS:ublox_MAX" H 9850 1600 50  0001 C CNN
F 3 "https://www.u-blox.com/sites/default/files/MAX-M8-FW3_DataSheet_%28UBX-15031506%29.pdf" H 9450 2250 50  0001 C CNN
	1    9450 2250
	1    0    0    -1  
$EndComp
$Comp
L teensy:Teensy4.1 U?
U 1 1 62144D72
P 2750 9200
F 0 "U?" H 2750 11765 50  0000 C CNN
F 1 "Teensy4.1" H 2750 11674 50  0000 C CNN
F 2 "" H 2350 9600 50  0001 C CNN
F 3 "" H 2350 9600 50  0001 C CNN
	1    2750 9200
	1    0    0    -1  
$EndComp
$Comp
L aquila_main-rescue:L-cusf-kicad L1
U 1 1 621BC7E3
P 3000 1100
F 0 "L1" H 3050 1281 50  0000 C CNN
F 1 "2u2" H 3050 1190 50  0000 C CNN
F 2 "" H 3000 1100 50  0001 C CNN
F 3 "" H 3000 1100 50  0001 C CNN
	1    3000 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 1100 3000 1100
Text Label 3300 1700 0    50   ~ 0
PG
Wire Wire Line
	3100 1100 3150 1100
Connection ~ 2100 1900
Wire Wire Line
	2100 1900 2100 2000
Wire Wire Line
	2100 1800 2100 1900
Connection ~ 2100 2200
Wire Wire Line
	2100 2200 2100 2300
Connection ~ 2100 2000
Connection ~ 2100 2100
Wire Wire Line
	2100 2100 2100 2200
Wire Wire Line
	2100 2000 2100 2100
Connection ~ 2900 1100
Connection ~ 2100 1300
Wire Wire Line
	2100 1300 2100 1400
Connection ~ 2100 1200
Wire Wire Line
	2100 1200 2100 1300
Wire Wire Line
	2100 1100 2100 1200
Connection ~ 2900 1200
Wire Wire Line
	2900 1300 2900 1200
Wire Wire Line
	2900 1100 2900 1200
$Comp
L aquila_main-rescue:R-cusf-kicad R1
U 1 1 621BE318
P 3050 1550
F 0 "R1" V 3054 1594 50  0000 L CNN
F 1 "100k" V 3145 1594 50  0000 L CNN
F 2 "" H 3050 1550 50  0001 C CNN
F 3 "" H 3050 1550 50  0001 C CNN
	1    3050 1550
	0    1    1    0   
$EndComp
$Comp
L aquila_main-rescue:TPS62132-cusf-kicad IC1
U 1 1 621B6BB0
P 2500 1700
F 0 "IC1" H 2500 2525 50  0000 C CNN
F 1 "TPS62152" H 2500 2434 50  0000 C CNN
F 2 "cusf:QFN-16-EP-TI" H 2200 900 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps62132.pdf" H 2200 800 50  0001 L CNN
F 4 "2492468" H 2200 700 50  0001 L CNN "Farnell"
	1    2500 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 1700 3050 1700
Wire Wire Line
	2900 1600 2900 1500
Wire Wire Line
	2900 1500 3050 1500
Wire Wire Line
	3150 1500 3150 1100
Connection ~ 2900 1500
Connection ~ 3150 1100
Wire Wire Line
	3150 1100 3450 1100
Wire Wire Line
	3050 1550 3050 1500
Connection ~ 3050 1500
Wire Wire Line
	3050 1500 3150 1500
Wire Wire Line
	3050 1650 3050 1700
Connection ~ 3050 1700
Wire Wire Line
	3050 1700 3300 1700
$Comp
L aquila_main-rescue:C-cusf-kicad C1
U 1 1 621C7671
P 3450 1150
F 0 "C1" V 3454 1208 50  0000 L CNN
F 1 "22u" V 3545 1208 50  0000 L CNN
F 2 "" H 3450 1150 50  0001 C CNN
F 3 "" H 3450 1150 50  0001 C CNN
	1    3450 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 1150 3450 1100
Connection ~ 3450 1100
Wire Wire Line
	3450 1350 3450 1250
$Comp
L aquila_main-rescue:C-cusf-kicad C2
U 1 1 621C9BB4
P 1950 1600
F 0 "C2" H 2000 1795 50  0000 C CNN
F 1 "3n3" H 2000 1704 50  0000 C CNN
F 2 "" H 1950 1600 50  0001 C CNN
F 3 "" H 1950 1600 50  0001 C CNN
	1    1950 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 1600 2100 1600
Wire Wire Line
	2100 2300 2100 2400
Connection ~ 2100 2300
$Comp
L power:GND #PWR?
U 1 1 621CD2DB
P 3450 1350
F 0 "#PWR?" H 3450 1100 50  0001 C CNN
F 1 "GND" H 3455 1177 50  0000 C CNN
F 2 "" H 3450 1350 50  0001 C CNN
F 3 "" H 3450 1350 50  0001 C CNN
	1    3450 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 621CD85E
P 2100 2400
F 0 "#PWR?" H 2100 2150 50  0001 C CNN
F 1 "GND" H 2105 2227 50  0000 C CNN
F 2 "" H 2100 2400 50  0001 C CNN
F 3 "" H 2100 2400 50  0001 C CNN
	1    2100 2400
	1    0    0    -1  
$EndComp
$Comp
L aquila_main-rescue:C-cusf-kicad C3
U 1 1 621CE116
P 1650 1300
F 0 "C3" V 1654 1358 50  0000 L CNN
F 1 "100n" V 1745 1358 50  0000 L CNN
F 2 "" H 1650 1300 50  0001 C CNN
F 3 "" H 1650 1300 50  0001 C CNN
	1    1650 1300
	0    1    1    0   
$EndComp
$Comp
L aquila_main-rescue:C-cusf-kicad C4
U 1 1 621CE655
P 1350 1300
F 0 "C4" V 1354 1358 50  0000 L CNN
F 1 "10u" V 1445 1358 50  0000 L CNN
F 2 "" H 1350 1300 50  0001 C CNN
F 3 "" H 1350 1300 50  0001 C CNN
	1    1350 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	1650 1300 1650 1100
Wire Wire Line
	1650 1100 2100 1100
Connection ~ 2100 1100
Wire Wire Line
	1350 1300 1350 1100
Wire Wire Line
	1350 1100 1650 1100
Connection ~ 1650 1100
Wire Wire Line
	1650 1400 1650 1600
Wire Wire Line
	1650 1600 1950 1600
Wire Wire Line
	1350 1400 1350 1600
Wire Wire Line
	1350 1600 1650 1600
Connection ~ 1650 1600
$Comp
L power:GND #PWR?
U 1 1 621D0865
P 1650 1600
F 0 "#PWR?" H 1650 1350 50  0001 C CNN
F 1 "GND" H 1655 1427 50  0000 C CNN
F 2 "" H 1650 1600 50  0001 C CNN
F 3 "" H 1650 1600 50  0001 C CNN
	1    1650 1600
	1    0    0    -1  
$EndComp
Text Label 1350 1100 2    50   ~ 0
BATT_P
Text Label 1350 2300 2    50   ~ 0
BATT_N
Wire Wire Line
	2100 2300 1350 2300
$Comp
L aquila_main-rescue:3v3-cusf-kicad #PWR?
U 1 1 621D7AA7
P 3450 1100
F 0 "#PWR?" H 3450 1210 50  0001 L CNN
F 1 "3v3" H 3450 1223 50  0000 C CNN
F 2 "" H 3450 1100 50  0001 C CNN
F 3 "" H 3450 1100 50  0001 C CNN
	1    3450 1100
	1    0    0    -1  
$EndComp
Wire Notes Line
	3800 800  3800 2650
Wire Notes Line
	1000 2650 1000 800 
Text Notes 3150 2600 0    50   ~ 0
1A, 3.3V Supply
$Comp
L aquila_main-rescue:Si5515CDC-cusf-kicad Q?
U 1 1 6220014D
P 12700 4750
F 0 "Q?" H 12848 4796 50  0000 L CNN
F 1 "Si5515CDC" H 12848 4705 50  0000 L CNN
F 2 "cusf:ChipFET-1206-8" H 12700 4000 50  0001 C CNN
F 3 "http://www.vishay.com/docs/68747/si5515cd.pdf" H 12700 4200 50  0001 C CNN
F 4 "2335332" H 12700 4100 50  0001 C CNN "Farnell"
	1    12700 4750
	1    0    0    -1  
$EndComp
$Comp
L aquila_main-rescue:Si5515CDC-cusf-kicad Q?
U 2 1 62201137
P 13350 4500
F 0 "Q?" H 13100 4550 50  0000 L CNN
F 1 "Si5515CDC" H 12850 4450 50  0000 L CNN
F 2 "cusf:ChipFET-1206-8" H 13350 3750 50  0001 C CNN
F 3 "http://www.vishay.com/docs/68747/si5515cd.pdf" H 13350 3950 50  0001 C CNN
F 4 "2335332" H 13350 3850 50  0001 C CNN "Farnell"
	2    13350 4500
	1    0    0    -1  
$EndComp
$Comp
L aquila_main-rescue:L-cusf-kicad L2
U 1 1 622093DB
P 3000 3000
F 0 "L2" H 3050 3181 50  0000 C CNN
F 1 "2u2" H 3050 3090 50  0000 C CNN
F 2 "" H 3000 3000 50  0001 C CNN
F 3 "" H 3000 3000 50  0001 C CNN
	1    3000 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3000 3000 3000
Text Label 3300 3600 0    50   ~ 0
pyro_PG
Wire Wire Line
	3100 3000 3150 3000
Connection ~ 2100 3800
Wire Wire Line
	2100 3800 2100 3900
Wire Wire Line
	2100 3700 2100 3800
Connection ~ 2100 4100
Wire Wire Line
	2100 4100 2100 4200
Connection ~ 2100 3900
Connection ~ 2100 4000
Wire Wire Line
	2100 4000 2100 4100
Wire Wire Line
	2100 3900 2100 4000
Connection ~ 2900 3000
Connection ~ 2100 3100
Wire Wire Line
	2100 3100 2100 3200
Wire Wire Line
	2100 3000 2100 3100
Connection ~ 2900 3100
Wire Wire Line
	2900 3200 2900 3100
Wire Wire Line
	2900 3000 2900 3100
$Comp
L aquila_main-rescue:TPS62132-cusf-kicad IC2
U 1 1 622093FD
P 2500 3600
F 0 "IC2" H 2500 4425 50  0000 C CNN
F 1 "TPS62132" H 2500 4334 50  0000 C CNN
F 2 "cusf:QFN-16-EP-TI" H 2200 2800 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps62133.pdf" H 2200 2700 50  0001 L CNN
F 4 "2492468" H 2200 2600 50  0001 L CNN "Farnell"
	1    2500 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3600 3050 3600
Wire Wire Line
	2900 3500 2900 3400
Wire Wire Line
	2900 3400 3050 3400
Wire Wire Line
	3150 3400 3150 3000
Connection ~ 2900 3400
Wire Wire Line
	3050 3450 3050 3400
Connection ~ 3050 3400
Wire Wire Line
	3050 3400 3150 3400
Wire Wire Line
	3050 3550 3050 3600
Connection ~ 3050 3600
Wire Wire Line
	3050 3600 3300 3600
$Comp
L aquila_main-rescue:C-cusf-kicad C5
U 1 1 62209410
P 3450 3050
F 0 "C5" V 3454 3108 50  0000 L CNN
F 1 "22u" V 3545 3108 50  0000 L CNN
F 2 "" H 3450 3050 50  0001 C CNN
F 3 "" H 3450 3050 50  0001 C CNN
	1    3450 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 3250 3450 3150
Wire Wire Line
	2100 4200 2100 4300
Connection ~ 2100 4200
$Comp
L power:GND #PWR?
U 1 1 62209422
P 3450 3250
F 0 "#PWR?" H 3450 3000 50  0001 C CNN
F 1 "GND" H 3455 3077 50  0000 C CNN
F 2 "" H 3450 3250 50  0001 C CNN
F 3 "" H 3450 3250 50  0001 C CNN
	1    3450 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62209428
P 2100 4300
F 0 "#PWR?" H 2100 4050 50  0001 C CNN
F 1 "GND" H 2105 4127 50  0000 C CNN
F 2 "" H 2100 4300 50  0001 C CNN
F 3 "" H 2100 4300 50  0001 C CNN
	1    2100 4300
	1    0    0    -1  
$EndComp
Connection ~ 2100 3000
Text Label 1350 3000 2    50   ~ 0
BATT_P
Text Label 1350 4200 2    50   ~ 0
BATT_N
Wire Notes Line
	1000 4550 1000 2700
Text Notes 2750 4500 0    50   ~ 0
3A, 3.3V  for Pyrotechnics
Wire Wire Line
	3150 3000 3450 3000
Wire Wire Line
	3450 3000 3450 3050
Connection ~ 3150 3000
$Comp
L aquila_main-rescue:R-cusf-kicad R?
U 1 1 62220D78
P 12500 4950
F 0 "R?" V 12504 4994 50  0000 L CNN
F 1 "10k" V 12595 4994 50  0000 L CNN
F 2 "" H 12500 4950 50  0001 C CNN
F 3 "" H 12500 4950 50  0001 C CNN
	1    12500 4950
	0    1    1    0   
$EndComp
Wire Wire Line
	12500 4850 12500 4950
Wire Wire Line
	12500 5050 12500 5150
$Comp
L power:GND #PWR?
U 1 1 62226CD6
P 12500 5150
F 0 "#PWR?" H 12500 4900 50  0001 C CNN
F 1 "GND" H 12505 4977 50  0000 C CNN
F 2 "" H 12500 5150 50  0001 C CNN
F 3 "" H 12500 5150 50  0001 C CNN
	1    12500 5150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 62227685
P 13750 5050
F 0 "J?" H 13830 5042 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 13830 4951 50  0000 L CNN
F 2 "" H 13750 5050 50  0001 C CNN
F 3 "~" H 13750 5050 50  0001 C CNN
	1    13750 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	12800 4550 12700 4550
Wire Wire Line
	12700 4550 12700 4400
Connection ~ 12700 4550
$Comp
L aquila_main-rescue:R-cusf-kicad R?
U 1 1 622379D8
P 12700 4250
F 0 "R?" V 12704 4294 50  0000 L CNN
F 1 "10k" V 12795 4294 50  0000 L CNN
F 2 "" H 12700 4250 50  0001 C CNN
F 3 "" H 12700 4250 50  0001 C CNN
	1    12700 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	12700 4250 12700 4200
Wire Wire Line
	12700 4350 12700 4400
Wire Wire Line
	13350 4300 13350 4200
Wire Wire Line
	13450 4700 13350 4700
Wire Wire Line
	12500 5150 12700 5150
Connection ~ 12500 5150
Wire Wire Line
	12700 4950 12700 5150
Text Label 12350 4850 2    50   ~ 0
pyro_ch1
$Comp
L aquila_main-rescue:R-cusf-kicad R?
U 1 1 62252943
P 13550 4400
F 0 "R?" V 13554 4444 50  0000 L CNN
F 1 "100k" V 13645 4444 50  0000 L CNN
F 2 "" H 13550 4400 50  0001 C CNN
F 3 "" H 13550 4400 50  0001 C CNN
	1    13550 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	13550 4200 13550 4400
Wire Wire Line
	13550 4500 13550 4700
Wire Wire Line
	13350 4200 13550 4200
Connection ~ 13350 4200
Wire Wire Line
	13550 5050 13550 4700
Wire Wire Line
	13550 4700 13450 4700
Connection ~ 13450 4700
Wire Wire Line
	13550 4700 13700 4700
Text Label 13700 4700 0    50   ~ 0
pyro_cont1
Wire Notes Line
	3800 2700 3800 4550
Text Label 3450 3000 0    50   ~ 0
pyro_pwr
Wire Notes Line
	1000 2650 3800 2650
Wire Notes Line
	1000 2700 3800 2700
Wire Notes Line
	1000 4550 3800 4550
Wire Notes Line
	1000 800  3800 800 
Text Label 12350 4200 2    50   ~ 0
pyro_pwr
Connection ~ 13550 4700
Wire Wire Line
	13550 5150 12700 5150
Connection ~ 12700 5150
$Comp
L aquila_main-rescue:C-cusf-kicad C6
U 1 1 623162D2
P 2100 3650
F 0 "C6" V 2196 3592 50  0000 R CNN
F 1 "3n3" V 2105 3592 50  0000 R CNN
F 2 "" H 2100 3650 50  0001 C CNN
F 3 "" H 2100 3650 50  0001 C CNN
	1    2100 3650
	0    1    -1   0   
$EndComp
Text Label 1450 3550 2    50   ~ 0
pyro_en
$Comp
L aquila_main-rescue:C-cusf-kicad C7
U 1 1 6220942E
P 1600 3050
F 0 "C7" V 1604 3108 50  0000 L CNN
F 1 "100n" V 1695 3108 50  0000 L CNN
F 2 "" H 1600 3050 50  0001 C CNN
F 3 "" H 1600 3050 50  0001 C CNN
	1    1600 3050
	0    1    1    0   
$EndComp
$Comp
L aquila_main-rescue:C-cusf-kicad C8
U 1 1 62209434
P 1350 3050
F 0 "C8" V 1354 3108 50  0000 L CNN
F 1 "10u" V 1445 3108 50  0000 L CNN
F 2 "" H 1350 3050 50  0001 C CNN
F 3 "" H 1350 3050 50  0001 C CNN
	1    1350 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	1350 3000 1600 3000
Wire Wire Line
	1350 3050 1350 3000
Wire Wire Line
	1600 3050 1600 3000
Connection ~ 1600 3000
Wire Wire Line
	1600 3000 2100 3000
Wire Wire Line
	2100 3500 2100 3550
Wire Wire Line
	2100 3650 2100 3700
Connection ~ 2100 3700
$Comp
L power:GND #PWR?
U 1 1 62440965
P 1600 3300
F 0 "#PWR?" H 1600 3050 50  0001 C CNN
F 1 "GND" H 1605 3127 50  0000 C CNN
F 2 "" H 1600 3300 50  0001 C CNN
F 3 "" H 1600 3300 50  0001 C CNN
	1    1600 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 3300 1600 3300
Connection ~ 1600 3300
$Comp
L aquila_main-rescue:R-cusf-kicad R2
U 1 1 62468E4B
P 3050 3550
F 0 "R2" V 3146 3506 50  0000 R CNN
F 1 "100k" V 3055 3506 50  0000 R CNN
F 2 "" H 3050 3550 50  0001 C CNN
F 3 "" H 3050 3550 50  0001 C CNN
	1    3050 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1350 4200 2100 4200
$Comp
L aquila_main-rescue:R-cusf-kicad R3
U 1 1 624827F3
P 1850 3300
F 0 "R3" H 1900 3119 50  0000 C CNN
F 1 "10k" H 1900 3210 50  0000 C CNN
F 2 "" H 1850 3300 50  0001 C CNN
F 3 "" H 1850 3300 50  0001 C CNN
	1    1850 3300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1850 3300 1900 3300
Wire Wire Line
	1600 3300 1750 3300
Wire Wire Line
	1900 3300 1900 3550
Wire Notes Line
	11950 4100 11950 5450
Wire Notes Line
	14750 5450 14750 4100
Wire Notes Line
	14750 4100 11950 4100
Wire Notes Line
	11950 5450 14750 5450
Text Notes 14150 5400 0    50   ~ 0
Pyro channel 1
Wire Wire Line
	1350 3150 1350 3300
Wire Wire Line
	1600 3150 1600 3300
Wire Wire Line
	12500 4850 12350 4850
Connection ~ 12500 4850
Connection ~ 12700 4200
Wire Wire Line
	12700 4200 12350 4200
Wire Wire Line
	12700 4200 13350 4200
Connection ~ 12700 4400
Wire Wire Line
	12700 4400 13150 4400
$Comp
L aquila:ADXL357 U?
U 1 1 625041A3
P 5850 900
F 0 "U?" H 5850 925 50  0000 C CNN
F 1 "ADXL357" H 5850 834 50  0000 C CNN
F 2 "" H 5850 833 50  0001 C CNN
F 3 "" H 5850 900 50  0001 C CNN
	1    5850 900 
	1    0    0    -1  
$EndComp
$Comp
L aquila_main-rescue:3v3-cusf-kicad #PWR?
U 1 1 625137DC
P 7250 1400
F 0 "#PWR?" H 7250 1510 50  0001 L CNN
F 1 "3v3" H 7250 1523 50  0000 C CNN
F 2 "" H 7250 1400 50  0001 C CNN
F 3 "" H 7250 1400 50  0001 C CNN
	1    7250 1400
	1    0    0    -1  
$EndComp
$Comp
L aquila_main-rescue:C-cusf-kicad C?
U 1 1 62513E1F
P 7250 1450
F 0 "C?" V 7254 1508 50  0000 L CNN
F 1 "10u" V 7345 1508 50  0000 L CNN
F 2 "" H 7250 1450 50  0001 C CNN
F 3 "" H 7250 1450 50  0001 C CNN
	1    7250 1450
	0    1    1    0   
$EndComp
$Comp
L aquila_main-rescue:C-cusf-kicad C?
U 1 1 6251A2DF
P 7000 1450
F 0 "C?" V 7004 1508 50  0000 L CNN
F 1 "0u1" V 7095 1508 50  0000 L CNN
F 2 "" H 7000 1450 50  0001 C CNN
F 3 "" H 7000 1450 50  0001 C CNN
	1    7000 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	7250 1450 7250 1400
Connection ~ 7250 1400
Wire Wire Line
	7000 1450 7000 1400
Connection ~ 7000 1400
Wire Wire Line
	7000 1400 7250 1400
Wire Wire Line
	7000 1550 7000 1600
Wire Wire Line
	7000 1600 7250 1600
Wire Wire Line
	7250 1600 7250 1550
$Comp
L aquila_main-rescue:C-cusf-kicad C?
U 1 1 62535AB8
P 6950 1700
F 0 "C?" V 6954 1758 50  0000 L CNN
F 1 "10u" V 7045 1758 50  0000 L CNN
F 2 "" H 6950 1700 50  0001 C CNN
F 3 "" H 6950 1700 50  0001 C CNN
	1    6950 1700
	0    1    1    0   
$EndComp
$Comp
L aquila_main-rescue:C-cusf-kicad C?
U 1 1 62535ABE
P 6700 1700
F 0 "C?" V 6704 1758 50  0000 L CNN
F 1 "0u1" V 6795 1758 50  0000 L CNN
F 2 "" H 6700 1700 50  0001 C CNN
F 3 "" H 6700 1700 50  0001 C CNN
	1    6700 1700
	0    1    1    0   
$EndComp
Wire Wire Line
	6950 1850 6950 1800
Wire Wire Line
	6450 1400 7000 1400
Wire Wire Line
	6450 1600 6600 1600
Wire Wire Line
	6600 1600 6600 2150
$Comp
L power:GND #PWR?
U 1 1 62546C2D
P 6600 2150
F 0 "#PWR?" H 6600 1900 50  0001 C CNN
F 1 "GND" H 6605 1977 50  0000 C CNN
F 2 "" H 6600 2150 50  0001 C CNN
F 3 "" H 6600 2150 50  0001 C CNN
	1    6600 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 1600 7250 2150
Connection ~ 7250 1600
Connection ~ 6600 2150
Wire Wire Line
	6700 1800 6700 1850
Wire Wire Line
	6950 1700 6950 1650
Wire Wire Line
	6950 1650 6800 1650
Wire Wire Line
	6700 1650 6700 1700
Wire Wire Line
	6700 1850 6800 1850
Wire Wire Line
	6600 2150 6800 2150
Wire Wire Line
	6800 1500 6800 1650
Wire Wire Line
	6450 1500 6800 1500
Connection ~ 6800 1650
Wire Wire Line
	6800 1650 6700 1650
Wire Wire Line
	6800 1850 6800 2150
Connection ~ 6800 1850
Wire Wire Line
	6800 1850 6950 1850
Connection ~ 6800 2150
Wire Wire Line
	6800 2150 7250 2150
$Comp
L aquila_main-rescue:C-cusf-kicad C?
U 1 1 6257E52C
P 6550 1950
F 0 "C?" V 6554 2008 50  0000 L CNN
F 1 "10u" V 6645 2008 50  0000 L CNN
F 2 "" H 6550 1950 50  0001 C CNN
F 3 "" H 6550 1950 50  0001 C CNN
	1    6550 1950
	0    1    1    0   
$EndComp
$Comp
L aquila_main-rescue:C-cusf-kicad C?
U 1 1 6257E532
P 6300 1950
F 0 "C?" V 6304 2008 50  0000 L CNN
F 1 "0u1" V 6395 2008 50  0000 L CNN
F 2 "" H 6300 1950 50  0001 C CNN
F 3 "" H 6300 1950 50  0001 C CNN
	1    6300 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	6550 2100 6550 2050
Wire Wire Line
	6300 2050 6300 2100
Wire Wire Line
	6550 1950 6550 1900
Wire Wire Line
	6300 1900 6300 1950
Wire Wire Line
	6300 1900 6450 1900
Wire Wire Line
	6300 2100 6450 2100
Wire Wire Line
	6450 1700 6450 1900
Connection ~ 6450 1900
Wire Wire Line
	6450 1900 6550 1900
Wire Wire Line
	6450 2100 6450 2150
Wire Wire Line
	6450 2150 6600 2150
Connection ~ 6450 2100
Wire Wire Line
	6450 2100 6550 2100
$Comp
L aquila_main-rescue:C-cusf-kicad C?
U 1 1 6259291D
P 4900 1850
F 0 "C?" V 4904 1908 50  0000 L CNN
F 1 "10u" V 4995 1908 50  0000 L CNN
F 2 "" H 4900 1850 50  0001 C CNN
F 3 "" H 4900 1850 50  0001 C CNN
	1    4900 1850
	0    1    1    0   
$EndComp
$Comp
L aquila_main-rescue:C-cusf-kicad C?
U 1 1 62592923
P 4650 1850
F 0 "C?" V 4654 1908 50  0000 L CNN
F 1 "0u1" V 4745 1908 50  0000 L CNN
F 2 "" H 4650 1850 50  0001 C CNN
F 3 "" H 4650 1850 50  0001 C CNN
	1    4650 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 2000 4900 1950
Wire Wire Line
	4650 1950 4650 2000
Wire Wire Line
	4900 1850 4900 1800
Wire Wire Line
	4650 1800 4650 1850
Wire Wire Line
	5250 1600 5150 1600
Wire Wire Line
	5150 1600 5150 2150
$Comp
L power:GND #PWR?
U 1 1 625A2DA0
P 5150 2150
F 0 "#PWR?" H 5150 1900 50  0001 C CNN
F 1 "GND" H 5155 1977 50  0000 C CNN
F 2 "" H 5150 2150 50  0001 C CNN
F 3 "" H 5150 2150 50  0001 C CNN
	1    5150 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 1800 4800 1800
Connection ~ 5150 2150
Wire Wire Line
	5250 1500 4800 1500
Wire Wire Line
	4800 1500 4800 1800
Connection ~ 4800 1800
Wire Wire Line
	4800 1800 4900 1800
Wire Wire Line
	4650 2000 4800 2000
Wire Wire Line
	4800 2000 4800 2150
Wire Wire Line
	4800 2150 5150 2150
Connection ~ 4800 2000
Wire Wire Line
	4800 2000 4900 2000
$Comp
L aquila_main-rescue:3v3-cusf-kicad #PWR?
U 1 1 625C7175
P 4800 1500
F 0 "#PWR?" H 4800 1610 50  0001 L CNN
F 1 "3v3" H 4800 1623 50  0000 C CNN
F 2 "" H 4800 1500 50  0001 C CNN
F 3 "" H 4800 1500 50  0001 C CNN
	1    4800 1500
	1    0    0    -1  
$EndComp
Connection ~ 4800 1500
Entry Wire Line
	4950 1100 5050 1200
Entry Wire Line
	4950 1200 5050 1300
Entry Wire Line
	4950 1300 5050 1400
Wire Bus Line
	4950 1100 4650 1100
Wire Wire Line
	5250 1200 5050 1200
Wire Wire Line
	5250 1300 5050 1300
Wire Wire Line
	5050 1400 5250 1400
Text Label 5050 1200 0    50   ~ 0
SCLK
Text Label 5050 1300 0    50   ~ 0
MOSI
Text Label 5050 1400 0    50   ~ 0
MISO
Text Label 4650 1100 2    50   ~ 0
SPI1
Wire Wire Line
	5250 1100 5150 1100
Wire Wire Line
	5150 950  4650 950 
Text Label 4650 950  2    50   ~ 0
accel_cs
Wire Wire Line
	5150 1100 5150 950 
Wire Notes Line
	4250 800  7550 800 
Wire Notes Line
	7550 2550 4250 2550
Text Notes 6200 2500 0    50   ~ 0
+/-40g, 70ug res. Accelerometer
Wire Notes Line
	7550 800  7550 2550
Wire Notes Line
	4250 800  4250 2550
NoConn ~ 5250 1700
NoConn ~ 6450 1200
NoConn ~ 6450 1300
Text Label 6700 1100 0    50   ~ 0
accel_drdy
Wire Wire Line
	6450 1100 6700 1100
$Comp
L RF:Si4463 U?
U 1 1 6268F7FD
P 5750 4700
F 0 "U?" H 5750 5600 50  0000 C CNN
F 1 "Si4463" H 5750 5500 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-20-1EP_4x4mm_P0.5mm_EP2.6x2.6mm_ThermalVias" H 5750 5900 50  0001 C CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/Si4464-63-61-60.pdf" H 5450 4600 50  0001 C CNN
	1    5750 4700
	1    0    0    -1  
$EndComp
$Comp
L aquila:120591-1 J?
U 1 1 626A7BFD
P 1550 4650
F 0 "J?" H 1678 4526 50  0000 L CNN
F 1 "120591-1" H 1678 4435 50  0000 L CNN
F 2 "" H 1550 4800 50  0001 C CNN
F 3 "https://www.farnell.com/cad/1815976.pdf" H 1550 4800 50  0001 C CNN
	1    1550 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 4900 1400 5000
$Comp
L power:GND #PWR?
U 1 1 626ADD67
P 1400 5000
F 0 "#PWR?" H 1400 4750 50  0001 C CNN
F 1 "GND" H 1405 4827 50  0000 C CNN
F 2 "" H 1400 5000 50  0001 C CNN
F 3 "" H 1400 5000 50  0001 C CNN
	1    1400 5000
	1    0    0    -1  
$EndComp
Text Label 1250 4750 2    50   ~ 0
vbat
Wire Wire Line
	1250 4750 1400 4750
Wire Notes Line
	1000 4600 3800 4600
Wire Notes Line
	1000 5300 3800 5300
Wire Notes Line
	1000 4600 1000 5300
Wire Notes Line
	3800 4600 3800 5300
Text Notes 2550 5250 0    50   ~ 0
3V CR2032 for Real Time Clock 
Text Notes 2150 10800 0    50   ~ 0
https://github.com/XenGi/teensy_library
Text Notes 2150 10900 0    50   ~ 0
https://github.com/XenGi/teensy.pretty
$Comp
L aquila_main-rescue:3v3-cusf-kicad #PWR?
U 1 1 622BAFBF
P 4900 3000
F 0 "#PWR?" H 4900 3110 50  0001 L CNN
F 1 "3v3" H 4900 3123 50  0000 C CNN
F 2 "" H 4900 3000 50  0001 C CNN
F 3 "" H 4900 3000 50  0001 C CNN
	1    4900 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 3000 4900 3000
$Comp
L cusf-kicad:MS5611-01BA03 IC?
U 1 1 622B2C48
P 5350 3100
F 0 "IC?" H 5400 3425 50  0000 C CNN
F 1 "MS5611-01BA03" H 5400 3334 50  0000 C CNN
F 2 "cusf:MS5611" H 5150 2700 50  0001 L CNN
F 3 "" H 5400 3100 50  0001 C CNN
F 4 "2362662" H 5150 2600 50  0001 L CNN "Farnell"
	1    5350 3100
	1    0    0    -1  
$EndComp
NoConn ~ 5050 3300
$Comp
L power:GND #PWR?
U 1 1 622FE465
P 4900 3250
F 0 "#PWR?" H 4900 3000 50  0001 C CNN
F 1 "GND" H 4905 3077 50  0000 C CNN
F 2 "" H 4900 3250 50  0001 C CNN
F 3 "" H 4900 3250 50  0001 C CNN
	1    4900 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 3200 5000 3200
Wire Wire Line
	4900 3200 4900 3250
Wire Wire Line
	5050 3100 5000 3100
Wire Wire Line
	5000 3100 5000 3200
Connection ~ 5000 3200
Wire Wire Line
	5000 3200 4900 3200
$Comp
L aquila_main-rescue:C-cusf-kicad C?
U 1 1 62311113
P 4900 3050
F 0 "C?" V 4900 2900 50  0000 L CNN
F 1 "0u1" V 5000 2850 50  0000 L CNN
F 2 "" H 4900 3050 50  0001 C CNN
F 3 "" H 4900 3050 50  0001 C CNN
	1    4900 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 3000 4900 3050
Connection ~ 4900 3000
Wire Wire Line
	4900 3150 4900 3200
Connection ~ 4900 3200
Entry Wire Line
	6050 3000 6150 2900
Entry Wire Line
	6050 3100 6150 3000
Entry Wire Line
	6050 3200 6150 3100
Wire Bus Line
	6150 2900 6300 2900
Wire Wire Line
	6050 3000 5750 3000
Wire Wire Line
	5750 3100 6050 3100
Wire Wire Line
	6050 3200 5750 3200
Text Label 5850 3000 0    50   ~ 0
SCLK
Text Label 5850 3100 0    50   ~ 0
MOSI
Text Label 5850 3200 0    50   ~ 0
MISO
Text Label 6300 2900 0    50   ~ 0
SPI2
Wire Wire Line
	5750 3300 6300 3300
Text Label 6300 3300 0    50   ~ 0
baro_cs
Wire Notes Line
	4250 2600 4250 3600
Wire Notes Line
	4250 3600 7550 3600
Wire Notes Line
	7550 3600 7550 2600
Wire Notes Line
	7550 2600 4250 2600
Text Notes 6400 3550 0    50   ~ 0
Barometric Pressure Sensor
Connection ~ 1900 3300
Wire Wire Line
	1900 3300 2100 3300
Wire Wire Line
	1450 3550 1900 3550
Wire Wire Line
	5750 4000 5850 4000
$Comp
L aquila_main-rescue:3v3-cusf-kicad #PWR?
U 1 1 622EE19D
P 4550 4000
F 0 "#PWR?" H 4550 4110 50  0001 L CNN
F 1 "3v3" H 4550 4123 50  0000 C CNN
F 2 "" H 4550 4000 50  0001 C CNN
F 3 "" H 4550 4000 50  0001 C CNN
	1    4550 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 622FD1D4
P 5750 5450
F 0 "#PWR?" H 5750 5200 50  0001 C CNN
F 1 "GND" H 5755 5277 50  0000 C CNN
F 2 "" H 5750 5450 50  0001 C CNN
F 3 "" H 5750 5450 50  0001 C CNN
	1    5750 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 5400 5750 5450
Connection ~ 5750 4000
Wire Wire Line
	5350 4800 5050 4800
Wire Wire Line
	5050 4900 5350 4900
Wire Wire Line
	5350 5000 5050 5000
Text Label 5150 4800 0    50   ~ 0
SCLK
Text Label 5150 4900 0    50   ~ 0
MOSI
Text Label 5150 5000 0    50   ~ 0
MISO
Entry Wire Line
	4950 4700 5050 4800
Entry Wire Line
	4950 4800 5050 4900
Entry Wire Line
	4950 4900 5050 5000
Wire Bus Line
	4950 4700 4850 4700
Text Label 4850 4700 2    50   ~ 0
SPI2
$Comp
L Device:Crystal_Small Y?
U 1 1 623AB755
P 5250 4500
F 0 "Y?" V 5200 4700 50  0000 R CNN
F 1 "30M" V 5300 4750 50  0000 R CNN
F 2 "" H 5250 4500 50  0001 C CNN
F 3 "~" H 5250 4500 50  0001 C CNN
	1    5250 4500
	0    -1   1    0   
$EndComp
Wire Wire Line
	5350 4400 5250 4400
Wire Wire Line
	5350 4600 5250 4600
Text Label 4850 5100 2    50   ~ 0
radio_cs
Text Label 4850 5200 2    50   ~ 0
radio_int
Wire Wire Line
	5350 5100 4850 5100
Wire Wire Line
	5350 5200 4850 5200
NoConn ~ 6150 4900
NoConn ~ 6150 5000
NoConn ~ 6150 5100
NoConn ~ 6150 5200
NoConn ~ 6150 4400
$Comp
L aquila_main-rescue:C-cusf-kicad C?
U 1 1 6245FDD3
P 5050 4050
F 0 "C?" V 5050 3900 50  0000 L CNN
F 1 "1u" V 5150 3850 50  0000 L CNN
F 2 "" H 5050 4050 50  0001 C CNN
F 3 "" H 5050 4050 50  0001 C CNN
	1    5050 4050
	0    1    1    0   
$EndComp
$Comp
L aquila_main-rescue:C-cusf-kicad C?
U 1 1 6246826D
P 4800 4050
F 0 "C?" V 4800 3900 50  0000 L CNN
F 1 "100n" V 4900 3850 50  0000 L CNN
F 2 "" H 4800 4050 50  0001 C CNN
F 3 "" H 4800 4050 50  0001 C CNN
	1    4800 4050
	0    1    1    0   
$EndComp
$Comp
L aquila_main-rescue:C-cusf-kicad C?
U 1 1 624707F0
P 4550 4050
F 0 "C?" V 4550 3900 50  0000 L CNN
F 1 "100p" V 4650 3850 50  0000 L CNN
F 2 "" H 4550 4050 50  0001 C CNN
F 3 "" H 4550 4050 50  0001 C CNN
	1    4550 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	5350 4200 5050 4200
Wire Wire Line
	4550 4200 4550 4150
Wire Wire Line
	4800 4150 4800 4200
Connection ~ 4800 4200
Wire Wire Line
	4800 4200 4550 4200
Wire Wire Line
	5050 4150 5050 4200
Connection ~ 5050 4200
Wire Wire Line
	5050 4200 4800 4200
Wire Wire Line
	4550 4050 4550 4000
Connection ~ 4550 4000
Wire Wire Line
	4550 4000 4800 4000
Wire Wire Line
	4800 4050 4800 4000
Connection ~ 4800 4000
Wire Wire Line
	4800 4000 5050 4000
Wire Wire Line
	5050 4050 5050 4000
Connection ~ 5050 4000
Wire Wire Line
	5050 4000 5750 4000
$Comp
L power:GND #PWR?
U 1 1 624DD7BB
P 4550 4200
F 0 "#PWR?" H 4550 3950 50  0001 C CNN
F 1 "GND" H 4555 4027 50  0000 C CNN
F 2 "" H 4550 4200 50  0001 C CNN
F 3 "" H 4550 4200 50  0001 C CNN
	1    4550 4200
	1    0    0    -1  
$EndComp
Connection ~ 4550 4200
Wire Notes Line
	4250 3650 7550 3650
Wire Notes Line
	7550 3650 7550 5750
Wire Notes Line
	7550 5750 4250 5750
Wire Notes Line
	4250 5750 4250 3650
Text Notes 6900 5700 0    50   ~ 0
Telemetry Radio
Text Label 6350 4200 0    50   ~ 0
radio_tx
Text Label 6350 4600 0    50   ~ 0
radio_rxp
Text Label 6350 4700 0    50   ~ 0
radio_rxn
Wire Wire Line
	6350 4200 6150 4200
Wire Wire Line
	6350 4600 6150 4600
Wire Wire Line
	6350 4700 6150 4700
Wire Bus Line
	4950 1100 4950 1300
Wire Bus Line
	6150 2900 6150 3100
Wire Bus Line
	4950 4700 4950 4900
$EndSCHEMATC
