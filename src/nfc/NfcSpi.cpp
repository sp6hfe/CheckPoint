#include <nfc/NfcSpi.hpp>

#include <optional>

namespace hwwrapper {

bool NfcSpi::init() {
  _isinit = false;

  if (_nfc.begin()) {
    auto fwVersion = _nfc.getFirmwareVersion();
    if (fwVersion > 0U) {
      _isinit = true;
    }
  }

  return _isinit;
}

bool NfcSpi::isInit() {
  return _isinit;
}

std::optional<uint32_t> NfcSpi::getFwVersion() {
  if (!_isinit) {
    return std::nullopt;
  }

  return _nfc.getFirmwareVersion();
}

std::optional<hwicd> NfcSpi::lookupCard(uint16_t timeout_ms) {
  if (!_isinit) {
    return std::nullopt;
  }

  uint8_t uid[hwicd::MAX_UID_LEN] = {};  // UID buffer
  uint8_t uidLength = 0U;                // UID length (4 or 7 bytes)

  const auto success = _nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, timeout_ms);
  if (!success) {
    return std::nullopt;
  }

  hwicd cardDetails{uid, uidLength};
  return cardDetails;
}

}  // namespace hwwrapper