#include <app/helpers.hpp>
#include <nfc/INfc.hpp>

#include <etl/string.h>
#include <etl/string_view.h>

namespace app::helpers {

etl::string_view cardDetailsToUidHexStr(const hw::interface::INfc::CardDetails& details) {
  const char* hex = "0123456789ABCDEF";
  const auto uid = details.getUid();

  etl::string<2 * hw::interface::INfc::CardDetails::MAX_UID_LEN> uid_str{};
  uid_str.clear();

  for (const auto byte : uid) {
    uid_str.push_back(hex[(byte >> 4) & 0x0F]);
    uid_str.push_back(hex[byte & 0x0F]);
  }

  return etl::string_view(uid_str.begin(), uid_str.length());
}

}  // namespace app::helpers
