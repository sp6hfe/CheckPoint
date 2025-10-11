#pragma once

#include "INfc.hpp"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_PN532.h>

#include <stdint.h>

namespace hwwrapper {

class NfcSpi : public hw::INfc {
public:
  NfcSpi(uint8_t clk, uint8_t miso, uint8_t mosi,
    uint8_t ss) : _nfc(clk, miso, mosi, ss) {}

  NfcSpi(uint8_t ss) : _nfc(ss) {}

  ~NfcSpi() {}

  bool init();

  bool isInit() override;

  uint32_t getFwVersion() override;

private:
  Adafruit_PN532 _nfc;

  bool _isinit{false};
};

}  // namespace hwwrapper