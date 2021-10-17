//-----------------------------------------------------------------
// Title    : ESP32_LightControl
// Function : Lighting control code for use on ESP32 boards
// History  : 20211006
//-----------------------------------------------------------------
//시리얼(true)(int), 와이파이(false)(char) 통신 방식을 설정하는
#define DEBUG false

#include <WiFi.h>

//시리얼 통신의 보드레이트설정
#define BOADRATE 115200

//와이파이 통신에 필요한 정보
#define AP_SSID "lab10"
#define AP_PSWD "1234567890"
#define HOST_IP "192.168.0.4"
#define PORT 80

//센서들의 핀설정
#define LIGHT1_PIN 12
#define LIGHT2_PIN 13
#define SWITCH1_PIN 14
#define SWITCH2_PIN 15

IPAddress server(192,168,0,4);
WiFiClient client;

//flag = 0 : LIGHT1 OFF LIGHT2 OFF
//flag = 1 : LIGHT1 ON  LIGHT2 OFF
//flag = 2 : LIGHT1 OFF LIGHT2 ON
//flag = 3 : LIGHT1 ON  LIGHT2 ON
int flag = -1; 

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
  
  pinMode(LIGHT1_PIN, OUTPUT);
  pinMode(SWITCH1_PIN, INPUT);
  pinMode(LIGHT2_PIN, OUTPUT);
  pinMode(SWITCH2_PIN, INPUT);
}

void loop() {
  if(client.connect(server, PORT)){
    
    Serial.println("server connected");
    
    flag = communication(); 
    Serial.println(flag);

    //  if(digitalRead(SWITCH1_PIN) == HIGH){
    //    flag = switchFlag();
    //  }
    
    if(flag == 0){ lightOff(LIGHT1_PIN);  lightOff(LIGHT2_PIN); }
    if(flag == 1){ lightOn(LIGHT1_PIN);   lightOff(LIGHT2_PIN); }
    if(flag == 2){ lightOff(LIGHT1_PIN);  lightOn(LIGHT2_PIN);  }
    if(flag == 3){ lightOn(LIGHT1_PIN);   lightOn(LIGHT2_PIN);  }

    sendStat();
    client.flush();
  }
  
  delay(1000);
}

int communication(){
  int value = 0;

  //시리얼 통신코드
  if(DEBUG == true){
    if(Serial.available()){
      value = Serial.read();  //int형
      return value;
    }
  }

  //WiFi 통신
  if(DEBUG == false){
    if(client.available()){
//      String to charArray code 
      String buf = client.readStringUntil('\r');
      Serial.println(buf);
      
      String cmd = buf.substring(0,2);
      if(cmd == "L1"){
        String str = buf.substring(3,4);
        if(str == "0") return 0;
        else if(str == "1") return 1;
        else if(str == "2") return 2;
        else if(str == "3") return 3;
      }
      return -1;
    }
  }
}

// Light 상태 전송
void sendStat(){
  String str = "L1-" + String(flag);
  client.write((char*)str.c_str(), str.length());
  client.write('\r');
  Serial.println(str);
}

//스위치 눌렸을 때 동작
int switchFlag(){
  if(flag == 0){    //flag = 0 : LIGHT1 OFF LIGHT2 OFF
    if(digitalRead(SWITCH1_PIN) == HIGH){return 1;}
    if(digitalRead(SWITCH2_PIN) == HIGH){return 2;}
  }
  if(flag == 1){    //flag = 1 : LIGHT1 ON  LIGHT2 OFF
    if(digitalRead(SWITCH1_PIN) == HIGH){return 0;}
    if(digitalRead(SWITCH2_PIN) == HIGH){return 3;}
  }
  if(flag == 2){    //flag = 2 : LIGHT1 OFF LIGHT2 ON
    if(digitalRead(SWITCH1_PIN) == HIGH){return 3;}
    if(digitalRead(SWITCH2_PIN) == HIGH){return 0;}
  }
  if(flag == 3){    //flag = 3 : LIGHT1 ON  LIGHT2 ON
    if(digitalRead(SWITCH1_PIN) == HIGH){return 2;}
    if(digitalRead(SWITCH2_PIN) == HIGH){return 1;}
  }
}

//조명 켜기
void lightOn(int pin){
  digitalWrite(pin, HIGH);
  Serial.print(pin);
  Serial.println(" : 조명 ON");
}

//조명 끄기
void lightOff(int pin){
  digitalWrite(pin, LOW);
  Serial.print(pin);
  Serial.println(" : 조명 OFF");
}
