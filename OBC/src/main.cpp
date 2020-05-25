#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <menu.h>

int button_pin = 2;

LiquidCrystal_I2C lcd (0x27,16,2);
Menu.

void setup() {
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();
  lcd.print("ok");
  pinMode(button_pin,INPUT);
  delay(2000);
}

void loop() 
{
  lcd.clear();
  if (digitalRead(button_pin) == LOW){
    Menu.
  lcd.print("Pressed");
  delay(50);
  };

  // put your main code here, to run repeatedly:
};