// -------------------------------------------------
// FileName : ESP32_main.ino
// Describe : ESP32 메인/서버 코드
// History : 2021-10-17
// -------------------------------------------------
#define DEBUG 1

// 시리얼 통신의 보드레이트 설정
#define BOADRATE 115200

#include <WiFi.h>

// AP 통신에 필요한 정보
#define AP_SSID "lab10"               // WIFI NAME
#define AP_PSWD "1234567890"          // WIFI PASSWORD
#define PORT 80                       // Server PORT

WiFiServer server(PORT);              // 지정된 포트에서 들어오는 연결을 수신 대기하는 서버 생성



void setup() {
  Serial.begin(BOADRATE);

  set();

}

void loop() {
  // put your main code here, to run repeatedly:

}

void set() {
  Serial.println();
  Serial.print("Conneting to ");
  Serial.println(AP_SSID);

  WiFi.begin(AP_SSID, AP_PSWD);         // WIFI 연결 시작

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WIFI connected!");

  server.begin();                       // server start

  Serial.println();
  Serial.println("Server Start!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
