#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int switchState = 0;
int prevSwitchState = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(6, INPUT);

  lcd.begin(16, 2);

  setMessage("The Northerners", "Eve Online");
}

void loop() {
  // put your main code here, to run repeatedly:
  switchState = digitalRead(6);
  digitalWrite(LED_BUILTIN, switchState);
  
  if (switchState != prevSwitchState) {
    if (switchState == HIGH) {
        switchMessage();
    }
    prevSwitchState = switchState;
  }

  delay(1500);
  switchMessage();
}

void switchMessage() {
  int rnd = random(3);
  switch(rnd) {
    case 0:
        setMessage("rippz4ever", "Join fleet, NOW!");
        break;
    case 1:
        setMessage("Baron Holbach", "Never logs in....");
        break;
    case 2:
        setMessage("Kristinsa", "Avoids meetups");
        break;  
  }
  Serial.print("switch: ");
  Serial.println(rnd);
}

void setMessage(String line1, String line2) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(line1);
        lcd.setCursor(0, 1);
        lcd.print(line2);
}
