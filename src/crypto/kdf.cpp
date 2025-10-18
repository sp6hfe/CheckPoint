#include <crypto/kdf.hpp>

#include <array>

namespace crypto::kdf {

std::array<uint8_t, INFC::AUTH_KEY_LEN> mifareAuthKdf(etl::array_view<uint8_t> uid, uint8_t sectorNo) {
  // TODO: implement KDF based on card's uid
  return {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
}

}  // namespace crypto::kdf
