//----------------------------------------------------------------------------
// Title    : SerialParsing.ino 
// Function : Code that divides the value coming through serial into an array
// History  : 20210918
//----------------------------------------------------------------------------

#define DATACNT 3
#define MAXDEVICE 6
// --------------------     ------------------------------------
//  SerialText(Srting)       data                              
// --------------------     ------------------------------------
// |   i |      value |     |   i |           j<10             |
// --------------------     ------------------------------------
// |   0 |        LED |     |   0 |              module coount |
// |   1 |       PLUG |     |   1 |              module coount |
// |   2 |     AirCon |     |   2 |   0:ON/OFF, 1:TEMP, 2:WIND |
// --------------------     ------------------------------------
String SerialText[DATACNT];
int data[DATACNT][MAXDEVICE];     


void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    String SerialText = Serial.readStringUntil('\n');
    divisionInfo(SerialText);
    divisionData();
  }
}

void divisionInfo(String string){
  int i = 0;
  while(1){
    int division = string.indexOf('&');
    int len = string.length();
    if(division == -1){
      SerialText[2] = string;
      break;}
    SerialText[i] = string.substring(0, division);
    string = string.substring(division+1, len);
    i++;
  }
  
  //SerialTextShow();
}

void divisionData(){
  int len;
  for(int i = 0; i<DATACNT; i++){
    for(int j = 0; j<10; j++){
      len = SerialText[i].length();
      data[i][j] = SerialText[i].substring(0,1).toInt();
      if(len <= 1){break;}
      else{SerialText[i] = SerialText[i].substring(1,len);}
    }
  }
  
  //dataShow();
}

void dataShow(){
  //data show code
  for(int i = 0; i<DATACNT; i++){
    for(int j = 0; j<10; j++){
      Serial.print(data[i][j]);
      Serial.print(",");
    }
    Serial.println();
  }
}
void SerialTextShow(){
  // SerialText show code    
  Serial.println(SerialText[0]);
  Serial.println(SerialText[1]);
  Serial.println(SerialText[2]);
}
