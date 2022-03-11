#if __INCLUDE_LEVEL__ != 0
#error "Don't include this file"
#endif
#include "field.h"

#include <cstring>
#include <iomanip>
#include <iostream>

extern "C"
{
#include "portable_endian.h"
#include <emmintrin.h>
#include <immintrin.h>
#include <wmmintrin.h>
#include <xmmintrin.h>
}

namespace
{

  inline void clmul_karatsuba(__m128i out[2], const __m128i a, const __m128i b)
  {
    __m128i tmp[4];
    out[0] = _mm_clmulepi64_si128(a, b, 0x00);
    out[1] = _mm_clmulepi64_si128(a, b, 0x11);

    tmp[0] = _mm_srli_si128(a, 8);
    tmp[1] = _mm_xor_si128(a, tmp[0]);
    tmp[2] = _mm_srli_si128(b, 8);
    tmp[3] = _mm_xor_si128(b, tmp[2]);

    tmp[0] = _mm_clmulepi64_si128(tmp[1], tmp[3], 0x00);
    tmp[1] = _mm_xor_si128(out[1], out[0]);
    tmp[0] = _mm_xor_si128(tmp[0], tmp[1]);

    tmp[1] = _mm_slli_si128(tmp[0], 8);
    tmp[2] = _mm_srli_si128(tmp[0], 8);

    out[0] = _mm_xor_si128(out[0], tmp[1]);
    out[1] = _mm_xor_si128(out[1], tmp[2]);
  }
  inline void clmul_schoolbook(__m128i out[2], const __m128i a, const __m128i b)
  {
    __m128i tmp[3];
    out[0] = _mm_clmulepi64_si128(a, b, 0x00);
    out[1] = _mm_clmulepi64_si128(a, b, 0x11);

    tmp[0] = _mm_clmulepi64_si128(a, b, 0x01);
    tmp[1] = _mm_clmulepi64_si128(a, b, 0x10);

    tmp[0] = _mm_xor_si128(tmp[0], tmp[1]);
    tmp[1] = _mm_slli_si128(tmp[0], 8);
    tmp[2] = _mm_srli_si128(tmp[0], 8);

    out[0] = _mm_xor_si128(out[0], tmp[1]);
    out[1] = _mm_xor_si128(out[1], tmp[2]);
  }

  inline void sqr(__m128i out[2], const __m128i a)
  {
    __m128i tmp[2];
    __m128i sqrT = _mm_set_epi64x(0x5554515045444140, 0x1514111005040100);
    __m128i mask = _mm_set_epi64x(0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F);
    tmp[0] = _mm_and_si128(a, mask);
    tmp[1] = _mm_srli_epi64(a, 4);
    tmp[1] = _mm_and_si128(tmp[1], mask);
    tmp[0] = _mm_shuffle_epi8(sqrT, tmp[0]);
    tmp[1] = _mm_shuffle_epi8(sqrT, tmp[1]);
    out[0] = _mm_unpacklo_epi8(tmp[0], tmp[1]);
    out[1] = _mm_unpackhi_epi8(tmp[0], tmp[1]);
  }

  inline void reduce_u64(__m128i out[1], const __m128i in[2])
  {
    uint64_t tmp[4];
    uint64_t t0, t1, t2;
    _mm_store_si128((__m128i *)&tmp[0], in[0]);
    _mm_store_si128((__m128i *)&tmp[2], in[1]);

    // printf("%16llx %16llx %16llx %16llx\n", tmp[3], tmp[2], tmp[1], tmp[0]);
    // modulus = x^128 + x^7 + x^2 + x^1 + 1
    t2 = (tmp[3] >> 57) ^ (tmp[3] >> 62) ^ (tmp[3] >> 63);
    tmp[2] ^= t2;
    t1 = (tmp[3] << 7) | (tmp[2] >> 57);
    t1 ^= (tmp[3] << 2) | (tmp[2] >> 62);
    t1 ^= (tmp[3] << 1) | (tmp[2] >> 63);
    t1 ^= tmp[3];
    tmp[1] ^= t1;
    t0 = (tmp[2] << 7);
    t0 ^= (tmp[2] << 2);
    t0 ^= (tmp[2] << 1);
    t0 ^= tmp[2];
    tmp[0] ^= t0;
    // printf("%16llx %16llx %16llx %16llx\n", tmp[3], tmp[2], tmp[1], tmp[0]);
    out[0] = _mm_load_si128((__m128i *)&tmp[0]);
  }

