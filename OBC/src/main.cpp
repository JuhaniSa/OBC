#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
byte data_bytes [39];
byte ResponseLength =37;
byte byte_number;
byte out_input [4];
byte send [7];
byte send_data_bytes[8];
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2);
int TPS;
int ADV;
int VE;
int AE;
int IAT;
int MAP;



void req_data_r() //Requests all the data available.
{
Serial.write("r"); //new type real time data.
Serial.write(0x00); //Speeduino TS canID, not used atm.
Serial.write(0x30); //command type, 0x30 for real time data.
Serial.write(4); //offset for the data. LSB
Serial.write(0x00); // offset is in 2 bytes. LSB first.
Serial.write(ResponseLength); //how many bytes we need back. LSB
Serial.write(0x00); // number of bytes is in 2 bytes. LSB first.
}

void read_data(byte data [])  //Saves data from temporary array (and prints it for debug..)
{
  TPS=(data[25]);
  ADV=data[24];
  VE=data[17];
  AE=data[15];
  IAT =data[6];
  MAP=data[2];
  lcd.clear();
  lcd.print("TPS: ");
  lcd.print(TPS);
  lcd.print("MAP: ");
  lcd.print(MAP);
  lcd.setCursor(0,1);
  lcd.print(Serial.available());
  delay(5);
}
void setup() {
  lcd.backlight(); //Setup Backlight
  lcd.init();//Intialize lcd
  lcd.begin(16,2);//set display size
  lcd.print("Lcd-intialized");
  Serial.begin(115200);//Start serial
  delay(2000);
  lcd.clear();
}
void send_data()
{
  char start = Serial.read();
}



void save_data()
{
  if (Serial.available() > 0)//Checks if serial data is recieved
  {
    for (int b=0;b<sizeof(data_bytes);b++)//Read and save all the data to Byte array
    {
      data_bytes[b]=Serial.read();
      }
    
    /*
    for (int i ;i<sizeof(data_bytes);i++)   //Print all data from byte array to serial
    {
      Serial.print("Data at:");
      Serial.print(i);
      Serial.print(data_bytes[i],DEC);
      Serial.print("***");
    }
    */

   //int testi= Serial.read(); //Print all data to serial in one int
   //Serial.print(testi);
   //Serial.print("***");
  if(data_bytes[0]==114)  //Check if the data array is saved correctly
  {
    read_data(data_bytes);   //Calls function to process data
  }

  }
  
  else
  {
    lcd.clear();
    lcd.print("No connection!");
    delay(2000);
    lcd.clear();
    
  }
  memset(data_bytes,0,sizeof(data_bytes));
  byte_number=0;
  req_data_r();
  
}


void loop()
 {
   lcd.clear();
   int sensor0 = analogRead(A0);
   
   if (Serial.available()>0)
   {
     for(int i=0;i<sizeof(out_input);i++){
       out_input[i] = Serial.read();
       Serial.print(out_input[i]);
     }
     if (out_input[0]==82){
       Serial.write("G");
       Serial.write(1);//Confirms valid data request
       Serial.write(0);//Input chanel

       Serial.write(sensor0);//Data bit
       Serial.write(0);
       Serial.write(0);
       Serial.write(0);
       Serial.write(0);
       Serial.write(0);
       Serial.write(0);
       Serial.write(0);
      

     }
     
     }
     delay(50);
     save_data();
     delay(50);
   }
  //save_data();

 
 
  
