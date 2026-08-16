#define MicAO 8
const int CLAP_GAP_MIN = 50;      // min. interval between claps, ms
const int CLAP_WINDOW = 400;      // window for detecting 2 claps, ms
const int STEP_DELAY = 2;         // delay between motor steps, ms
// Motor
const int PINS[] = {2, 3, 4, 5};
const bool STEPS[8][4] = {
  {HIGH, LOW,  LOW,  LOW},
  {HIGH, HIGH, LOW,  LOW},
  {LOW,  HIGH, LOW,  LOW},
  {LOW,  HIGH, HIGH, LOW},
  {LOW,  LOW,  HIGH, LOW},
  {LOW,  LOW,  HIGH, HIGH},
  {LOW,  LOW,  LOW,  HIGH},
  {HIGH, LOW,  LOW,  HIGH},
};
int currentStep = 0;
long lastStepTime = 0;

// Хлопок
int clap = 0;
long detection_range_start = 0;
long detection_range = 0;
boolean status_lights = false;
//LED
const int BLED = 11;
const int GLED = 10;
const int RLED = 9;


void setup() {
  pinMode(MicAO, INPUT);
  for (int i = 0; i < 4; i++)
    pinMode(PINS[i], OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
}

void loop() {
  long now = millis();

  // Motor detector
  int status_MicAO = digitalRead(MicAO);
  if (status_MicAO == 0) {
    if (clap == 0) {
      detection_range_start = detection_range = now;
      clap++;
    } else if (clap > 0 && now - detection_range >= CLAP_GAP_MIN) {
      detection_range = now;
      clap++;
    }
  }

  if (now - detection_range_start >= CLAP_WINDOW) {
    if (clap == 2)
      status_lights = !status_lights;
    clap = 0;
  }

  //Motor
  if (status_lights && now - lastStepTime >= STEP_DELAY) {
    for (int pin = 0; pin < 4; pin++)
      digitalWrite(PINS[pin], STEPS[currentStep][pin]);
    currentStep = (currentStep + 1) % 8;
    lastStepTime = now;

  }
  //LED system to show working proccess
  if(status_lights == false){
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  }  
  if(status_lights == true){
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, LOW);
  }
}