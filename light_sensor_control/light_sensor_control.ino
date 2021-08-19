void setup() {
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}
int pins_LED[3] = {9, 10, 11};
void loop() {
  int ADC_value = analogRead(A0);
  int PWM_value = ADC_value >> 2;

  Serial.print(String("ADC vlaue:") + ADC_value);
  Serial.println(String(", PWM value:") + PWM_value);

  for (int i=0;i<4;i++){
    analogWrite(pins_LED[i], PWM_value);
  }
//  delay(1000);
}
