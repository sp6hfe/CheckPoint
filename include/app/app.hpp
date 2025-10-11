#pragma once

#include <nfc/INfc.hpp>

namespace app {

class App {
public:
  App(hw::INfc& nfc) : _nfc(nfc) {}

  ~App() {}

  bool init();

  void process();

private:
  hw::INfc& _nfc;
};

}  // namespace app