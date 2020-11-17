
#include <SparkFun_Ublox_Arduino_Library.h>
SFE_UBLOX_GPS myGPS;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);
long lastTime = 0;
 
void setup()
{

  Serial.begin(115200);
  lcd.begin(16, 2);
  do {
    Serial.println("GPS: trying 38400 baud");
    mySerial.begin(38400);
    if (myGPS.begin(mySerial) == true) break;
  }while(1);
   myGPS.setUART1Output(COM_TYPE_UBX);

}

void loop()
{
    String latString = "LAT:" ;
    String lonString = "LON:" ;
   
 if (millis() - lastTime > 1000)
  {
    lastTime = millis(); //Update the timer
    long latitude = myGPS.getLatitude();
    Serial.print(latString);
    Serial.println(latitude);

    long longitude = myGPS.getLongitude();
    Serial.print(lonString);
    Serial.println(longitude);

     latString += latitude; lonString += longitude ;
     lcd.setCursor(0,0);
     lcd.print(latString);
     lcd.setCursor(0,1);
     lcd.print(lonString);

  }
     
}
