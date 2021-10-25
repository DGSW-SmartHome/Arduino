#include <IRremote.h>

#define BAUDRATE 115200
#define SEND_PIN 12

IRsend irsend(SEND_PIN);

void setup() {
  Serial.begin(BAUDRATE);

  irsend.begin(SEND_PIN, ENABLE_LED_FEEDBACK);
//  IrSender.enableIROut(38); // call it with 38 kHz
  
  
  Serial.println("ready");

}


void loop() {
  Serial.println("send");

  irsend.sendNECMSB(0xF708FB04, 32);

  
  delay(1000);

  
}
