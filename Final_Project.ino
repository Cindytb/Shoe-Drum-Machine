// Buttons
int clockPin = 13;
int dataPin = 11;
String datavalue = "S";

// Switches
int switch1 = 12;

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
int HH = 42;
int Ride = 51;
int Pedal = 44;
int OHH = 46;
int Side = 37;

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
  pinMode(clockPin, OUTPUT); // These three are used for the keypad
  pinMode(dataPin, INPUT);
  digitalWrite(clockPin, LOW);

  pinMode(LedPin, OUTPUT); // LEDs
  pinMode(LedPin2, OUTPUT);
  pinMode(LedPin3, OUTPUT);
  pinMode(LedPin4, OUTPUT);
  pinMode(switch1, INPUT);
  Serial.begin(9600);
}

void loop() {
  continuousControls(); // contains manual drum controls, read button controls, and fills
  suspendedCymbal(); // suspended cymbal roll; cannot be played at the same time as the presets
  TempoTap(); // tap tempo function
  PlayOne(); // all of the Play functions are the presets
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
}

void PlayOne() { // basic rock beat
  if (datavalue == "S1011111111111111" && DrumOneStatus == "off") { //reads the keypad and checks the status of the trigger
    DrumOneStatus = "turning on";
  }
  if (datavalue != "S1011111111111111" && DrumOneStatus == "turning on") { // this is so the preset plays after the button is released
    DrumOneStatus = "on";
    countOff(); // counts off in blinking lights if the switch is on
  }
  while (DrumOneStatus == "on") { // "while" loops this entire thing exclusively
    if (datavalue == "S1011111111111111") {
      DrumOneStatus = "off";
    }
    for (int i = 0; i < 8; i++) {
      tempoMod(); // function to change the tempo
      if (analogRead(8) > 0 ) { //analogRead(8) is exclusively for tempo modulation
        Step = modMetro / 2; //changes the tempo
      }
      else {
        Step = Metron / 2; // or keeps it according to the already stated tempo
      }
      presetOne(noteArrayOne[i]); // chooses the specific combination of drums in the sequence
      continuousControls(); // since it's a while loop, it still needs to be able to read the buttons and manual settings
      delay(Step);
      STOP(); // turns off the preset (and all presets)
    }
  }
}

