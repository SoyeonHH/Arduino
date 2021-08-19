int segmentLEDs[] = {26,25,17,16,27,14,12,13};
int digit_select_num[] = {5,23,19,18};
int digitForNum[10][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0}, //0
  {0, 1, 1, 0, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1, 0}, //2
  {1, 1, 1, 1, 0, 0, 1, 0}, //3
  {0, 1, 1, 0, 0, 1, 1, 0}, //4
  {1, 0, 1, 1, 0, 1, 1, 0}, //5
  {1, 0, 1, 1, 1, 1, 1, 0}, //6
  {1, 1, 1, 0, 0, 0, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1, 0}, //8
  {1, 1, 1, 1, 0, 1, 1, 0}  //9
};
void setup() {
  // put your setup code here, to run once:
  for(int i = 0 ; i < 8 ; i++) {
    pinMode(segmentLEDs[i], OUTPUT);
  }
  for(int i=0; i<4;i++)
  {
    pinMode(digit_select_num[i], OUTPUT);
  }
  xTaskCreate(task1,"task1",2048,NULL,1,NULL);
//  ledcAttachPin(5,0); //channel 0 ~ 7
//  ledcSetup(0,1000,8); //channel , frequency, 8bit 0 ~ 255
}
int a = 0;

void seg_display(int number) //1234 , 4321
{
  int digit4 = number/1000;
  int digit3 = (number%1000)/100;
  int digit2 = (number%100)/10;
  int digit1 = (number%10);

  seg_1_digit(1,digit4);
  vTaskDelay(5/portTICK_PERIOD_MS);
  seg_1_digit(2,digit3);
  vTaskDelay(5/portTICK_PERIOD_MS);
  seg_1_digit(3,digit2);
  vTaskDelay(5/portTICK_PERIOD_MS);
  seg_1_digit(4,digit1);
  vTaskDelay(5/portTICK_PERIOD_MS);
}
void seg_1_digit(int digit, int num)
{   switch(digit)
    {
      case 1:
        digitalWrite(digit_select_num[0], LOW);
        digitalWrite(digit_select_num[1], HIGH);
        digitalWrite(digit_select_num[2], HIGH);
        digitalWrite(digit_select_num[3], HIGH);
        break;
      case 2:
        digitalWrite(digit_select_num[0], HIGH);
        digitalWrite(digit_select_num[1], LOW);
        digitalWrite(digit_select_num[2], HIGH);
        digitalWrite(digit_select_num[3], HIGH);
        break;
      case 3:
        digitalWrite(digit_select_num[0], HIGH);
        digitalWrite(digit_select_num[1], HIGH);
        digitalWrite(digit_select_num[2], LOW);
        digitalWrite(digit_select_num[3], HIGH);
        break;
      case 4:
        digitalWrite(digit_select_num[0], HIGH);
        digitalWrite(digit_select_num[1], HIGH);
        digitalWrite(digit_select_num[2], HIGH);
        digitalWrite(digit_select_num[3], LOW);
        break;
    }
    for(int j=0; j< 8;j++){
      digitalWrite(segmentLEDs[j],digitForNum[num][j]);
    }
}
void loop() {
//  ledcWrite(0, 50); //channel, 0 ~ 255
  // put your main code here, to run repeatedly:
  seg_display(a);
}
void task1(void *parameter)
{
  while(1){
    a++;
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}
