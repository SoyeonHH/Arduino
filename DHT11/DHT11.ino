#include "DHT.h"
#define DHT_PIN 2
DHT dht(DHT_PIN, DHT11);
void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Humanity: ");
  Serial.print(h);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("'C");
  delay(2000);
}
