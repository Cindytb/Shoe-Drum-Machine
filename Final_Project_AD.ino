// Buttons
int clockPin = 13;
int dataPin = 11;
String datavalue = "S";

// Switches
int switch1 = 12;
String switchStatus = "off";

// Lights
int LedPin = 3;
int LedPin2 = 2;
int LedPin3 = 1;
int LedPin4 = 0;

//Manual Drum Controls
int BDOne = 0;
int scaledVelocity = 0;
String statushitBDOne = "off";
int BDTwo = 0;
int scaledVelocity2 = 0;
String statushitBDTwo = "off";
int SDOne = 0;
int scaledVelocity3 = 0;
String statushitSDOne = "off";

//Metronome counter
int Metron = 500;
int Step = 250;
String tempohit = "zero";
unsigned long StartTempo = 0;
unsigned long TempoTimer = 0;
unsigned long TempoTimerTwo = 0;
unsigned long TempoTimerThree = 0;
unsigned long TempoTimerFour = 0;
unsigned long OneTwo;
int modMetro = 500;

//Universal Controls
int ReadVelocitySnare = 100;
int ReadVelocityBass = 100;
int ReadVelocityRide = 100;
int ReadVelocityPedal = 100;
int ReadVelocityHH = 100;
int BD = 36;
int SD = 38;
int HH = 49;
int Ride = 60;
int Pedal = 48;
int OHH = 54;
int Side = 44;

//Cymbal stuff
String CymbStatus = "start";
int CymbVelocity = 0;
int Cymb = 57;
int number = 0;

//Preset One
String DrumOneStatus = "off";
int noteArrayOne[] = {1, 2, 3, 1, 1, 2, 3, 2};

//Preset Two
String DrumTwoStatus = "off";
int noteArrayTwo[] = {1, 0, 2, 0, 3, 0, 2, 4, 2, 0, 1, 0, 3, 0, 2, 0};

//Preset Three
String DrumThreeStatus = "off";
int noteArrayThree[] = {1, 0, 0, 2, 0, 1, 1, 0, 0, 2, 0, 1};

//Preset Four
String DrumFourStatus = "off";
int noteArrayFour[] = {1, 2, 2, 2, 3, 2, 2, 1, 1, 2, 1, 2, 3, 2, 2, 2};

//Preset Five
String DrumFiveStatus = "off";
int noteArrayFive[] = {1, 2, 2, 1, 3, 2, 4, 3, 3, 2, 4, 3, 3, 4, 2, 3};

//Preset Six
String DrumSixStatus = "off";
int noteArraySix[] =  {1, 2, 3, 4, 4, 5, 6, 1, 4, 5, 6, 1, 1, 5, 3, 4};

//Preset Seven
String DrumSevenStatus = "off";
int noteArraySeven[] = {1, 0, 2, 0, 3, 4, 2, 0, 1, 0, 2, 0, 3, 4, 2, 0, };

//Preset Eight
String DrumEightStatus = "off";
int noteArrayEight[] = {1, 2, 3, 2, 4, 2, 3, 0};

//Preset Nine
String DrumNineStatus = "off";
int noteArrayNine[] = {1, 2, 3, 2, 1, 2, 3, 2};

//Preset Ten
String DrumTenStatus = "off";
int noteArrayTen[] = {0, 0, 1, 2, 0, 0, 3, 0};

//Preset Eleven
String DrumElevenStatus = "off";
int noteArrayEleven[] = {1, 0, 2, 0, 3, 0, 4, 5, 1, 0, 1, 0, 4, 6, 3, 0, 4, 5, 1, 0, 3, 0, 4, 5, 1, 0, 1, 0, 3, 5, 4, 5};

//Random Fill Generator
int randNoteArray[] = {36, 38, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 0, 0, 0, 0, 0, 0};

void setup() {
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);
  digitalWrite(clockPin, LOW);

  pinMode(LedPin, OUTPUT);
  pinMode(LedPin2, OUTPUT);
  pinMode(LedPin3, OUTPUT);
  pinMode(LedPin4, OUTPUT);

  pinMode(switch1, INPUT);

  Serial.begin(9600);
}

