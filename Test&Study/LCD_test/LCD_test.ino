#define BAUDRATE 115200

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  float dust = 3.123;

  String str = String(dust) + "ug/m3";
  lcd.setCursor(0,0);
  lcd.print(str);
//  lcd.setCursor(6,0);
//  lcd.print("ug/m3");
  delay(1000);
  lcd.clear();
}
