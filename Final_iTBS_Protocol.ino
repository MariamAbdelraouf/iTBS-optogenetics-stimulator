// ==========================
// Pin assignments
// ==========================
const int stimPin     = 2;  // White LED or Laser (via BNC)
const int redLEDPin   = 3;  // Red LED indicator
const int buzzerPin   = 8;  // Buzzer indicator
const int buttonPin   = 6;  // Push button

// ==========================
// Debounce variables
// ==========================
int buttonState;
int lastButtonState = HIGH;  // INPUT_PULLUP → idle = HIGH
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// ==========================
// State tracking
// ==========================
enum State { IDLE, START_SIGNAL, STIMULATION, END_SIGNAL };
State currentState = IDLE;

bool paused = false;
bool restartRequested = false;

// ==========================
// Double-press tracking
// ==========================
unsigned long lastPressTime = 0;
unsigned long doublePressWindow = 400; // ms

// ==========================
void setup() {
  pinMode(stimPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(stimPin, LOW);
  digitalWrite(redLEDPin, LOW);
  noTone(buzzerPin);
}

// ==========================
void loop() {
  checkButton();

  switch (currentState) {
    case IDLE:
      // Do nothing until button pressed
      break;

    case START_SIGNAL:
      signal3x();
      if (!restartRequested) currentState = STIMULATION;
      break;

    case STIMULATION:
      runProtocol();
      if (!restartRequested) currentState = END_SIGNAL;
      break;

    case END_SIGNAL:
      signal3x();
      currentState = IDLE;
      break;
  }

  if (restartRequested) {
    restartRequested = false;
    currentState = START_SIGNAL;
  }
}

// ==========================
// Button handler
// ==========================
void checkButton() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        unsigned long now = millis();

        if (now - lastPressTime < doublePressWindow) {
          // Double press → Restart
          restartRequested = true;
          paused = false; // clear pause
        } else {
          // Single press
          if (currentState == IDLE) {
            paused = false;
            restartRequested = false;
            currentState = START_SIGNAL;
          } else if (paused) {
            paused = false; // Resume
          } else {
            paused = true;  // Pause
          }
        }

        lastPressTime = now;
      }
    }
  }

  lastButtonState = reading;
}

// ==========================
// Full stimulation protocol
// ==========================
void runProtocol() {
  for (int session = 0; session < 5 && !restartRequested; session++) {
    for (int block = 0; block < 20 && !restartRequested; block++) {
      for (int burst = 0; burst < 10 && !restartRequested; burst++) {
        for (int pulse = 0; pulse < 3 && !restartRequested; pulse++) {
          waitIfPaused();
          if (restartRequested) break;

          digitalWrite(stimPin, HIGH);
          smartDelay(10);
          digitalWrite(stimPin, LOW);
          if (pulse < 2) smartDelay(50);
        }
        smartDelay(100); // between bursts
      }
      smartDelay(8000); // rest between blocks
    }
    if (session < 4 && !restartRequested) {
      smartDelay(120000); // rest between sessions
    }
  }
}

// ==========================
// Smart delay (pause/restart aware)
// ==========================
void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms && !restartRequested) {
    checkButton();
    if (paused) waitIfPaused();
  }
}

// ==========================
// Pause waiting loop
// ==========================
void waitIfPaused() {
  while (paused && !restartRequested) {
    checkButton();
    delay(10);
  }
}

// ==========================
// 3x buzzer + LED signal
// ==========================
void signal3x() {
  for (int i = 0; i < 3 && !restartRequested; i++) {
    waitIfPaused();
    if (restartRequested) break;

    digitalWrite(redLEDPin, HIGH);
    tone(buzzerPin, 1000);
    smartDelay(300);
    digitalWrite(redLEDPin, LOW);
    noTone(buzzerPin);
    smartDelay(300);
  }
}