void loop() {
  continuousControls();
  suspendedCymbal();
  TempoTap();
  PlayOne();
  PlayTwo();
  PlayThree();
  PlayFour();
  PlayFive();
  PlaySix();
  PlaySeven();
  PlayEight();
  PlayNine();
  PlayTen();
  PlayEleven();
  Serial.println(ReadVelocitySnare);
}

void PlayOne() {
  if (datavalue == "S1011111111111111" && DrumOneStatus == "off") {
    DrumOneStatus = "turning on";
  }
  if (datavalue != "S1011111111111111" && DrumOneStatus == "turning on") {
    DrumOneStatus = "on";
    countOff();
  }
  while (DrumOneStatus == "on") {
    if (datavalue == "S1011111111111111") {
      DrumOneStatus = "off";
    }
    for (int i = 0; i < 8; i++) {
      tempoMod();
      if (analogRead(8) > 0 ) {
        Step = modMetro / 2;
      }
      else {
        Step = Metron / 2;
      }
      presetOne(noteArrayOne[i]);
      continuousControls();
      delay(Step);
      STOP();
    }
  }
}

void PlayTwo() {
  if (datavalue == "S1101111111111111" && DrumTwoStatus == "off") {
    DrumTwoStatus = "turning on";
  }
  if (datavalue != "S1101111111111111" && DrumTwoStatus == "turning on") {
    DrumTwoStatus = "on";
    Step = Metron / 2;
    countOff();
  }
  while (DrumTwoStatus == "on") {
    for (int i = 0; i < 16; i++) {
      tempoMod();
      if (analogRead(8) > 0 ) {
        Step = modMetro / 2;
      }
      else {
        Step = Metron / 2;
      }
      presetTwo(noteArrayTwo[i]);
      continuousControls();
      delay(Step / 2);
      STOP();
      if (datavalue == "S1101111111111111") {
        DrumTwoStatus = "off";
      }
    }
  }
}


void PlayThree() {
  if (datavalue == "S1110111111111111" && DrumThreeStatus == "off") {
    DrumThreeStatus = "turning on";
  }
  if (datavalue != "S1110111111111111" && DrumThreeStatus == "turning on") {
    DrumThreeStatus = "on";
    Step = Metron / 3;
    countOff();
  }
  while (DrumThreeStatus == "on") {
    for (int i = 0; i < 12; i++) {
      tempoMod();
      if (analogRead(8) > 0 ) {
        Step = modMetro / 3;
      }
      else {
        Step = Metron / 3;
      }
      presetThree(noteArrayThree[i]);
      continuousControls();
      Serial.println(datavalue);
      delay(Step);
      STOP();

      if (datavalue == "S1110111111111111") {
        DrumThreeStatus = "off";
      }
    }
  }
}

void PlayFour() {
  if (datavalue == "S1111011111111111" && DrumFourStatus == "off") {
    DrumFourStatus = "turning on";
  }
  if (datavalue != "S1111011111111111" && DrumFourStatus == "turning on") {
    DrumFourStatus = "on";
    Step = Metron / 2;
    countOff();
  }
  while (DrumFourStatus == "on") {
    for (int i = 0; i < 16; i++) {
      tempoMod();
      if (analogRead(8) > 0 ) {
        Step = modMetro / 2;
      }
      else {
        Step = Metron / 2;
      }
      presetFour(noteArrayFour[i]);
      continuousControls();
      delay(Step / 2);
      STOP();
      if (datavalue == "S1111011111111111") {
        DrumFourStatus = "off";
      }
    }
  }
}

void PlayFive() {
  if (datavalue == "S1111101111111111" && DrumFiveStatus == "off") {
    DrumFiveStatus = "turning on";
  }
  if (datavalue != "S11111011" && DrumFiveStatus == "turning on") {
    DrumFiveStatus = "on";
    Step = Metron / 2;
    countOff();
  }
  while (DrumFiveStatus == "on") {
    for (int i = 0; i < 16; i++) {
      tempoMod();
      if (analogRead(8) > 0 ) {
        Step = modMetro / 2;
      }
      else {
        Step = Metron / 2;
      }
      presetFive(noteArrayFive[i]);
      continuousControls();
      delay(Step);
      STOP();
      if (datavalue == "S1111101111111111") {
        DrumFiveStatus = "off";
      }
    }
  }
}

