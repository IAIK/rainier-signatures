
#include <array>
#include <cmath>
#include <complex>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace field {

// Reads the precomputed DENOMINATOR from file
template <typename GF>
void read_precomputed_denominator_from_file(
    std::vector<GF> &precomputed_denominator) {
  std::ifstream file;
  file.open("precomputed_denominator_out.txt");
  if (file.is_open()) {
    std::string line;
    size_t counter = 0;
    while (std::getline(file, line)) {
      precomputed_denominator[counter] = GF(line);
      counter++;
    }
  } else {
    throw std::runtime_error(
        "Cannot open file to read precomputed denominator data");
  }
  file.close();
}

// debug + dev mode only
// Use to precompute the constants of the DENOMINATOR.INVERSE()
template <typename GF>
std::vector<GF>
write_precomputed_denominator_to_file(const std::vector<GF> &x_values) {
  // Check if value size is power of 2
  if (ceil(log2(x_values.size())) != floor(log2(x_values.size()))) {
    throw std::runtime_error("invalid sizes for interpolation");
  }
  std::ofstream file;
  file.open("precomputed_denominator_out.txt");

  size_t values_size = x_values.size();

  std::vector<GF> denominator_all;
  denominator_all.reserve(values_size);
  GF denominator;
  for (size_t k = 0; k < values_size; ++k) {
    denominator = GF(1);
    for (size_t i = 0; i < values_size; ++i) {
      if (i != k) {
        denominator *= x_values[k] - x_values[i];
      }
    }
    denominator_all.push_back(denominator);
    file << denominator.inverse() << std::endl;
  }
  return denominator_all;
}

// Computing the precomputable part of the plain langrange interpolation
template <typename GF>
std::vector<std::vector<GF>>
precompute_lagrange_polynomials(const std::vector<GF> &x_values) {
  size_t m = x_values.size();
  std::vector<std::vector<GF>> precomputed_lagrange_polynomials;
  precomputed_lagrange_polynomials.reserve(m);

  std::vector<GF> x_except_k;
  GF denominator;
  for (size_t k = 0; k < m; k++) {
    denominator = GF(1);
    x_except_k.clear();
    x_except_k.reserve(m - 1);
    for (size_t j = 0; j < m; j++) {
      if (k != j) {
        denominator *= x_values[k] - x_values[j];
        x_except_k.push_back(x_values[j]);
      }
    }
    std::vector<GF> numerator = build_from_roots(x_except_k);

    numerator = numerator * denominator.inverse();
    precomputed_lagrange_polynomials.push_back(numerator);
  }

  return precomputed_lagrange_polynomials;
}

// Langrange interpolation with precomputation
template <typename GF>
std::vector<GF> interpolate_with_precomputation(
    const std::vector<std::vector<GF>> &precomputed_lagrange_polynomials,
    const std::vector<GF> &y_values) {
  if (precomputed_lagrange_polynomials.size() != y_values.size() ||
      y_values.empty())
    throw std::runtime_error("invalid sizes for interpolation");

  std::vector<GF> res(precomputed_lagrange_polynomials[0].size());
  size_t m = y_values.size();
  for (size_t k = 0; k < m; k++) {
    res += precomputed_lagrange_polynomials[k] * y_values[k];
  }
  return res;
}

// Fast langrange interpolation with precomputation
template <typename GF>
std::vector<GF>
interpolate_with_precomputation(const std::vector<GF> &precomputed_denominator,
                                const std::vector<GF> &y_values,
                                const size_t index) {

  std::vector<GF> a_precomputed_denominator;
  a_precomputed_denominator.reserve(1);
  a_precomputed_denominator.push_back(precomputed_denominator[index]);

  return y_values[index] * a_precomputed_denominator;
}

// Fast langrange interpolation using recurssion
template <typename GF>
std::vector<GF> interpolate_fast(const std::vector<GF> &x_values,
                                 const std::vector<GF> &y_values,
                                 const std::vector<GF> &precomputed_denominator,
                                 const size_t start_index,
                                 const size_t length) {

  const size_t len_half = length / 2;
  const size_t end_index = start_index + length - 1;
  const size_t first_half_end_index = start_index + len_half - 1;
  const size_t second_half_start_index = start_index + len_half;

  // The recurssion part !!
  if (length != 2) {

    std::vector<GF> x_first_half_root, x_second_half_root;
    x_first_half_root.reserve(len_half);
    for (size_t i = start_index; i <= first_half_end_index; i++) {
      x_first_half_root.push_back(x_values[i]);
    }

    x_second_half_root.reserve(len_half);
    for (size_t i = second_half_start_index; i <= end_index; i++) {
      x_second_half_root.push_back(x_values[i]);
    }
    std::vector<GF> x_first_half_poly = build_from_roots(x_first_half_root);
    std::vector<GF> x_second_half_poly = build_from_roots(x_second_half_root);

    return (x_second_half_poly * interpolate_fast(x_values, y_values,
                                                  precomputed_denominator,
                                                  start_index, len_half)) +
           (x_first_half_poly *
            interpolate_fast(x_values, y_values, precomputed_denominator,
                             second_half_start_index, len_half));
  }

  std::vector<GF> x_first_half_roots;
  x_first_half_roots.reserve(len_half);
  x_first_half_roots.push_back(x_values[start_index]);
  std::vector<GF> x_first_half_poly = build_from_roots(x_first_half_roots);

  std::vector<GF> x_second_half_roots;
  x_second_half_roots.reserve(len_half);
  x_second_half_roots.push_back(x_values[end_index]);
  std::vector<GF> x_second_half_poly = build_from_roots(x_second_half_roots);

  return (x_second_half_poly *
          interpolate_with_precomputation(precomputed_denominator, y_values,
                                          start_index)) +
         (x_first_half_poly *
          interpolate_with_precomputation(precomputed_denominator, y_values,
                                          end_index));
}

