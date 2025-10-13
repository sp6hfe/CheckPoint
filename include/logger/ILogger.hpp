#pragma once

#include <stdarg.h>
#include <stdint.h>

namespace interface {

class ILogger {
public:
  enum class LogLevel : uint8_t {
    None = 0,
    Error = 1,
    Warn = 2,
    Info = 3,
    Debug = 4,
    Verbose = 5
  };

  virtual ~ILogger() {}

  virtual void setLevel(LogLevel lvl) = 0;

  virtual LogLevel level() const = 0;

  virtual void logf(LogLevel lvl, const char* tag, const char* fmt, ...) = 0;

  virtual void vlogf(LogLevel lvl, const char* tag, const char* fmt, va_list ap) = 0;
};

}  // namespace interface
