int pin_button=2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin_button,INPUT_PULLUP);
}

int count = 0;
bool state_current = false;
bool state_previous = false;

void loop() {
  // put your main code here, to run repeatedly:
  state_current = digitalRead(pin_button);

  if(!state_current){
    if(state_previous == false){
      count++;
      state_previous=true;
      Serial.println(count);
    }
    delay(50);  //디바운싱
  }
  else{
    state_previous=false;
  }
}
