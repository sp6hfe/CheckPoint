#include <app/app.hpp>
#include <app/helpers.hpp>

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
    _logger.logf(LogLevel::Info, "app", "Card detected. UID: %s", app::helpers::cardDetailsToUidHexStr(cardDetails.value()).data());
  }
}

}  // namespace app