#include <AccelStepper.h>

// Menentukan jenis motor interface
// InterfaceType = 1 bermaksud Driver (Step/Direction)
// CNC Shield menggunakan pin Step dan Direction yang tetap.

// Definisi Pin untuk Arduino Uno dengan CNC Shield V3
// Pin Step (Pulse)
#define PIN_STEP_X 2
#define PIN_STEP_Y 3
#define PIN_STEP_Z 4

// Pin Direction (Arah)
#define PIN_DIR_X 5
#define PIN_DIR_Y 6
#define PIN_DIR_Z 7

// Pin Enable (Opsional: Active LOW). 
// Kita boleh biarkan kosong atau sambung ke pin 8 jika mahu mematikan motor apabila idle.
#define PIN_ENABLE 8 

// Cipta objek motor (Driver interface, pin step, pin dir)
AccelStepper motorX(1, PIN_STEP_X, PIN_DIR_X);
AccelStepper motorY(1, PIN_STEP_Y, PIN_DIR_Y);
AccelStepper motorZ(1, PIN_STEP_Z, PIN_DIR_Z);

void setup() {
  Serial.begin(9600);

  // Setkan kelajuan maksimum (Speed)
  // Nilai ini perlu cuba-cuba (trial & error). 
  // Jika terlalu laju, motor akan bunyi "cik" dan tak bergerak.
  motorX.setMaxSpeed(1000); 
  motorY.setMaxSpeed(1000);
  motorZ.setMaxSpeed(1000);

  // Setkan pecutan (Acceleration)
  // Penting supaya motor tak "stuck" bila mula gerak dari keadaan diam.
  motorX.setAcceleration(500);
  motorY.setAcceleration(500);
  motorZ.setAcceleration(500);

  // Opsional: Matikan Enable pin untuk pastikan motor hidup (Active LOW)
  pinMode(PIN_ENABLE, OUTPUT);
  digitalWrite(PIN_ENABLE, LOW);
}

void loop() {
  // Kod di bawah menggerakkan motor ke depan 2000 langkah, kemudian undur balik.
  // 200 langkah biasanya sama dengan 1 putaran penuh (jika guna Full Step).

  // Bergerak ke posisi 2000
  motorX.moveTo(2000);
  motorY.moveTo(2000);
  motorZ.moveTo(2000);

  // Fungsi run() mesti dipanggil berulang-kali secepat mungkin dalam loop
  // Ia akan menjalankan motor sehingga sampai destinasi.
  while (motorX.distanceToGo() != 0 || motorY.distanceToGo() != 0 || motorZ.distanceToGo() != 0) {
    motorX.run();
    motorY.run();
    motorZ.run();
  }

  // Tahan sekejap (1 saat)
  delay(1000);

  // Bergerak kembali ke posisi 0
  motorX.moveTo(0);
  motorY.moveTo(0);
  motorZ.moveTo(0);

  while (motorX.distanceToGo() != 0 || motorY.distanceToGo() != 0 || motorZ.distanceToGo() != 0) {
    motorX.run();
    motorY.run();
    motorZ.run();
  }

  // Tahan sekejap sebelum ulang semula
  delay(1000);
}
