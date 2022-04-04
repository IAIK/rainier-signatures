
#include <array>
#include <cmath>
#include <complex>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace field {

// Reads the precomputed NUMERATOR * DENOMINATOR.INVERSE() (first/second halves)
// from file
template <typename GF>
void read_precomputed_n_mul_d_inv_root_n_from_file(
    std::vector<std::vector<GF>> &precomputed_firsthalf,
    std::vector<std::vector<GF>> &precomputed_secondhalf) {

  std::ifstream file_1;
  file_1.open("precomputation_constants_firsthalf_out.txt");
  if (file_1.is_open()) {
    std::string line;
    size_t outcounter = 0;
    size_t incounter = 0;
    precomputed_firsthalf[0].reserve(ROOT_SIZE_HALF);
    while (std::getline(file_1, line)) {
      precomputed_firsthalf[outcounter].push_back(GF(line));
      incounter++;
      if (incounter == ROOT_SIZE_HALF) {
        incounter = 0;
        outcounter++;
        precomputed_firsthalf[outcounter].reserve(ROOT_SIZE_HALF);
      }
    }
  } else {
    throw std::runtime_error(
        "Cannot open file to read precomputed first-half data");
  }
  file_1.close();

  std::ifstream file_2;
  file_2.open("precomputation_constants_secondhalf_out.txt");
  if (file_2.is_open()) {
    std::string line;
    size_t outcounter = 0;
    size_t incounter = 0;
    precomputed_secondhalf[0].reserve(ROOT_SIZE_HALF);
    while (std::getline(file_2, line)) {
      precomputed_secondhalf[outcounter].push_back(GF(line));
      incounter++;
      if (incounter == ROOT_SIZE_HALF) {
        incounter = 0;
        outcounter++;
        precomputed_secondhalf[outcounter].reserve(ROOT_SIZE_HALF);
      }
    }
  } else {
    throw std::runtime_error(
        "Cannot open file to read precomputed first-half data");
  }
  file_2.close();
}

// Reads the precomputed NUMERATOR (first/second halves) from file
template <typename GF>
void read_precomputed_numerator_from_file(
    std::vector<GF> &precomputed_numerator_firsthalf,
    std::vector<GF> &precomputed_numerator_secondhalf) {

  std::ifstream file_1;
  file_1.open("precomputed_numerator_firsthalf_out.txt");
  if (file_1.is_open()) {
    std::string line;
    size_t counter = 0;
    while (std::getline(file_1, line)) {
      precomputed_numerator_firsthalf[counter] = GF(line);
      counter++;
    }
  } else {
    throw std::runtime_error(
        "Cannot open file to read precomputed numerator data");
  }
  file_1.close();

  std::ifstream file_2;
  file_2.open("precomputed_numerator_secondhalf_out.txt");
  if (file_2.is_open()) {
    std::string line;
    size_t counter = 0;
    while (std::getline(file_2, line)) {
      precomputed_numerator_secondhalf[counter] = GF(line);
      counter++;
    }
  } else {
    throw std::runtime_error(
        "Cannot open file to read precomputed numerator data");
  }
  file_2.close();
}

// Reads the precomputed DENOMINATOR from file
template <typename GF>
void read_precomputed_denominator_from_file(std::vector<GF> &denominator) {
  std::ifstream file;
  file.open("precomputed_denominator_out.txt");
  if (file.is_open()) {
    std::string line;
    size_t counter = 0;
    while (std::getline(file, line)) {
      denominator[counter] = GF(line);
      counter++;
    }
  } else {
    throw std::runtime_error(
        "Cannot open file to read precomputed denominator data");
  }
  file.close();
}

