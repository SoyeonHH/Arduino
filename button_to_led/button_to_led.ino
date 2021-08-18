int led1 = 4;
int led2 = 5;
int led3 = 6;
int led4 = 7;
int pin_button = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
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
      Serial.print("Trun ON LED");
      Serial.println(count%4);
      if(count%4==1){
        digitalWrite(led1,HIGH);
        digitalWrite(led2,LOW);
        digitalWrite(led3,LOW);
        digitalWrite(led4,LOW);
      }
      if(count%4==2){
        digitalWrite(led2,HIGH);
        digitalWrite(led1,LOW);
        digitalWrite(led3,LOW);
        digitalWrite(led4,LOW);
      }
      if(count%4==3){
        digitalWrite(led3,HIGH);
        digitalWrite(led2,LOW);
        digitalWrite(led1,LOW);
        digitalWrite(led4,LOW);
      }
      if(count%4==0){
        digitalWrite(led4,HIGH);
        digitalWrite(led2,LOW);
        digitalWrite(led3,LOW);
        digitalWrite(led1,LOW);
      }
    }
    delay(50);
  }
  else{
    state_previous=false;
  }
}
