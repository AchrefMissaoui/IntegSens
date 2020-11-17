#include <SparkFun_Ublox_Arduino_Library.h> 
SFE_UBLOX_GPS myGPS;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

void setup()
{
  Serial.begin(115200);
  lcd.begin(16, 2);
  
  lcd.print("...");
  do {
    mySerial.begin(38400);
    if (myGPS.begin(mySerial) == true) break;
  }while(1);
   myGPS.setUART1Output(COM_TYPE_UBX); //Set the UART port to output UBX only
  myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  }


void loop()
{
myGPS.getEsfInfo();myGPS.getEsfIns();
      lcd.clear();
      lcd.print("fusion mode "); lcd.print(myGPS.imuMeas.fusionMode);     
      Serial.print("fusion mode ");Serial.println(myGPS.imuMeas.fusionMode);
if(myGPS.getEsfIns()){
   Serial.print(F("X: "));
    Serial.println(myGPS.imuMeas.xAngRate);  
    Serial.print(F("Y: "));
    Serial.println(myGPS.imuMeas.yAngRate);  
    Serial.print(F("Z: "));
    Serial.println(myGPS.imuMeas.zAngRate);  
    Serial.print(F("data "));
   Serial.println(myGPS.imuMeas.rawDataType);  }
 

  
//}
  delay(1200);
}
