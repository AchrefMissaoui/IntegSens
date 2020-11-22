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
  
  lcd.print("connecting...");
  do {
    mySerial.begin(38400);
    if (myGPS.begin(mySerial) == true) break;
  }while(1);
   myGPS.setUART1Output(COM_TYPE_UBX); //Set the UART port to output UBX only
  }


void loop()
{
myGPS.getEsfInfo();myGPS.getEsfIns();
      lcd.clear();
      lcd.print("fusion mode "); lcd.print(myGPS.imuMeas.fusionMode);     
      Serial.print("fusion mode ");Serial.println(myGPS.imuMeas.fusionMode);
    Serial.print(F("X: "));
    Serial.println(myGPS.imuMeas.xAngRate);  
    Serial.print(F("Y: "));
    Serial.println(myGPS.imuMeas.yAngRate);  
    Serial.print(F("Z: "));
    Serial.println(myGPS.imuMeas.zAngRate);  
    Serial.print(F("data "));
    Serial.println(myGPS.imuMeas.rawDataType);
    if(myGPS.imuMeas.fusionMode==1){
      lcd.clear();
      lcd.print("X");lcd.setCursor(0,1);lcd.print(myGPS.imuMeas.xAngRate/1000);
      lcd.setCursor(5,0);lcd.print("Y");lcd.setCursor(5,1);lcd.print(myGPS.imuMeas.yAngRate/1000);
      lcd.setCursor(10,0); lcd.print("Z");lcd.setCursor(10,1);lcd.print(myGPS.imuMeas.zAngRate/1000);
    }

  delay(250);
}
