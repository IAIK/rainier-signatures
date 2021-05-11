#pragma once

#include "../field.h"
#include <NTL/GF2E.h>
#include <NTL/vec_GF2E.h>

using namespace NTL;

namespace utils {

enum NTL_INSTANCE { GF2_128, GF2_192, GF2_256 };

void init_ntl_extension_field(NTL_INSTANCE instance);
const GF2E &lift_uint8_t(uint8_t value);
GF2E GF2E_from_bytes(const std::vector<uint8_t> &value);

vec_GF2E get_first_n_field_elements(size_t n);
std::vector<GF2EX> precompute_lagrange_polynomials(const vec_GF2E &x_values);
GF2EX interpolate_with_precomputation(
    const std::vector<GF2EX> &precomputed_lagrange_polynomials,
    const vec_GF2E &y_values);

template <typename GF> GF ntl_to_custom(const GF2E &element) {
  const GF2X &poly_rep = rep(element);
  std::array<uint8_t, GF::BYTE_SIZE> buffer{};
  BytesFromGF2X(buffer.data(), poly_rep, buffer.size());
  GF a;
  a.from_bytes(buffer.data());
  return a;
}
template <typename GF> GF2E custom_to_ntl(const GF &element) {
  std::array<uint8_t, GF::BYTE_SIZE> buffer{};
  element.to_bytes(buffer.data());
  GF2X inner = GF2XFromBytes(buffer.data(), buffer.size());
  return conv<GF2E>(inner);
}

} // namespace utils