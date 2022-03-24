
#include <array>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <vector>

namespace field {

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

template <typename GF>
std::vector<GF> precompute_numerator_half(const std::vector<GF> &x_values,
                                          bool first_half) {
  size_t values_half_size = x_values.size() / 2;
  std::vector<GF> numerator(values_half_size + 1);
  std::vector<GF> x_half(values_half_size);
  if (first_half) {
    for (size_t j = 0; j < values_half_size; ++j) {
      x_half[j] = x_values[j];
    }
    return build_from_roots(x_half);

  } else {
    for (size_t j = 0; j < values_half_size; ++j) {
      x_half[j] = x_values[j + values_half_size];
    }
    return build_from_roots(x_half);
  }

  // return build_from_roots(x_values);
}

template <typename GF>
std::vector<GF> interpolate_with_seperation(std::vector<GF> x_values,
                                            std::vector<GF> y_values) {
  if (x_values.size() != y_values.size() || y_values.empty() ||
      x_values.empty())
    throw std::runtime_error("invalid sizes for interpolation");

  // Check if value size is power of 2
  if (ceil(log2(x_values.size())) != floor(log2(x_values.size()))) {
    throw std::runtime_error("invalid sizes for interpolation");
  }
  size_t values_size = x_values.size();
  size_t values_half_size = values_size / 2;

  std::vector<GF> numerator_first_half = precompute_numerator_half(
      x_values, true); // Building first numerator MUL_(N/2)+1^N (x-x_i)
  std::vector<GF> numerator_second_half = precompute_numerator_half(
      x_values, false); // Building second numerator MUL_1^N/2 (x-x_i)

  std::vector<GF> x_values_first_half(values_half_size);
  for (size_t i = 0; i < values_half_size; ++i) {
    x_values_first_half[i] = x_values[i]; // Getting first half of X values
  }
  std::vector<GF> y_values_first_half(values_half_size);
  for (size_t i = 0; i < values_half_size; ++i) {
    y_values_first_half[i] = y_values[i]; // Getting first half of Y values
  }

  std::vector<GF> x_values_second_half(values_half_size);
  for (size_t i = 0; i < values_half_size; ++i) {
    x_values_second_half[i] =
        x_values[i + values_half_size]; // Getting second half of X values
  }
  std::vector<GF> y_values_second_half(values_half_size);
  for (size_t i = 0; i < values_half_size; ++i) {
    y_values_second_half[i] =
        y_values[i + values_half_size]; // Getting first half of Y values
  }

  std::cout << "INSIDE - " << values_size << std::endl;
  std::cout << "1" << std::endl;

  // If x.size() != 4, we continue with recurssion
  if (values_size != 4) {

    std::cout << "2" << std::endl;

    // Recurssion return will multiply with the MUL_(N/2)+1^N (x-x_i) part
    std::vector<GF> interpolation_result_first =
        interpolate_with_seperation(x_values_first_half, y_values_first_half);
    std::cout << "FIRST RETURN - " << values_size << std::endl;
    std::vector<GF> results_first(interpolation_result_first.size() +
                                  numerator_second_half.size() - 1);
    results_first += interpolation_result_first * numerator_second_half;

    std::cout << "3" << std::endl;

    // Recurssion return will multiply with the MUL_1^N/2 (x-x_i) part
    std::vector<GF> interpolation_result_second =
        interpolate_with_seperation(x_values_second_half, y_values_second_half);
    std::cout << "SECOND RETURN - " << values_size << std::endl;
    std::vector<GF> results_second(interpolation_result_second.size() +
                                   numerator_first_half.size() - 1);
    results_second += interpolation_result_second * numerator_first_half;

    std::cout << "4" << std::endl;

    std::vector<GF> results_final(results_first.size());
    // Adding the result first and second
    for (size_t i = 0; i < results_first.size(); ++i) {
      results_final[i] = results_first[i] + results_second[i];
    }

    std::cout << "5" << std::endl;

    std::cout << "FINAL RESULT DEGREE - " << results_final.size() << std::endl;
    return results_final;

  }
  // If x.size() = 4 then we apply the fast algorithm
  else {

    std::cout << "6" << std::endl;

    // Building SUM_1^N/2 u_k * a_k * (MUL_1wherei!=k^(N/2) x - x_i )
    std::vector<std::vector<GF>> precomputed_lagrange_polynomials_first =
        precompute_lagrange_polynomials(x_values_first_half);
    std::vector<GF> first_part = interpolate_with_precomputation(
        precomputed_lagrange_polynomials_first, y_values_first_half);
    // Multiplying the res first with the numerator second half
    std::vector<GF> results_first(numerator_second_half.size() +
                                  first_part.size() - 1);
    results_first = numerator_second_half * first_part;

    std::cout << "7" << std::endl;

    // Building SUM_(N/2)+1^N u_k * a_k * (MUL_(N/2)+1wherei!=k^N x - x_i )
    std::vector<std::vector<GF>> precomputed_lagrange_polynomials_second =
        precompute_lagrange_polynomials(x_values_second_half);
    std::vector<GF> second_part = interpolate_with_precomputation(
        precomputed_lagrange_polynomials_second, y_values_second_half);
    // Multiplying the res second with numerator first half
    std::vector<GF> results_second(numerator_first_half.size() +
                                   second_part.size() - 1);
    results_second = numerator_first_half * second_part;

    std::cout << "8" << std::endl;

    std::vector<GF> results_final(results_first.size());
    // Adding results of A and B
    results_final = results_first + results_second;

    std::cout << "results_final" << std::endl;
    for (size_t i = 0; i < results_final.size(); i++) {
      std::cout << results_final[i] << ",";
    }
    std::cout << std::endl;
    std::cout << "RETURN DEGREE - " << results_final.size() << std::endl;
    std::cout << "9" << std::endl;

    return results_final;
  }
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
  template TYPE field::eval(const std::vector<TYPE> &poly, const TYPE &point); \
  template std::vector<std::vector<TYPE>>                                      \
  field::precompute_lagrange_polynomials(const std::vector<TYPE> &x_values);   \
  template std::vector<TYPE> field::precompute_numerator_half(                 \
      const std::vector<TYPE> &x_values, bool first_half);                     \
  template std::vector<TYPE> field::interpolate_with_seperation(               \
      const std::vector<TYPE> x_values, const std::vector<TYPE> y_values);     \
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
