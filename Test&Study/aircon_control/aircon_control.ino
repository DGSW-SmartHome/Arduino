// ------------------------------------------------------------
// FileName : aircon_control.ino
// Describe : 적외선신호를 이용한 에어컨제어
// History : 2021-10-18
// ------------------------------------------------------------
#include <IRremote.h>

#define BOADRATE 115200
#define RECV_PIN 2

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(BOADRATE);
  irrecv.enableIRIn();
}

void loop() {
  if(irrecv.decode(&results)) {             // 만약 IR센서로 신호가 들어온다면 데이터 주소 저장

    Serial.print(results.value, HEX);
    Serial.println();

    irrecv.resume();
  }
}
