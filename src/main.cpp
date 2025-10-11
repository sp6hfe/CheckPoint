#include <Arduino.h>

#include <nfc/NfcSpi.hpp>
#include <app/app.hpp>

#include <optional>

#define PN532_MISO (D6)
#define PN532_MOSI (D7)
#define PN532_SCK (D5)
#define PN532_SS (D2)

// Placeholders (to initialize in setup())
static std::optional<app::App> appl;
static std::optional<hwwrapper::NfcSpi> nfc;

void blinkForever() {
  while (true) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
  }
}

void setup() {
  // General
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(115200);
  Serial.println("\nCheckPoint init...");

  // NFC
  nfc.emplace(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);
  if (!nfc.has_value()) {
    Serial.println("ERROR -> NFC object not constructed.");
    blinkForever();
  }
  if (!nfc->init()) {
    Serial.println("ERROR -> NFC module not initialized.");
    blinkForever();
  }

  const auto fwVersion = nfc->getFwVersion();
  if (fwVersion == 0U) {
    Serial.println("ERROR -> NFC module version not readable.");
    blinkForever();
  }
  Serial.print("NFC chip: PN5");
  Serial.print((fwVersion >> 24) & 0xFF, HEX);
  Serial.print(", FW version: ");
  Serial.print((fwVersion >> 16) & 0xFF, DEC);
  Serial.print('.');
  Serial.println((fwVersion >> 8) & 0xFF, DEC);

  // App
  appl.emplace(nfc.value());
  if (!appl.has_value()) {
    Serial.println("ERROR -> Application object not constructed.");
    blinkForever();
  }
  if (!appl.value().init()) {
    Serial.println("ERROR -> Application not initialized.");
    blinkForever();
  }
}

void loop() {
  if (appl.has_value()) {
    appl.value().process();
  }
  delay(10);
}
