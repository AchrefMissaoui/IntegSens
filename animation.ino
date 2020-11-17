/*
  Achref Missaoui, Mayar Affash WS2020/2021

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K potentiometer:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * 10K poterntiometer on pin A0


*/

// include the library code:
#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);

// make some custom characters:
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
  int animationY = 0;
  int delayTime = 500;
  int initialX = 8 , currentX;
 

void setup() {
  // initialize LCD and set up the number of columns and rows:
  lcd.begin(16, 2);
  // create a new character
  lcd.createChar(1, armsDown);
  // create a new character
  lcd.createChar(2, armsUp);
  currentX = initialX;


  
}

void loop() {
 switch (animationDirection){
    case 0: break; // animation stays in place
    case 1: // animation moves to the right
    if(currentX == 16){
      currentX = 0;}else{
    currentX++;}
    break;
    case 2: // animation moves to the left
    if(currentX == 0){
      currentX = 16;}else{
    currentX--;}
    break;
  }
    lcd.clear();
    lcd.setCursor(currentX, animationY);
    lcd.write(1);
    delay(delayTime);
    lcd.setCursor(currentX, animationY);
    lcd.write(2);
    delay(delayTime);
    
}