template <typename GF>
std::vector<GF> build_from_roots(const std::vector<GF> &roots) {
  size_t len = roots.size();

  std::vector<GF> poly(roots);
  poly.push_back(GF(0));

  GF tmp;
  for (size_t k = 1; k < len; k++) {
    tmp = poly[k];
    poly[k] = tmp + poly[k - 1];
    for (size_t i = k - 1; i >= 1; i--) {
      poly[i] = poly[i] * tmp + poly[i - 1];
    }
    poly[0] *= tmp;
  }
  poly[len] = GF(1);
  return poly;
}
// horner eval
template <typename GF> GF eval(const std::vector<GF> &poly, const GF &point) {
  GF acc;
  long i;

  for (i = poly.size() - 1; i >= 0; i--) {
    acc *= point;
    acc += poly[i];
  }

  return acc;
}

template <typename GF> std::vector<GF> get_first_n_field_elements(size_t n) {
  std::vector<GF> result;
  result.reserve(n);
  GF x(2);
  GF gen = x;
  for (size_t i = 0; i < n; i++) {
    result.push_back(gen);
    gen = gen * x;
  }
  return result;
}

} // namespace field

template <typename GF>
std::vector<GF> operator+(const std::vector<GF> &lhs,
                          const std::vector<GF> &rhs) {
  if (lhs.size() != rhs.size())
    throw std::runtime_error("adding vectors of different sizes");

  std::vector<GF> result(lhs);
  for (size_t i = 0; i < lhs.size(); i++)
    result[i] += rhs[i];

  return result;
}

template <typename GF>
std::vector<GF> &operator+=(std::vector<GF> &lhs, const std::vector<GF> &rhs) {
  if (lhs.size() != rhs.size())
    throw std::runtime_error("adding vectors of different sizes");

  for (size_t i = 0; i < lhs.size(); i++)
    lhs[i] += rhs[i];

  return lhs;
}

template <typename GF>
std::vector<GF> operator*(const std::vector<GF> &lhs, const GF &rhs) {
  std::vector<GF> result(lhs);
  for (size_t i = 0; i < lhs.size(); i++)
    result[i] *= rhs;

  return result;
}

template <typename GF>
std::vector<GF> operator*(const GF &lhs, const std::vector<GF> &rhs) {
  return rhs * lhs;
}

// naive polynomial multiplication
template <typename GF>
std::vector<GF> operator*(const std::vector<GF> &lhs,
                          const std::vector<GF> &rhs) {

  std::vector<GF> result(lhs.size() + rhs.size() - 1);
  for (size_t i = 0; i < lhs.size(); i++)
    for (size_t j = 0; j < rhs.size(); j++)
      result[i + j] += lhs[i] * rhs[j];

  return result;
}

#define INSTANTIATE_TEMPLATES_FOR(TYPE)                                        \
  template void field::read_precomputed_denominator_from_file(                 \
      std::vector<TYPE> &precomputed_denominator);                             \
  template TYPE field::eval(const std::vector<TYPE> &poly, const TYPE &point); \
  template std::vector<std::vector<TYPE>>                                      \
  field::precompute_lagrange_polynomials(const std::vector<TYPE> &x_values);   \
  template std::vector<TYPE> field::write_precomputed_denominator_to_file(     \
      const std::vector<TYPE> &x_values);                                      \
  template std::vector<TYPE> field::interpolate_fast(                          \
      const std::vector<TYPE> &x_values, const std::vector<TYPE> &y_values,    \
      const std::vector<TYPE> &precomputed_denominator,                        \
      const size_t start_index, const size_t length);                          \
  template std::vector<TYPE> field::interpolate_with_precomputation(           \
      const std::vector<std::vector<TYPE>> &precomputed_lagrange_polynomials,  \
      const std::vector<TYPE> &y_values);                                      \
  template std::vector<TYPE> field::interpolate_with_precomputation(           \
      const std::vector<TYPE> &precomputed_denominator,                        \
      const std::vector<TYPE> &y_values, const size_t index);                  \
  template std::vector<TYPE> field::get_first_n_field_elements(size_t n);      \
  template std::vector<TYPE> operator+(const std::vector<TYPE> &lhs,           \
                                       const std::vector<TYPE> &rhs);          \
  template std::vector<TYPE> &operator+=(std::vector<TYPE> &lhs,               \
                                         const std::vector<TYPE> &rhs);        \
  template std::vector<TYPE> operator*(const std::vector<TYPE> &lhs,           \
                                       const TYPE &rhs);                       \
  template std::vector<TYPE> operator*(const TYPE &lhs,                        \
                                       const std::vector<TYPE> &rhs);          \
  template std::vector<TYPE> operator*(const std::vector<TYPE> &lhs,           \
                                       const std::vector<TYPE> &rhs);\