void PlaySix() {
  if (datavalue == "S1111110111111111" && DrumSixStatus == "off") {
    DrumSixStatus = "turning on";
  }
  if (datavalue != "S1111110111111111" && DrumSixStatus == "turning on") {
    DrumSixStatus = "on";
    Step = Metron / 2;
    countOff();
  }
  while (DrumSixStatus == "on") {
    for (int i = 0; i < 8; i++) {
      tempoMod();
      if (analogRead(8) > 0 ) {
        Step = modMetro / 2;
      }
      else {
        Step = Metron / 2;
      }
      presetSix(noteArraySix[i]);
      continuousControls();
      delay(Step);
      STOP();
      if (datavalue == "S1111110111111111") {
        DrumSixStatus = "off";
      }
    }
  }
}

void PlaySeven() {
  if (datavalue == "S1111111011111111" && DrumSevenStatus == "off") {
    DrumSevenStatus = "turning on";
  }
  if (datavalue != "S1111111011111111" && DrumSevenStatus == "turning on") {
    DrumSevenStatus = "on";
    Step = Metron / 4;
    countOff();
  }
  while (DrumSevenStatus == "on") {
    for (int i = 0; i < 16; i++) {
      tempoMod();
      if (analogRead(8) > 0 ) {
        Step = modMetro / 4;
      }
      else {
        Step = Metron / 4;
      }
      presetSeven(noteArraySeven[i]);
      continuousControls();
      delay(Step);
      STOP();

      if (datavalue == "S1111111011111111") {
        DrumSevenStatus = "off";
      }
    }
  }
}

void PlayEight() {
  if (datavalue == "S1111111101111111" && DrumEightStatus == "off") {
    DrumEightStatus = "turning on";
  }
  if (datavalue != "S1111111101111111" && DrumEightStatus == "turning on") {
    DrumEightStatus = "on";
    Step = Metron / 2;
    countOff();
  }
  while (DrumEightStatus == "on") {
    for (int i = 0; i < 8; i++) {
      tempoMod();
      if (analogRead(8) > 0 ) {
        Step = modMetro / 2;
      }
      else {
        Step = Metron / 2;
      }
      presetEight(noteArrayEight[i]);
      continuousControls();
      delay(Step);
      STOP();
      if (datavalue == "S1111111101111111") {
        DrumEightStatus = "off";
      }
    }
  }
}

void PlayNine() {
  if (datavalue == "S1111111110111111" && DrumNineStatus == "off") {
    DrumNineStatus = "turning on";
  }
  if (datavalue != "S1111111110111111" && DrumNineStatus == "turning on") {
    DrumNineStatus = "on";
    Step = Metron / 2;
    countOff();
  }
  while (DrumNineStatus == "on") {
    for (int i = 0; i < 8; i++) {
      tempoMod();
      if (analogRead(8) > 0 ) {
        Step = modMetro / 2;
      }
      else {
        Step = Metron / 2;
      }
      presetNine(noteArrayNine[i]);
      continuousControls();
      delay(Step);
      STOP();
      if (datavalue == "S1111111110111111") {
        DrumNineStatus = "off";
      }
    }
  }
}

void PlayTen() {
  if (datavalue == "S1111111111011111" && DrumTenStatus == "off") {
    DrumTenStatus = "turning on";
  }
  if (datavalue != "S1111111111011111" && DrumTenStatus == "turning on") {
    DrumTenStatus = "on";
    Step = Metron / 2;
    countOff();
  }
  while (DrumTenStatus == "on") {
    for (int i = 0; i < 8; i++) {
      tempoMod();
      if (analogRead(8) > 0 ) {
        Step = modMetro / 2;
      }
      else {
        Step = Metron / 2;
      }
      presetTen(noteArrayTen[i]);
      continuousControls();
      delay(Step);
      STOP();
      if (datavalue == "S1111111111011111") {
        DrumTenStatus = "off";
      }
    }
  }
}

void PlayEleven() {
  if (datavalue == "S1111111111101111" && DrumElevenStatus == "off") {
    DrumElevenStatus = "turning on";
  }
  if (datavalue != "S1111111111101111" && DrumElevenStatus == "turning on") {
    DrumElevenStatus = "on";
    Step = Metron / 4;
    countOff();
  }
  while (DrumElevenStatus == "on") {
    for (int i = 0; i < 32; i++) {
      tempoMod();
      if (analogRead(8) > 0 ) {
        Step = modMetro / 4;
      }
      else {
        Step = Metron / 4;
      }
      presetEleven(noteArrayEleven[i]);
      continuousControls();
      delay(Step);
      STOP();
      if (datavalue == "S1111111111101111") {
        DrumElevenStatus = "off";
      }
    }
  }
}

