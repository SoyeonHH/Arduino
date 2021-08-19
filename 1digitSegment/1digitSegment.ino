int segmentLEDs[] = {26, 25, 17, 16, 27, 14, 12, 13};
int digitForNum[10][8] = {
  {0, 0, 0, 0, 0, 0, 1, 1}, //0
  {1, 0, 0, 1, 1, 1, 1, 1}, //1
  {0, 0, 1, 0, 0, 1, 0, 1}, //2
  {0, 0, 0, 0, 1, 1, 0, 1}, //3
  {1, 0, 0, 1, 1, 0, 0, 1}, //4
  {0, 1, 0, 0, 1, 0, 0, 1}, //5
  {0, 1, 0, 0, 0, 0, 0, 1}, //6
  {0, 0, 0, 1, 1, 1, 1, 1}, //7
  {0, 0, 0, 0, 0, 0, 0, 1}, //8
  {0, 0, 0, 0, 1, 0, 0, 1}  //9
};
void setup() {
  for(int i = 0; i < 8; i++){
    pinMode(segmentLEDs[i],OUTPUT);
  }
  ledcAttachPin(5,0); // channel 0 ~ 7
  ledcSetup(0,100,8); // channel, frequency, 8bit
}

void loop() {
  ledcWrite(0,50);

  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 8; j++){
      digitalWrite(segmentLEDs[j],digitForNum[i][j]);
    }
    delay(1000);
  }
}
