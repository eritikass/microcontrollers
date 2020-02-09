#define GREEN 3
#define YELLOW 4
#define RED 5
#define BLUE 6
#define RED2 7
#define BLUE2 8
#define YELLO2 9
#define GREEN2 10

#define BUTTON1 2

#define INIT_STATE 0b10101010

int switchState = 0;
bool toggleAll = false;
byte state = INIT_STATE;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
  

  pinMode(RED2, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE2, OUTPUT);
  pinMode(YELLO2, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(BUTTON1, INPUT);

  digitalPinToInterrupt(BUTTON1);
}

int getStateHighLow(int bitNumber) {
   return (state & (1 << (bitNumber - 1))) != 0 ? HIGH : LOW;
}

void loop() {
  int switchStateTmp = digitalRead(BUTTON1);
  digitalWrite(LED_BUILTIN, switchStateTmp);
  
  if (switchStateTmp != switchState) {
    switchState = switchStateTmp;
    if (switchState == HIGH) {
      toggleAll = !toggleAll;
      state = INIT_STATE;
    }
  }

  if (toggleAll) {
    if (state == 0b11111111) {
      state = 0b00000000;
    } else {
      state = 0b11111111;
    }
  } else {
    state = state << 1;
    if (getStateHighLow(3) == HIGH) {
      state |= 1UL << 0;
    }
  }

  Serial.println(state);

  digitalWrite(RED2, getStateHighLow(1));
  digitalWrite(BLUE, getStateHighLow(2));
  digitalWrite(RED, getStateHighLow(3));
  digitalWrite(YELLOW, getStateHighLow(4));
  digitalWrite(GREEN, getStateHighLow(5));
  digitalWrite(BLUE2, getStateHighLow(6));
  digitalWrite(YELLO2, getStateHighLow(7));
  digitalWrite(GREEN2, getStateHighLow(8));

  delay(400);
}