void randomEighth() {
  if (datavalue == "S1111111111110111") {
    Step = Metron / 2;
    for (int i = 0; i < 8; i++) {
      usbMIDI.sendNoteOn(randNoteArray[random(18)], random(70, 128), 1);
      usbMIDI.sendNoteOn(randNoteArray[random(18)], random(70, 128), 1);
      usbMIDI.sendNoteOn(randNoteArray[random(18)], random(70, 128), 1);
      delay(Step);
    }
  }
}

void randomTriplet() {
  if (datavalue == "S1111111111111011") {
    Step = Metron / 3;
    for (int i = 0; i < 12; i++) {
      usbMIDI.sendNoteOn(randNoteArray[random(18)], random(70, 128), 1);
      usbMIDI.sendNoteOn(randNoteArray[random(18)], random(70, 128), 1);
      usbMIDI.sendNoteOn(randNoteArray[random(18)], random(70, 128), 1);
      delay(Step);
    }
  }
}

void randomSixteenth() {
  if (datavalue == "S1111111111111101") {
    Step = Metron / 4;
    for (int i = 0; i < 16; i++) {
      usbMIDI.sendNoteOn(randNoteArray[random(18)], random(70, 128), 1);
      usbMIDI.sendNoteOn(randNoteArray[random(18)], random(70, 128), 1);
      usbMIDI.sendNoteOn(randNoteArray[random(18)], random(70, 128), 1);
      delay(Step);
    }
  }
}

void presetOne(int note) {
  if (note == 1) {
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 3) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(SD, ReadVelocitySnare, 1);
  }
}

void presetTwo(int note) {
  if (note == 1) {
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 3) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(SD, ReadVelocitySnare, 1);
  }
  if (note == 4) {
    usbMIDI.sendNoteOn(SD, ReadVelocitySnare, 1);
  }
}

void presetThree(int note) {
  if (note == 1) {
    usbMIDI.sendNoteOn(Ride, ReadVelocityRide, 1);
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(Ride, ReadVelocityRide, 1);
  }
}

void presetFour(int note) {
  if (note == 1) {
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 3) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(SD, ReadVelocitySnare, 1);
  }
}

void presetFive(int note) {
  if (note == 1) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(Side, ReadVelocitySnare, 1);
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 3) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
  }
  if (note == 4) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(Side, ReadVelocitySnare, 1);
  }
}



void presetSix(int note) {
  if (note == 1) {
    usbMIDI.sendNoteOn(Ride, ReadVelocityRide, 1);
    usbMIDI.sendNoteOn(Side, ReadVelocitySnare, 1);
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(Ride, ReadVelocityRide, 1);
  }
  if (note == 3) {
    if (ReadVelocityRide < 107) {
      ReadVelocityRide = ReadVelocityRide + 20;
    }
    else {
      ReadVelocityRide = 127;
    }
    if (ReadVelocitySnare < 107) {
      ReadVelocitySnare = ReadVelocitySnare + 20;
    }
    else {
      ReadVelocitySnare = 127;
    }
    usbMIDI.sendNoteOn(Ride, ReadVelocityRide, 1);
    usbMIDI.sendNoteOn(Side, ReadVelocitySnare, 1);
    readVelocities();
  }
  if (note == 4) {
    usbMIDI.sendNoteOn(Ride, ReadVelocityRide, 1);
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
  }
  if (note == 5) {
    usbMIDI.sendNoteOn(Ride, ReadVelocityRide, 1);
    usbMIDI.sendNoteOn(Side, ReadVelocitySnare, 1);
  }
  if (note == 6) {
    if (ReadVelocityRide < 107) {
      ReadVelocityRide = ReadVelocityRide + 20;
    }
    else {
      ReadVelocityRide = 127;
    }
    usbMIDI.sendNoteOn(Ride, ReadVelocityRide, 1);
    readVelocities();
  }

}

void presetSeven(int note) {
  if (note == 1) {
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(SD, ReadVelocitySnare, 1);
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 3) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 4) {
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
  }
}

