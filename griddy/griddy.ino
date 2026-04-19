#include <Wire.h>
#include <LiquidCrystal.h>

const int LED1 = 4;
const int LED2 = 3;
const int LED3 = 5;
const int LED4 = 2;

const int potentiometer_pin = A1; 
const int photoresitor = A0;


unsigned long lastUpdate = 0;
const long interval = 50;

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);


  lcd.begin(16, 2);
  
  Serial.begin(9600);
  
  
  Wire.begin(9); 
}

void loop() {
  unsigned long currentMillis = millis();

  //no dealy cuz of papa theys
  if (currentMillis - lastUpdate >= interval) {
    lastUpdate = currentMillis;


    int potValue = analogRead(potentiometer_pin); 
    int lightValue = analogRead(photoresitor);     

    //get individual inputs
    int potPercent = map(potValue, 0, 1023, 0, 100);
    int lightPercent = map(lightValue, 0, 1023, 0, 100);

    // average of the two consumer inputs
    int totalLevel = (potPercent + lightPercent) / 2;

    //Easyies way I think
    digitalWrite(LED1, (totalLevel > 10) ? HIGH : LOW);
    digitalWrite(LED2, (totalLevel > 35) ? HIGH : LOW);
    digitalWrite(LED3, (totalLevel > 65) ? HIGH : LOW);
    digitalWrite(LED4, (totalLevel > 85) ? HIGH : LOW);

    
    lcd.setCursor(0, 0);
    if (totalLevel >= 95) {
      
      lcd.print("STATE: OVERLOAD!"); 
      lcd.setCursor(0, 1);
      lcd.print("Load: 100%      ");
    } else {
      lcd.print("Grid: Healthy   "); 
      lcd.setCursor(0, 1);
      lcd.print("Load: ");
      lcd.print(totalLevel);
      lcd.print("%          ");
    }

    
    Serial.print("Load: ");
    Serial.println(totalLevel);
  }
}