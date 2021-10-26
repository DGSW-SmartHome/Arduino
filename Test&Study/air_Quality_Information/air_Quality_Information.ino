#include <PMsensor.h>


PMsensor PM;

void setup() {
  Serial.begin(115200);

  PM.init(4, 32);
  
}

void loop() {

  float pm = PM.read(0.1);
//  if ((err = PM.read(&pm, true, 0.4)) != PMsensorErrSuccess)
//  {
//    Serial.print("Error = ");
//    Serial.println(err);
//    delay(3000);
//    return;
//  }

  Serial.print("PM : ");
  Serial.print(pm);
  Serial.println(" ug/m^3");

  delay(1000);
}
