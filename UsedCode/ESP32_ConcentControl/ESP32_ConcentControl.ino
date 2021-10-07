//----------------------------------------------------------------------------
// Title    : ESP32_ConcentControl
// Function : Outlet control cords for use with ESP32 boards
// History  : 20211007
//----------------------------------------------------------------------------

#define OUTLET_PIN 10
#define LEDR_PIN 11        //LED to indicate status
#define LEDG_PIN 12
#define BOADRATE 115200

//flag = 1 : Concent ON
//flag = 0 : Concent OFF
int flag = 0;
int value = 0;

void setup() {
  Serial.begin(BOADRATE);
  Serial.print("start");

  pinMode(OUTLET_PIN, OUTPUT);
  pinMode(LEDR_PIN, OUTPUT);
  pinMode(LEDG_PIN, OUTPUT);
}

void loop() {
  flag = communication();
  if(flag == 1)outletOn();
  if(flag == 0)outletOff();
}

//wifi(시리얼)을 통한 값을 받았을때 동작
int communication(){  
  if(Serial.available()){
    value = Serial.read();
    if(value == '1')return 1;
    if(value == '0')return 0;
  }
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
