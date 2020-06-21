#include <Arduino.h>
#include <Wire.h>
#include <TinyGPS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>

//ECU data reading settings
byte ResponseLength = 37;
byte data_bytes[75];
byte byte_number;
byte out_input[4];
byte send[7];
byte send_data_bytes[8];

int TPS;
int ADV;
int VE;
int AE;
int IAT;
int MAP;
int CLT;
int DWELL;
int VOLTAGE;
int O2;
int RPM_LB;
int RPM_HB;
int AFR_TARG;
int PW_LB;
int PW_HB; 
int RPM;
int PW;

//Screen settings
unsigned long refresh_time = 200;
unsigned long lastTime = 0;
unsigned long  last_loop_time = 0;
unsigned long data_ref_rate =  15;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_ADDR  0x3C
Adafruit_SSD1306 OLED1 (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//Reading sensor data
//int sensor0 = analogRead(A0);
//int sensor1 = analogRead(A1);

void req_data_r() //Sends data request to ECU
{
  

  Serial.write("r");            //new type real time data.
  Serial.write(0x00);           //Speeduino TS canID, not used atm.
  Serial.write(0x30);           //command type, 0x30 for real time data.
  Serial.write(4);              //offset for the data. LSB
  Serial.write(0x00);           // offset is in 2 bytes. LSB first.
  Serial.write(ResponseLength); //how many bytes we need back. LSB
  Serial.write(0x00);         // number of bytes is in 2 bytes. LSB first.
}

void req_data_A()
{
  Serial.write("A");
}
void read_data(byte data[]) //Saves data from temporary array (and prints it for debug..)
{ 
  //For "r" method
  // DWELL = data[1];//varma
  // MAP = data[2];//varma
  // IAT = data[4];//varma
  // CLT = data[5];
  // VOLTAGE = data[7];//varma
  // O2 = data[8];//varma
  // RPM_LB = data[12];
  // RPM_HB = data[13];
  // VE = data[16];
  // AFR_TARG = data[17];
  // PW_LB = data[18];
  // PW_HB = data[19];
  // ADV = data[21];
  // TPS = data[22];
  
  DWELL = data[4];//varma
  MAP = data[5];//varma
  IAT = data[7];//varma
  CLT = data[8];
  VOLTAGE = data[10];//varma
  O2 = data[11];//varma
  RPM_LB = data[15];
  RPM_HB = data[16];
  VE = data[19];
  AFR_TARG = data[20];
  PW_LB = data[21];
  PW_HB = data[22];
  ADV = data[24];
  TPS = data[25];

  RPM = word(data[16],data[15]);
  PW = word(data[21],data[22]);
}

void setup()
{
  lcd.backlight();  //Setup Backlight
  lcd.init();       //Intialize lcd
  lcd.begin(16, 2); //set display size
  lcd.print("Lcd-intialized");
  Serial.begin(115200); //Start serial

  OLED1.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  OLED1.clearDisplay();
   OLED1.print("TOIMII!!");

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

    if (data_bytes[0] == 0x41) //Check if the data array is saved correctly
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
  //sensor0 = analogRead(A0);
  //sensor1 = analogRead(A1);
}
  
void display(int location)
{
  lcd.clear();
  lcd.print("RPM:");
  lcd.print(RPM);
  lcd.setCursor(7,0);
  lcd.print(" ");
  lcd.print("MAP: ");
  lcd.print(MAP);
  lcd.setCursor(0,1);
  lcd.print("PW:");
  lcd.print(PW);
  lcd.setCursor(7,1);
  lcd.print(" CLT: ");
  lcd.print(CLT);
  

}


void loop()
{ 
  unsigned long currentTime = millis();
  
  
  //Read sensor data
  //read_sensors();
  //Start timer
  
  //Send sensor data
 // if (Serial.available()>0)
  {
    //send_data(sensor0, 0);
    //delay(2);
    //send_data(sensor0,1);
    //delay(2);
  }
  req_data_A();
  delay(20);           //No idea why, but this has to be here??!
  save_data();
  Serial.flush();
  //Update screen
  if(currentTime-lastTime>refresh_time)
  { 
    {
    display(0x27);
   
    }
  lastTime=currentTime;
  }
  last_loop_time=currentTime;
  
 
}

