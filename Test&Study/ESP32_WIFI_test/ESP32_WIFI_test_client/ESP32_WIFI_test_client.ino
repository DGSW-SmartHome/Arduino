#include <WiFi.h>

#define AP_ssid "Seven_Labs"
#define AP_password "7777Labs"
#define host "192.168.0.41"
#define port 80

IPAddress server(192,168,0,41);
WiFiClient client;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(AP_ssid);

  WiFi.begin(AP_ssid, AP_password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  if(client.connect(server, 80)) {
    Serial.println("server connected");
  }

  client.connect(server, port);
}

void loop() {
  if(client.available()){
    char c = client.read();
    Serial.println(c);
  }
  
}
