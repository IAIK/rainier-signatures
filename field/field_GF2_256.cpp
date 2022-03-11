#if __INCLUDE_LEVEL__ != 0
#error "Don't include this file"
#endif
#include "field.h"

#include <cstring>
#include <iomanip>
#include <iostream>

extern "C" {
#include "portable_endian.h"
#include <emmintrin.h>
#include <smmintrin.h>
#include <wmmintrin.h>
}

namespace {

inline void clmul_schoolbook(__m128i out[4], const __m128i a[2],
                             const __m128i b[2]) {
  __m128i tmp[4];
  out[0] = _mm_clmulepi64_si128(a[0], b[0], 0x00);

  out[1] = _mm_clmulepi64_si128(a[0], b[0], 0x11);
  out[1] = _mm_xor_si128(out[1], _mm_clmulepi64_si128(a[0], b[1], 0x00));
  out[1] = _mm_xor_si128(out[1], _mm_clmulepi64_si128(a[1], b[0], 0x00));

  out[2] = _mm_clmulepi64_si128(a[1], b[1], 0x00);
  out[2] = _mm_xor_si128(out[2], _mm_clmulepi64_si128(a[0], b[1], 0x11));
  out[2] = _mm_xor_si128(out[2], _mm_clmulepi64_si128(a[1], b[0], 0x11));

  out[3] = _mm_clmulepi64_si128(a[1], b[1], 0x11);

  tmp[0] = _mm_clmulepi64_si128(a[0], b[0], 0x01);
  tmp[1] = _mm_clmulepi64_si128(a[0], b[0], 0x10);

  tmp[0] = _mm_xor_si128(tmp[0], tmp[1]);
  tmp[1] = _mm_slli_si128(tmp[0], 8);
  tmp[2] = _mm_srli_si128(tmp[0], 8);

  out[0] = _mm_xor_si128(out[0], tmp[1]);
  out[1] = _mm_xor_si128(out[1], tmp[2]);

  tmp[0] = _mm_clmulepi64_si128(a[1], b[0], 0x10);
  tmp[1] = _mm_clmulepi64_si128(a[0], b[1], 0x01);
  tmp[2] = _mm_clmulepi64_si128(a[0], b[1], 0x10);
  tmp[3] = _mm_clmulepi64_si128(a[1], b[0], 0x01);

  tmp[0] = _mm_xor_si128(tmp[0], tmp[1]);
  tmp[2] = _mm_xor_si128(tmp[2], tmp[3]);
  tmp[0] = _mm_xor_si128(tmp[0], tmp[2]);
  tmp[1] = _mm_slli_si128(tmp[0], 8);
  tmp[2] = _mm_srli_si128(tmp[0], 8);

  out[1] = _mm_xor_si128(out[1], tmp[1]);
  out[2] = _mm_xor_si128(out[2], tmp[2]);

  tmp[0] = _mm_clmulepi64_si128(a[1], b[1], 0x01);
  tmp[1] = _mm_clmulepi64_si128(a[1], b[1], 0x10);

  tmp[0] = _mm_xor_si128(tmp[0], tmp[1]);
  tmp[1] = _mm_slli_si128(tmp[0], 8);
  tmp[2] = _mm_srli_si128(tmp[0], 8);

  out[2] = _mm_xor_si128(out[2], tmp[1]);
  out[3] = _mm_xor_si128(out[3], tmp[2]);
}

inline void sqr(__m128i out[4], const __m128i a[2]) {
  __m128i tmp[2];
  __m128i sqrT = _mm_set_epi64x(0x5554515045444140, 0x1514111005040100);
  __m128i mask = _mm_set_epi64x(0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F);
  tmp[0] = _mm_and_si128(a[0], mask);
  tmp[1] = _mm_srli_epi64(a[0], 4);
  tmp[1] = _mm_and_si128(tmp[1], mask);
  tmp[0] = _mm_shuffle_epi8(sqrT, tmp[0]);
  tmp[1] = _mm_shuffle_epi8(sqrT, tmp[1]);
  out[0] = _mm_unpacklo_epi8(tmp[0], tmp[1]);
  out[1] = _mm_unpackhi_epi8(tmp[0], tmp[1]);

  tmp[0] = _mm_and_si128(a[1], mask);
  tmp[1] = _mm_srli_epi64(a[1], 4);
  tmp[1] = _mm_and_si128(tmp[1], mask);
  tmp[0] = _mm_shuffle_epi8(sqrT, tmp[0]);
  tmp[1] = _mm_shuffle_epi8(sqrT, tmp[1]);
  out[2] = _mm_unpacklo_epi8(tmp[0], tmp[1]);
  out[3] = _mm_unpackhi_epi8(tmp[0], tmp[1]);
}

inline void reduce_u64(__m128i out[2], const __m128i in[4]) {
  uint64_t tmp[8];
  uint64_t t0, t1, t2, t3, t4;
  _mm_store_si128((__m128i *)&tmp[0], in[0]);
  _mm_store_si128((__m128i *)&tmp[2], in[1]);
  _mm_store_si128((__m128i *)&tmp[4], in[2]);
  _mm_store_si128((__m128i *)&tmp[6], in[3]);

  // modulus = x^256 + x^10 + x^5 + x^2 + 1
  t4 = (tmp[7] >> 54) ^ (tmp[7] >> 59) ^ (tmp[7] >> 62);
  tmp[4] ^= t4;
  t3 = (tmp[7] << 10) | (tmp[6] >> 54);
  t3 ^= (tmp[7] << 5) | (tmp[6] >> 59);
  t3 ^= (tmp[7] << 2) | (tmp[6] >> 62);
  t3 ^= tmp[7];
  tmp[3] ^= t3;
  t2 = (tmp[6] << 10) | (tmp[5] >> 54);
  t2 ^= (tmp[6] << 5) | (tmp[5] >> 59);
  t2 ^= (tmp[6] << 2) | (tmp[5] >> 62);
  t2 ^= tmp[6];
  tmp[2] ^= t2;
  t1 = (tmp[5] << 10) | (tmp[4] >> 54);
  t1 ^= (tmp[5] << 5) | (tmp[4] >> 59);
  t1 ^= (tmp[5] << 2) | (tmp[4] >> 62);
  t1 ^= tmp[5];
  tmp[1] ^= t1;
  t0 = (tmp[4] << 10);
  t0 ^= (tmp[4] << 5);
  t0 ^= (tmp[4] << 2);
  t0 ^= tmp[4];
  tmp[0] ^= t0;
  // printf("%16llx %16llx %16llx %16llx\n", tmp[3], tmp[2], tmp[1], tmp[0]);
  out[0] = _mm_load_si128((__m128i *)&tmp[0]);
  out[1] = _mm_load_si128((__m128i *)&tmp[2]);
}

inline void reduce_clmul(__m128i out[2], const __m128i in[4]) {
  // modulus = x^256 + x^10 + x^5 + x^2 + 1
  __m128i p = _mm_set_epi64x(0x0, 0x425);
  __m128i t0, t1, t2, t3;
  t0 = _mm_clmulepi64_si128(in[3], p, 0x01); // in[3]_high * p
  t1 = _mm_slli_si128(t0, 8);        // low 64bit of result, shifted to high
  t2 = _mm_srli_si128(t0, 8);        // high 64bit of result, shifted to low
  t3 = _mm_xor_si128(in[2], t2);     // update in[2]_low
  out[1] = _mm_xor_si128(in[1], t1); // update in[1]_hi

  t0 = _mm_clmulepi64_si128(in[3], p, 0x00); // in[3]_low * p
  out[1] = _mm_xor_si128(out[1], t0);        // update in[1]_hi and in[1]_lo

  t0 = _mm_clmulepi64_si128(in[2], p, 0x01); // in[2]_high * p
  t1 = _mm_slli_si128(t0, 8);         // low 64bit of result, shifted to high
  t2 = _mm_srli_si128(t0, 8);         // high 64bit of result, shifted to low
  out[1] = _mm_xor_si128(out[1], t2); // update in[1]_low
  out[0] = _mm_xor_si128(t1, in[0]);
  t0 = _mm_clmulepi64_si128(t3, p, 0x00); // in[2]_low * p
  out[0] = _mm_xor_si128(t0, out[0]);
}

inline void gf256mul(__m128i *out, const __m128i *in1, const __m128i *in2) {
  __m128i tmp[4];
  clmul_schoolbook(tmp, in1, in2);
  reduce_clmul(out, tmp);
}
inline void gf256sqr(__m128i *out, const __m128i *in) {
  __m128i tmp[4];
  sqr(tmp, in);
  reduce_clmul(out, tmp);
}

inline void gf256add(__m128i *out, const __m128i *in1, const __m128i *in2) {
  out[0] = _mm_xor_si128(in1[0], in2[0]);
  out[1] = _mm_xor_si128(in1[1], in2[1]);
}
inline void gf256add(__m256i *out, const __m256i *in1, const __m256i *in2) {
  out[0] = _mm256_xor_si256(in1[0], in2[0]);
}

static inline __m256i mm256_compute_mask(const uint64_t idx, const size_t bit) {
  return _mm256_set1_epi64x(-((idx >> bit) & 1));
}

} // namespace

