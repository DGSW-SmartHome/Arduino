//----------------------------------------------------------------------------
// Title    : ESP32_OutletControl
// Function : Outlet control cords for use with ESP32 boards
// History  : 20211007
//----------------------------------------------------------------------------

#define OUTLET_PIN 13
#define LEDR_PIN 10        //LED to indicate status
#define LEDG_PIN 11
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

void loop(){
  //통신과 관련된 코드
  //-----------------------------
  if(Serial.available()){
    value = Serial.read();
    if(value == '1' && flag == 0)flag = 1;
    else if(value == '1' && flag == 1)flag = 0;
  }
  //-----------------------------
  
  if(flag == 1)outletOn();
  if(flag == 0)outletOff();
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
