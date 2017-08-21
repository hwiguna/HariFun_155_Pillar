int inA1 = 4; // input 1 of the stepper
int inA2 = 5; // input 2 of the stepper
int inB1 = 7; // input 3 of the stepper
int inB2 = 6; // input 4 of the stepper

byte forwardButton = 2;
byte reverseButton = 3;
const byte isPressed = 0;

byte mode = 0;
byte stopMode = 0;
const byte forwardMode = 1;
const byte reverseMode = 2;

int stepDelay = 3; // Delay between steps in milliseconds

void setup() {
  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);
  pinMode(forwardButton, INPUT_PULLUP);
  pinMode(reverseButton, INPUT_PULLUP);
}

void step1() {
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
  delay(stepDelay);

}
void step2() {
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
  delay(stepDelay);
}
void step3() {
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
  delay(stepDelay);
}
void step4() {
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
  delay(stepDelay);
}
void stopMotor() {
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);
}

void loop() {
  bool forwardPressed = digitalRead(forwardButton) == isPressed;
  bool reversePressed = digitalRead(reverseButton) == isPressed;
  bool bothPressed = forwardPressed && reversePressed;
  if (bothPressed) {
    mode = stopMode;
    delay(500);
  }
  else {
    if (forwardPressed) mode = forwardMode;
    if (reversePressed) mode = reverseMode;
  }

  switch (mode)
  {
    case forwardMode:
      step1();
      step2();
      step3();
      step4();
      break;
    case reverseMode:
      step3();
      step2();
      step1();
      step4();
      break;
  }
}

