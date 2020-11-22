/*
  Achref Missaoui, Mayar Affash WS2020/2021
*/

// include the library code:
#include <SparkFun_Ublox_Arduino_Library.h> 
SFE_UBLOX_GPS myGPS;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

// make custom characters:
byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};
  int animationDirection = 2;// 0 : nothing , 1 : >>> , 2 : <<<
  int animationY = 0 , animationX;
  int delayTime = 500;
  int initialX = 8 ;
  int gyroX , gyroY , gyroZ , lastGyroX , lastGyroY , lastGyroZ;
 

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.print("connecting...");
  do {
    mySerial.begin(38400);
    if (myGPS.begin(mySerial) == true) break;
  }while(1);
   myGPS.setUART1Output(COM_TYPE_UBX); //Set the UART port to output UBX only
  myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  
  // create a new character
  lcd.createChar(1, armsDown);
  // create a new character
  lcd.createChar(2, armsUp);
  
  animationX = initialX;

  //gyro info
    gyroX = 0 ; gyroY = 0 ; gyroZ = 0 ; 
    lastGyroX = 0 ; lastGyroY = 0 ; lastGyroZ = 0;
  

  
}

void loop() {
myGPS.getEsfInfo();myGPS.getEsfIns();
  gyroX = myGPS.imuMeas.xAngRate;
  gyroY = myGPS.imuMeas.yAngRate;
  gyroZ = myGPS.imuMeas.zAngRate;

if(gyroY > lastGyroY){
  animationDirection = 1;
}else if (gyroY < lastGyroY){ animationDirection = 2;
}else {animationDirection = 0;
}if(gyroZ > lastGyroZ){
  animationY = 0;
}else if(gyroZ < lastGyroZ){animationY = 1;}

lastGyroY = gyroY; lastGyroZ = gyroZ;
  
 switch (animationDirection){
    case 0: break; // animation stays in place
    case 1: // animation moves to the right
    if(animationX == 16){animationX = 0;}else{animationX++;}
    break;
    case 2: // animation moves to the left
    if(animationX == 0){animationX = 16;}else{animationX--;}
    break;}

    
    lcd.clear();
    lcd.setCursor(animationX, animationY);
    lcd.write(1);
    delay(delayTime);
    lcd.setCursor(animationX, animationY);
    lcd.write(2);
    delay(delayTime);
    
}
