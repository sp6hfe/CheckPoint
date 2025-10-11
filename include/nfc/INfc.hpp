#pragma once

#include <stdint.h>

namespace hw {

class INfc {
public:
  virtual bool isInit() = 0;

  virtual uint32_t getFwVersion() = 0;

  virtual ~INfc() {};
};

}  // namespace hw
