//----------------------------------------------------------------------------
// Title    : Switch_Flag
// Function : Change the value of the flag when a switch is pressed or 
//                                         when serial is input
// History  : 20210927
//----------------------------------------------------------------------------

#define SWITCH_PIN 12
int flag = 0;
int input;

void setup() {
  Serial.begin(9600); 
  pinMode(SWITCH_PIN,OUTPUT);
}

void loop() {
  if(Serial.available()){
    input = Serial.read();
    if(input == '1'){
      RelayOn(RELAY_PIN); //이코드에는 없는 함수입니다.
    }
    if(input == '0'){
      RelayOff(RELAY_PIN);  //이코드에는 없는 함수입니다.
    }
  }
}
