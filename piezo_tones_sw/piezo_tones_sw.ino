int piezo=3;
int sw=5;

int numTones=8;
int tones[]={261, 294, 330, 349, 392, 440, 494, 523};  // 주파수
void setup() {
  pinMode(piezo,OUTPUT);
  pinMode(sw,INPUT_PULLUP);
}

void loop() {
  if(digitalRead(sw)==LOW){
    for(int i = 0; i < numTones; i++){
      tone(piezo, tones[i]);
      delay(500);
    }
    noTone(piezo);
  }
}
