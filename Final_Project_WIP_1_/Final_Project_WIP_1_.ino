const int ButtonPin1 = 2;
const int ButtonPin2 = 3;
const int ButtonPin3 = 4;
const int PiezoPin = 5;
const int LED = 13;

const int C4 = 261;
const int D4 = 294;
const int E4 = 329;

const int noteSequence[] = {C4, D4, E4, E4, D4, C4, D4, C4, C4, E4};
const int sequenceLength = sizeof(noteSequence) / sizeof(int);
int position = 0;

bool GameWin;
bool GameOver;

void setup() {
  pinMode(ButtonPin1, INPUT_PULLUP);
  pinMode(ButtonPin2, INPUT_PULLUP);
  pinMode(ButtonPin3, INPUT_PULLUP);

  pinMode(LED, OUTPUT);
  pinMode(PiezoPin, OUTPUT);

  Serial.begin(9600);
  playNoteAndSendPosition(noteSequence[0]);
}

void loop() {
  if (GameOver) {

    if (GameWin) {
      digitalWrite(LED, HIGH);
      delay(500);
      digitalWrite(LED, LOW);
      delay(500);
    } else {
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
    }

    delay(1000);
    position = 0;
    GameWin = true;
    GameOver = false;
    playNoteAndSendPosition(noteSequence[0]);
  }

  if (digitalRead(ButtonPin1) == LOW) {
    checkNotePressed(C4);
  } else if (digitalRead(ButtonPin2) == LOW) {
    checkNotePressed(D4);
  } else if (digitalRead(ButtonPin3) == LOW) {
    checkNotePressed(E4);
  }
}


void playNoteAndSendPosition(int note) {
  tone(PiezoPin, note, 200);
  delay(200);
  noTone(PiezoPin);
  Serial.write(note);
}



void playNoteAndAdvanceSequence() {
  position++;

  if (position == sequenceLength) {
    GameWin = true;
    GameOver = true;
  } else {
    playNoteAndSendPosition(noteSequence[position]);
  }
}


void checkNotePressed(int note) {

  if (note == noteSequence[position]) {
    playNoteAndAdvanceSequence();
  } else {
    GameWin = false;
    GameOver = true;
    Serial.write(position);
  }
}
