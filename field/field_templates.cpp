
#include <algorithm>
#include <array>
#include <cmath>
#include <complex>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace field {

// Reads the precomputed denominator from file
template <typename GF>
void read_precomputed_denominator_from_file(
    std::vector<GF> &precomputed_denominator, size_t x_len) {
  precomputed_denominator.reserve(x_len);
  std::ifstream file;
  file.open("precomputed_denominator_out.txt");
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      precomputed_denominator.push_back(GF(line));
    }
  } else {
    throw std::runtime_error(
        "Cannot open file to read precomputed denominator data");
  }
  file.close();
}

// Read the precomputed x - xi
template <typename GF>
void read_precomputed_x_minus_xi_to_file(
    std::vector<std::vector<GF>> &precomputed_x_minus_xi,
    const size_t root_count, std::ifstream &file) {

  size_t line_count = 0;
  for (size_t i = root_count; i > 1; i /= 2) {
    line_count += i;
  }
  precomputed_x_minus_xi.reserve(line_count);

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      // Parsing line by line and pushing to the vector
      int elem_count = std::count(line.begin(), line.end(), ',');
      std::vector<GF> gf_elem;
      gf_elem.reserve(elem_count);
      size_t start_search_index = 0;
      for (size_t i = 0; i < (size_t)elem_count; ++i) {
        // Spiting with ","
        size_t found_index = line.find(',', start_search_index);
        size_t s = found_index - start_search_index;
        gf_elem.push_back(GF(line.substr(start_search_index, s)));
        start_search_index = found_index + 1;
      }
      precomputed_x_minus_xi.push_back(gf_elem);
    }
  } else {
    throw std::runtime_error(
        "Cannot open file to read precomputed x - xi data");
  }
  file.close();
}

// debug + dev mode only
// Use to precompute the constants of the denominaotr.inverse()
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

