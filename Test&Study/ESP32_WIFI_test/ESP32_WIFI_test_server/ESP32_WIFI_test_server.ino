// FileName : ESP32_WIFI_test_server.ino
// Describe : ESP32를 이용한 AP통신 테스트
// History : 2021-10-07 JAH
// --------------------------------------------------------------------
#include <WiFi.h>

#define AP_SSID "lab10"                  // WIFI NAME
#define AP_PSWD "1234567890"                // WIFI PASSWORD
#define PORT 80
int status = WL_IDLE_STATUS;
int flag = 0;

WiFiServer server(PORT);                        // 지정된 포트에서 들어오는 연결을 수신 대기하는 서버 생성
WiFiClient client;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(AP_SSID);

  WiFi.begin(AP_SSID, AP_PSWD);            // WIFI 연결 시작

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
  client = server.available();        // 서버에 연결되어 있는 클라이언트를 가져옴

  if (client.connected()) {                     // 클라이언트가 연결되었는가?
    commandSend();
  }

  if(client.available()){
    recvStat();
  }

  if(!client.connected()){
    client.stop();                                // 클라이언트 닫기
  }
  delay(1000);
}

void commandSend() {
  Serial.println("Connected to client");
  String cmd = "O1-0";
  client.write((char*)cmd.c_str(), cmd.length());
}

void recvStat() {
  String buf = client.readStringUntil('\r');
  Serial.println(buf);
}