  inline void reduce_clmul(__m128i out[1], const __m128i in[2])
  {
    __m128i p = _mm_set_epi64x(0x0, 0x87);
    __m128i t0, t1, t2;
    t0 = _mm_clmulepi64_si128(in[1], p, 0x01); // in[1]_high * p
    t1 = _mm_slli_si128(t0, 8);                // low 64bit of result, shifted to high
    t2 = _mm_srli_si128(t0, 8);                // high 64bit of result, shifted to high
    t2 = _mm_xor_si128(t2, in[1]);             // update in[1]_low with high64 of result

    t0 = _mm_clmulepi64_si128(t2, p, 0x00); // updated in[1]_low * p
    out[0] = _mm_xor_si128(t0, in[0]);      // add in[1]_low * p to result
    out[0] = _mm_xor_si128(out[0], t1);     // also add the low part of in[1]_high * p
  }

  inline void reduce_m128i(__m128i out[1], const __m128i in[2])
  {
    __m128i t0, t1, t2, t3, t4, t5;

    t0 = _mm_srli_epi64(in[1], 57);
    t1 = _mm_srli_epi64(in[1], 62);
    t2 = _mm_srli_epi64(in[1], 63);
    t1 = _mm_xor_si128(t1, t2);
    t0 = _mm_xor_si128(t0, t1);

    t1 = _mm_slli_si128(t0, 8);
    t2 = _mm_srli_si128(t0, 8);

    t0 = _mm_xor_si128(in[1], t2);

    t3 = _mm_slli_epi64(t0, 7);
    t4 = _mm_slli_epi64(t0, 2);
    t5 = _mm_slli_epi64(t0, 1);
    t3 = _mm_xor_si128(t3, t4);
    t0 = _mm_xor_si128(t5, t0);
    t0 = _mm_xor_si128(t0, t3);
    t0 = _mm_xor_si128(t0, t1);

    out[0] = _mm_xor_si128(t0, in[0]);
  }

  inline void reduce_intel(__m128i out[1], const __m128i in[2])
  {
    __m128i XMMMASK = _mm_setr_epi32(0xffffffff, 0x0, 0x0, 0x0);
    __m128i tmp3, tmp6, tmp7, tmp8, tmp9, tmp10, tmp11, tmp12;

    tmp7 = _mm_srli_epi32(in[1], 31);
    tmp8 = _mm_srli_epi32(in[1], 30);
    tmp9 = _mm_srli_epi32(in[1], 25);
    tmp7 = _mm_xor_si128(tmp7, tmp8);
    tmp7 = _mm_xor_si128(tmp7, tmp9);
    tmp8 = _mm_shuffle_epi32(tmp7, 147);

    tmp7 = _mm_and_si128(XMMMASK, tmp8);
    tmp8 = _mm_andnot_si128(XMMMASK, tmp8);
    tmp3 = _mm_xor_si128(in[0], tmp8);
    tmp6 = _mm_xor_si128(in[1], tmp7);
    tmp10 = _mm_slli_epi32(tmp6, 1);
    tmp3 = _mm_xor_si128(tmp3, tmp10);
    tmp11 = _mm_slli_epi32(tmp6, 2);
    tmp3 = _mm_xor_si128(tmp3, tmp11);
    tmp12 = _mm_slli_epi32(tmp6, 7);
    tmp3 = _mm_xor_si128(tmp3, tmp12);

    out[0] = _mm_xor_si128(tmp3, tmp6);
  }

  inline void gf128mul(__m128i *out, const __m128i *in1, const __m128i *in2)
  {
    __m128i tmp[2];
    clmul_schoolbook(tmp, *in1, *in2);
    reduce_clmul(out, tmp);
  }
  inline void gf128sqr(__m128i *out, const __m128i *in)
  {
    __m128i tmp[2];
    sqr(tmp, *in);
    reduce_clmul(out, tmp);
  }

  inline void gf128add(__m128i *out, const __m128i *in1, const __m128i *in2)
  {
    *out = _mm_xor_si128(*in1, *in2);
  }

  static inline __m256i mm256_compute_mask_2(const uint64_t idx,
                                             const size_t bit)
  {
    const uint64_t m1 = -((idx >> bit) & 1);
    const uint64_t m2 = -((idx >> (bit + 1)) & 1);
    return _mm256_set_epi64x(m2, m2, m1, m1);
  }

} // namespace

namespace field
{

