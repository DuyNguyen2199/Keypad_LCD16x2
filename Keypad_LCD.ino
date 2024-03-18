#include <LiquidCrystal_I2C.h>
#include <Keypad.h>  
#include<EEPROM.h>  
//#include "HX711.h"

//HX711 scale(A1, A0);
#define clk  4
#define data 3
#define buzzer 10
#define Relay 12
#define led 13
  
 const byte ROWS = 4; 
 const byte COLS = 4; 
 char hexaKeys[ROWS][COLS] = {  
  {'1','2','3','A'},  
  {'4','5','6','B'},  
  {'7','8','9','C'},  
  {'*','0','#','D'}  
 };  
 byte rowPins[ROWS] = {9,8,7,6}; /* connect to the row pinouts of the keypad */  
 byte colPins[COLS] = {5,4,3,2}; /* connect to the column pinouts of the keypad */  
 Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);   
 LiquidCrystal_I2C lcd(0x27,20,2);
 char password[4];  
 char pass[4],pass1[4];  
 int i=0;  
 char customKey=0;  

 void setup() {
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
  pinMode(Relay,OUTPUT);
  pinMode(led,OUTPUT);
  //scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  //scale.tare();               // reset the scale to 0
  lcd.init();                    
  lcd.init();
  lcd.backlight();
  lcd.print(" XIN CHAO ");  
  lcd.setCursor(0,1);  
  lcd.print(" Keypad Lock ");  
  delay(2000);  
  lcd.clear();  
  lcd.print("Enter Pass:");  
  lcd.setCursor(0,1);  
  for(int j=0;j<4;j++)  
  EEPROM.write(j, j+49);  
  for(int j=0;j<4;j++)  
  pass[j]=EEPROM.read(j);  
}

 void loop()  
 {  
  customKey = customKeypad.getKey();  
  if(customKey=='#')  
  change();  
  if (customKey)  
  {  
    password[i++]=customKey;  
    lcd.print(customKey);  
    beep();  
  }  
  if(i==4)  
  {  
   delay(200);  
   for(int j=0;j<4;j++)  
   pass[j]=EEPROM.read(j);  
   if(!(strncmp(password, pass,4)))  
   {  
     digitalWrite(1, HIGH  
     );  
    digitalWrite(led, HIGH);  
    beep();  
    lcd.clear();  
    lcd.print("Pass Accepted");  
    delay(2000);  
    lcd.setCursor(0,1);  
    lcd.print("#.Change Pass");  
    delay(2000);  
    lcd.clear();  
    lcd.print("Enter Pass:");  
    lcd.setCursor(0,1);  
    i=0;  
    digitalWrite(led, LOW);  
     digitalWrite(1, LOW);  
   }  
   else  
   {  
    digitalWrite(buzzer, HIGH);  
    lcd.clear();  
    lcd.print("WRONG PASS");  
    lcd.setCursor(0,1);  
    lcd.print("#.Change Pass");  
    delay(2000);  
    lcd.clear();  
    lcd.print("Enter Pass:");  
    lcd.setCursor(0,1);  
    i=0;  
    digitalWrite(buzzer, LOW);  
   }  
  }  
 }  
 void change()  
 {  
  int j=0;  
  lcd.clear();  
  lcd.print("UR Current Pass");  
  lcd.setCursor(0,1);  
  while(j<4)  
  {  
   char key=customKeypad.getKey();  
   if(key)  
   {  
    pass1[j++]=key;  
    lcd.print(key);  
    beep();  
   }  
   key=0;  
  }  
  delay(500);  
  if((strncmp(pass1, pass, 4)))  
  {  
   lcd.clear();  
   lcd.print("Wrong Pass...");  
   lcd.setCursor(0,1);  
   lcd.print("Better Luck Again");  
   delay(1000);  
  }  
  else  
  {  
   j=0;  
  lcd.clear();  
  lcd.print("Enter New Pass:");  
  lcd.setCursor(0,1);  
  while(j<4)  
  {  
   char key=customKeypad.getKey();  
   if(key)  
   {  
    pass[j]=key;  
    lcd.print(key);  
    EEPROM.write(j,key);  
    j++;  
    beep();  
   }  
  }  
  lcd.print(" Done......");  
  delay(1000);  
  }  
  lcd.clear();  
  lcd.print("Enter Ur Pass:");  
  lcd.setCursor(0,1);  
  customKey=0;  
 }  
 void beep()  
 {  
  digitalWrite(buzzer, HIGH);  
  delay(20);  
  digitalWrite(buzzer, LOW);  
 } 
