// -------------------------------------------------
// FileName : ESP32_main.ino
// Describe : ESP32 메인/서버 코드
// History : 2021-10-17
// -------------------------------------------------
//#define DEBUG 1
// 시리얼 통신의 보드레이트 설정
#define BAUDRATE 115200

#include <WiFi.h>

// AP 통신에 필요한 정보
#define AP_SSID "lab10"               // WIFI NAME
#define AP_PSWD "1234567890"          // WIFI PASSWORD
#define PORT 80                       // Server PORT              

WiFiServer server(PORT);              // 지정된 포트에서 들어오는 연결을 수신 대기하는 서버 생성
WiFiClient client;

String recvCmdmsg = "";
String recvStatmsg = "";
int light[3] = { 0,0,0 };

void setup() {
  Serial.begin(BAUDRATE);

  wifiSetting();
  
}

void loop() {
  client = server.available();
  
  if(client) {
    Serial.println("Connected to Client");
    while(client.connected()) {
      sendCmd();
      
      if(client.available()) {
        recvStat();
      }
      
      sendStat();
      delay(100);
    }
  }
  
  delay(100);
}

void serialEvent(){
  recvCmd();
}

// WIFI Connect & Server Connect function
void wifiSetting() {
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

// 아두이노에게 제어메세지 전송
void sendCmd() {
  client.write((char*)recvCmdmsg.c_str(), recvCmdmsg.length());
  client.write('\r');
}

// 아두이노에서 상태 메세지 받기
void recvStat() {
  recvStatmsg = client.readStringUntil('\r');
  Serial.println(recvStatmsg);

  if(recvStatmsg.substring(0,2) == "L1") light[0] = recvStatmsg.substring(3,4).toInt();
  else if(recvStatmsg.substring(0,2) == "L2") light[1] = recvStatmsg.substring(3,4).toInt();
  else if(recvStatmsg.substring(0,2) == "L3") light[2] = recvStatmsg.substring(3,4).toInt();
}

// 라즈베리파이에서 제어메세지 받기
void recvCmd() {
  recvCmdmsg = Serial.readStringUntil('\r');
  Serial.println(recvCmdmsg);
}

// 라즈베리파이에게 상태 메세지 전송
void sendStat() {
  // light stat
#ifdef DEBUG
  Serial.print("light1: ");
  Serial.print(light[0]);
  Serial.print(" / light2: ");
  Serial.print(light[1]);
  Serial.print(" / light3: ");
  Serial.print(light[2]);
  Serial.println();
#else
  Serial.write("L1");
  Serial.write((byte*)&light[0], 1);
  Serial.write("L2");
  Serial.write((byte*)&light[1], 1);
  Serial.write("L3");
  Serial.write((byte*)&light[2], 1);
  Serial.write('\n');
#endif
}