void PlayTwo() { //same exact format as PlayOne, varied rock beat
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


void PlayThree() { //jazz time
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

void PlayFour() { // R & B type beat
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

void PlayFive() { // bossa nova
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

void PlaySix() { // samba
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

void PlaySeven() { // drumbeat to Kryptonite by Three Doors Down
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

void PlayEight() { // drumbeat to Sound of Madness by Shinedown
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

void PlayNine() { // hip hop / pop beat
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

void PlayTen() { // afro-cuban drumming tumabu and hi hat
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

void PlayEleven() { // funk
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

void randomEighth() { //this is the random fill generator on the 8th note subdivision level
  if (datavalue == "S1111111111110111") {
    Step = Metron / 2;
    for (int i = 0; i < 8; i++) {
      usbMIDI.sendNoteOn(randNoteArray[random(20)], random(70, 128), 1); //the 20 digit array is made up of drum midi notes
      usbMIDI.sendNoteOn(randNoteArray[random(20)], random(70, 128), 1);
      usbMIDI.sendNoteOn(randNoteArray[random(20)], random(70, 128), 1);
      delay(Step);
    }
  }
}

void randomTriplet() { // triplet subdivision level as noted by...
  if (datavalue == "S1111111111111011") {
    Step = Metron / 3; // this
    for (int i = 0; i < 12; i++) {
      usbMIDI.sendNoteOn(randNoteArray[random(20)], random(70, 128), 1);
      usbMIDI.sendNoteOn(randNoteArray[random(20)], random(70, 128), 1);
      usbMIDI.sendNoteOn(randNoteArray[random(20)], random(70, 128), 1);
      delay(Step);
    }
  }
}

void randomSixteenth() { // and the 16th note subdivision level
  if (datavalue == "S1111111111111101") {
    Step = Metron / 4;
    for (int i = 0; i < 16; i++) {
      usbMIDI.sendNoteOn(randNoteArray[random(20)], random(70, 128), 1);
      usbMIDI.sendNoteOn(randNoteArray[random(20)], random(70, 128), 1);
      usbMIDI.sendNoteOn(randNoteArray[random(20)], random(70, 128), 1);
      delay(Step);
    }
  }
}

void presetOne(int note) { //this defines what each note in the array does, presetOne is a standard rock beat
  if (note == 1) {
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1); // BD = Bass drum
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1); // HH = Hi hat (closed)
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
  }
  if (note == 3) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(SD, ReadVelocitySnare, 1); // SD = Snare drum
  }
}

void presetTwo(int note) { // variation on a rock beat
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

void presetThree(int note) { //jazz time
  if (note == 1) {
    usbMIDI.sendNoteOn(Ride, ReadVelocityRide, 1); //Ride cymbal
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(Pedal, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(Ride, ReadVelocityRide, 1);
  }
}

void presetFour(int note) { // R & B beat
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

void presetFive(int note) { //bossa nova
  if (note == 1) {
    usbMIDI.sendNoteOn(HH, ReadVelocityHH, 1);
    usbMIDI.sendNoteOn(Side, ReadVelocitySnare, 1); //Rim clicks emulating claves for latin beats
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



void presetSix(int note) { //samba
  if (note == 1) {
    usbMIDI.sendNoteOn(Ride, ReadVelocityRide, 1);
    usbMIDI.sendNoteOn(Side, ReadVelocitySnare, 1);
    usbMIDI.sendNoteOn(BD, ReadVelocityBass, 1);
  }
  if (note == 2) {
    usbMIDI.sendNoteOn(Ride, ReadVelocityRide, 1);
  }
  if (note == 3) {
    if (ReadVelocityRide < 107) { //sambas accent specific notes, and this creates the accent by adding 20 to the velocity unless the velocity is already 127
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
    readVelocities(); // then it resets the velocity back to normal
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

void presetSeven(int note) { //rock drumbeat of Kryptonite by Three Doors Down
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

void presetEight(int note) { //thick, heavy rock drumbeat of Sound of Madness by Shinedown
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

void presetNine(int note) { // hip hop or pop beat
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

void presetTen(int note) { // tumabu and hi hat pattern of afro-cuban drumming
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

void presetEleven(int note) { // funk beat
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
void TempoTap() { // tap tempo function
  if (datavalue == "S0111111111111111" && tempohit == "zero") { // datavalue == "S0111111111111111" means keep pressing button 1!
    tempohit = "zeroand";
    StartTempo = millis(); // start the timer
    digitalWrite(LedPin, HIGH); // turn on the first LED
  }
  if (datavalue != "S0111111111111111" && tempohit == "zeroand") { // this is when the button is released
    tempohit = "one";
  }
  if (datavalue == "S0111111111111111" && tempohit == "one") { // when the button is pressed again
    tempohit = "oneand";
    TempoTimerTwo = millis() - StartTempo; // this is the difference between 1st button press and 2nd
    digitalWrite(LedPin2, HIGH); // turn on the second LED
  }
  if (datavalue != "S0111111111111111" && tempohit == "oneand") { // when the button is released
    tempohit = "two";
  }
  if (datavalue == "S0111111111111111" && tempohit == "two") {
    tempohit = "twoand";
    TempoTimerThree = millis() - StartTempo - TempoTimerTwo; // difference between 2nd button press and 3rd
    digitalWrite(LedPin3, HIGH); // turn on third LED
  }
  if (datavalue != "S0111111111111111" && tempohit == "twoand") { // etc
    tempohit = "three";
  }
  if (datavalue == "S0111111111111111" && tempohit == "three") {
    tempohit = "threeand";
    TempoTimerFour = millis() - StartTempo - TempoTimerThree - TempoTimerTwo;
    digitalWrite(LedPin4, HIGH);
  }
  if (datavalue != "S0111111111111111" && tempohit == "threeand") {
    tempohit = "zero"; // restart the entire process

    Metron = (TempoTimerTwo + TempoTimerThree + TempoTimerFour) / 3 ; // find average of the three
    digitalWrite(LedPin, LOW); // turn off all the LEDs
    digitalWrite(LedPin2, LOW);
    digitalWrite(LedPin3, LOW);
    digitalWrite(LedPin4, LOW);
  }
}

void readVelocities() { // these control the velocities for the presets
  ReadVelocitySnare = map(analogRead(3), 0, 1023, 1, 127);
  ReadVelocityBass = map(analogRead(4), 0, 1023, 1, 127);
  ReadVelocityRide = map(analogRead(5), 0, 1023, 1, 127);
  ReadVelocityPedal = map(analogRead(6), 0, 1023, 1, 127);
  ReadVelocityHH = map(analogRead(7), 0, 1023, 1, 127);
}

void countOff() { // turns on the LED for an 8th note, turns it off for an 8th note, and repeat 4x
  if (digitalRead(switch1) == HIGH) {
    digitalWrite(LedPin, HIGH);
    delay(Metron / 2);
    digitalWrite(LedPin, LOW);
    delay(Metron / 2);
    digitalWrite(LedPin, HIGH);
    delay(Metron / 2);
    digitalWrite(LedPin, LOW);
    delay(Metron / 2);
    digitalWrite(LedPin, HIGH);
    delay(Metron / 2);
    digitalWrite(LedPin, LOW);
    delay(Metron / 2);
    digitalWrite(LedPin, HIGH);
    delay(Metron / 2);
    digitalWrite(LedPin, LOW);
    delay(Metron / 2);
  }
}

void continuousControls() { // functionception where I put functions inside of a function to make things shorter
  ManualDrums();
  readButtons();
  readVelocities();
  randomEighth();
  randomTriplet();
  randomSixteenth();
}

void ManualDrums() {
  SDOne = analogRead(0);
  BDOne = analogRead(1);
  BDTwo = analogRead(2);

  if (BDOne > 500 && statushitBDOne == "off") { // if the button is pressed hard enough, it will turn on a trigger
    scaledVelocity = map(BDOne, 600, 900, 70, 127); // maps the velocity so the harder I hit, the louder it'll be
    constrain(scaledVelocity, 0, 127); // makes sure the velocity doesn't go above 127
    usbMIDI.sendNoteOn(BD, scaledVelocity, 1); // sends the note with the scaledVelocity
    statushitBDOne = "on"; // turns on the trigger and won't play a note again until it's turned off
  }
  if (BDOne < 400 && statushitBDOne == "on") { // waits until my heel is released from the pressure sensor so it
    usbMIDI.sendNoteOff(BD, 0, 1); // it turns the note off
    statushitBDOne = "off"; // and resets the trigger
  }
  if (BDTwo > 600 && statushitBDTwo == "off") { // does the same exact thing, but this is for my right foot so it's callibrated differently
    scaledVelocity2 = map(BDTwo, 600, 900, 70, 127);
    constrain(scaledVelocity2, 0, 127);
    usbMIDI.sendNoteOn(BD, scaledVelocity2, 1);
    statushitBDTwo = "on";
  }
  if (BDTwo < 450 && statushitBDTwo == "on") {
    usbMIDI.sendNoteOff(BD, 0, 1);
    statushitBDTwo = "off";

  }
  if (SDOne > 500 && statushitSDOne == "off") { //same process except with the ball of my left foot
    scaledVelocity3 = map(SDOne, 600, 900, 70, 127);
    constrain(scaledVelocity3, 0, 127);
    usbMIDI.sendNoteOn(SD, scaledVelocity3, 1);
    statushitSDOne = "on";
  }
  if (SDOne < 200 && statushitSDOne == "on") {
    usbMIDI.sendNoteOff(SD, 0, 1);
    statushitSDOne = "off";
  }
}

void readButtons() { //continually reads the values coming from the keypad
  datavalue = "S";
  for (int button = 0; button < 16; button++) {
    digitalWrite(clockPin, LOW);
    int databit = digitalRead(dataPin);
    digitalWrite(clockPin, HIGH);
    datavalue.concat(databit);
  }
}

void tempoMod() { // modifies the tempo
  if ((analogRead(8)) > 0) { // if the pot is above 0, it will take effect
    modMetro = map(analogRead(8), 1, 1023, Metron, 100);
  }
}
void suspendedCymbal() {
  number = analogRead(9);
  CymbVelocity = map(number, 0, 1000, 50, 124); // maps the velocity to the potentiometer value
  if (number == 0) {
    CymbVelocity = 0;
  }
  if (number == 0 && number < 250 && CymbStatus == "start") { // each if loop divides the potentiometer range into 4 chunks
    usbMIDI.sendNoteOn(Cymb, CymbVelocity, 1); //sends a note-on every 250 milliseconds, or a an 8th note at 120 bpm to emulate a roll
    delay(250);
  }
  if (number > 250 && number < 500 && CymbStatus == "start") {
    usbMIDI.sendNoteOn(Cymb, CymbVelocity, 1); // makes the roll strokes go faster with each chunk
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
  if (number > 1010 && CymbStatus == "start") { // when the number reaches above 1010 (not 1023 to makeup for human/analog inaccuracies)
    CymbVelocity = 127; // it sends a crash at 127 velocity
    usbMIDI.sendNoteOn(Cymb, CymbVelocity, 1);
    CymbStatus = "end"; //and stops the notes from getting triggered
  }
  if (number == 0 && CymbStatus == "end") { // until the potentiometer is reset to 0
    CymbVelocity = 0;
    CymbStatus = "start"; // then the entire process starts again
    usbMIDI.sendNoteOff(Cymb, 0, 1);
  }
}

void STOP() {
  if (datavalue == "S1111111111111110") { // if the keypad reads 16, it turns all drum statuses off
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
