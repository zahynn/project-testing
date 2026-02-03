#include <AccelStepper.h>

// --- DEFINISI PIN MOTOR ---
#define PIN_STEP_X 2
#define PIN_DIR_X 5
#define PIN_STEP_Y 3
#define PIN_DIR_Y 6
#define PIN_STEP_Z 4
#define PIN_DIR_Z 7
#define PIN_ENABLE 8 

// --- DEFINISI PIN LIMIT SWITCH ---
#define LIM_X_MIN 9
#define LIM_X_MAX 12
#define LIM_Y_MIN 10
#define LIM_Y_MAX 13
// Limit Z Tak Diguna

// --- OBJEK MOTOR ---
AccelStepper motorX(1, PIN_STEP_X, PIN_DIR_X);
AccelStepper motorY(1, PIN_STEP_Y, PIN_DIR_Y);
AccelStepper motorZ(1, PIN_STEP_Z, PIN_DIR_Z);

// --- KONFIGURASI STEPS PER MM (1/2 STEP) ---
const float stepsPerMM_X = 10.0; 
const float stepsPerMM_Y = 50.0; 
const float stepsPerMM_Z = 10.0; 

// --- KOORDINAT SLOT (MM) ---
float targetSlot_X = 80.0;
float targetSlot_Y = 40.0;
float targetSlot_Z = 15.0;

void setup() {
  // Setup Serial (Menerima arahan dari ESP32)
  Serial.begin(9600);

  // Setup Limits (Hanya X & Y)
  pinMode(LIM_X_MIN, INPUT_PULLUP);
  pinMode(LIM_X_MAX, INPUT_PULLUP);
  pinMode(LIM_Y_MIN, INPUT_PULLUP);
  pinMode(LIM_Y_MAX, INPUT_PULLUP);

  // Setup Motor
  motorX.setMaxSpeed(2500); motorX.setAcceleration(1000);
  motorY.setMaxSpeed(1500); motorY.setAcceleration(800);
  motorZ.setMaxSpeed(600);   motorZ.setAcceleration(300);

  // Enable motors
  pinMode(PIN_ENABLE, OUTPUT);
  digitalWrite(PIN_ENABLE, LOW);

  Serial.println("Arduino Slave Sedia. Menunggu arahan Blynk...");
}

void loop() {
  // BACA ARAHAN DARI ESP32 (SERIAL 2)
  if (Serial.available() > 0) {
    char command = Serial.read(); // Baca huruf 'S' atau 'H'

    if (command == 'S') {
      Serial.println("Menerima Blynk: Pergi ke Slot");
      gerakKeKoordinatSelamat(targetSlot_X, targetSlot_Y, targetSlot_Z);
    }
    else if (command == 'H') {
      Serial.println("Menerima Blynk: Pergi ke Home");
      gerakKeKoordinatSelamat(0, 0, 0);
    }
  }
}

// --- FUNGSI GERAKKAN DENGAN LIMIT SWITCH ---
void gerakKeKoordinatSelamat(float mmX, float mmY, float mmZ) {
  
  // 1. Tukar MM kepada Steps
  long targetStepsX = mmX * stepsPerMM_X;
  long targetStepsY = mmY * stepsPerMM_Y;
  long targetStepsZ = mmZ * stepsPerMM_Z;

  // 2. Hantar arahan
  motorX.moveTo(targetStepsX);
  motorY.moveTo(targetStepsY);
  motorZ.moveTo(targetStepsZ);

  // 3. Gelung Selagi Motor Tak Sampai
  while (motorX.distanceToGo() != 0 || motorY.distanceToGo() != 0 || motorZ.distanceToGo() != 0) {
    
    // --- KESALAMATAN PAKSI X & Y ---
    if (digitalRead(LIM_X_MAX) == LOW || digitalRead(LIM_X_MIN) == LOW) {
      motorX.stop();
    } else {
      motorX.run(); // Hanya run jika tak kena limit
    }

    if (digitalRead(LIM_Y_MAX) == LOW || digitalRead(LIM_Y_MIN) == LOW) {
      motorY.stop();
    } else {
      motorY.run();
    }

    // --- PAKSI Z: LANGSUNG RUN (TANPA LIMIT) ---
    motorZ.run();
  }
  
  Serial.println(">> SAMPAI DESTINASI");
}