void presetEight(int note) {
  if (note == 1) {
    usbMIDI.sendNoteOn(OHH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 3) {
    usbMIDI.sendNoteOn(OHH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(SD, ReadVelocitySnare, 1);
  }
  if (note == 4) {
    usbMIDI.sendNoteOn(OHH, ReadVelocityHH, 1);
  }
}

void presetNine(int note) {
  if (note == 1) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(OHH, ReadVelocityHH, 1);
  }
  if (note == 3) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(SD, ReadVelocitySnare, 1);
  }
}

void presetTen(int note) {
  if (note == 1) {
    usbMIDI.sendNoteOn(OHH, ReadVelocityHH, 1);
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
  }
  if (note == 3) {
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
    usbMIDI.sendNoteOn(OHH, ReadVelocityHH, 1);
  }
}

void presetEleven(int note) {
  if (note == 1) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(OHH, ReadVelocityHH, 1);
  }
  if (note == 3) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(SD, ReadVelocitySnare, 1);
  }
  if (note == 4) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 5) {
    usbMIDI.sendNoteOn(SD, ReadVelocitySnare, 1);
  }
  if (note == 6) {
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
  }
}
void TempoTap() {
  if (datavalue == "S0111111111111111" && tempohit == "zero") {
    tempohit = "zeroand";
    StartTempo = millis();
    TempoTimer = millis() - StartTempo;
    digitalWrite(LedPin, HIGH);
  }
  if (datavalue != "S0111111111111111" && tempohit == "zeroand") {
    tempohit = "one";
  }
  if (datavalue == "S0111111111111111" && tempohit == "one") {
    tempohit = "oneand";
    TempoTimerTwo = millis() - StartTempo;
    digitalWrite(LedPin2, HIGH);
  }
  if (datavalue != "S0111111111111111" && tempohit == "oneand") {
    tempohit = "two";
  }
  if (datavalue == "S0111111111111111" && tempohit == "two") {
    tempohit = "twoand";
    TempoTimerThree = millis() - StartTempo - TempoTimerTwo;
    digitalWrite(LedPin3, HIGH);
  }
  if (datavalue != "S0111111111111111" && tempohit == "twoand") {
    tempohit = "three";
  }
  if (datavalue == "S0111111111111111" && tempohit == "three") {
    tempohit = "threeand";
    TempoTimerFour = millis() - StartTempo - TempoTimerThree - TempoTimerTwo;
    digitalWrite(LedPin4, HIGH);
  }
  if (datavalue != "S0111111111111111" && tempohit == "threeand") {
    tempohit = "zero";

    Metron = (TempoTimerTwo + TempoTimerThree + TempoTimerFour) / 3 ;
    digitalWrite(LedPin, LOW);
    digitalWrite(LedPin2, LOW);
    digitalWrite(LedPin3, LOW);
    digitalWrite(LedPin4, LOW);
  }
}

void readVelocities() {
  ReadVelocitySnare = map(analogRead(3), 0, 1023, 1, 127);
  ReadVelocityBass = map(analogRead(4), 0, 1023, 1, 127);
  ReadVelocityRide = map(analogRead(5), 0, 1023, 1, 127);
  ReadVelocityPedal = map(analogRead(6), 0, 1023, 1, 127);
  ReadVelocityHH = map(analogRead(7), 0, 1023, 1, 127);
}
void countOff() {
  if (digitalRead(switch1) == HIGH && switchStatus == "off") {
    switchStatus = "on";
    digitalWrite(LedPin, HIGH);
    delay(Step);
    digitalWrite(LedPin, LOW);
    delay(Step);
    digitalWrite(LedPin, HIGH);
    delay(Step);
    digitalWrite(LedPin, LOW);
    delay(Step);
    digitalWrite(LedPin, HIGH);
    delay(Step);
    digitalWrite(LedPin, LOW);
    delay(Step);
    digitalWrite(LedPin, HIGH);
    delay(Step);
    digitalWrite(LedPin, LOW);
    delay(Step);
  }
  if (digitalRead(switch1) == LOW & switchStatus == "on") {
    switchStatus = "off";
  }
}

void continuousControls() {
  ManualDrums();
  readButtons();
  randomEighth();
  randomTriplet();
  randomSixteenth();
  readVelocities();
}

