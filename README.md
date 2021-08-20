# Arduino
 공공데이터를 활용한 IoT디바이스 만들기, 2021

## Learning Flow
Steps|Topic|Sketch
 ---|---|---
1|아두이노 시리얼 통신|[print Hello](https://github.com/SoyeonHH/Arduino/blob/main/Hello/Hello.ino)
2|LED 출력|[Blink](https://github.com/SoyeonHH/Arduino/blob/main/sketch_blink/sketch_blink.ino), [입력값에 따른 LED 출력](https://github.com/SoyeonHH/Arduino/blob/main/LED_serial_print/LED_serial_print.ino)
3|Button 입력|[Tact Switch의 사용](https://github.com/SoyeonHH/Arduino/blob/main/Tact_switch/Tact_switch.ino), [Pull up Button Push Count](https://github.com/SoyeonHH/Arduino/blob/main/count_pushButton_pullup/count_pushButton_pullup.ino), [Button Push to LED](https://github.com/SoyeonHH/Arduino/blob/main/button_to_led/button_to_led.ino), [주기적인 데이터 처리](https://github.com/SoyeonHH/Arduino/blob/main/Periodic_led_control/Periodic_led_control.ino)
4|아날로그 입력|[기본 입력 읽기](https://github.com/SoyeonHH/Arduino/blob/main/analogRead/analogRead.ino), [온습도 센서](https://github.com/SoyeonHH/Arduino/blob/main/DHT11/DHT11.ino), [초음파 센서](https://github.com/SoyeonHH/Arduino/blob/main/UltraSonic/UltraSonic.ino)
5|아날로그 출력|[RGB LED 밝기 제어](https://github.com/SoyeonHH/Arduino/blob/main/RGB_LED_Control/RGB_LED_Control.ino), [조도 센서 PWM 컨트롤](https://github.com/SoyeonHH/Arduino/blob/main/light_sensor_control/light_sensor_control.ino), [도레미파솔라시도](https://github.com/SoyeonHH/Arduino/blob/main/piezo_tones_sw/piezo_tones_sw.ino), [Servo Moter 컨트롤](https://github.com/SoyeonHH/Arduino/blob/main/servo_moter_control/servo_moter_control.ino)
6|ESP32 아두이노|[ROTS](https://github.com/SoyeonHH/Arduino/blob/main/DHT11/DHT11.ino)(Real Time Operatin System), [1 digit Segment](https://github.com/SoyeonHH/Arduino/blob/main/DHT11/1digitSegment.ino), [4 digit Segment](https://github.com/SoyeonHH/Arduino/blob/main/DHT11/4digitSegment.ino)

## Project

### 1. Weather

* Description: 기상청의 실시간 동네 날씨 정보를 통해 현재 기온과 날씨를 출력한다.
* 4-digit Segment: 현재 기온
* [GREEN] Clear, [RED] Rain, [BLUE] Cloudy or mostly Cloudy
* [Code](https://github.com/SoyeonHH/Arduino/blob/main/BasicHttpClient_wheather_ex1/BasicHttpClient_wheather_ex1.ino)
* [Source](http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4111753000)

![Weather](/image/wheather.PNG)

### 2. Bustop

* Description: 버스 노선 조회 공공데이터를 통해 특정 정류소에서 특정 버스의 예상 대기 시간을 출력한다.
* 4-digit Segment: 예상 대기 시간1 (2-digit), 예상 대기 시간2 (2-digit)
* Buzzor: 예상 대기 시간이 5분 이내일 때 부저가 울림
* [Code](https://github.com/SoyeonHH/Arduino/blob/main/BasicHttpClient_bustop_ex2/BasicHttpClient_bustop_ex2.ino)

![Bustop](/image/bustop.PNG)
