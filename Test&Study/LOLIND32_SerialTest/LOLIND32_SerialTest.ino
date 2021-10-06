void setup() {
  Serial.begin(115200);
  Serial.print("start");
}

int t = 0;
void loop() {
  Serial.print("acting : ");
  Serial.print(t);
  Serial.println("sec");
  delay(1000);
}
