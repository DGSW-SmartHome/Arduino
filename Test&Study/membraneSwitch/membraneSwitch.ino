//----------------------------------------------------------------------------
// Title    : membraneSwitch 
// Function : Outlet control cords for use with ESP32 boards
// History  : 20211007
//----------------------------------------------------------------------------

#define MEMBRANE_PIN 7
#define BOADRATE 115200

void setup() {
  Serial.begin(BOADRATE);
  Serial.print("start");

  pinMode(MEMBRANE_PIN, INPUT);
}

void loop() {
  Serial.println(digitalRead(MEMBRANE_PIN));
  delay(100);
}
