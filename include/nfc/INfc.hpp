#pragma once

#include <algorithm>
#include <array>
#include <optional>
#include <stdint.h>

namespace hw::interface {

class INfc {
public:
  class CardDetails {
  public:
    static constexpr uint8_t MAX_UID_LEN = 7U;

    CardDetails(uint8_t* uid, uint8_t uidLen) {
      const auto len = (uidLen > MAX_UID_LEN ? MAX_UID_LEN : uidLen);
      std::copy_n(uid, len, _uid.begin());
    }

  private:
    std::array<uint8_t, MAX_UID_LEN> _uid{};
    uint8_t _uidLen{};
  };

  virtual bool isInit() = 0;

  virtual std::optional<uint32_t> getFwVersion() = 0;

  virtual std::optional<CardDetails> lookupCard() = 0;

  virtual ~INfc() {};
};

}  // namespace hw::interface
