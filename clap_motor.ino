#define MicAO 8

// Мотор
const int PINS[] = {2, 3, 4, 5};
const int dl = 2;
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

  // --- Детектор хлопка ---
  int status_MicAO = digitalRead(MicAO);
  if (status_MicAO == 0) {
    if (clap == 0) {
      detection_range_start = detection_range = now;
      clap++;
    } else if (clap > 0 && now - detection_range >= 50) {
      detection_range = now;
      clap++;
    }
  }

  if (now - detection_range_start >= 400) {
    if (clap == 2)
      status_lights = !status_lights;
    clap = 0;
  }

  // --- Мотор ---
  if (status_lights && now - lastStepTime >= dl) {
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