#include <DHT.h>

#define BAUDRATE 115200

#define pin 2
DHT dgt = DHT(pin, DHT11);

void setup() {
  Serial.begin(BAUDRATE);

  dht.begin();
}

void loop() {
  int humidity = dgt.readHumidity();
  int temperature = dht.readTemperature();

  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.print(" / temperature: ");
  Serial.println(temperature);
}
