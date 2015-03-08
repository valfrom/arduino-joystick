/*
 For the Arduino Leonardo, Micro or Due
 */
 
int rows[] = {
  A2,
  2,
  3,
  9,
  10,
  11
};

int cols[] = {
    A0,
    A1
};

char keys[] = {
  'w', //Up
  'd', //Right
  'p', //Start
  's', //Down
  'a', //Left
  '5', //None
  'c', //C
  'x', //X
  '1', //A
  'y', //Y
  'z', //Z
  'b', //B
};

int keyStates[] = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
};

#define COLS 2
#define ROWS 6
#define LED 13

void setup() {
  Keyboard.begin();
  
  pinMode(LED, OUTPUT);
  
  int i=0;
  for(i=0;i<COLS;i++) {
    pinMode(cols[i], INPUT_PULLUP);
  }
  
  for(i=0;i<ROWS;i++) {
    pinMode(rows[i], INPUT);
  }
}

void loop() {
  int i;
  int j;
  digitalWrite(LED, HIGH); 
  for(i=0;i<COLS;i++) {
    for(j=0;j<ROWS;j++) {
      pinMode(rows[j], OUTPUT);
      digitalWrite(rows[j], LOW);
      int sensorValue = analogRead(cols[i]);
      pinMode(rows[j], INPUT);
      int index = i*ROWS+j;
      if(sensorValue < 512) {
        keyStates[index] = 1;
      } else {
        keyStates[index] = 0;
      }
    }
  }  

  for(i=0;i<COLS*ROWS;i++) {
    char key = keys[i];
    if(keyStates[i] == 1) {
      Keyboard.press(key);
    } else {
      Keyboard.release(key);
    }
  }
  
  digitalWrite(LED, LOW); 
  
  delay(1);
}
