// uses example values from MS5607 datasheet (NOT MS5611)

// datasheet example values 
/*
float c1 = 46372;
float c2 = 43981;
float c3 = 29059;
float c4 = 27842;
float c5 = 31553;
float c6 = 28165;
float D1 = 6465444;
float D2 = 8077636;
*/

// my sensor values
float c1 = 40345;
float c2 = 37766;
float c3 = 25582;
float c4 = 23987;
float c5 = 32093;
float c6 = 27986;

float D1 = 6472300;
float D2 = 8370462;



float dT;
float temp;

float off;
float sens;
float pressure;

void setup() {
  Serial.begin(9600);

  delay(100);

  dT = D2 - (c5 * 256.0);
  Serial.print("dT: ");
  Serial.println(dT);

  temp = 2000.0 + ((dT * c6) / 8388608.0);
  Serial.print("temp: ");
  Serial.println(temp/100.0);

  off = (c2 * 131072.0) + ((c4 * dT) / 64.0);
  Serial.print("off: ");
  Serial.println(off);

  sens = (c1 * 65536.0) + ((c3 * dT) / 128.0);
  Serial.print("sens: ");
  Serial.println(sens);

  pressure = (((D1 * sens) / 2097152.0) - off) / 32768.0;
  Serial.print("pressure: ");
  Serial.println(pressure/100.0);

}

void loop() {
  // put your main code here, to run repeatedly:

}