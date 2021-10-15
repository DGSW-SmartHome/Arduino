//------------------------------------------------------------------
// Title    : ESP32_OutletControl
// Function : Outlet control cords for use with ESP32 boards
// History  : 20211007
//------------------------------------------------------------------

#include <WiFi.h>

//시리얼 통신의 보드레이트설정
#define BOADRATE 115200
//와이파이 통신에 필요한 정보
#define AP_SSID "lab10"
#define AP_PSWD "1234567890"
#define HOST_IP "192.168.0.4"
#define PORT 80
//센서들의 핀설정
#define OUTLET_PIN 13
#define LEDR_PIN 10        //LED to indicate status
#define LEDG_PIN 11
//시리얼(true)(int), 와이파이(false)(char) 통신 방식을 설정하는
#define COM_METHOD false
#define TYPE byte
//Client Cmd
#define CLIENT "O1"

IPAddress server(192,168,0,4);
WiFiClient client;

//flag = 1 : Concent ON
//flag = 0 : Concent OFF
int flag = 0;

void setup() {
  Serial.begin(BOADRATE);
  Serial.print("start");

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(AP_SSID);

  WiFi.begin(AP_SSID, AP_PSWD);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");}
      
  Serial.println("");
  Serial.println("WiFi connected");
  
  if(client.connect(server, PORT)){Serial.println("server connected");}
  
  client.connect(server, PORT);

  pinMode(OUTLET_PIN, OUTPUT);
  pinMode(LEDR_PIN, OUTPUT);
  pinMode(LEDG_PIN, OUTPUT);
}

void loop(){
  if(client.available()){
    flag =  recvCmd();
    Serial.println(flag);
    
    if(flag == 1)outletOn();
    if(flag == 0)outletOff();
  }

  sendStat();
  delay(1000);
}

// 서버에서 cmd 수신
int recvCmd(){
  TYPE value;

  //시리얼 통신코드
  if(COM_METHOD == true){
    if(Serial.available()){
      value = Serial.read();  //int형
      return value;
    }
  }
  
  //WiFi 통신
  if(COM_METHOD == false){
    if(client.available()){
//      String to charArray code 
      String buf = client.readStringUntil('\r');
      Serial.println(buf);
      
      String cmd = buf.substring(0,2);
      if(cmd == CLIENT){
        String str = buf.substring(2,3);
        if(str == "0") return 0;
        else if(str == "1") return 1;
      }
      return -1;
    }
  }
}

// Outlet 상태 전송
void sendStat(){
  client.write("O1-1");
}

//콘센트 켜기
void outletOn(){
  digitalWrite(OUTLET_PIN, HIGH);
  digitalWrite(LEDR_PIN, LOW);
  digitalWrite(LEDG_PIN, HIGH);
}

//콘센트 끄기
void outletOff(){
  digitalWrite(OUTLET_PIN, LOW);
  digitalWrite(LEDR_PIN, HIGH);
  digitalWrite(LEDG_PIN, LOW);
}
