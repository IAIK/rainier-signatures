
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

// Use to precompute the constants of the denominaotr.inverse()
template <typename GF>
std::vector<GF> precompute_denominator(const std::vector<GF> &x_values) {
  // Check if value size is power of 2
  if (ceil(log2(x_values.size())) != floor(log2(x_values.size()))) {
    throw std::runtime_error("invalid sizes for interpolation");
  }
  size_t values_size = x_values.size();
  std::vector<GF> precomputed_denominator;
  precomputed_denominator.reserve(values_size);
  GF denominator;

  for (size_t k = 0; k < values_size; ++k) {
    denominator = GF(1);
    for (size_t i = 0; i < values_size; ++i) {
      if (i != k) {
        denominator *= x_values[k] - x_values[i];
      }
    }
    precomputed_denominator.push_back(denominator.inverse());
  }

  return precomputed_denominator;
}

template <typename GF>
void set_x_minus_xi_poly_size(
    std::vector<std::vector<GF>> &precomputed_x_minus_xi, size_t root_count) {
  size_t split_count = 0;
  for (size_t i = root_count; i > 1; i /= 2) {
    split_count += i;
  }
  precomputed_x_minus_xi.reserve(split_count);
}

// Use to precompute x - xi recurssively
template <typename GF>
void precompute_x_minus_xi_poly_splits(
    const std::vector<GF> &x_values,
    std::vector<std::vector<GF>> &precomputed_x_minus_xi) {

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
  std::vector<GF> x_first_half_poly = build_from_roots<GF>(x_first_half_roots);
  // Save poly
  precomputed_x_minus_xi.push_back(x_first_half_poly);
  // Recurssion with the first half roots
  precompute_x_minus_xi_poly_splits(x_first_half_roots, precomputed_x_minus_xi);

  // Gets the second half roots
  std::vector<GF> x_second_half_roots;
  x_second_half_roots.reserve(len / 2);
  for (size_t i = len_half; i < len; ++i) {
    x_second_half_roots.push_back(x_values[i]);
  }
  // Generates poly from roots
  std::vector<GF> x_second_half_poly =
      build_from_roots<GF>(x_second_half_roots);
  // Save poly
  precomputed_x_minus_xi.push_back(x_second_half_poly);
  // Recurssion with the second half roots
  precompute_x_minus_xi_poly_splits(x_second_half_roots,
                                    precomputed_x_minus_xi);
}

