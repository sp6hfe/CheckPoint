#include <nfc/INfc.hpp>

#include <array>
#include <etl/array_view.h>
#include <stdint.h>

namespace crypto::kdf {

using INFC = hw::interface::INfc;

std::array<uint8_t, INFC::AUTH_KEY_LEN> mifareAuthKdf(etl::array_view<uint8_t> uid, uint8_t sectorNo);

}  // namespace crypto::kdf
