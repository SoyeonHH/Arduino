#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>
#define USE_SERIAL Serial

WiFiMulti wifiMulti;

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
int Buzzer_Pin = 39;
int tones[8] = {261, 293, 329, 349, 392,440,494,523};
void setup() {

    USE_SERIAL.begin(115200);

    for(int i = 0 ; i < 8 ; i++) {
      pinMode(segmentLEDs[i], OUTPUT);
    }
    for(int i=0; i<4;i++)
    {
      pinMode(digit_select_num[i], OUTPUT);
    }
    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
    ledcSetup(0,1000,10);
    ledcAttachPin(Buzzer_Pin, 0);
    wifiMulti.addAP("SK_WiFiB0BF", "1408051989");
    xTaskCreate(task1,"task1",4096,NULL,0,NULL);
    xTaskCreate(task2,"task2",4096,NULL,0,NULL);
}
String predictTime1;
String predictTime2;
int endtag_index = 0;
String tag_str;
String content_str;

void loop() {
  // wait for WiFi connection
  if((wifiMulti.run() == WL_CONNECTED)) {

      HTTPClient http;

      USE_SERIAL.print("[HTTP] begin...\n");
      // configure traged server and url
      http.begin("http://apis.data.go.kr/6410000/busarrivalservice/getBusArrivalItem?serviceKey=oISueKBEW09cXOi8L8JC3OOWqnbBP6OMf9bY%2BzmkbxnENefS8JrpK5V%2FD2UkN08brtDH7MPlOvg4Lx7AMCK%2B%2Fw%3D%3D&stationId=203000099&routeId=200000144&staOrder=62"); //HTTP

      USE_SERIAL.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if(httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

          // file found at server
          if(httpCode == HTTP_CODE_OK) {
              String payload = http.getString();
              USE_SERIAL.println(payload);
              endtag_index = payload.indexOf("</busArrivalItem>");
              //USE_SERIAL.println(endtag_index);

              if(endtag_index > 0)
              {
                  tag_str = "<busArrivalItem>";
                  content_str =payload.substring(payload.indexOf(tag_str)+tag_str.length(),endtag_index);
                  //USE_SERIAL.println(content_str);

                  endtag_index = content_str.indexOf("</predictTime1>");
                  if(endtag_index > 0)
                  {
                    tag_str = "<predictTime1>";
                    predictTime1 =content_str.substring(content_str.indexOf(tag_str)+tag_str.length(),endtag_index);
                    USE_SERIAL.println(predictTime1);
                  }

                  endtag_index = content_str.indexOf("</predictTime2>");
                  if(endtag_index > 0)
                  {
                    tag_str = "<predictTime2>";
                    predictTime2 =content_str.substring(content_str.indexOf(tag_str)+tag_str.length(),endtag_index);
                    USE_SERIAL.println(predictTime2);
                  }
              }
          }
      } else {
          USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
  }
  vTaskDelay(30000/portTICK_PERIOD_MS);
}

int display_number;

void task1(void *parameter)
{
  while(1){
      if(predictTime2.toInt() > 0)
      {
        if(predictTime1.toInt() < 0)
        {
          predictTime1 = "0";
        }
       display_number = (predictTime2.toInt() * 100)+predictTime1.toInt();
       seg_display(display_number);
      }
  }
}

void task2(void *parameter)
{
  while(1){
    if((predictTime1.toInt() < 5)&&(predictTime1.toInt() > 0))
    {
      ledcWrite(0,tones[0]);
      vTaskDelay(500/portTICK_PERIOD_MS);
      ledcWrite(0,tones[3]);
      vTaskDelay(500/portTICK_PERIOD_MS);
      ledcWrite(0,tones[6]);
      vTaskDelay(500/portTICK_PERIOD_MS);
    }
    else
    {
      ledcWrite(0,0);
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void seg_display(int number) //1234 , 4321
{
  int digit4 = number/1000;
  int digit3 = (number%1000)/100;
  int digit2 = (number%100)/10;
  int digit1 = (number%10);

  seg_1_digit(1,digit4);
  vTaskDelay(2/portTICK_PERIOD_MS);
  seg_1_digit(2,digit3);
  vTaskDelay(2/portTICK_PERIOD_MS);
  seg_1_digit(3,digit2);
  vTaskDelay(2/portTICK_PERIOD_MS);
  seg_1_digit(4,digit1);
  vTaskDelay(2/portTICK_PERIOD_MS);
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
