const int pyro_en = 6;

const int pyro1 = 40;
const int pyro2 = 38;
const int pyro3 = 36;
const int pyro4 = 34;

const int cont1 = 41;
const int cont2 = 39;
const int cont3 = 37;
const int cont4 = 35;

void setup() {
  pinMode(pyro_en, OUTPUT);
  digitalWrite(pyro_en, HIGH);
  Serial.begin(9600);
  pinMode(pyro1, OUTPUT);
  pinMode(cont1, INPUT);
  pinMode(pyro2, OUTPUT);
  pinMode(cont2, INPUT);
  pinMode(pyro3, OUTPUT);
  pinMode(cont3, INPUT);
  pinMode(pyro4, OUTPUT);
  pinMode(cont4, INPUT);
  

  

}

void loop() {
  Serial.println(analogRead(cont1));
  if (millis() > 10000) {
    digitalWrite(pyro_en, LOW);
  }
  if (millis() > 15000 && millis() < 16000) {
    digitalWrite(pyro1, HIGH);
  }else{
    digitalWrite(pyro1, LOW);
  }

  if (millis() > 16000 && millis() < 17000) {
    digitalWrite(pyro2, HIGH);
  }else{
    digitalWrite(pyro2, LOW);
  }

  if (millis() > 17000 && millis() < 18000) {
    digitalWrite(pyro3, HIGH);
  }else{
    digitalWrite(pyro3, LOW);
  }

  if (millis() > 18000 && millis() < 19000) {
    digitalWrite(pyro4, HIGH);
  }else{
    digitalWrite(pyro4, LOW);
  }

}
