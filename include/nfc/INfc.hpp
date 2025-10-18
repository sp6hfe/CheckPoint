#pragma once

#include <algorithm>
#include <array>
#include <optional>
#include <stdint.h>

#include <etl/span.h>

namespace hw::interface {

class INfc {
public:
  static constexpr std::size_t AUTH_KEY_LEN{6U};

  class CardDetails {
  public:
    static constexpr std::size_t MAX_UID_LEN{7U};

    CardDetails(uint8_t* uid, std::size_t uidLen) {
      const auto len = (uidLen > MAX_UID_LEN ? MAX_UID_LEN : uidLen);
      std::copy_n(uid, len, _uid.begin());
      _uidLen = len;
    }

    etl::span<const uint8_t> getUid() const {
      return {_uid.data(), _uidLen};
    }

  private:
    std::array<uint8_t, MAX_UID_LEN> _uid{};
    std::size_t _uidLen{};
  };

  virtual bool isInit() = 0;

  virtual std::optional<uint32_t> getFwVersion() = 0;

  virtual std::optional<CardDetails> lookupCard(uint16_t timeout_ms) = 0;

  virtual ~INfc() {};
};

}  // namespace hw::interface
