#define RELAY_PIN 12
int input;

void setup() {
  Serial.begin(9600); 
  pinMode(RELAY_PIN,OUTPUT);
}

void loop() {
  if(Serial.available()){
    input = Serial.read();
    if(input == '1'){
      RelayOn(RELAY_PIN);
    }
    if(input == '0'){
      RelayOff(RELAY_PIN);
    }
  }
}

void RelayOn(int pin){
  digitalWrite(pin, HIGH);
  Serial.println("RelayOn");
}

void RelayOff(int pin){
  digitalWrite(pin, LOW);
  Serial.println("RelayOff");
}
