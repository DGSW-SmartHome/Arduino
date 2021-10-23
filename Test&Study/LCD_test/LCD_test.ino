#define BAUDRATE 115200

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void loop() {
  lcd.print("Hello, World!");
  delay(1000);
  lcd.clear();
}
