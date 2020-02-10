#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int switchState = 0;
int prevSwitchState = 0;

int min = 32;
int hr = 3;
int sec = 0;

// For accurate Time reading, use Arduino Real Time Clock
static uint32_t last_time, now = 0; // RTC

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  lcd.begin(16, 2);

  now = millis();
  last_time = millis();
  showTime();
}

void loop() {
  
  showTime();
  
  sec += 1;

  if (sec >= 60) {
    sec = 0;
    min += 1;
  }

  if (min >= 60) {
    min = 0;
    hr += 1;
  }

  if (hr >= 24) {
    hr = 0;
  }

  now=millis();
  while ((now-last_time) < 1000 ) // wait1000ms
  {
    now=millis();
//    Serial.println(now-last_time);
  }
  last_time = millis();
}

void showTime() {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" ");
        lcdPrintNumber(hr);
//        Serial.print(hr);
        lcd.print(" : ");
//        Serial.print(" : ");
        lcdPrintNumber(min);
//        Serial.print(min);
        if (sec % 2 == 1) {
          lcd.print(" : ");
//        Serial.print(" : ");
        } else {
          lcd.print(" . ");
//        Serial.print(" : ");
        }

        lcdPrintNumber(sec);
//        Serial.println(sec);
        
}

void lcdPrintNumber(int number) {
  if (number < 10) {
    lcd.print(0);
  }
  lcd.print(number);
}
