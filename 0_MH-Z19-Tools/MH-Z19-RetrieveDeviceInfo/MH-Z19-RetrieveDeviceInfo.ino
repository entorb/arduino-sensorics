#include "MHZ19.h"                                                                                                 
#include <Arduino.h>
#include <SoftwareSerial.h>                               //  Remove if using HardwareSerial or non-uno compatabile device    

#define RX_PIN 16
#define TX_PIN 17
#define BAUDRATE_ESP32 115200
#define BAUDRATE_MHZ19 9600 // Native to the sensor (do not change)

MHZ19 myMHZ19;
SoftwareSerial mySerial(RX_PIN, TX_PIN);                  // Uno example

void setup()
{
  Serial.begin(BAUDRATE_ESP32);

  mySerial.begin(BAUDRATE_MHZ19);                               // Uno example: Begin Stream with MHZ19 baudrate  
  myMHZ19.begin(mySerial);                                // *Important, Pass your Stream reference here

  /*
    getVersion(char array[]) returns version number to the argument. The first 2 char are the major 
    version, and second 2 bytes the minor version. e.g 02.11
  */


}

void loop()
{
  char myVersion[4];          
  myMHZ19.getVersion(myVersion);

  Serial.print("\nFirmware Version: ");
  for(byte i = 0; i < 4; i++)
  {
    Serial.print(myVersion[i]);
    if(i == 1)
      Serial.print(".");    
  }
   Serial.println("");

   Serial.print("Range: ");
   Serial.println(myMHZ19.getRange());   
   Serial.print("CO2 (ppm): ");                      
   Serial.println(myMHZ19.getCO2());                                
   Serial.print("Background CO2: ");
   Serial.println(myMHZ19.getBackgroundCO2());
   Serial.print("Temperature Cal: ");
   Serial.println(myMHZ19.getTempAdjustment());
   Serial.print("ABC Status: "); myMHZ19.getABC() ? Serial.println("ON") :  Serial.println("OFF");
   delay(1000);
}
