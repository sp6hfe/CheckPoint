#pragma once

#include <logger/ILogger.hpp>
#include <nfc/INfc.hpp>

namespace app {

class App {
public:
  App(interface::ILogger& logger, hw::interface::INfc& nfc) : _logger(logger), _nfc(nfc) {}

  ~App() {}

  bool init();

  void process();

private:
  interface::ILogger& _logger;
  hw::interface::INfc& _nfc;
};

}  // namespace app