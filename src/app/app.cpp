#include <app/app.hpp>

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
  // const auto cardDetails = _nfc.lookupCard();
  // if (cardDetails.has_value()) {
  // }
}

}  // namespace app