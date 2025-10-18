#include <nfc/INfc.hpp>

#include <etl/string_view.h>

namespace app::helpers {

etl::string_view cardDetailsToUidHexStr(const hw::interface::INfc::CardDetails& details);

}  // namespace app::helpers
