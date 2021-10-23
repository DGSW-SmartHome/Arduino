#define BAUDRATE 115200

#define pin 8

int pulse = 0;
float ugm3 = 0;

void setup() {
  Serial.begin(BAUDRATE);
  pinMode(pin, INPUT);
}

void loop() {
  pulse = pulseIn(pin, LOW);
  ugm3 = (pulse-1400) / 14.0;
  Serial.print(ugm3, 4);
  Serial.println("\tug/m3");
  delay(100);
}
