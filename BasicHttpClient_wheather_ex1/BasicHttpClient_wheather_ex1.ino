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
int tones[8] = {261, 293, 329, 349, 392,440,494,523};
int Clear_LED = 2;
int Rain_LED = 4;
int Cloudy_LED = SCL; //SDA
void setup() {

    USE_SERIAL.begin(115200);

    for(int i = 0 ; i < 8 ; i++) {
      pinMode(segmentLEDs[i], OUTPUT);
    }
    for(int i=0; i<4;i++)
    {
      pinMode(digit_select_num[i], OUTPUT);
    }
    pinMode(Clear_LED, OUTPUT);
    pinMode(Rain_LED, OUTPUT);
    pinMode(Cloudy_LED, OUTPUT);
    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
    ledcSetup(0,1000,10); // 0 ~ 1023 // 0 ~ 255
    ledcAttachPin(SDA,0);
    
    wifiMulti.addAP("SK_WiFiB0BF", "1408051989");
    xTaskCreate(task1,"task1",2048,NULL,1,NULL);
}
String temp;
String wfEn;

void loop() {
  int endtag_index = 0;
  String tag_str;
  String content_str;
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        http.begin("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4111753000"); //HTTP

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
                endtag_index = payload.indexOf("</data>");
                //USE_SERIAL.println(payload_index);

                if(endtag_index > 0) // 원하는 값을 찾았으면,
                {
                    tag_str = "<data seq=\"0\">"; // abcd.substring(1,4) = bc
                    content_str =payload.substring(payload.indexOf(tag_str)+(tag_str.length()) , endtag_index);
                    //USE_SERIAL.println(content_str);

                    endtag_index = content_str.indexOf("</wfEn>");
                    if(endtag_index > 0)
                    {
                      tag_str = "<wfEn>";
                      wfEn =content_str.substring(content_str.indexOf(tag_str)+tag_str.length(),endtag_index);
                      USE_SERIAL.println(wfEn);
                    }

                    endtag_index = content_str.indexOf("</temp>");
                    if(endtag_index > 0)
                    {
                      tag_str = "<temp>";
                      temp =content_str.substring(content_str.indexOf(tag_str)+tag_str.length(),endtag_index);
                      USE_SERIAL.println(temp);
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

void task1(void *parameter)
{
  while(1){
    if(temp.toInt() > 0)
    {
        seg_display(temp.toInt());
    }
    if(wfEn.equals("Clear") == 1)
    {
      digitalWrite(Clear_LED, HIGH);
      digitalWrite(Rain_LED, LOW);
      digitalWrite(Cloudy_LED, LOW);
    }
    if((wfEn.equals("Rain") == 1) || (wfEn.equals("Shower") == 1))
    {
      digitalWrite(Clear_LED, LOW);
      digitalWrite(Rain_LED, HIGH);
      digitalWrite(Cloudy_LED, LOW);
    }
    if((wfEn.equals("Cloudy") == 1)||(wfEn.equals("Mostly Cloudy") == 1))
    {
      digitalWrite(Clear_LED, LOW);
      digitalWrite(Rain_LED, LOW);
      digitalWrite(Cloudy_LED, HIGH);
    }
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