  GF2_128::GF2_128(std::string hex_string)
  {
    // check if hex_string start with 0x or 0X
    if (hex_string.rfind("0x", 0) == 0 || hex_string.rfind("0X", 0) == 0)
    {
      hex_string = hex_string.substr(2);
    }
    else
    {
      throw std::runtime_error("input needs to be a hex number");
    }
    constexpr size_t num_hex_chars = 128 / 4;
    if (hex_string.length() > num_hex_chars)
      throw std::runtime_error("input hex is too large");
    // pad to 128 bit
    hex_string.insert(hex_string.begin(), num_hex_chars - hex_string.length(),
                      '0');
    // high 64 bit
    uint64_t high = std::stoull(hex_string.substr(0, 64 / 4), nullptr, 16);
    // low 64 bit
    uint64_t low = std::stoull(hex_string.substr(64 / 4, 64 / 4), nullptr, 16);
    data[0] = low;
    data[1] = high;
  }

  GF2_128 GF2_128::operator+(const GF2_128 &other) const
  {
    GF2_128 result;
    gf128add(result.as_m128i(), this->as_const_m128i(), other.as_const_m128i());
    return result;
  }
  GF2_128 &GF2_128::operator+=(const GF2_128 &other)
  {
    gf128add(this->as_m128i(), this->as_const_m128i(), other.as_const_m128i());
    return *this;
  }
  GF2_128 GF2_128::operator-(const GF2_128 &other) const
  {
    GF2_128 result;
    gf128add(result.as_m128i(), this->as_const_m128i(), other.as_const_m128i());
    return result;
  }
  GF2_128 &GF2_128::operator-=(const GF2_128 &other)
  {
    gf128add(this->as_m128i(), this->as_const_m128i(), other.as_const_m128i());
    return *this;
  }
  GF2_128 GF2_128::operator*(const GF2_128 &other) const
  {
    GF2_128 result;
    gf128mul(result.as_m128i(), this->as_const_m128i(), other.as_const_m128i());
    return result;
  }
  GF2_128 &GF2_128::operator*=(const GF2_128 &other)
  {
    gf128mul(this->as_m128i(), this->as_const_m128i(), other.as_const_m128i());
    return *this;
  }
  bool GF2_128::operator==(const GF2_128 &other) const
  {
    return std::memcmp(this->data.data(), other.data.data(), BYTE_SIZE) == 0;
  }
  bool GF2_128::operator!=(const GF2_128 &other) const
  {
    return std::memcmp(this->data.data(), other.data.data(), BYTE_SIZE) != 0;
  }

  GF2_128 GF2_128::inverse() const
  {
    size_t u[11] = {1, 2, 3, 6, 12, 24, 48, 51, 63, 126, 127};
    __m128i b[11];
    size_t u_len = 11;

    b[0] = *(this->as_const_m128i());

    for (size_t i = 1; i < u_len; ++i)
    {
      size_t p = u[i - 1];
      size_t q = u[i] - p;

      size_t p_index;
      for (size_t m = 0; m < i; ++m)
      {
        if (u[m] == p)
        {
          p_index = m;
          break;
        }
      }

      size_t q_index;
      for (size_t m = 0; m < i; ++m)
      {
        if (u[m] == q)
        {
          q_index = m;
          break;
        }
      }

      __m128i b_p = b[p_index];
      __m128i b_q = b[q_index];

      for (size_t m = q; m; --m)
      {
        gf128sqr(&b_p, &b_p);
      }

      gf128mul(&b[i], &b_p, &b_q);
    }

    GF2_128 out;
    gf128sqr(out.as_m128i(), &b[u_len - 1]);

    return out;
  }

  GF2_128 GF2_128::inverse_slow() const
  {
    // Fixed-op square-multiply
    // 2^n - 2 in binary is 0b1111..10
    __m128i t1 = *this->as_const_m128i(), t2;
    gf128sqr(&t2, &t1);

    // First 127 one-bits (start from second)
    for (size_t i = 0; i < 126; i++)
    {
      gf128mul(&t1, &t1, &t2);
      gf128sqr(&t2, &t2);
    }

    // Final zero-bit
    gf128sqr(&t1, &t1);
    GF2_128 result;
    *result.as_m128i() = t1;
    return result;
  }

  GF2_128
  GF2_128::multiply_with_GF2_matrix(const std::array<uint64_t, 2> *matrix) const
  {
    GF2_128 result;

    for (size_t j = 0; j < 2; j++)
    {
      uint64_t t = 0;
      for (size_t i = 0; i < 64; i++)
      {
        const uint64_t *A = matrix[j * 64 + i].data();
        uint64_t bit =
            _mm_popcnt_u64((this->data[0] & A[0]) ^ (this->data[1] & A[1])) & 1;
        t ^= (bit << i);
      }
      result.data[j] = t;
    }
    return result;
  }

