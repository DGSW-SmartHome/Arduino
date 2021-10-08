// FileName : ESP32_WIFI_test_server.ino
// Describe : ESP32를 이용한 AP통신 테스트
// History : 2021-10-07 JAH 
// --------------------------------------------------------------------
#include <WiFi.h>

#define AP_ssid "Seven_Labs"                  // WIFI NAME
#define AP_password "7777Labs"                // WIFI PASSWORD
int status = WL_IDLE_STATUS;

WiFiServer server(80);                        // 지정된 포트에서 들어오는 연결을 수신 대기하는 서버 생성

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(AP_ssid);

  WiFi.begin(AP_ssid, AP_password);            // WIFI 연결 시작

  while (WiFi.status() != WL_CONNECTED) {      // WIFI가 연결이 되어 있지 않다면
      delay(500);
      Serial.print(".");
  }

  server.begin();                               // 서버 시작
  Serial.println("");
  Serial.println("Server Start!");
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());               // 와이파이 IP 주소 출력

}

void loop() {
  WiFiClient client = server.available();        // 서버에 연결되어 있는 클라이언트를 가져옴
  
  if(client){

    if(client.connected()){                       // 클라이언트가 연결되었는가?
      Serial.println("Connected to client");
      client.write("Connected to server");        // 클라이언트에 메세지 전달 - 수정예정
    }
  }
//  client.stop();                                // 클라이언트 닫기
  delay(1000);
}