namespace field {

GF2_256::GF2_256(std::string hex_string) {
  // check if hex_string start with 0x or 0X
  if (hex_string.rfind("0x", 0) == 0 || hex_string.rfind("0X", 0) == 0) {
    hex_string = hex_string.substr(2);
  } else {
    throw std::runtime_error("input needs to be a hex number");
  }
  constexpr size_t num_hex_chars = 256 / 4;
  if (hex_string.length() > num_hex_chars)
    throw std::runtime_error("input hex is too large");
  // pad to 256 bit
  hex_string.insert(hex_string.begin(), num_hex_chars - hex_string.length(),
                    '0');
  // high 64 bit
  uint64_t high = std::stoull(hex_string.substr(0, 64 / 4), nullptr, 16);
  // mid_hi 64 bit
  uint64_t mid_hi = std::stoull(hex_string.substr(64 / 4, 64 / 4), nullptr, 16);
  // mid_lo 64 bit
  uint64_t mid_lo =
      std::stoull(hex_string.substr(128 / 4, 64 / 4), nullptr, 16);
  // low 64 bit
  uint64_t low = std::stoull(hex_string.substr(192 / 4, 64 / 4), nullptr, 16);
  data[0] = low;
  data[1] = mid_lo;
  data[2] = mid_hi;
  data[3] = high;
}

GF2_256 GF2_256::operator+(const GF2_256 &other) const {
  GF2_256 result;
  gf256add(result.as_m256i(), this->as_const_m256i(), other.as_const_m256i());
  return result;
}
GF2_256 &GF2_256::operator+=(const GF2_256 &other) {
  gf256add(this->as_m256i(), this->as_const_m256i(), other.as_const_m256i());
  return *this;
}
GF2_256 GF2_256::operator-(const GF2_256 &other) const {
  GF2_256 result;
  gf256add(result.as_m256i(), this->as_const_m256i(), other.as_const_m256i());
  return result;
}
GF2_256 &GF2_256::operator-=(const GF2_256 &other) {
  gf256add(this->as_m256i(), this->as_const_m256i(), other.as_const_m256i());
  return *this;
}
GF2_256 GF2_256::operator*(const GF2_256 &other) const {
  GF2_256 result;
  gf256mul(result.as_m128i(), this->as_const_m128i(), other.as_const_m128i());
  return result;
}
GF2_256 &GF2_256::operator*=(const GF2_256 &other) {
  gf256mul(this->as_m128i(), this->as_const_m128i(), other.as_const_m128i());
  return *this;
}
bool GF2_256::operator==(const GF2_256 &other) const {
  return this->data == other.data;
}
bool GF2_256::operator!=(const GF2_256 &other) const {
  return this->data != other.data;
}

GF2_256 GF2_256::inverse() const {
  size_t u[11] = {1, 2, 3, 6, 12, 15, 30, 60, 120, 240, 255};
  __m128i b[11][2];
  size_t u_len = 11;

  b[0][0] = (this->as_const_m128i()[0]);
  b[0][1] = (this->as_const_m128i()[1]);

  for (size_t i = 1; i < u_len; ++i) {
    size_t p = u[i - 1];
    size_t q = u[i] - p;

    size_t p_index;
    for (size_t m = 0; m < i; ++m) {
      if (u[m] == p) {
        p_index = m;
        break;
      }
    }

    size_t q_index;
    for (size_t m = 0; m < i; ++m) {
      if (u[m] == q) {
        q_index = m;
        break;
      }
    }

    __m128i b_p[2] = {b[p_index][0], b[p_index][1]};
    __m128i b_q[2] = {b[q_index][0], b[q_index][1]};

    for (size_t m = q; m; --m) {
      gf256sqr(b_p, b_p);
    }

    gf256mul(b[i], b_p, b_q);
  }

  GF2_256 out;
  gf256sqr(out.as_m128i(), b[u_len - 1]);

  return out;
}

GF2_256 GF2_256::inverse_slow() const {
  // Fixed-op square-multiply
  // 2^n - 2 in binary is 0b1111..10
  __m128i t1[2], t2[2];
  t1[0] = this->as_const_m128i()[0];
  t1[1] = this->as_const_m128i()[1];
  gf256sqr(t2, t1); // TODO: optimize squaring

  // First 255 one-bits (start from second)
  for (size_t i = 0; i < 254; i++) {
    gf256mul(t1, t1, t2);
    gf256sqr(t2, t2);
  }

  GF2_256 result;
  // Final zero-bit
  gf256sqr(result.as_m128i(), t1);
  return result;
}

GF2_256
GF2_256::multiply_with_GF2_matrix(const std::array<uint64_t, 4> *matrix) const {
  GF2_256 result;

  for (size_t j = 0; j < 4; j++) {
    uint64_t t = 0;
    for (size_t i = 0; i < 64; i++) {
      const uint64_t *A = matrix[j * 64 + i].data();
      uint64_t bit =
          _mm_popcnt_u64((this->data[0] & A[0]) ^ (this->data[1] & A[1]) ^
                         (this->data[2] & A[2]) ^ (this->data[3] & A[3])) &
          1;
      t ^= (bit << i);
    }
    result.data[j] = t;
  }
  return result;
}
GF2_256
GF2_256::multiply_with_transposed_GF2_matrix(
    const std::array<uint64_t, 4> *matrix) const {
  const uint64_t *vptr = this->data.data();
  const __m256i *Ablock = reinterpret_cast<const __m256i *>(matrix->data());

  __m256i cval[2] = {_mm256_setzero_si256(), _mm256_setzero_si256()};
  for (unsigned int w = 4; w; --w, ++vptr) {
    uint64_t idx = *vptr;
    for (unsigned int i = sizeof(uint64_t) * 8; i;
         i -= 4, idx >>= 4, Ablock += 4) {
      cval[0] = _mm256_xor_si256(
          cval[0], _mm256_and_si256(Ablock[0], mm256_compute_mask(idx, 0)));
      cval[1] = _mm256_xor_si256(
          cval[1], _mm256_and_si256(Ablock[1], mm256_compute_mask(idx, 1)));
      cval[0] = _mm256_xor_si256(
          cval[0], _mm256_and_si256(Ablock[2], mm256_compute_mask(idx, 2)));
      cval[1] = _mm256_xor_si256(
          cval[1], _mm256_and_si256(Ablock[3], mm256_compute_mask(idx, 3)));
    }
  }
  GF2_256 result;
  result.as_m256i()[0] = _mm256_xor_si256(cval[0], cval[1]);
  return result;
}

void GF2_256::to_bytes(uint8_t *out) const {
  uint64_t le_data = htole64(data[0]);
  memcpy(out, (uint8_t *)(&le_data), sizeof(uint64_t));
  le_data = htole64(data[1]);
  memcpy(out + sizeof(uint64_t), (uint8_t *)(&le_data), sizeof(uint64_t));
  le_data = htole64(data[2]);
  memcpy(out + 2 * sizeof(uint64_t), (uint8_t *)(&le_data), sizeof(uint64_t));
  le_data = htole64(data[3]);
  memcpy(out + 3 * sizeof(uint64_t), (uint8_t *)(&le_data), sizeof(uint64_t));
}

void GF2_256::from_bytes(const uint8_t *in) {
  uint64_t tmp;
  memcpy((uint8_t *)(&tmp), in, sizeof(uint64_t));
  data[0] = le64toh(tmp);
  memcpy((uint8_t *)(&tmp), in + sizeof(uint64_t), sizeof(uint64_t));
  data[1] = le64toh(tmp);
  memcpy((uint8_t *)(&tmp), in + 2 * sizeof(uint64_t), sizeof(uint64_t));
  data[2] = le64toh(tmp);
  memcpy((uint8_t *)(&tmp), in + 3 * sizeof(uint64_t), sizeof(uint64_t));
  data[3] = le64toh(tmp);
}

} // namespace field

