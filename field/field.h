#pragma once

#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
extern "C" {
#include <emmintrin.h>
#include <immintrin.h>
}

namespace field {
class GF2_128;
class GF2_192;
class GF2_256;
} // namespace field

field::GF2_128 dot_product(const std::vector<field::GF2_128> &lhs,
                           const std::vector<field::GF2_128> &rhs);
std::ostream &operator<<(std::ostream &os, const field::GF2_128 &ele);

field::GF2_192 dot_product(const std::vector<field::GF2_192> &lhs,
                           const std::vector<field::GF2_192> &rhs);
std::ostream &operator<<(std::ostream &os, const field::GF2_192 &ele);

field::GF2_256 dot_product(const std::vector<field::GF2_256> &lhs,
                           const std::vector<field::GF2_256> &rhs);
std::ostream &operator<<(std::ostream &os, const field::GF2_256 &ele);

namespace field {

class GF2_128 {
  alignas(16) std::array<uint64_t, 2> data;

  // helper functions for sse stuff
  inline __m128i *as_m128i() {
    return reinterpret_cast<__m128i *>(data.data());
  };
  inline const __m128i *as_const_m128i() const {
    return reinterpret_cast<const __m128i *>(data.data());
  };

public:
  constexpr static size_t BYTE_SIZE = 16;
  constexpr GF2_128() : data{} {};
  constexpr GF2_128(uint64_t data) : data{data, 0} {}
  constexpr GF2_128(std::array<uint64_t, 2> data) : data(data) {}
  GF2_128(std::string hex_string);
  GF2_128(const GF2_128 &other) = default;
  ~GF2_128() = default;
  GF2_128 &operator=(const GF2_128 &other) = default;

  inline void clear() { data = {}; }
  inline bool is_zero() const { return data[0] == 0 && data[1] == 0; }
  inline void set_coeff(size_t idx) { data[idx / 64] |= (1ULL << (idx % 64)); }

  GF2_128 operator+(const GF2_128 &other) const;
  GF2_128 &operator+=(const GF2_128 &other);
  GF2_128 operator-(const GF2_128 &other) const;
  GF2_128 &operator-=(const GF2_128 &other);
  GF2_128 operator*(const GF2_128 &other) const;
  GF2_128 &operator*=(const GF2_128 &other);
  bool operator==(const GF2_128 &other) const;
  bool operator!=(const GF2_128 &other) const;

  GF2_128 inverse() const;
  GF2_128 inverse_slow() const;
  GF2_128 multiply_with_GF2_matrix(const std::array<uint64_t, 2> *matrix) const;
  GF2_128 multiply_with_transposed_GF2_matrix(
      const std::array<uint64_t, 2> *matrix) const;

  void to_bytes(uint8_t *out) const;
  void from_bytes(const uint8_t *in);

  friend GF2_128(::dot_product)(const std::vector<field::GF2_128> &lhs,
                                const std::vector<field::GF2_128> &rhs);
  friend std::ostream &(::operator<<)(std::ostream &os,
                                      const field::GF2_128 &ele);
};

class GF2_192 {
  // we waste 1 u64 here for alignment
  alignas(32) std::array<uint64_t, 4> data;

  // helper functions for sse stuff
  inline __m128i *as_m128i() {
    return reinterpret_cast<__m128i *>(data.data());
  };
  inline const __m128i *as_const_m128i() const {
    return reinterpret_cast<const __m128i *>(data.data());
  };
  // helper functions for avx2 stuff
  inline __m256i *as_m256i() {
    return reinterpret_cast<__m256i *>(data.data());
  };
  inline const __m256i *as_const_m256i() const {
    return reinterpret_cast<const __m256i *>(data.data());
  };

public:
  constexpr static size_t BYTE_SIZE = 24;
  constexpr GF2_192() : data{} {};
  constexpr GF2_192(uint64_t data) : data{data, 0, 0, 0} {}
  constexpr GF2_192(std::array<uint64_t, 4> data) : data{data} {}
  GF2_192(std::string hex_string);
  GF2_192(const GF2_192 &other) = default;
  ~GF2_192() = default;
  GF2_192 &operator=(const GF2_192 &other) = default;

  inline void clear() { data = {}; }
  inline bool is_zero() const {
    return data[0] == 0 && data[1] == 0 && data[2] == 0;
  }
  inline void set_coeff(size_t idx) { data[idx / 64] |= (1ULL << (idx % 64)); }
  GF2_192 operator+(const GF2_192 &other) const;
  GF2_192 &operator+=(const GF2_192 &other);
  GF2_192 operator-(const GF2_192 &other) const;
  GF2_192 &operator-=(const GF2_192 &other);
  GF2_192 operator*(const GF2_192 &other) const;
  GF2_192 &operator*=(const GF2_192 &other);
  bool operator==(const GF2_192 &other) const;
  bool operator!=(const GF2_192 &other) const;

