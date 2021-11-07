//-----------------------------------------------------------------
// Title    : ESP32_LightControl
// Function : Lighting control code for use on ESP32 boards
// History  : 20211006
//-----------------------------------------------------------------

#include <WiFi.h>

//시리얼 통신의 보드레이트설정
#define BOADRATE 115200

//와이파이 통신에 필요한 정보
#define AP_SSID "lab10"
#define AP_PSWD "1234567890"
#define HOST_IP "192.168.0.3"
#define PORT 80

//센서들의 핀설정
#define LIGHT1_PIN 12
#define LIGHT2_PIN 13
#define SWITCH1_PIN 16
#define SWITCH2_PIN 17

IPAddress server(192,168,0,3);
WiFiClient client;

//flag = 0 : LIGHT1 OFF LIGHT2 OFF
//flag = 1 : LIGHT1 ON  LIGHT2 OFF
//flag = 2 : LIGHT1 OFF LIGHT2 ON
//flag = 3 : LIGHT1 ON  LIGHT2 ON
int flag = 0;
int check1 = 0; 
int check2 = 0;
int stat1 = 0;
int stat2 = 0;

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
  pinMode(LIGHT2_PIN, OUTPUT);
  pinMode(SWITCH1_PIN, INPUT_PULLUP);
  pinMode(SWITCH2_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SWITCH1_PIN), toggleSW1, RISING);
  attachInterrupt(digitalPinToInterrupt(SWITCH2_PIN), toggleSW2, RISING);
  
}

void loop() {
  if(client.connect(server, PORT)) {
    Serial.println("server connected");

    flag = communication(); 
    Serial.println(flag);
    
    if(flag == 0){ lightOff(LIGHT1_PIN);  lightOff(LIGHT2_PIN); }
    if(flag == 1){ lightOn(LIGHT1_PIN);   lightOff(LIGHT2_PIN); }
    if(flag == 2){ lightOff(LIGHT1_PIN);  lightOn(LIGHT2_PIN);  }
    if(flag == 3){ lightOn(LIGHT1_PIN);   lightOn(LIGHT2_PIN);  }
    
    sendStat();
    client.flush();
  
  }
  delay(500);
}

void toggleSW1(){
  if(stat1 == 0){
    Serial.println("1 on");
    digitalWrite(LIGHT1_PIN, HIGH);
    stat1 = 1;
  }
  else if(stat1 == 1){
    Serial.println("1 off");
     digitalWrite(LIGHT1_PIN, LOW);
    stat1 = 0;
  }
  
  if(flag == 0) flag = 1;
  else if(flag == 1) flag = 0;
  else if(flag == 2) flag = 3;
  else if(flag == 3) flag = 2;

  
  Serial.println(flag);
  delayMicroseconds(10000);
}

void toggleSW2(){
  if(stat2 == 0){
    Serial.println("2 on");
    digitalWrite(LIGHT2_PIN, HIGH);
    stat2 = 1;
  }
  else if(stat2 == 1){
    Serial.println("2 off");
    digitalWrite(LIGHT2_PIN, LOW);
    stat2 = 0;
  }
  
  if(flag == 0) flag = 2;
  else if(flag == 1) flag = 3;
  else if(flag == 2) flag = 0;
  else if(flag == 3) flag = 1;
  
  
  Serial.println(flag);
  delayMicroseconds(10000);
}

int communication(){
  if(client.available()){
//      String to charArray code 
    String buf = client.readStringUntil('\r');

    String cmd = buf.substring(0,2);
    if(cmd == "L1"){
      String str = buf.substring(3,4);
      check1 = buf.substring(3,4).toInt();
      if(check1 != check2){
        check2 = check1;
        Serial.println(str);
        if(str == "0") return 0;
        else if(str == "1") return 1;
        else if(str == "2") return 2;
        else if(str == "3") return 3;
      }
    }
    check1 = flag;
    return check1;
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