// somewhat optimized inner product, only do one lazy reduction
field::GF2_256 dot_product(const std::vector<field::GF2_256> &lhs,
                           const std::vector<field::GF2_256> &rhs) {

  if (lhs.size() != rhs.size())
    throw std::runtime_error("adding vectors of different sizes");

  __m128i accum[4] = {_mm_setzero_si128(), _mm_setzero_si128(),
                      _mm_setzero_si128(), _mm_setzero_si128()};
  __m128i tmp[5];
  tmp[0] = _mm_setzero_si128();
  tmp[1] = _mm_setzero_si128();
  tmp[2] = _mm_setzero_si128();
  for (size_t i = 0; i < lhs.size(); i++) {
    accum[0] = _mm_xor_si128(
        accum[0], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[0],
                                       rhs[i].as_const_m128i()[0], 0x00));
    accum[1] = _mm_xor_si128(
        accum[1], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[0],
                                       rhs[i].as_const_m128i()[0], 0x11));
    accum[1] = _mm_xor_si128(
        accum[1], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[1],
                                       rhs[i].as_const_m128i()[0], 0x00));
    accum[1] = _mm_xor_si128(
        accum[1], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[0],
                                       rhs[i].as_const_m128i()[1], 0x00));
    accum[2] = _mm_xor_si128(
        accum[2], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[1],
                                       rhs[i].as_const_m128i()[1], 0x00));
    accum[2] = _mm_xor_si128(
        accum[2], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[0],
                                       rhs[i].as_const_m128i()[1], 0x11));
    accum[2] = _mm_xor_si128(
        accum[2], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[1],
                                       rhs[i].as_const_m128i()[0], 0x11));
    accum[3] = _mm_xor_si128(
        accum[3], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[1],
                                       rhs[i].as_const_m128i()[1], 0x11));
    tmp[0] = _mm_xor_si128(
        tmp[0], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[0],
                                     rhs[i].as_const_m128i()[0], 0x10));
    tmp[0] = _mm_xor_si128(
        tmp[0], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[0],
                                     rhs[i].as_const_m128i()[0], 0x01));

    tmp[1] = _mm_xor_si128(
        tmp[1], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[1],
                                     rhs[i].as_const_m128i()[0], 0x10));
    tmp[1] = _mm_xor_si128(
        tmp[1], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[0],
                                     rhs[i].as_const_m128i()[1], 0x01));
    tmp[1] = _mm_xor_si128(
        tmp[1], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[1],
                                     rhs[i].as_const_m128i()[0], 0x01));
    tmp[1] = _mm_xor_si128(
        tmp[1], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[0],
                                     rhs[i].as_const_m128i()[1], 0x10));
    tmp[2] = _mm_xor_si128(
        tmp[2], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[1],
                                     rhs[i].as_const_m128i()[1], 0x10));
    tmp[2] = _mm_xor_si128(
        tmp[2], _mm_clmulepi64_si128(lhs[i].as_const_m128i()[1],
                                     rhs[i].as_const_m128i()[1], 0x01));
  }
  tmp[3] = _mm_slli_si128(tmp[0], 8);
  tmp[4] = _mm_srli_si128(tmp[0], 8);

  accum[0] = _mm_xor_si128(accum[0], tmp[3]);
  accum[1] = _mm_xor_si128(accum[1], tmp[4]);

  tmp[3] = _mm_slli_si128(tmp[1], 8);
  tmp[4] = _mm_srli_si128(tmp[1], 8);

  accum[1] = _mm_xor_si128(accum[1], tmp[3]);
  accum[2] = _mm_xor_si128(accum[2], tmp[4]);

  tmp[3] = _mm_slli_si128(tmp[2], 8);
  tmp[4] = _mm_srli_si128(tmp[2], 8);

  accum[2] = _mm_xor_si128(accum[2], tmp[3]);
  accum[3] = _mm_xor_si128(accum[3], tmp[4]);
  // combined reduction
  field::GF2_256 result;
  reduce_clmul(result.as_m128i(), accum);
  return result;
}

std::ostream &operator<<(std::ostream &os, const field::GF2_256 &ele) {
  os << "0x" << std::setfill('0') << std::hex << std::setw(16) << ele.data[3]
     << std::hex << std::setw(16) << ele.data[2] << std::hex << std::setw(16)
     << ele.data[1] << std::hex << std::setw(16) << ele.data[0];
  return os;
}

// TEMPLATE INSTANTIATIONS for GF2_256

// yes we include the cpp file with the template stuff
#include "field_templates.cpp"

INSTANTIATE_TEMPLATES_FOR(field::GF2_256)
// END TEMPLATE INSTANTIATIONS for GF2_256