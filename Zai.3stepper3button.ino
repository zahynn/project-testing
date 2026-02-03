#include <AccelStepper.h>

// --- DEFINISI PIN MOTOR (Sama seperti sebelum ini) ---
#define PIN_STEP_X 2
#define PIN_DIR_X 5
#define PIN_STEP_Y 3
#define PIN_DIR_Y 6
#define PIN_STEP_Z 4
#define PIN_DIR_Z 7
#define PIN_ENABLE 8 

// --- DEFINISI PIN BUTTON ---
// Kita guna pin Analog sebagai Digital (A0=14, A1=15, A2=16)
#define BUTTON_X A0
#define BUTTON_Y A1
#define BUTTON_Z A2

// --- Cipta Objek Motor ---
AccelStepper motorX(1, PIN_STEP_X, PIN_DIR_X);
AccelStepper motorY(1, PIN_STEP_Y, PIN_DIR_Y);
AccelStepper motorZ(1, PIN_STEP_Z, PIN_DIR_Z);

void setup() {
  Serial.begin(9600);

  // Setup Button (Menggunakan INPUT_PULLUP)
  // Pin akan baca HIGH bila tak ditekan, LOW bila ditekan
  pinMode(BUTTON_X, INPUT_PULLUP);
  pinMode(BUTTON_Y, INPUT_PULLUP);
  pinMode(BUTTON_Z, INPUT_PULLUP);

  // Setup Motor
  // SetMaxSpeed mestilah lebih tinggi dari setSpeed
  motorX.setMaxSpeed(1000);
  motorY.setMaxSpeed(1000);
  motorZ.setMaxSpeed(1000);

  // Enable motors
  pinMode(PIN_ENABLE, OUTPUT);
  digitalWrite(PIN_ENABLE, LOW);
}

void loop() {
  // --- LOGIK BUTAN & GERAKAN ---
  
  // PAKSI X
  if (digitalRead(BUTTON_X) == LOW) { 
    // Jika button ditekan (Logic LOW kerana pullup)
    motorX.setSpeed(500); // Motor berputar laju
  } else {
    motorX.setSpeed(0);   // Jika dilepas, berhenti
  }
  motorX.runSpeed();      // Jalankan motor mengikut kelajuan yang set

  // PAKSI Y
  if (digitalRead(BUTTON_Y) == LOW) {
    motorY.setSpeed(500);
  } else {
    motorY.setSpeed(0);
  }
  motorY.runSpeed();

  // PAKSI Z
  if (digitalRead(BUTTON_Z) == LOW) {
    motorZ.setSpeed(500);
  } else {
    motorZ.setSpeed(0);
  }
  motorZ.runSpeed();
}