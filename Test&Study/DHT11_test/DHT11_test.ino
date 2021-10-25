#include "DHT.h"

#define BAUDRATE 115200

#define PIN 4
DHT dht(PIN, DHT11);

void setup() {
  Serial.begin(BAUDRATE);

  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.print(" / temperature: ");
  Serial.println(temperature);

  delay(1000);
}