// debug + dev mode only
// Use to precompute x - xi recurssively
template <typename GF>
void write_precomputed_x_minus_xi_to_file(const std::vector<GF> &x_values,
                                          std::ofstream &file) {
  size_t len = x_values.size();
  if (len == 1) {
    return;
  }
  size_t len_half = len / 2;

  // Gets the first half roots
  std::vector<GF> x_first_half_roots;
  x_first_half_roots.reserve(len / 2);
  for (size_t i = 0; i < len_half; ++i) {
    x_first_half_roots.push_back(x_values[i]);
  }
  // Generates poly from roots
  std::vector<GF> x_first_half_poly = build_from_roots(x_first_half_roots);
  // Writes poly to file
  size_t len_first_poly = x_first_half_poly.size();
  for (size_t i = 0; i < len_first_poly; ++i) {
    file << x_first_half_poly[i] << ",";
  }
  file << std::endl;
  // Recurssion with the first half roots
  write_precomputed_x_minus_xi_to_file(x_first_half_roots, file);

  // Gets the second half roots
  std::vector<GF> x_second_half_roots;
  x_second_half_roots.reserve(len / 2);
  for (size_t i = len_half; i < len; ++i) {
    x_second_half_roots.push_back(x_values[i]);
  }
  // Generates poly from roots
  std::vector<GF> x_second_half_poly = build_from_roots(x_second_half_roots);
  // Write poly to file
  size_t len_second_poly = x_second_half_poly.size();
  for (size_t i = 0; i < len_second_poly; i++) {
    file << x_second_half_poly[i] << ",";
  }
  file << std::endl;
  // Recurssion with the second half roots
  write_precomputed_x_minus_xi_to_file(x_second_half_roots, file);
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
std::vector<GF> interpolate_fast(
    const std::vector<GF> &x_values, const std::vector<GF> &y_values,
    const std::vector<GF> &precomputed_denominator,
    const std::vector<std::vector<GF>> &precomputed_x_minus_xi,
    const size_t x_start_index, const size_t x_length,
    const size_t x_minus_xi_first_index, const size_t x_minus_xi_length) {

  // For indexing x_values
  const size_t x_len_half = x_length / 2;
  const size_t x_end_index = x_start_index + x_length - 1;
  const size_t x_second_half_start_index = x_start_index + x_len_half;

  // For indexing x_minus_xi values
  const size_t x_minus_xi_half_length = x_minus_xi_length / 2;
  const size_t x_minus_xi_second_index =
      x_minus_xi_half_length + x_minus_xi_first_index;

  // The recurssion part !!
  if (x_length != 2) {

    return (precomputed_x_minus_xi[x_minus_xi_second_index] *
            interpolate_fast(x_values, y_values, precomputed_denominator,
                             precomputed_x_minus_xi, x_start_index, x_len_half,
                             x_minus_xi_first_index + 1,
                             x_minus_xi_half_length - 1)) +
           (precomputed_x_minus_xi[x_minus_xi_first_index] *
            interpolate_fast(x_values, y_values, precomputed_denominator,
                             precomputed_x_minus_xi, x_second_half_start_index,
                             x_len_half, x_minus_xi_second_index + 1,
                             x_minus_xi_half_length - 1));
  }

  std::vector<GF> x_first_half_roots;
  x_first_half_roots.reserve(x_len_half);
  x_first_half_roots.push_back(x_values[x_start_index]);
  std::vector<GF> x_first_half_poly = build_from_roots(x_first_half_roots);

  std::vector<GF> x_second_half_roots;
  x_second_half_roots.reserve(x_len_half);
  x_second_half_roots.push_back(x_values[x_end_index]);
  std::vector<GF> x_second_half_poly = build_from_roots(x_second_half_roots);

  return (x_second_half_poly *
          interpolate_with_precomputation(precomputed_denominator, y_values,
                                          x_start_index)) +
         (x_first_half_poly *
          interpolate_with_precomputation(precomputed_denominator, y_values,
                                          x_end_index));
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

// polynomial division of x^n*c^n + x^n-1*c^n-1 + .... by x - a
template <typename GF>
std::vector<GF> operator/(const std::vector<GF> &lhs, const GF &rhs) {
  std::vector<GF> temp(lhs);
  size_t end_index = temp.size() - 1;
  std::vector<GF> result;
  result.reserve(end_index);
  for (size_t i = end_index; i > 0; --i) {
    GF t = temp[i] * rhs;
    temp[i - 1] -= t;
  }
  for (size_t i = 1; i <= end_index; i++) {
    result.push_back(temp[i]);
  }
  return result;
}

#define INSTANTIATE_TEMPLATES_FOR(TYPE)                                        \
  template void field::read_precomputed_denominator_from_file(                 \
      std::vector<TYPE> &precomputed_denominator, size_t x_len);               \
  template void field::read_precomputed_x_minus_xi_to_file(                    \
      std::vector<std::vector<TYPE>> &precomputed_x_minus_xi,                  \
      const size_t root_count, std::ifstream &file);                           \
  template TYPE field::eval(const std::vector<TYPE> &poly, const TYPE &point); \
  template std::vector<std::vector<TYPE>>                                      \
  field::precompute_lagrange_polynomials(const std::vector<TYPE> &x_values);   \
  template void field::write_precomputed_denominator_to_file(                  \
      const std::vector<TYPE> &x_values);                                      \
  template void field::write_precomputed_x_minus_xi_to_file(                   \
      const std::vector<TYPE> &x_values, std::ofstream &file);                 \
  template std::vector<TYPE> field::interpolate_fast(                          \
      const std::vector<TYPE> &x_values, const std::vector<TYPE> &y_values,    \
      const std::vector<TYPE> &precomputed_denominator,                        \
      const std::vector<std::vector<TYPE>> &precomputed_x_minus_xi,            \
      const size_t start_index, const size_t length,                           \
      const size_t x_minus_xi_start_index, const size_t x_minus_xi_length);    \
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
                                       const std::vector<TYPE> &rhs);          \
  template std::vector<TYPE> operator/(const std::vector<TYPE> &lhs,           \
                                       const TYPE &rhs);\
