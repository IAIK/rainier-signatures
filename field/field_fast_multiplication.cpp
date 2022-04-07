

// JUST DROPPING FAST MULTIPLICATION STUFF HERE TO DO LATER !!

/*
// Recursive function of FFT
template <typename GF>
void fast_fourier_transform(std::vector<std::complex<GF>> &a, bool is_inverse) {
  const double PI = acos(-1);
  int n = a.size();
  // if input contains just one element
  if (n == 1) {
    return;
  }

  std::vector<std::complex<GF>> a_0(n / 2), a_1(n / 2);
  for (int i = 0; i < n / 2; i++) {
    // even indexed coefficients
    a_0[i] = a[i * 2];
    // odd indexed coefficients
    a_1[i] = a[i * 2 + 1];
  }
  // Recursive call for even indexed coefficients
  fast_fourier_transform(a_0, is_inverse);
  // Recursive call for odd indexed coefficients
  fast_fourier_transform(a_1, is_inverse);

  // Complex nth roots of unity
  double alpha = 2 * PI / n * (is_inverse ? -1 : 1);
  std::complex<GF> w(1), wn(cos(alpha), sin(alpha));

  // For storing values of y0, y1, y2, ..., yn-1.
  std::vector<std::complex<GF>> y(n);
  for (int k = 0; k < n / 2; k++) {
    a[k] = a_0[k] + w * a_1[k];
    a[k + n / 2] = a_0[k] - w * a_1[k];
    if (is_inverse) {
      GF two = GF(2);
      a[k] *= two.inverse();
      a[k + n / 2] *= two.inverse();
    }
    w *= wn;
  }
}

template <typename GF>
void fast_gf2_mul(std::vector<std::complex<GF>> &a_fft,
                  std::vector<std::complex<GF>> &b_fft) {

  fast_fourier_transform(a_fft,
                         false); // coefficient to point-value representation
  fast_fourier_transform(b_fft,
                         false); // coefficient to point-value representation

  size_t combined_size = a_fft.size();
  for (size_t i = 0; i < combined_size; i++) {
    a_fft[i] *= b_fft[i]; // MUL using point-value representation
  }

  fast_fourier_transform(
      a_fft, true); // Interpolate point-value to coeffficient representation
}

TEST_CASE("TEST CENTER", "COMMON") {

  std::vector<field::GF2_128> x =
      field::get_first_n_field_elements<field::GF2_128>(field::ROOT_SIZE - 1);

  std::vector<field::GF2_128> x_poly = field::build_from_roots(x);
  std::vector<field::GF2_128> y_poly = x_poly;

  std::cout << "x_poly" << std::endl;
  for (size_t i = 0; i < x_poly.size(); ++i) {
    std::cout << x_poly[i] << std::endl;
  }
  std::cout << std::endl;

  typedef std::complex<field::GF2_128> cd;
  std::vector<cd> a_fft(field::ROOT_SIZE); // These are the coefficients
  std::vector<cd> b_fft(field::ROOT_SIZE); // These are the coefficients

  for (size_t i = 0; i < field::ROOT_SIZE; ++i) {
    a_fft[i] = x_poly[i];
    b_fft[i] = y_poly[i];
  }

  std::cout << "a_fft" << std::endl;
  for (size_t i = 0; i < a_fft.size(); ++i) {
    std::cout << "(" << a_fft[i].real() << "," << a_fft[i].imag() << ")"
              << std::endl;
  }
  std::cout << std::endl;

  size_t combined_size = a_fft.size() + b_fft.size(); // Combined size after MUL
  a_fft.resize(combined_size);
  b_fft.resize(combined_size);

  // Old slow poly mul
  std::vector<field::GF2_128> result = x_poly * y_poly;
  // Young fast poly mul
  field::fast_gf2_mul(a_fft, b_fft);

  std::cout << "a_fft size - " << std::dec << a_fft.size() << std::endl;
  for (size_t i = 0; i < combined_size; ++i) {
    std::cout << a_fft[i].real() << ",";
  }
  std::cout << std::endl;

  std::cout << "result size - " << std::dec << result.size() << std::endl;
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i] << ",";
  }
  std::cout << std::endl;

  // BENCHMARK("SLOW MULTIPLICATION") { return x * y; };

  // BENCHMARK("FAST MULTIPLICATION") { return field::test_center(a_fft, b_fft);
  // };
}
*/