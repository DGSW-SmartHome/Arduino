// -------------------------------------------------
// FileName : Serial test.ino
// Describe : 아두이노 라즈베리파이 간 시리얼 통신
// History : 2021-10-17
// -------------------------------------------------
#define DEBUG 1

#define BOADRATE 115200

int light[6] = {0,0,0,0,0,0};

void setup() {
  Serial.begin(BOADRATE);
}

void loop() {
  if (Serial.available()){
//    recvCmd();
    recvStat();
  }
  sendStat();

  delay(1000);
}

void recvCmd() {
  String cmd = Serial.readStringUntil('\r');
  Serial.println(cmd);
}

void recvStat() {
  String cmd = Serial.readStringUntil('\r');
  Serial.println(cmd);

  if(cmd.substring(0,2) == "L1") light[0] = cmd.substring(3,4).toInt();
  else if(cmd.substring(0,2) == "L2") light[1] = cmd.substring(3,4).toInt();
  else if(cmd.substring(0,2) == "L3") light[2] = cmd.substring(3,4).toInt();
  else if(cmd.substring(0,2) == "L4") light[3] = cmd.substring(3,4).toInt();
  else if(cmd.substring(0,2) == "L5") light[4] = cmd.substring(3,4).toInt();
  else if(cmd.substring(0,2) == "L6") light[5] = cmd.substring(3,4).toInt();
}

void sendStat() {
  // finedust
  int finedust = 0;
#ifdef DEBUG
  Serial.print("finedust: ");
  Serial.print(finedust);
#else
  Serial.write("F");
  Serial.write((byte*)&finedust, 4);
#endif

  // light
#ifdef DEBUG
  Serial.print(" / light1: ");
  Serial.print(light[0]);
  Serial.print(" / light2: ");
  Serial.print(light[1]);
  Serial.print(" / light3: ");
  Serial.print(light[2]);
  Serial.print(" / light4: ");
  Serial.print(light[3]);
  Serial.print(" / light5: ");
  Serial.print(light[4]);
  Serial.print(" / light6: ");
  Serial.println(light[5]);
#else
  Serial.write("L1");
  Serial.write((byte*)&light[0], 1);
  Serial.write("L2");
  Serial.write((byte*)&light[1], 1);
  Serial.write("L3");
  Serial.write((byte*)&light[2], 1);
  Serial.write("L4");
  Serial.write((byte*)&light[3], 1);
  Serial.write("L5");
  Serial.write((byte*)&light[4], 1);
  Serial.write("L6");
  Serial.write((byte*)&light[5], 1);
  Serial.write('\n');
#endif
}
