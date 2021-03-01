#define SPEC_TRG         A0
#define SPEC_ST          A1
#define SPEC_CLK         A2
#define SPEC_VIDEO       A3
#define WHITE_LED        A4
#define LASER_404        A5
#define BUTTON           8

#define SPEC_CHANNELS    511 // New Spec Channel
uint16_t data[SPEC_CHANNELS];

void setup(){
  pinMode(BUTTON, INPUT_PULLUP); // Set button pin to INPUT

  pinMode(SPEC_CLK, OUTPUT); // Set pins to OUTPUT
  pinMode(SPEC_ST, OUTPUT);
  pinMode(LASER_404, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);

  digitalWrite(SPEC_CLK, HIGH); // Set SPEC_CLK High
  digitalWrite(SPEC_ST, LOW); // Set SPEC_ST Low

  Serial.begin(115200); // Baud Rate set to 115200
}

void readSpectrometer(){
	// reads spectrometer data from SPEC_VIDEO (c.f. Timing Chart below)
  int delayTime = 1; // delay time

  // Start clock cycle and set start pulse to signal start
  digitalWrite(SPEC_CLK, LOW);
  delayMicroseconds(delayTime);
  digitalWrite(SPEC_CLK, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(SPEC_CLK, LOW);
  digitalWrite(SPEC_ST, HIGH);
  delayMicroseconds(delayTime);

  //Sample for a period of time
  for(int i = 0; i < 15; i++){
      digitalWrite(SPEC_CLK, HIGH);
      delayMicroseconds(delayTime);
      digitalWrite(SPEC_CLK, LOW);
      delayMicroseconds(delayTime); 
  }

  digitalWrite(SPEC_ST, LOW); // Set SPEC_ST to low

  //Sample for a period of time
  for(int i = 0; i < 85; i++){
      digitalWrite(SPEC_CLK, HIGH);
      delayMicroseconds(delayTime);
      digitalWrite(SPEC_CLK, LOW);
      delayMicroseconds(delayTime);
  }

  //One more clock pulse before the actual read
  digitalWrite(SPEC_CLK, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(SPEC_CLK, LOW);
  delayMicroseconds(delayTime);

  //Read from SPEC_VIDEO
  for(int i = 0; i < SPEC_CHANNELS; i++){
      data[i] = analogRead(SPEC_VIDEO);
      
      digitalWrite(SPEC_CLK, HIGH);
      delayMicroseconds(delayTime);
      digitalWrite(SPEC_CLK, LOW);
      delayMicroseconds(delayTime);
  }

  digitalWrite(SPEC_ST, HIGH); // Set SPEC_ST to high

  //Sample for a small amount of time
  for(int i = 0; i < 7; i++){
      digitalWrite(SPEC_CLK, HIGH);
      delayMicroseconds(delayTime);
      digitalWrite(SPEC_CLK, LOW);
      delayMicroseconds(delayTime);
  }

  digitalWrite(SPEC_CLK, HIGH);
  delayMicroseconds(delayTime);
}


void printData(){
  //prints out data to the terminal or processing plot
  for (int i = 0; i < SPEC_CHANNELS; i++){
    Serial.print(data[i]);
    Serial.print(',');
  }
  Serial.print("\n");
}

void loop(){
  if (digitalRead(BUTTON) == LOW){  // Switch ON
    readSpectrometer();
    printData();
    delay(100);
  }
  else{   // Switch OFF
  }
}
