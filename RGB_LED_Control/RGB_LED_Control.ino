long randNumber1;
long randNumber2;
long randNumber3;

void setup() {
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop() {
  randNumber1 = random(0, 256);
  randNumber2 = random(0, 256);
  randNumber3 = random(0, 256);
  
  analogWrite(9, randNumber1);
  analogWrite(10, randNumber2);
  analogWrite(11, randNumber3);
  Serial.print(randNumber1);
  Serial.print("\t");
  Serial.print(randNumber2);
  Serial.print("\t");
  Serial.print(randNumber3);
  Serial.println("\t");
  delay(1000);
}
