#include <nfc/NfcSpi.hpp>

#include <crypto/kdf.hpp>

#include <array>
#include <optional>

namespace hwwrapper {

static constexpr uint8_t MIFARE_AUTH_KEY_A{0U};
static constexpr uint8_t MIFARE_AUTH_KEY_B{1U};

inline std::array<uint8_t, hw::interface::INfc::AUTH_KEY_LEN> DEFAULT_AUTH_KEY{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

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
  static constexpr uint8_t AUTH_TRIES{3U};

  if (!_isinit) {
    return std::nullopt;
  }

  std::array<uint8_t, hwicd::MAX_UID_LEN> uid{};
  uint8_t uidLength = 0U;

  bool authenticated{false};
  for (auto auth_try = 0U; auth_try < AUTH_TRIES; auth_try++) {
    // detect the card
    auto success = _nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid.begin(), &uidLength, timeout_ms);
    if (!success) {
      continue;
    }

    if ((uidLength != 4U) && (uidLength != 7U)) {
      return std::nullopt;
    }

    // try to authenticate
    uint32_t DEFAULT_AUTH_BLOCK{4U};
    success = _nfc.mifareclassic_AuthenticateBlock(uid.begin(), uidLength, DEFAULT_AUTH_BLOCK, MIFARE_AUTH_KEY_A, DEFAULT_AUTH_KEY.begin());
    if (success) {
      authenticated = true;
      break;
    }
    delayMicroseconds(100);
    auto kdfAuthKey = crypto::kdf::mifareAuthKdf({uid.data(), uidLength}, DEFAULT_AUTH_BLOCK);
    success = _nfc.mifareclassic_AuthenticateBlock(uid.data(), uidLength, DEFAULT_AUTH_BLOCK, MIFARE_AUTH_KEY_A, kdfAuthKey.begin());
    if (success) {
      authenticated = true;
      break;
    }
  }

  if (!authenticated) {
    return std::nullopt;
  }

  hwicd cardDetails{uid.data(), uidLength};
  return cardDetails;
}

}  // namespace hwwrapper