void ManualDrums() {
  SDOne = analogRead(0);
  BDOne = analogRead(1);
  BDTwo = analogRead(2);

  if (BDOne > 500 && statushitBDOne == "off") {
    scaledVelocity = map(BDOne, 600, 900, 70, 127);
    constrain(scaledVelocity, 0, 127);
    usbMIDI.sendNoteOn(BD, scaledVelocity, 1);
    statushitBDOne = "on";
    Serial.print(BDOne);
    Serial.print("     ");
    Serial.print(SDOne);
    Serial.print("     ");
    Serial.println(BDTwo);
  }
  if (BDOne < 400 && statushitBDOne == "on") {
    usbMIDI.sendNoteOff(BD, 0, 1);
    statushitBDOne = "off";
  }
  if (BDTwo > 600 && statushitBDTwo == "off") {
    scaledVelocity2 = map(BDTwo, 600, 900, 70, 127);
    constrain(scaledVelocity2, 0, 127);
    usbMIDI.sendNoteOn(BD, scaledVelocity2, 1);
    statushitBDTwo = "on";
    Serial.print(BDOne);
    Serial.print("     ");
    Serial.print(SDOne);
    Serial.print("     ");
    Serial.println(BDTwo);
  }
  if (BDTwo < 450 && statushitBDTwo == "on") {
    usbMIDI.sendNoteOff(BD, 0, 1);
    statushitBDTwo = "off";

  }
  if (SDOne > 500 && statushitSDOne == "off") {
    scaledVelocity3 = map(SDOne, 600, 900, 70, 127);
    constrain(scaledVelocity3, 0, 127);
    usbMIDI.sendNoteOn(SD, scaledVelocity3, 1);
    statushitSDOne = "on";
    Serial.print(BDOne);
    Serial.print("     ");
    Serial.print(SDOne);
    Serial.print("     ");
    Serial.println(BDTwo);
  }
  if (SDOne < 200 && statushitSDOne == "on") {
    usbMIDI.sendNoteOff(SD, 0, 1);
    statushitSDOne = "off";
  }
}

void readButtons() {
  datavalue = "S";
  for (int button = 0; button < 16; button++) {
    digitalWrite(clockPin, LOW);
    int databit = digitalRead(dataPin);
    digitalWrite(clockPin, HIGH);
    datavalue.concat(databit);
  }
}

void tempoMod() {
  if ((analogRead(8)) > 0) {
    modMetro = map(analogRead(8), 1, 1023, Metron, 100);

  }
}
void suspendedCymbal() {
  number = analogRead(9);
  CymbVelocity = map(number, 0, 1000, 50, 124);
  if (number == 0) {
    CymbVelocity = 0;
  }
  if (number == 0 && number < 250 && CymbStatus == "start") {
    usbMIDI.sendNoteOn(Cymb, CymbVelocity, 1);
    delay(250);
  }
  if (number > 250 && number < 500 && CymbStatus == "start") {
    usbMIDI.sendNoteOn(Cymb, CymbVelocity, 1);
    delay(125);
  }
  if (number > 500 && number < 750 && CymbStatus == "start") {
    usbMIDI.sendNoteOn(Cymb, CymbVelocity, 1);
    delay(62);
  }
  if (number > 750 && number < 1010 && CymbStatus == "start") {
    usbMIDI.sendNoteOn(Cymb, CymbVelocity, 1);
    delay(50);
  }
  if (number > 1010 && CymbStatus == "start") {
    CymbVelocity = 127;
    usbMIDI.sendNoteOn(Cymb, CymbVelocity, 1);
    CymbStatus = "end";
  }
  if (number == 0 && CymbStatus == "end") {
    CymbVelocity = 0;
    CymbStatus = "start";
    usbMIDI.sendNoteOff(Cymb, CymbVelocity, 1);
  }
}

void STOP() {
  if (datavalue == "S1111111111111110") {
    DrumOneStatus = "off";
    DrumTwoStatus = "off";
    DrumThreeStatus = "off";
    DrumFourStatus = "off";
    DrumFiveStatus = "off";
    DrumSixStatus = "off";
    DrumSevenStatus = "off";
    DrumEightStatus = "off";
    DrumNineStatus = "off";
    DrumTenStatus = "off";
    DrumElevenStatus = "off";
  }
}

