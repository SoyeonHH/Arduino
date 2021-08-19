void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);  // BUILT IN: 2
  vTaskDelay(1000/portTICK_PERIOD_MS);  // delay(1000)
  // 각 task loop에 할당되는 메모리의 양
  xTaskCreate(task1,"task1",2048,NULL,1,NULL);
  xTaskCreate(task2,"task2",2048,NULL,1,NULL);
}

void loop() {
  vTaskDelay(1000/portTICK_PERIOD_MS);
}
void task1(void *parameter)
{
  while(1){
    Serial.println("Hello World");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
void task2(void *parameter)
{
  while(1){
    digitalWrite(2,HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);
    digitalWrite(2,LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
  
}
