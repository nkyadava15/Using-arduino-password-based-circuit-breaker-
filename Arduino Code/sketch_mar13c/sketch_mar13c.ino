#include <Password.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27,16,2); 
#include <Keypad.h> 
 
const byte numRows= 4; 
 
const byte numCols= 4; 
 
char keymap[numRows][numCols]= { {'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},  
{'*', '0', '#', 'D'} }; 

byte rowPins[numRows] = {9,8,7,6};
byte colPins[numCols]= {5,4,3,2}; 
 
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols); 
int bulb=12; 
 
Password passwd = Password("123A4"); 
char passwd2[6]=""; 
int led = 13; 
const int pinBuz = 11;
 
 
void setup() { 
	Serial.begin(9600); 
	pinMode(bulb, OUTPUT); 
	pinMode(led, OUTPUT); 
	pinMode(pinBuz,OUTPUT);
	lcd.begin(); 
	lcd.clear();
	lcd.setCursor(1,0);  
	lcd.print("Enter Password: ");  
} 
 
void loop() { 
char key = myKeypad.getKey(); 
   if (key != NO_KEY){ 
         digitalWrite(pinBuz,HIGH);
delay(300); 
	  digitalWrite(pinBuz,LOW); 
	  Serial.print(key); 
	  delay(50);  
      switch (key){ 
      case 'D': changepasswd(); break;  
      case '*': checkpasswd(); break; 
      case '#':{ passwd.reset(); 
      lcd.clear(); 
	  lcd.setCursor(0,0);  
	  lcd.print(" Enter Password ");  
      break; 
      } 
     default: passwd.append(key); 
      } 
   } 
 
} 
 
void checkpasswd() { 
   if (passwd.evaluate()){ 
     lcd.clear();
     Serial.println("OK."); 
	 lcd.setCursor(0,0);  
	lcd.print("   SuccessfuL   ");  
	digitalWrite(led,HIGH); 
	digitalWrite(bulb,HIGH); 
   } else { 
    digitalWrite(led,LOW); 
     digitalWrite(bulb,LOW); 
     lcd.clear();
	 lcd.setCursor(0,0);  
	 lcd.print(" Wrong Password! ");  
	 Serial.println("Wrong password!"); 
   }  
   passwd.reset(); 
    
} 
 
void changepasswd(){ 
  
	lcd.clear();
    lcd.setCursor(0,0);  
   lcd.print("Change Password:");  
    for(byte i=0;i<5;i++){ 
       char key = NO_KEY; 
       while(key == NO_KEY || key=='*' || key=='#' || key=='D') key = myKeypad.getKey(); 
        passwd2[i] = key; 
        delay(60); 
    } 
    passwd2[5] = '\0'; 
    passwd.set(passwd2); 
	lcd.clear(); 
    lcd.setCursor(0,0);  
    lcd.print(" PW Changed To: ");  
    lcd.setCursor(0,1);  
	lcd.print("     ");  
	lcd.print(passwd2);  
	lcd.print("     ");  
    Serial.print("Password changed to "); 
	Serial.println(passwd2); 
}
