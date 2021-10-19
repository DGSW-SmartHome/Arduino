// ------------------------------------------------------------
// FileName : aircon_control.ino
// Describe : 적외선신호를 이용한 에어컨제어
// History : 2021-10-18
// ------------------------------------------------------------
#include <IRremote.h>

#define BOADRATE 115200
#define RECV_PIN 2

IRrecv irrecv(RECV_PIN);
//decode_results results;

void setup() {
  Serial.begin(BOADRATE);
  irrecv.enableIRIn();

  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(RECV_PIN);
}

void loop() { // ReceiveDump 예제를 참고했음.
  if(irrecv.decode()) {             // 만약 IR센서로 신호가 들어온다면 
     Serial.println("Receive!");

    if (irrecv.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
      Serial.println("IR code too long. Edit IRremoteInt.h and increase RAW_BUFFER_LENGTH");
    } else {
      Serial.println();                               
      Serial.println();
      irrecv.printIRResultShort(&Serial);
      Serial.println();
      Serial.println(F("Raw result in internal ticks (50 us) - with leading gap"));
      irrecv.printIRResultRawFormatted(&Serial, false); // Output the results in RAW format
      Serial.println(F("Raw result in microseconds - with leading gap"));
      irrecv.printIRResultRawFormatted(&Serial, true);  // Output the results in RAW format
      Serial.println();                               // blank line between entries
      Serial.print(F("Result as internal ticks (50 us) array - compensated with MARK_EXCESS_MICROS="));
      Serial.println(MARK_EXCESS_MICROS);
      irrecv.compensateAndPrintIRResultAsCArray(&Serial, false); // Output the results as uint8_t source code array of ticks
      Serial.print(F("Result as microseconds array - compensated with MARK_EXCESS_MICROS="));
      Serial.println(MARK_EXCESS_MICROS);
      irrecv.compensateAndPrintIRResultAsCArray(&Serial, true); // Output the results as uint16_t source code array of micros
      irrecv.printIRResultAsCVariables(&Serial);  // Output address and data as source code variables

      irrecv.compensateAndPrintIRResultAsPronto(&Serial);
    }
    delay(1000);
  }
    irrecv.resume();
}
