/*************************************************************
  Download Blynk library:
  http://librarymanager.allthingstalk.com/Blynk
 *************************************************************/

#define BLYNK_TEMPLATE_ID "TMPL6sCKLk1qD"
#define BLYNK_TEMPLATE_NAME "ESP 32 ARDUINO UNO"
#define BLYNK_AUTH_TOKEN "Eswb6aaDFR84B-GC8SfK4qdjsz5odCYu"

// Comment baris ini untuk disable debug dan simpan sambungan
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <HardwareSerial.h> // Penting untuk guna Serial2 dengan pin lain

// WiFi Credentials (SILA ISI)
char ssid[] = "Hariz";
char pass[] = "hariz2005";

// --- DEFINISI PIN EXPLICIT UNTUK SERIAL2 ---
// Kebanyakan board ESP32: RX2=16, TX2=17.
// Jika board awak berbeza, tukar nombor ini.
const int RX_PIN = 16; 
const int TX_PIN = 17;

// Setup Serial untuk komunikasi ke Arduino Uno
// Guna Serial 2
HardwareSerial ArduinoSerial(2);

void setup() {
  // Debug Serial ke PC
  Serial.begin(115200);

  // Serial ke Arduino Uno (Guna Pin Explicit)
  // ArduinoSerial.begin(Baud, Format, RX_PIN, TX_PIN)
  ArduinoSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN); 
  
  /* 
     WIRING WAJIB (Cari label TX2/RX2 pada board, atau ikut GPIO di atas):
     ESP32 TX_PIN (GPIO 17) -------------------> Arduino RX (D0)
     ESP32 RX_PIN (GPIO 16) -------------------> Arduino TX (D1)
     ESP32 GND -----------------------------> Arduino GND
  */

  // Connect ke WiFi & Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}

// --- FUNGSI BLYNK ---

// Bila Button V0 (Slot) ditekan, hantar 'S' ke Arduino
BLYNK_WRITE(V0) {
  int val = param.asInt();
  if (val == 1) {
    ArduinoSerial.print('S'); // S = Slot
    Serial.println("Arahan Blynk: Pergi Ke Slot");
  }
}

// Bila Button V1 (Home) ditekan, hantar 'H' ke Arduino
BLYNK_WRITE(V1) {
  int val = param.asInt();
  if (val == 1) {
    ArduinoSerial.print('H'); // H = Home
    Serial.println("Arahan Blynk: Balik Ke Home");
  }
}
