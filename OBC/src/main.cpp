#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
byte data_bytes[39];
byte ResponseLength = 37;
byte byte_number;
byte out_input[4];
byte send[7];
byte send_data_bytes[8];
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
int TPS;
int ADV;
int VE;
int AE;
int IAT;
int MAP;

unsigned long refresh_time = 60;
unsigned long lastTime = 0;

int sensor0 = analogRead(A0);
int sensor1 = analogRead(A1);

void req_data_r() //Requests all the data available.
{
  

  Serial.write("r");            //new type real time data.
  Serial.write(0x00);           //Speeduino TS canID, not used atm.
  Serial.write(0x30);           //command type, 0x30 for real time data.
  Serial.write(4);              //offset for the data. LSB
  Serial.write(0x00);           // offset is in 2 bytes. LSB first.
  Serial.write(ResponseLength); //how many bytes we need back. LSB
  Serial.write(0x00);         // number of bytes is in 2 bytes. LSB first.
}

void read_data(byte data[]) //Saves data from temporary array (and prints it for debug..)
{
  TPS = (data[25]);
  ADV = data[24];
  VE = data[17];
  AE = data[15];
  IAT = data[6];
  MAP = data[2];
  
  
  
}

void setup()
{
  lcd.backlight();  //Setup Backlight
  lcd.init();       //Intialize lcd
  lcd.begin(16, 2); //set display size
  lcd.print("Lcd-intialized");
  Serial.begin(115200); //Start serial
  delay(2000);
  lcd.clear();
}

void save_data()
{
  
  if (Serial.available() > 0) //Checks if serial data is recieved
  {
    for (int b = 0; b < sizeof(data_bytes); b++) //Read and save all the data to Byte array
    {
      data_bytes[b] = Serial.read();
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

    if (data_bytes[0] == 114) //Check if the data array is saved correctly
    {
            read_data(data_bytes); //Calls function to process data
    }
  }
  memset(data_bytes,0,sizeof(data_bytes)); 
  byte_number=0;
  

}

void send_data(int val, int location)
{
  
    for (int i = 0; i < sizeof(out_input); i++)
    {
      out_input[i] = Serial.read();
      //Serial.print(out_input[i]);   //For debug
    }
    if (out_input[0] == 82)
    {
      Serial.write("G");
      Serial.write(1);               //Confirms valid data request
      Serial.write(location);        //Input chanel
      Serial.write(val);             //Data bit
      Serial.write(0);
      Serial.write(0);
      Serial.write(0);
      Serial.write(0);
      Serial.write(0);
      Serial.write(0);
      Serial.write(0);
    }
  
}

void read_sensors()
{
  sensor0 = analogRead(A0);
  sensor1 = analogRead(A1);
}
  
void display(int location)
{
  lcd.clear();
  lcd.print("MAP: ");
  lcd.print(MAP);
  lcd.print(" ");
  lcd.print("TPS :");
  lcd.print(TPS);
}


void loop()
{ 
  read_sensors();
  unsigned long currentTime = millis();

  if (Serial.available()>0)
  {
    send_data(sensor0, 0);
    send_data(sensor0,1);
  }
  req_data_r();
  delay(10);        //No idea why this has to be here??!
  save_data();
  
  
  
  
  if(currentTime-lastTime>refresh_time)
  {
    display(0x27);
    lastTime=currentTime;
  }
 
 
}

