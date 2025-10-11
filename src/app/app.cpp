#include <app/app.hpp>

#include <nfc/INfc.hpp>

namespace app {

bool App::init() {
  if (!_nfc.isInit()) {
    return false;
  }

  return true;
}

void App::process() {
}

}  // namespace app