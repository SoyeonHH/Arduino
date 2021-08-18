//초음파 센서의 핀번호를 설정한다.
int echoPin = 8;
int trigPin = 9;

void setup() {
  Serial.begin(9600);
  // frig를 출력모드로 설정, echo를 입력 모드로 설정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 한다.
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);
  delayMicroseconds(2);

  // 진동
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // echoPin이 HIGH를 유지한 시간을 저장한다.
  unsigned long duration = pulseIn(echoPin, HIGH);
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산한다.
  float distance = ((float)(340*duration)/10000) / 2;

  Serial.print(distance);
  Serial.println("cm");
  delay(500);
}
