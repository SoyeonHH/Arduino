int LED1 = 6;
int LED2 = 7;
int button = 2;
bool LED_state = false;
bool LED_state2 = false;
bool button_state_current = false;
bool button_state_previous = false;
int time_current = 0;
int time_previous = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(button,INPUT_PULLUP);
}

void loop() {
  // delay() 함수 사용하지 않고 1초마다 blink
  time_current = millis();

  // 1초 이상 시간이 경과한 경우
  if(time_current-time_previous >= 1000){
    time_previous = time_current;

    LED_state = !LED_state;
    digitalWrite(LED1,LED_state);
  }

  button_state_current = digitalRead(button);
  if(!button_state_current){
    if(!button_state_previous){
      button_state_previous = true;
      LED_state2 = !LED_state2;
      digitalWrite(LED2, LED_state2);
    }
  }
  else{
    button_state_previous = false;
  }
}
