int up = 2, dn = 3, ure = 4, dre = 5;
int cm = 0, sdel = 0;
String dat = "";
void setup() {
  Serial.begin(9600);
  pinMode(up, OUTPUT);
  digitalWrite(up, 0);
  pinMode(dn, OUTPUT);
  digitalWrite(dn, 0);
  pinMode(ure, OUTPUT);
  digitalWrite(ure, 0);
  pinMode(dre, OUTPUT);
  digitalWrite(dre, 0);
  OCR1A = 0xAF;
  TIMSK1 |= _BV(OCIE1A);
}

ISR(TIMER1_COMPA_vect) 
{

  if (cm == 1)
   {
    sdel++;  //Serial.println("int");
    if (sdel == 8000) {
      cm = 0;
      sdel = 0;
      Serial.println("int off");
      digitalWrite(up, 0);
      digitalWrite(dn, 0);
      digitalWrite(ure, 0);
      digitalWrite(dre, 0);
    }
  }
}

void loop() {
  if (Serial.available()) {
    dat = Serial.readString();
    if (dat == "down") {
      cm = 1;
      sdel = 0;
      Serial.println("down");
      digitalWrite(up, 0);
      digitalWrite(dn, 1);
    }
    if (dat == "up") {
      cm = 1;
      sdel = 0;
      Serial.println("up");
      digitalWrite(up, 1);
      digitalWrite(dn, 0);
    }

    if (dat == "head down") {

      cm = 1;
      sdel = 0;
      Serial.println("head down");
      digitalWrite(ure, 1);
      digitalWrite(dre, 0);
    }
    if (dat == "head up") {
      cm = 1;
      sdel = 0;
      Serial.println("head up");
      digitalWrite(ure, 0);
      digitalWrite(dre, 1);
    }
    if (dat == "home") {
      cm = 1;
      sdel = 0;
      Serial.println("home");
      digitalWrite(up, 0);
      digitalWrite(dn, 1);
      digitalWrite(ure, 0);
      digitalWrite(dre, 1);
    }
    if (dat == "stop") {
      Serial.println("stop");
      digitalWrite(up, 0);
      digitalWrite(dn, 0);
      digitalWrite(ure, 0);
      digitalWrite(dre, 0);
    }
  }
}
