#include <nfc/NfcSpi.hpp>

namespace hwwrapper {

bool NfcSpi::init() {
  _isinit = false;

  if (!_nfc.begin()) {
    return _isinit;
  }

  auto fwVersion = _nfc.getFirmwareVersion();
  if (fwVersion == 0U) {
    return _isinit;
  }

  _isinit = true;
  return _isinit;
}

bool NfcSpi::isInit() {
  return _isinit;
}

uint32_t NfcSpi::getFwVersion() {
  return _isinit ? _nfc.getFirmwareVersion() : 0U;
}

}  // namespace hwwrapper