// Computing the precomputable part of the plain langrange interpolation
// (not-optimized)
template <typename GF>
std::vector<std::vector<GF>>
precompute_lagrange_polynomials_slow(const std::vector<GF> &x_values) {
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

// Computing the precomputable part of the plain langrange interpolation
// (optimized)
template <typename GF>
std::vector<std::vector<GF>>
precompute_lagrange_polynomials(const std::vector<GF> &x_values) {
  size_t m = x_values.size();
  std::vector<std::vector<GF>> precomputed_lagrange_polynomials;
  precomputed_lagrange_polynomials.reserve(m);

  std::vector<GF> x_minus_xi = build_from_roots(x_values);
  for (size_t k = 0; k < m; k++) {

    std::vector<GF> numerator = x_minus_xi / x_values[k];

    numerator = eval(numerator, x_values[k]).inverse() * numerator;
    precomputed_lagrange_polynomials.push_back(numerator);
  }

  return precomputed_lagrange_polynomials;
}

// Langrange interpolation with precomputation (slow)
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

// Langrange interpolation with precomputation (fast)
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

// Langrange interpolation using recurssion (fast)
template <typename GF>
std::vector<GF> interpolate_with_recurrsion(
    const std::vector<GF> &y_values,
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
            interpolate_with_recurrsion(y_values, precomputed_denominator,
                                        precomputed_x_minus_xi, x_start_index,
                                        x_len_half, x_minus_xi_first_index + 1,
                                        x_minus_xi_half_length - 1)) +
           (precomputed_x_minus_xi[x_minus_xi_first_index] *
            interpolate_with_recurrsion(
                y_values, precomputed_denominator, precomputed_x_minus_xi,
                x_second_half_start_index, x_len_half,
                x_minus_xi_second_index + 1, x_minus_xi_half_length - 1));
  }

  return (precomputed_x_minus_xi[x_minus_xi_second_index] *
          interpolate_with_precomputation(precomputed_denominator, y_values,
                                          x_start_index)) +
         (precomputed_x_minus_xi[x_minus_xi_first_index] *
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

template <typename GF>
// Multiplies polynomial of arbitarty degree
std::vector<GF> mul_karatsuba_arbideg(const std::vector<GF> &lhs,
                                      const std::vector<GF> &rhs) {

  if (lhs.size() != rhs.size())
    throw std::runtime_error("karatsuba mul vectors of different sizes");

  GF d[lhs.size()];
  std::vector<GF> c(lhs.size() + rhs.size() - 1);

  // When i == 0
  d[0] = lhs[0] * rhs[0];

  // When i == 1
  d[1] = lhs[1] * rhs[1];
  c[1] = ((lhs[0] + lhs[1]) * (rhs[0] + rhs[1])) - (d[1] + d[0]);

  // When i == 2..poly_length
  for (size_t i = 2; i < lhs.size(); ++i) {
    d[i] = lhs[i] * rhs[i];
    GF sum;
    for (size_t t = i; t > i / 2; --t) {
      sum +=
          ((lhs[i - t] + lhs[t]) * (rhs[i - t] + rhs[t])) - (d[t] + d[i - t]);
    }
    // If i is even
    sum += d[i / 2] * ((i + 1) % 2);
    c[i] = sum;
  }

  // When i == poly_len..poly_len*2-3
  for (size_t i = lhs.size(); i <= lhs.size() + rhs.size() - 3; ++i) {
    GF sum;
    for (size_t t = lhs.size() - 1; t > i / 2; --t) {
      sum +=
          ((lhs[i - t] + lhs[t]) * (rhs[i - t] + rhs[t])) - (d[t] + d[i - t]);
    }

    // If i is even
    sum += d[i / 2] * ((i + 1) % 2);
    c[i] = sum;
  }

  // Setting the first and the last i
  c[0] = d[0];
  c[lhs.size() + rhs.size() - 2] = d[lhs.size() - 1];

  return c;
}

template <typename GF>
// Adding dummy values to make the coeff size a power of 2
void mul_karatsuba_fixdeg_precondition_poly(std::vector<GF> &lhs,
                                            std::vector<GF> &rhs) {

  // Computes the next power of 2 for a 32 bit number
  // This represents the no. of coeffs
  size_t next_2_pow = lhs.size();
  next_2_pow--;
  next_2_pow |= next_2_pow >> 1;
  next_2_pow |= next_2_pow >> 2;
  next_2_pow |= next_2_pow >> 4;
  next_2_pow |= next_2_pow >> 8;
  next_2_pow |= next_2_pow >> 16;
  next_2_pow++;

  // Putting the dummy terms in the begining to make the polys 2^n - 1 degree ->
  // 2^n coeff
  lhs.resize(next_2_pow, GF(0));
  rhs.resize(next_2_pow, GF(0));
}

template <typename GF>
// Adding dummy values to make the coeff size a power of 2
void mul_karatsuba_fixdeg_normalize_poly(std::vector<GF> &poly,
                                         size_t old_size) {
  poly.resize((old_size << 1) - 1);
}

template <typename GF>
// Multiplies polynomial of 2^n - 1 degree -> 2^n coeff
std::vector<GF>
mul_karatsuba_fixdeg(const std::vector<GF> &lhs, const std::vector<GF> &rhs,
                     const size_t start_idx, const size_t end_idx) {

  size_t full_size = ((end_idx - start_idx) + 1);
  size_t half_size = full_size / 2;

  // If a polynomial with degree 0 -> const
  if (full_size == 1) {
    return std::vector<GF>(1, lhs[start_idx] * rhs[start_idx]);
  }

  std::vector<GF> d_0 =
      mul_karatsuba_fixdeg(lhs, rhs, start_idx, (start_idx + half_size) - 1);
  std::vector<GF> d_1 =
      mul_karatsuba_fixdeg(lhs, rhs, (start_idx + half_size), end_idx);

  std::vector<GF> lhs_l_add_u, rhs_l_add_u;
  lhs_l_add_u.reserve(half_size);
  rhs_l_add_u.reserve(half_size);
  // Getting the lower of lhs and rhs
  for (size_t i = start_idx; i < start_idx + half_size; ++i) {
    lhs_l_add_u.push_back(lhs[i] + lhs[half_size + i]);
    rhs_l_add_u.push_back(rhs[i] + rhs[half_size + i]);
  }
  std::vector<GF> d_01 =
      mul_karatsuba_fixdeg(lhs_l_add_u, rhs_l_add_u, 0, half_size - 1);

  std::vector<GF> c(d_1.size() + full_size);
  // D_1*x^n + (D_01 - D_0 - D_1)*x^(n/2) + d_0
  size_t cidx = c.size();
  for (size_t i = d_1.size(); i; --i) {
    c[cidx - 1] += d_1[i - 1];
    cidx--;
  }
  cidx = c.size() * 3 / 4;
  for (size_t i = d_0.size(); i; --i) {
    c[cidx - 1] += (d_01[i - 1] - d_0[i - 1] - d_1[i - 1]);
    cidx--;
  }
  cidx = (c.size() / 2);
  for (size_t i = d_0.size(); i; --i) {
    c[cidx - 1] += d_0[i - 1];
    cidx--;
  }

  return c;
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
  template std::vector<TYPE> field::precompute_denominator(                    \
      const std::vector<TYPE> &x_values);                                      \
  template std::vector<TYPE> field::mul_karatsuba_arbideg(                     \
      const std::vector<TYPE> &lhs, const std::vector<TYPE> &rhs);             \
  template void field::mul_karatsuba_fixdeg_precondition_poly(                 \
      std::vector<TYPE> &lhs, std::vector<TYPE> &rhs);                         \
  template void field::mul_karatsuba_fixdeg_normalize_poly(                    \
      std::vector<TYPE> &poly, size_t old_size);                               \
  template std::vector<TYPE> field::mul_karatsuba_fixdeg(                      \
      const std::vector<TYPE> &lhs, const std::vector<TYPE> &rhs,              \
      const size_t start_idx, const size_t end_idx);                           \
  template void field::set_x_minus_xi_poly_size(                               \
      std::vector<std::vector<TYPE>> &precomputed_x_minus_xi,                  \
      size_t root_count);                                                      \
  template void field::precompute_x_minus_xi_poly_splits(                      \
      const std::vector<TYPE> &x_values,                                       \
      std::vector<std::vector<TYPE>> &precomputed_x_minus_xi);                 \
  template std::vector<TYPE> field::get_first_n_field_elements(size_t n);      \
  template TYPE field::eval(const std::vector<TYPE> &poly, const TYPE &point); \
  template std::vector<std::vector<TYPE>>                                      \
  field::precompute_lagrange_polynomials_slow(                                 \
      const std::vector<TYPE> &x_values);                                      \
  template std::vector<std::vector<TYPE>>                                      \
  field::precompute_lagrange_polynomials(const std::vector<TYPE> &x_values);   \
  template std::vector<TYPE> field::interpolate_with_recurrsion(               \
      const std::vector<TYPE> &y_values,                                       \
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
