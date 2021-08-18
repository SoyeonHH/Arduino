void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  Serial.begin(9600);
  Serial.println("시리얼 통신 시작");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    char ch;
    ch = Serial.read();
    Serial.println(ch);
    if (ch=='1')
    {
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      Serial.println("1번 LED ON");
    }
    if (ch=='2')
    {
      digitalWrite(4,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      Serial.println("2번 LED ON");
    }
    if (ch=='3')
    {
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
      Serial.println("3번 LED ON");
    }
    if (ch=='4')
    {
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);
      Serial.println("4번 LED ON");
    }
    if (ch=='5')
    {
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);
      Serial.println("ALL LED ON");
    }
  }
}
