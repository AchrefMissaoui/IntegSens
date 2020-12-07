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
  int animationDirection = 0;// 0 : nothing , 1 : >>> , 2 : <<<
  int animationY = 0 , animationX;
  int delayTime = 250;
  int initialX = 8 ;
  int gyroX , gyroY , gyroZ;
 

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.print("connecting...");
  do {
    mySerial.begin(38400);
    if (myGPS.begin(mySerial) == true) break;
  }while(1);
   myGPS.setUART1Output(COM_TYPE_UBX); //Set the UART port to output UBX only
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
  
  // create a new character
  lcd.createChar(1, armsDown);
  // create a new character
  lcd.createChar(2, armsUp);
  
  animationX = initialX;

  //gyro info
   gyroY = 0; gyroZ = 0; gyroX = 0; 
  
  

  
}

void loop() {
  myGPS.getEsfInfo();myGPS.getEsfIns();
  lcd.clear();
  lcd.print("fusion mode "); lcd.print(myGPS.imuMeas.fusionMode);     
  Serial.print("fusion mode ");Serial.println(myGPS.imuMeas.fusionMode);
    if(myGPS.imuMeas.fusionMode==1){
      lcd.clear();
      gyroY = myGPS.imuMeas.yAngRate/1000;
      gyroZ = myGPS.imuMeas.zAngRate/1000;
      gyroX = myGPS.imuMeas.xAngRate/1000;

      
      if(gyroX > 0 &&  gyroZ < 0){
        animationDirection = 1;
                            }else 
      if(gyroX < 0 &&  gyroZ > 0){ 
        animationDirection = 2;
                            }else 
       {animationDirection = 0;
                            
     }if(gyroZ < 0 && gyroY > 0){animationY = 0;   
                            }else 
      if(gyroZ > 0 && gyroY < 0){animationY = 1;}

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

  
 
    
}