// debug + dev mode only
// Use to precompute the constants of the NUMERATOR * DENOMINATOR.INVERSE()
template <typename GF>
void write_precomputed_root_n_mul_d_inv_to_file(
    const std::vector<GF> &x_values) {
  // Check if value size is power of 2
  if (ceil(log2(x_values.size())) != floor(log2(x_values.size()))) {
    throw std::runtime_error("invalid sizes for interpolation");
  }
  std::ofstream file_1;
  file_1.open("precomputation_constants_firsthalf_out.txt");

  size_t full_size = ROOT_SIZE;
  size_t half_size = ROOT_SIZE_HALF;

  GF denominator;
  std::vector<GF> x_except_k;
  for (size_t k = 0; k < half_size; k++) {
    denominator = GF(1);
    x_except_k.clear();
    x_except_k.reserve(half_size - 1);
    for (size_t i_n = 0; i_n < half_size; i_n++) {
      if (k != i_n) {
        x_except_k.push_back(x_values[i_n]);
      }
    }
    for (size_t i_d = 0; i_d < full_size; i_d++) {
      if (k != i_d) {
        denominator *= x_values[k] - x_values[i_d];
      }
    }
    std::vector<GF> numerator = build_from_roots(x_except_k);
    numerator = numerator * denominator.inverse();

    for (size_t i = 0; i < numerator.size(); i++) {
      file_1 << numerator[i] << std::endl;
    }
  }
  file_1.close();

  std::ofstream file_2;
  file_2.open("precomputation_constants_secondhalf_out.txt");
  std::vector<GF> x_except_k_;
  for (size_t k = half_size; k < full_size; k++) {
    denominator = GF(1);
    x_except_k_.clear();
    x_except_k_.reserve(half_size - 1);
    for (size_t i_n = half_size; i_n < full_size; i_n++) {
      if (k != i_n) {
        x_except_k_.push_back(x_values[i_n]);
      }
    }
    for (size_t i_d = 0; i_d < full_size; i_d++) {
      if (k != i_d) {
        denominator *= x_values[k] - x_values[i_d];
      }
    }
    std::vector<GF> numerator = build_from_roots(x_except_k_);
    numerator = numerator * denominator.inverse();

    for (size_t i = 0; i < numerator.size(); i++) {
      file_2 << numerator[i] << std::endl;
    }
  }
  file_2.close();
}

// debug + dev mode only
// Use to precompute the constants of the NUMERATOR
template <typename GF>
void write_precomputed_numerator_to_file(const std::vector<GF> &x_values) {

  std::ofstream file_1;
  file_1.open("precomputed_numerator_firsthalf_out.txt");
  if (file_1.is_open()) {
    std::vector<GF> x_half_first(ROOT_SIZE_HALF);
    for (size_t j = 0; j < ROOT_SIZE_HALF; ++j) {
      x_half_first[j] = x_values[j];
    }
    std::vector<GF> poly_1 = build_from_roots(x_half_first);
    for (size_t i = 0; i < poly_1.size(); ++i) {
      file_1 << poly_1[i] << std::endl;
    }
    file_1.close();
  } else {
    throw std::runtime_error("Cannot open file to read precomputed data");
  }

  std::ofstream file_2;
  file_2.open("precomputed_numerator_secondhalf_out.txt");
  if (file_2.is_open()) {
    std::vector<GF> x_half_second(ROOT_SIZE_HALF);
    for (size_t j = 0; j < ROOT_SIZE_HALF; ++j) {
      x_half_second[j] = x_values[j + ROOT_SIZE_HALF];
    }
    std::vector<GF> poly_2 = build_from_roots(x_half_second);
    for (size_t i = 0; i < poly_2.size(); ++i) {
      file_2 << poly_2[i] << std::endl;
    }
    file_2.close();
  } else {
    throw std::runtime_error("Cannot open file to read precomputed data");
  }
}

