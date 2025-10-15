#include <app/app.hpp>

#include <etl/span.h>
#include <etl/string.h>

#include <logger/ILogger.hpp>
#include <nfc/INfc.hpp>

namespace app {

using LogLevel = interface::ILogger::LogLevel;

bool App::init() {
  _logger.logf(LogLevel::Info, "app", "Init...");
  if (!_nfc.isInit()) {
    return false;
  }

  return true;
}

void App::process() {
  const auto cardDetails = _nfc.lookupCard(200u);
  if (cardDetails.has_value()) {
    etl::string<(2 * hw::interface::INfc::CardDetails::MAX_UID_LEN) + 1> uid_str{};
    uid_str.clear();
    const char* hex = "0123456789ABCDEF";
    const auto uid = cardDetails->getUid();
    for (const auto byte : uid) {
      uid_str.push_back(hex[(byte >> 4) & 0x0F]);
      uid_str.push_back(hex[byte & 0x0F]);
    }

    _logger.logf(LogLevel::Info, "app", "Card detected. UID: %s", uid_str.data());
  }
}

}  // namespace app