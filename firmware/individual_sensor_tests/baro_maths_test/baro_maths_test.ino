// uses example values from MS5611 - 01BA03 datasheet

// example values 
/*float c1 = 40127;
float c2 = 36924;
float c3 = 23317;
float c4 = 23282;
float c5 = 33464;
float c6 = 28312;


uint32_t D1 = 9085466;
uint32_t D2 = 8569150;*/



float c1 = 40345;
float c2 = 37766;
float c3 = 25582;
float c4 = 23987;
float c5 = 32093;
float c6 = 27986;

float D1 = 6450748;
float D2 = 8405010;

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

  off = (c2 * 65536.0) + ((c4 * dT) / 128.0);
  Serial.print("off: ");
  Serial.println(off);

  sens = (c1 * 32768.0) + ((c3 * dT) / 256.0);
  Serial.print("sens: ");
  Serial.println(sens);

  pressure = (((D1 * sens) / 2097152) - off) / 32768.0;
  Serial.print("pressure: ");
  Serial.println(pressure/100.0);

}

void loop() {
  // put your main code here, to run repeatedly:

}