// debug + dev mode only
// Use to precompute the constants of the DENOMINATOR.INVERSE()
template <typename GF>
void write_d_inv_to_file(const std::vector<GF> &x_values) {
  // Check if value size is power of 2
  if (ceil(log2(x_values.size())) != floor(log2(x_values.size()))) {
    throw std::runtime_error("invalid sizes for interpolation");
  }
  std::ofstream file;
  file.open("precomputed_denominator_out.txt");

  size_t values_size = x_values.size();
  size_t values_half_size = values_size / 2;

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

// Computing the precomputable part of the langrange interpolation
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

// Fasting langrange interpolation using recurssive splitting in two parts
template <typename GF>
std::vector<GF>
interpolate_fast(std::vector<GF> y_values,
                 std::vector<std::vector<GF>> precomputed_firsthalf,
                 std::vector<std::vector<GF>> precomputed_secondhalf,
                 std::vector<GF> precomputed_numerator_firsthalf,
                 std::vector<GF> precomputed_numerator_secondhalf,
                 std::vector<GF> denominator) {

  // Check if value size is power of 2
  if (ceil(log2(y_values.size())) != floor(log2(y_values.size()))) {
    throw std::runtime_error("invalid sizes for interpolation");
  }

  std::vector<GF> y_values_first_half(ROOT_SIZE_HALF);
  std::vector<GF> y_values_second_half(ROOT_SIZE_HALF);
  for (size_t i = 0; i < ROOT_SIZE_HALF; ++i) {
    y_values_first_half[i] = y_values[i]; // Getting first half of Y values
    y_values_second_half[i] =
        y_values[i + ROOT_SIZE_HALF]; // Getting first half of Y values
  }

  // Building SUM_1^N/2 u_k * a_k * (MUL_1wherei!=k^(N/2) x - x_i )
  std::vector<GF> first_part = interpolate_with_precomputation(
      precomputed_firsthalf, y_values_first_half);
  // Multiplying the res first with the numerator second half
  std::vector<GF> results_first(precomputed_numerator_secondhalf.size() +
                                first_part.size() - 1);
  results_first = precomputed_numerator_secondhalf * first_part;

  // Building SUM_(N/2)+1^N u_k * a_k * (MUL_(N/2)+1wherei!=k^N x - x_i )
  std::vector<GF> second_part = interpolate_with_precomputation(
      precomputed_secondhalf, y_values_second_half);
  // Multiplying the res second with numerator first half
  std::vector<GF> results_second(precomputed_numerator_firsthalf.size() +
                                 second_part.size() - 1);
  results_second = precomputed_numerator_firsthalf * second_part;

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
      std::vector<TYPE> &denominator);                                         \
  template void field::read_precomputed_numerator_from_file(                   \
      std::vector<TYPE> &precomputed_numerator_firsthalf,                      \
      std::vector<TYPE> &precomputed_numerator_secondhalf);                    \
  template void field::read_precomputed_n_mul_d_inv_root_n_from_file(          \
      std::vector<std::vector<TYPE>> &precomputed_firsthalf,                   \
      std::vector<std::vector<TYPE>> &precomputed_secondhalf);                 \
  template TYPE field::eval(const std::vector<TYPE> &poly, const TYPE &point); \
  template std::vector<std::vector<TYPE>>                                      \
  field::precompute_lagrange_polynomials(const std::vector<TYPE> &x_values);   \
  template void field::write_d_inv_to_file(const std::vector<TYPE> &x_values); \
  template void field::write_precomputed_root_n_mul_d_inv_to_file(             \
      const std::vector<TYPE> &x_values);                                      \
  template void field::write_precomputed_numerator_to_file(                    \
      const std::vector<TYPE> &x_values);                                      \
  template std::vector<TYPE> field::interpolate_fast(                          \
      const std::vector<TYPE> y_values,                                        \
      std::vector<std::vector<TYPE>> precomputed_firsthalf,                    \
      std::vector<std::vector<TYPE>> precomputed_secondhalf,                   \
      std::vector<TYPE> precomputed_numerator_firsthalf,                       \
      std::vector<TYPE> precomputed_numerator_secondhalf,                      \
      std::vector<TYPE> denominator);                                          \
  template std::vector<TYPE> field::interpolate_with_precomputation(           \
      const std::vector<std::vector<TYPE>> &precomputed_lagrange_polynomials,  \
      const std::vector<TYPE> &y_values);                                      \
  template std::vector<TYPE> field::get_first_n_field_elements(size_t n);      \
                                                                               \
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
