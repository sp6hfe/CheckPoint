#include <logger/SerialLogger.hpp>

#include <stdio.h>

namespace logger {

SerialLogger::SerialLogger(Print& stream, interface::ILogger::LogLevel threshold)
    : _out(stream), _threshold(threshold), _buf{0} {}

void SerialLogger::setLevel(interface::ILogger::LogLevel lvl) { _threshold = lvl; }
interface::ILogger::LogLevel SerialLogger::level() const { return _threshold; }

void SerialLogger::logf(interface::ILogger::LogLevel lvl, const char* tag, const char* fmt, ...) {
  if (!_shouldLog(lvl)) return;
  va_list ap;
  va_start(ap, fmt);
  vlogf(lvl, tag, fmt, ap);
  va_end(ap);
}

void SerialLogger::vlogf(interface::ILogger::LogLevel lvl, const char* tag, const char* fmt, va_list ap) {
  if (!_shouldLog(lvl)) return;

  _printPrefix(lvl, tag);

  // Format into the fixed buffer. vsnprintf returns chars that *would* be written (no NUL).
  va_list apCopy;
  va_copy(apCopy, ap);
  int needed = vsnprintf(_buf, sizeof(_buf), fmt, apCopy);
  va_end(apCopy);

  if (needed < 0) {
    _out.println("<format error>");
    return;
  }

  if (static_cast<size_t>(needed) < sizeof(_buf)) {
    // Fully fit.
    _out.println(_buf);
    return;
  }

  // Truncated; ensure explicit "..." at the end if we have room.
  if (sizeof(_buf) >= 4) {
    const size_t end = sizeof(_buf);
    _buf[end - 4] = '.';
    _buf[end - 3] = '.';
    _buf[end - 2] = '.';
    _buf[end - 1] = '\0';
  } else if (sizeof(_buf) >= 2) {
    _buf[sizeof(_buf) - 1] = '\0';  // best effort
  }
  _out.println(_buf);
}

char SerialLogger::_levelChar(interface::ILogger::LogLevel lvl) {
  switch (lvl) {
    case interface::ILogger::LogLevel::Error:
      return 'E';
    case interface::ILogger::LogLevel::Warn:
      return 'W';
    case interface::ILogger::LogLevel::Info:
      return 'I';
    case interface::ILogger::LogLevel::Debug:
      return 'D';
    case interface::ILogger::LogLevel::Verbose:
      return 'V';
    case interface::ILogger::LogLevel::None:
      return '-';
  }
  return '?';
}

bool SerialLogger::_shouldLog(interface::ILogger::LogLevel lvl) const {
  if (_threshold == interface::ILogger::LogLevel::None) return false;
  return static_cast<uint8_t>(lvl) <= static_cast<uint8_t>(_threshold);
}

void SerialLogger::_printPrefix(interface::ILogger::LogLevel lvl, const char* tag) {
  _out.print('[');
  _out.print(_levelChar(lvl));
  _out.print("] ");
  if (tag && *tag) {
    _out.print('[');
    _out.print(tag);
    _out.print("] ");
  }
}

}  // namespace logger
