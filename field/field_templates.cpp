
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
    std::vector<GF> &precomputed_denominator_firsthalf,
    std::vector<GF> &precomputed_denominator_secondhalf) {
  std::ifstream file;
  file.open("precomputed_denominator_out.txt");
  if (file.is_open()) {
    std::string line;
    size_t first_half_index = 0;
    size_t second_half_index = 0;
    size_t counter = 0;
    size_t len_half = precomputed_denominator_firsthalf.size();
    while (std::getline(file, line)) {
      if (counter < len_half) {
        precomputed_denominator_firsthalf[first_half_index] = GF(line);
        first_half_index++;
      } else {
        precomputed_denominator_secondhalf[second_half_index] = GF(line);
        second_half_index++;
      }
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
void write_precomputed_denominator_to_file(const std::vector<GF> &x_values) {
  // Check if value size is power of 2
  if (ceil(log2(x_values.size())) != floor(log2(x_values.size()))) {
    throw std::runtime_error("invalid sizes for interpolation");
  }
  std::ofstream file;
  file.open("precomputed_denominator_out.txt");

  size_t values_size = x_values.size();

  GF denominator;
  for (size_t k = 0; k < values_size; ++k) {
    denominator = GF(1);
    for (size_t i = 0; i < values_size; ++i) {
      if (i != k) {
        denominator *= x_values[k] - x_values[i];
      }
    }
    file << denominator.inverse() << std::endl;
  }
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

  std::vector<GF> result(precomputed_lagrange_polynomials[0].size());
  size_t m = y_values.size();
  for (size_t k = 0; k < m; k++) {
    result += precomputed_lagrange_polynomials[k] * y_values[k];
  }
  return result;
}

// Fast langrange interpolation with precomputation
template <typename GF>
std::vector<GF>
interpolate_with_precomputation(const std::vector<GF> &precomputed_denominator,
                                const std::vector<GF> &y_values,
                                const size_t index) {

  std::vector<GF> result(precomputed_denominator.size());
  result += y_values[index] * precomputed_denominator;

  return result;
}

// Fast langrange interpolation using recurssion
template <typename GF>
std::vector<GF>
interpolate_fast(const std::vector<GF> &x_values,
                 const std::vector<GF> &y_values,
                 const std::vector<GF> &precomputed_denominator_firsthalf,
                 const std::vector<GF> &precomputed_denominator_secondhalf,
                 const size_t start_index, const size_t end_index) {

  // Check if value size is power of 2
  if (ceil(log2(y_values.size())) != floor(log2(y_values.size()))) {
    throw std::runtime_error("invalid sizes for interpolation");
  }

  size_t len = end_index - start_index + 1;
  size_t len_half = len / 2;

  std::cout << len << std::endl;
  std::cout << start_index << " " << end_index << std::endl;

  // The recurssion part !!
  if (len != 2) {

    std::vector<GF> res1 =
        interpolate_fast(x_values, y_values, precomputed_denominator_firsthalf,
                         precomputed_denominator_secondhalf, start_index,
                         (size_t)floor(end_index / 2));

    std::vector<GF> res2 =
        interpolate_fast(x_values, y_values, precomputed_denominator_firsthalf,
                         precomputed_denominator_secondhalf,
                         (size_t)ceil(end_index / 2), end_index);

    return res1 + res2;
  }

  std::vector<GF> x_first_half_roots;
  x_first_half_roots.reserve(len_half);
  x_first_half_roots.push_back(x_values[start_index]);
  std::vector<GF> x_first_half_poly = build_from_roots(x_first_half_roots);

  std::vector<GF> x_second_half_roots;
  x_second_half_roots.reserve(len_half);
  x_second_half_roots.push_back(x_values[end_index]);
  std::vector<GF> x_second_half_poly = build_from_roots(x_second_half_roots);

  std::cout << " - " << std::dec << x_first_half_poly.size() << std::endl;
  std::cout << " - " << std::dec << x_second_half_poly.size() << std::endl;

  throw std::runtime_error("STOP");

  // Building SUM_1^N/2 u_k * a_k * (MUL_1wherei!=k^(N/2) x - x_i )
  std::vector<GF> first_part = interpolate_with_precomputation(
      precomputed_denominator_firsthalf, y_values, start_index);
  // Multiplying the res first with the numerator second half
  std::vector<GF> results_first(len_half + first_part.size() - 1);
  results_first = x_second_half_poly * first_part;

  // Building SUM_(N/2)+1^N u_k * a_k * (MUL_(N/2)+1wherei!=k^N x - x_i )
  std::vector<GF> second_part = interpolate_with_precomputation(
      precomputed_denominator_secondhalf, y_values, end_index);
  // Multiplying the res second with numerator first half
  std::vector<GF> results_second(len_half + second_part.size() - 1);
  results_second = x_first_half_poly * second_part;

  std::vector<GF> results_final(results_first.size());
  // Adding results of A and B
  results_final = results_first + results_second;

  return results_final;
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

  // Can also do this
  // std::vector<GF> result;
  // result.reserve(n);
  // for (size_t i = 0; i < n; i++) {
  //   result.push_back(GF(i));
  // }
  // return result;

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
      std::vector<TYPE> &precomputed_denominator_firsthalf,                    \
      std::vector<TYPE> &precomputed_denominator_secondhalf);                  \
  template TYPE field::eval(const std::vector<TYPE> &poly, const TYPE &point); \
  template std::vector<std::vector<TYPE>>                                      \
  field::precompute_lagrange_polynomials(const std::vector<TYPE> &x_values);   \
  template void field::write_precomputed_denominator_to_file(                  \
      const std::vector<TYPE> &x_values);                                      \
  template std::vector<TYPE> field::interpolate_fast(                          \
      const std::vector<TYPE> &x_values, const std::vector<TYPE> &y_values,    \
      const std::vector<TYPE> &precomputed_denominator_firsthalf,              \
      const std::vector<TYPE> &precomputed_denominator_secondhalf,             \
      const size_t start_index, const size_t end_index);                       \
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