  GF2_192 inverse() const;
  GF2_192 inverse_slow() const;
  GF2_192 multiply_with_GF2_matrix(const std::array<uint64_t, 4> *matrix) const;
  GF2_192 multiply_with_transposed_GF2_matrix(
      const std::array<uint64_t, 4> *matrix) const;

  void to_bytes(uint8_t *out) const;
  void from_bytes(const uint8_t *in);

  friend GF2_192(::dot_product)(const std::vector<field::GF2_192> &lhs,
                                const std::vector<field::GF2_192> &rhs);
  friend std::ostream &(::operator<<)(std::ostream &os,
                                      const field::GF2_192 &ele);
};

class GF2_256 {
  alignas(32) std::array<uint64_t, 4> data;

  // helper functions for sse stuff
  inline __m128i *as_m128i() {
    return reinterpret_cast<__m128i *>(data.data());
  };
  inline const __m128i *as_const_m128i() const {
    return reinterpret_cast<const __m128i *>(data.data());
  };
  // helper functions for avx2 stuff
  inline __m256i *as_m256i() {
    return reinterpret_cast<__m256i *>(data.data());
  };
  inline const __m256i *as_const_m256i() const {
    return reinterpret_cast<const __m256i *>(data.data());
  };

public:
  constexpr static size_t BYTE_SIZE = 32;
  constexpr GF2_256() : data{} {};
  constexpr GF2_256(uint64_t data) : data{data, 0, 0, 0} {}
  constexpr GF2_256(std::array<uint64_t, 4> data) : data{data} {}
  GF2_256(std::string hex_string);
  GF2_256(const GF2_256 &other) = default;
  ~GF2_256() = default;
  GF2_256 &operator=(const GF2_256 &other) = default;

  inline void clear() { data = {}; }
  inline bool is_zero() const {
    return data[0] == 0 && data[1] == 0 && data[2] == 0 && data[3] == 0;
  }
  inline void set_coeff(size_t idx) { data[idx / 64] |= (1ULL << (idx % 64)); }
  GF2_256 operator+(const GF2_256 &other) const;
  GF2_256 &operator+=(const GF2_256 &other);
  GF2_256 operator-(const GF2_256 &other) const;
  GF2_256 &operator-=(const GF2_256 &other);
  GF2_256 operator*(const GF2_256 &other) const;
  GF2_256 &operator*=(const GF2_256 &other);
  bool operator==(const GF2_256 &other) const;
  bool operator!=(const GF2_256 &other) const;

  GF2_256 inverse() const;
  GF2_256 inverse_slow() const;
  GF2_256 multiply_with_GF2_matrix(const std::array<uint64_t, 4> *matrix) const;
  GF2_256 multiply_with_transposed_GF2_matrix(
      const std::array<uint64_t, 4> *matrix) const;

  void to_bytes(uint8_t *out) const;
  void from_bytes(const uint8_t *in);

  friend GF2_256(::dot_product)(const std::vector<field::GF2_256> &lhs,
                                const std::vector<field::GF2_256> &rhs);
  friend std::ostream &(::operator<<)(std::ostream &os,
                                      const field::GF2_256 &ele);
};

template <typename GF> std::vector<GF> get_first_n_field_elements(size_t n);

template <typename GF>
std::vector<std::vector<GF>>
precompute_lagrange_polynomials(const std::vector<GF> &x_values,
                                bool firsthalf);
template <typename GF>
std::vector<std::vector<GF>>
precompute_lagrange_polynomials(const std::vector<GF> &x_values);

template <typename GF>
std::vector<GF> interpolate_with_precomputation(
    const std::vector<std::vector<GF>> &precomputed_lagrange_polynomials,
    const std::vector<GF> &y_values);

template <typename GF>
std::vector<GF> precompute_numerator(const std::vector<GF> &x_values,
                                     bool first_half);

template <typename GF>
std::vector<GF> interpolate_with_seperation(std::vector<GF> x_values,
                                            std::vector<GF> y_values);

template <typename GF>
std::vector<GF> build_from_roots(const std::vector<GF> &roots);

template <typename GF> GF eval(const std::vector<GF> &poly, const GF &point);

} // namespace field

template <typename GF>
std::vector<GF> operator+(const std::vector<GF> &lhs,
                          const std::vector<GF> &rhs);
template <typename GF>
std::vector<GF> &operator+=(std::vector<GF> &self, const std::vector<GF> &rhs);
template <typename GF>
std::vector<GF> operator*(const std::vector<GF> &lhs, const GF &rhs);
template <typename GF>
std::vector<GF> operator*(const GF &lhs, const std::vector<GF> &rhs);
template <typename GF>
std::vector<GF> operator*(const std::vector<GF> &lhs,
                          const std::vector<GF> &rhs);
