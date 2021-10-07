//----------------------------------------------------------------------------
// Title    : ESP32_LightControl
// Function : Lighting control code for use on ESP32 boards
// History  : 20211006
//----------------------------------------------------------------------------

#define LIGHT_PIN 10
#define SWITCH_PIN 11
#define BOADRATE 115200

//flag = 1 : LIGHT ON
//flag = 0 : LIGHT OFF
int flag = 0; 

void setup() {
  Serial.begin(BOADRATE);
  Serial.print("start");

  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
}

void loop() {
  flag = communication();
  flag = switchFlag();
  if(flag == 1)lightOn();
  if(flag == 0)lightOff();
}

//wifi(시리얼)을 통한 값을 받았을때 동작
int communication(){
  int serialValue = 0;
  
  if(Serial.available()){
    serialValue = Serial.read();
    if(serialValue == '1'){
      return 1;
    }
    if(serialValue == '0'){
      return 0;
    }
  }
}

//스위치 눌렸을 때 동작
int switchFlag(){
  if (flag == 0 && digitalRead(SWITCH_PIN) == HIGH){
    return 1;
  }
  if (flag == 1 && digitalRead(SWITCH_PIN) == HIGH){
    return 0;
  }
}

//조명 켜기
void lightOn(){
  digitalWrite(LIGHT_PIN, HIGH);
}

//조명 끄기
void lightOff(){
  digitalWrite(LIGHT_PIN, LOW);
}