  GF2_128 GF2_128::multiply_with_transposed_GF2_matrix(
      const std::array<uint64_t, 2> *matrix) const
  {
    const uint64_t *vptr = this->data.data();
    const __m256i *Ablock = reinterpret_cast<const __m256i *>(matrix->data());

    __m256i cval[2] = {_mm256_setzero_si256(), _mm256_setzero_si256()};
    for (unsigned int w = 2; w; --w, ++vptr)
    {
      uint64_t idx = *vptr;
      for (unsigned int i = sizeof(uint64_t) * 8; i;
           i -= 8, idx >>= 8, Ablock += 4)
      {
        cval[0] = _mm256_xor_si256(
            cval[0], _mm256_and_si256(Ablock[0], mm256_compute_mask_2(idx, 0)));
        cval[1] = _mm256_xor_si256(
            cval[1], _mm256_and_si256(Ablock[1], mm256_compute_mask_2(idx, 2)));
        cval[0] = _mm256_xor_si256(
            cval[0], _mm256_and_si256(Ablock[2], mm256_compute_mask_2(idx, 4)));
        cval[1] = _mm256_xor_si256(
            cval[1], _mm256_and_si256(Ablock[3], mm256_compute_mask_2(idx, 6)));
      }
    }
    cval[0] = _mm256_xor_si256(cval[0], cval[1]);
    GF2_128 result;
    *result.as_m128i() = _mm_xor_si128(_mm256_extracti128_si256(cval[0], 0),
                                       _mm256_extracti128_si256(cval[0], 1));
    return result;
  }

  void GF2_128::to_bytes(uint8_t *out) const
  {
    uint64_t le_data = htole64(data[0]);
    memcpy(out, (uint8_t *)(&le_data), sizeof(uint64_t));
    le_data = htole64(data[1]);
    memcpy(out + sizeof(uint64_t), (uint8_t *)(&le_data), sizeof(uint64_t));
  }

  void GF2_128::from_bytes(const uint8_t *in)
  {
    uint64_t tmp;
    memcpy((uint8_t *)(&tmp), in, sizeof(uint64_t));
    data[0] = le64toh(tmp);
    memcpy((uint8_t *)(&tmp), in + sizeof(uint64_t), sizeof(uint64_t));
    data[1] = le64toh(tmp);
  }

} // namespace field

// somewhat optimized inner product, only do one lazy reduction
field::GF2_128 dot_product(const std::vector<field::GF2_128> &lhs,
                           const std::vector<field::GF2_128> &rhs)
{

  if (lhs.size() != rhs.size())
    throw std::runtime_error("adding vectors of different sizes");

  __m128i accum[2] = {_mm_setzero_si128(), _mm_setzero_si128()};
  __m128i tmp[3];
  tmp[0] = _mm_setzero_si128();
  tmp[1] = _mm_setzero_si128();
  for (size_t i = 0; i < lhs.size(); i++)
  {
    accum[0] = _mm_xor_si128(
        accum[0], _mm_clmulepi64_si128(*lhs[i].as_const_m128i(),
                                       *rhs[i].as_const_m128i(), 0x00));
    accum[1] = _mm_xor_si128(
        accum[1], _mm_clmulepi64_si128(*lhs[i].as_const_m128i(),
                                       *rhs[i].as_const_m128i(), 0x11));
    tmp[0] = _mm_xor_si128(
        tmp[0], _mm_clmulepi64_si128(*lhs[i].as_const_m128i(),
                                     *rhs[i].as_const_m128i(), 0x10));
    tmp[1] = _mm_xor_si128(
        tmp[1], _mm_clmulepi64_si128(*lhs[i].as_const_m128i(),
                                     *rhs[i].as_const_m128i(), 0x01));
  }
  tmp[0] = _mm_xor_si128(tmp[0], tmp[1]);
  tmp[1] = _mm_slli_si128(tmp[0], 8);
  tmp[2] = _mm_srli_si128(tmp[0], 8);

  accum[0] = _mm_xor_si128(accum[0], tmp[1]);
  accum[1] = _mm_xor_si128(accum[1], tmp[2]);
  // combined reduction

  field::GF2_128 result;
  reduce_clmul(result.as_m128i(), accum);
  return result;
}

std::ostream &operator<<(std::ostream &os, const field::GF2_128 &ele)
{
  os << "0x" << std::setfill('0') << std::hex << std::setw(16) << ele.data[1]
     << std::setw(16) << ele.data[0];
  return os;
}

// TEMPLATE INSTANTIATIONS for GF2_128

// yes we include the cpp file with the template stuff
#include "field_templates.cpp"

INSTANTIATE_TEMPLATES_FOR(field::GF2_128)
// END TEMPLATE INSTANTIATIONS for GF2_128