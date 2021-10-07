#include <WiFi.h>

#define AP_ssid "Seven_Labs"
#define AP_password "7777Labs"
int status = WL_IDLE_STATUS;

WiFiServer server(80);

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

  server.begin();
  Serial.println("");
  Serial.println("Server Start!");
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  WiFiClient client = server.available();
  
  if(client){

    if(client.connected()){
      Serial.println("Connected to client");
      client.write("Connected to server");
    }
  }
//  client.stop();
  delay(1000);
}
