#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
byte data_lenght [77];
byte byte_number;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2);
unsigned int AFR_RAW; //AFR value
float o2val; //AFR value
int MAP=-1; //MAP from speeduino
int BARO; //barometer from speeduino
float boost1;
float boost;

void req_data_r() //Requests all the data available.
{
Serial.write("r");
Serial.write(0x00); //Speeduino TS canID, not used atm.
Serial.write(0x30); //command type, 0x30 for real time data.
Serial.write(4); //offset for the data. LSB
Serial.write(0x00); // offset is in 2 bytes. LSB first.
Serial.write(37); //how many bytes we need back. LSB
Serial.write(0x00); // number of bytes is in 2 bytes. LSB first.
}

void read_data()
{

}
void setup() {
  lcd.backlight();
  lcd.init();
  lcd.begin(16,2);
  lcd.print("Lcd-intialized");
  Serial.begin(115200);
  delay(2000);
  lcd.clear();
  req_data_r();
  
}

void loop()
 {
  if (Serial.available() > 0)
  {
   lcd.clear();
   int info_ = Serial.read();
   Serial.print(info_);

  }
  
  else
  {
    lcd.clear();
    lcd.print("kakkaa");
    delay(2000);
  }
  delay(50);
  



  
}