#pragma once

#include "ILogger.hpp"

#include <Arduino.h>

#include <stdarg.h>
#include <stdint.h>

namespace logger {

#ifndef LOGGER_BUFFER_SIZE
#define LOGGER_BUFFER_SIZE 128
#endif

static_assert(LOGGER_BUFFER_SIZE >= 8, "LOGGER_BUFFER_SIZE must be >= 8");

class SerialLogger : public interface::ILogger {
public:
  explicit SerialLogger(Print& stream, interface::ILogger::LogLevel threshold = interface::ILogger::LogLevel::Info);

  void setLevel(interface::ILogger::LogLevel lvl) override;
  interface::ILogger::LogLevel level() const override;

  void logf(LogLevel lvl, const char* tag, const char* fmt, ...) override;
  void vlogf(LogLevel lvl, const char* tag, const char* fmt, va_list ap) override;

private:
  Print& _out;
  interface::ILogger::LogLevel _threshold;
  char _buf[LOGGER_BUFFER_SIZE];

  static char _levelChar(interface::ILogger::LogLevel lvl);
  bool _shouldLog(interface::ILogger::LogLevel lvl) const;
  void _printPrefix(interface::ILogger::LogLevel lvl, const char* tag);
};

}  // namespace logger
