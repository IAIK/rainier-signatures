#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include "../field.h"
#include "utils.h"

#include <NTL/GF2EX.h>

/*

TEST_CASE("Constructors for GF(2^128)", "[GF2_128]") {
  field::GF2_128 a;
  a.set_coeff(126);
  a.set_coeff(125);
  a.set_coeff(124);
  a.set_coeff(123);
  a.set_coeff(121);
  a.set_coeff(120);
  a.set_coeff(118);
  a.set_coeff(116);
  a.set_coeff(115);
  a.set_coeff(113);
  a.set_coeff(112);
  a.set_coeff(110);
  a.set_coeff(108);
  a.set_coeff(106);
  a.set_coeff(102);
  a.set_coeff(101);
  a.set_coeff(98);
  a.set_coeff(96);
  a.set_coeff(94);
  a.set_coeff(93);
  a.set_coeff(92);
  a.set_coeff(89);
  a.set_coeff(88);
  a.set_coeff(86);
  a.set_coeff(85);
  a.set_coeff(84);
  a.set_coeff(82);
  a.set_coeff(78);
  a.set_coeff(76);
  a.set_coeff(74);
  a.set_coeff(73);
  a.set_coeff(70);
  a.set_coeff(69);
  a.set_coeff(66);
  a.set_coeff(64);
  a.set_coeff(62);
  a.set_coeff(61);
  a.set_coeff(57);
  a.set_coeff(56);
  a.set_coeff(54);
  a.set_coeff(53);
  a.set_coeff(52);
  a.set_coeff(50);
  a.set_coeff(46);
  a.set_coeff(45);
  a.set_coeff(43);
  a.set_coeff(42);
  a.set_coeff(41);
  a.set_coeff(40);
  a.set_coeff(38);
  a.set_coeff(37);
  a.set_coeff(36);
  a.set_coeff(33);
  a.set_coeff(30);
  a.set_coeff(28);
  a.set_coeff(27);
  a.set_coeff(26);
  a.set_coeff(24);
  a.set_coeff(22);
  a.set_coeff(20);
  a.set_coeff(17);
  a.set_coeff(16);
  a.set_coeff(14);
  a.set_coeff(10);
  a.set_coeff(9);
  a.set_coeff(8);
  a.set_coeff(6);
  a.set_coeff(4);
  a.set_coeff(3);
  a.set_coeff(2);
  a.set_coeff(0);

  field::GF2_128 a_int(
      std::array<uint64_t, 2>{0x63746f725d53475d, 0x7b5b546573745665});
  field::GF2_128 a_str("0x7b5b54657374566563746f725d53475d");
  REQUIRE(a == a_int);
  REQUIRE(a == a_str);
}

TEST_CASE("Basic Arithmetic in GF(2^128)", "[GF2_128]") {
  field::GF2_128 zero;
  field::GF2_128 one(1);
  field::GF2_128 x(2);
  field::GF2_128 x_2(4);

  REQUIRE(one + zero == one);
  REQUIRE(zero + one == one);
  REQUIRE(zero + zero == zero);
  REQUIRE(one + one == zero);

  REQUIRE(one * one == one);
  REQUIRE(zero * one == zero);
  REQUIRE(one * zero == zero);
  REQUIRE(zero * zero == zero);

  REQUIRE(x * one == x);
  REQUIRE(x * x == x_2);
}
TEST_CASE("Modular Arithmetic KATs GF(2^128)", "[GF2_128]") {
  field::GF2_128 a, b;
  a.set_coeff(126);
  a.set_coeff(125);
  a.set_coeff(124);
  a.set_coeff(123);
  a.set_coeff(121);
  a.set_coeff(120);
  a.set_coeff(118);
  a.set_coeff(116);
  a.set_coeff(115);
  a.set_coeff(113);
  a.set_coeff(112);
  a.set_coeff(110);
  a.set_coeff(108);
  a.set_coeff(106);
  a.set_coeff(102);
  a.set_coeff(101);
  a.set_coeff(98);
  a.set_coeff(96);
  a.set_coeff(94);
  a.set_coeff(93);
  a.set_coeff(92);
  a.set_coeff(89);
  a.set_coeff(88);
  a.set_coeff(86);
  a.set_coeff(85);
  a.set_coeff(84);
  a.set_coeff(82);
  a.set_coeff(78);
  a.set_coeff(76);
  a.set_coeff(74);
  a.set_coeff(73);
  a.set_coeff(70);
  a.set_coeff(69);
  a.set_coeff(66);
  a.set_coeff(64);
  a.set_coeff(62);
  a.set_coeff(61);
  a.set_coeff(57);
  a.set_coeff(56);
  a.set_coeff(54);
  a.set_coeff(53);
  a.set_coeff(52);
  a.set_coeff(50);
  a.set_coeff(46);
  a.set_coeff(45);
  a.set_coeff(43);
  a.set_coeff(42);
  a.set_coeff(41);
  a.set_coeff(40);
  a.set_coeff(38);
  a.set_coeff(37);
  a.set_coeff(36);
  a.set_coeff(33);
  a.set_coeff(30);
  a.set_coeff(28);
  a.set_coeff(27);
  a.set_coeff(26);
  a.set_coeff(24);
  a.set_coeff(22);
  a.set_coeff(20);
  a.set_coeff(17);
  a.set_coeff(16);
  a.set_coeff(14);
  a.set_coeff(10);
  a.set_coeff(9);
  a.set_coeff(8);
  a.set_coeff(6);
  a.set_coeff(4);
  a.set_coeff(3);
  a.set_coeff(2);
  a.set_coeff(0);

  b.set_coeff(126);
  b.set_coeff(123);
  b.set_coeff(118);
  b.set_coeff(117);
  b.set_coeff(115);
  b.set_coeff(112);
  b.set_coeff(109);
  b.set_coeff(107);
  b.set_coeff(102);
  b.set_coeff(100);
  b.set_coeff(97);
  b.set_coeff(96);
  b.set_coeff(94);
  b.set_coeff(93);
  b.set_coeff(91);
  b.set_coeff(86);
  b.set_coeff(85);
  b.set_coeff(80);
  b.set_coeff(78);
  b.set_coeff(77);
  b.set_coeff(76);
  b.set_coeff(75);
  b.set_coeff(72);
  b.set_coeff(69);
  b.set_coeff(67);
  b.set_coeff(64);
  b.set_coeff(62);
  b.set_coeff(60);
  b.set_coeff(59);
  b.set_coeff(57);
  b.set_coeff(56);
  b.set_coeff(54);
  b.set_coeff(50);
  b.set_coeff(49);
  b.set_coeff(48);
  b.set_coeff(46);
  b.set_coeff(45);
  b.set_coeff(44);
  b.set_coeff(42);
  b.set_coeff(40);
  b.set_coeff(38);
  b.set_coeff(37);
  b.set_coeff(34);
  b.set_coeff(32);
  b.set_coeff(30);
  b.set_coeff(29);
  b.set_coeff(28);
  b.set_coeff(25);
  b.set_coeff(22);
  b.set_coeff(21);
  b.set_coeff(19);
  b.set_coeff(18);
  b.set_coeff(17);
  b.set_coeff(16);
  b.set_coeff(14);
  b.set_coeff(13);
  b.set_coeff(11);
  b.set_coeff(10);
  b.set_coeff(9);
  b.set_coeff(6);
  b.set_coeff(4);
  b.set_coeff(3);
  b.set_coeff(2);
  b.set_coeff(0);
  // a = 0x7b5b54657374566563746f725d53475d
  // b = 0x48692853686179295b477565726f6e5d
  field::GF2_128 a_int("0x7b5b54657374566563746f725d53475d"),
      b_int("0x48692853686179295b477565726f6e5d");
  REQUIRE(a == a_int);
  REQUIRE(b == b_int);

  // a*b = 0x040229a09a5ed12e7e4e10da323506d2
  // a*a = 0xdc56c143eb2f71f9f8c0f27ded737090
  // b*b = 0x408f5d5028d9e18058ce78d8de11282e
  field::GF2_128 ab("0x040229a09a5ed12e7e4e10da323506d2");
  field::GF2_128 a_2("0xdc56c143eb2f71f9f8c0f27ded737090");
  field::GF2_128 b_2("0x408f5d5028d9e18058ce78d8de11282e");
  field::GF2_128 ab_calc = a_int * b_int;
  REQUIRE(ab_calc == ab);
  REQUIRE(a * a == a_2);
  REQUIRE(b * b == b_2);

  BENCHMARK("GF Addition") { return a + b; };
  BENCHMARK("GF Multiplication") { return a * b; };
}

TEST_CASE("NTL to_bytes = custom to_bytes GF(2^128)", "[field]") {
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_128);
  field::GF2_128 a, b;
  a.set_coeff(103);
  a.set_coeff(99);
  a.set_coeff(70);
  a.set_coeff(40);
  a.set_coeff(31);
  a.set_coeff(29);
  a.set_coeff(28);
  a.set_coeff(24);
  a.set_coeff(23);
  a.set_coeff(21);
  a.set_coeff(19);
  a.set_coeff(15);
  a.set_coeff(14);
  a.set_coeff(9);
  a.set_coeff(8);
  a.set_coeff(0);

  b.set_coeff(29);
  b.set_coeff(27);
  b.set_coeff(26);
  b.set_coeff(25);
  b.set_coeff(20);
  b.set_coeff(17);
  b.set_coeff(14);
  b.set_coeff(11);
  b.set_coeff(10);
  b.set_coeff(5);
  b.set_coeff(3);
  b.set_coeff(2);
  GF2X c, d;
  SetCoeff(c, 103);
  SetCoeff(c, 99);
  SetCoeff(c, 70);
  SetCoeff(c, 40);
  SetCoeff(c, 31);
  SetCoeff(c, 29);
  SetCoeff(c, 28);
  SetCoeff(c, 24);
  SetCoeff(c, 23);
  SetCoeff(c, 21);
  SetCoeff(c, 19);
  SetCoeff(c, 15);
  SetCoeff(c, 14);
  SetCoeff(c, 9);
  SetCoeff(c, 8);
  SetCoeff(c, 0);
  GF2E c_e = conv<GF2E>(c);

  SetCoeff(d, 29);
  SetCoeff(d, 27);
  SetCoeff(d, 26);
  SetCoeff(d, 25);
  SetCoeff(d, 20);
  SetCoeff(d, 17);
  SetCoeff(d, 14);
  SetCoeff(d, 11);
  SetCoeff(d, 10);
  SetCoeff(d, 5);
  SetCoeff(d, 3);
  SetCoeff(d, 2);
  GF2E d_e = conv<GF2E>(d);

  const GF2X &poly_rep_c = rep(c_e);
  std::vector<uint8_t> buffer_c(field::GF2_128::BYTE_SIZE);
  BytesFromGF2X(buffer_c.data(), poly_rep_c, buffer_c.size());
  const GF2X &poly_rep_d = rep(d_e);
  std::vector<uint8_t> buffer_d(field::GF2_128::BYTE_SIZE);
  BytesFromGF2X(buffer_d.data(), poly_rep_d, buffer_d.size());

  std::vector<uint8_t> buffer_a(field::GF2_128::BYTE_SIZE);
  a.to_bytes(buffer_a.data());
  std::vector<uint8_t> buffer_b(field::GF2_128::BYTE_SIZE);
  b.to_bytes(buffer_b.data());
  REQUIRE(buffer_a == buffer_c);
  REQUIRE(buffer_b == buffer_d);
}
TEST_CASE("NTL to custom conversion GF(2^128)", "[GF2_128]") {
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_128);
  field::GF2_128 a, b;
  a.set_coeff(31);
  a.set_coeff(29);
  a.set_coeff(28);
  a.set_coeff(24);
  a.set_coeff(23);
  a.set_coeff(21);
  a.set_coeff(19);
  a.set_coeff(15);
  a.set_coeff(14);
  a.set_coeff(9);
  a.set_coeff(8);
  a.set_coeff(0);

  b.set_coeff(29);
  b.set_coeff(27);
  b.set_coeff(26);
  b.set_coeff(25);
  b.set_coeff(20);
  b.set_coeff(17);
  b.set_coeff(14);
  b.set_coeff(11);
  b.set_coeff(10);
  b.set_coeff(5);
  b.set_coeff(3);
  b.set_coeff(2);

  field::GF2_128 ab = a * b;
  GF2E a_ntl = utils::custom_to_ntl(a);
  GF2E ab_ntl = utils::custom_to_ntl(ab);
  GF2E b_ntl = ab_ntl / a_ntl;
  field::GF2_128 b2 = utils::ntl_to_custom<field::GF2_128>(b_ntl);
  REQUIRE(b == b2);
}
TEST_CASE("Custom fast inverse GF(2^128)", "[GF2_128]") {
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_128);
  field::GF2_128 a;
  a.set_coeff(31);
  a.set_coeff(29);
  a.set_coeff(28);
  a.set_coeff(24);
  a.set_coeff(23);
  a.set_coeff(21);
  a.set_coeff(19);
  a.set_coeff(15);
  a.set_coeff(14);
  a.set_coeff(9);
  a.set_coeff(8);
  a.set_coeff(0);

  for (size_t i = 0; i < 1; i++) {
    field::GF2_128 b = a.inverse();
    field::GF2_128 c = field::GF2_128("0x8368bf5aa4edd94e58692b13a40f3197");
    REQUIRE(b == c);
  }
  BENCHMARK("GF inverse") { return a.inverse(); };
}
TEST_CASE("Custom slow inverse GF(2^128)", "[GF2_128]") {
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_128);
  field::GF2_128 a;
  a.set_coeff(31);
  a.set_coeff(29);
  a.set_coeff(28);
  a.set_coeff(24);
  a.set_coeff(23);
  a.set_coeff(21);
  a.set_coeff(19);
  a.set_coeff(15);
  a.set_coeff(14);
  a.set_coeff(9);
  a.set_coeff(8);
  a.set_coeff(0);

  for (size_t i = 0; i < 1; i++) {
    field::GF2_128 b = a.inverse_slow();
    field::GF2_128 c = field::GF2_128("0x8368bf5aa4edd94e58692b13a40f3197");
    REQUIRE(b == c);
  }
  BENCHMARK("GF inverse") { return a.inverse_slow(); };
}
TEST_CASE("NTL inverse == custom inverse GF(2^128)", "[GF2_128]") {
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_128);
  field::GF2_128 a;
  a.set_coeff(31);
  a.set_coeff(29);
  a.set_coeff(28);
  a.set_coeff(24);
  a.set_coeff(23);
  a.set_coeff(21);
  a.set_coeff(19);
  a.set_coeff(15);
  a.set_coeff(14);
  a.set_coeff(9);
  a.set_coeff(8);
  a.set_coeff(0);

  field::GF2_128 b = a.inverse();
  field::GF2_128 c =
      utils::ntl_to_custom<field::GF2_128>(inv(utils::custom_to_ntl(a)));
  // std::cout << utils::custom_to_ntl(a) << ", " << utils::custom_to_ntl(b)
  //<< ", " << utils::custom_to_ntl(c) << "\n";
  // std::cout << utils::custom_to_ntl(a * b) << ", "
  //<< utils::custom_to_ntl(a * c) << ", "
  //<< utils::custom_to_ntl(a) * utils::custom_to_ntl(c) << "\n";
  REQUIRE(b == c);
  REQUIRE(a * b == field::GF2_128(1));
  BENCHMARK("GF inverse") { return a.inverse(); };
}
TEST_CASE("NTL interpolation == custom interpolation GF(2^128)", "[GF2_128]") {
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_128);

  std::vector<field::GF2_128> a =
      field::get_first_n_field_elements<field::GF2_128>(100);
  vec_GF2E b = utils::get_first_n_field_elements(100);
  for (size_t i = 0; i < 100; i++) {
    REQUIRE(a[i] == utils::ntl_to_custom<field::GF2_128>(b[i]));
  }
  std::vector<field::GF2_128> a_from_roots = field::build_from_roots(a);
  GF2EX b_from_roots = BuildFromRoots(b);
  REQUIRE(a_from_roots.size() == (size_t)b_from_roots.rep.length());
  for (size_t j = 0; j < a_from_roots.size(); j++) {
    REQUIRE(a_from_roots[j] ==
            utils::ntl_to_custom<field::GF2_128>(b_from_roots[j]));
  }

  std::vector<std::vector<field::GF2_128>> a_lag =
      field::precompute_lagrange_polynomials(a);
  std::vector<GF2EX> b_lag = utils::precompute_lagrange_polynomials(b);

  REQUIRE(a_lag.size() == b_lag.size());
  for (size_t i = 0; i < a_lag.size(); i++) {
    REQUIRE(a_lag[i].size() == (size_t)b_lag[i].rep.length());
    for (size_t j = 0; j < a_lag[i].size(); j++) {
      REQUIRE(a_lag[i][j] == utils::ntl_to_custom<field::GF2_128>(b_lag[i][j]));
    }
  }

  BENCHMARK("Lagrange Poly Precomputation") {
    return field::precompute_lagrange_polynomials(a);
  };
  BENCHMARK("Lagrange Poly Interpolation") {
    return field::interpolate_with_precomputation(a_lag, a);
  };
}

*/

TEST_CASE("Fast interpolation GF(2^128)", "[GF2_128]") {
  std::vector<field::GF2_128> x =
      field::get_first_n_field_elements<field::GF2_128>(2);
  std::vector<field::GF2_128> y =
      field::get_first_n_field_elements<field::GF2_128>(2);
  std::vector<std::vector<field::GF2_128>> x_lag =
      field::precompute_lagrange_polynomials(x);
  std::vector<field::GF2_128> result =
      field::interpolate_with_precomputation(x_lag, y);

  std::vector<field::GF2_128> x_fast =
      field::get_first_n_field_elements<field::GF2_128>(2);
  std::vector<field::GF2_128> y_fast =
      field::get_first_n_field_elements<field::GF2_128>(2);
  std::vector<field::GF2_128> result_fast =
      field::interpolate_with_seperation(x_fast, y_fast);

  std::cout << "SLOW INTERP RESULT" << std::endl;
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << result[i] << ",";
  }
  std::cout << std::endl;

  std::cout << "FAST INTERP RESULT" << std::endl;
  for (size_t i = 0; i < result_fast.size(); i++) {
    std::cout << result_fast[i] << ",";
  }

  REQUIRE(result.size() == result_fast.size());

  REQUIRE(result == result_fast);
}

/*
TEST_CASE("NTL dot product == custom GF(2^128)", "[GF2_128]") {

  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_128);
  std::vector<field::GF2_128> a =
      field::get_first_n_field_elements<field::GF2_128>(100);
  std::vector<field::GF2_128> b =
      field::get_first_n_field_elements<field::GF2_128>(200);
  b.erase(b.begin(), b.begin() + 100);

  vec_GF2E a_ntl = utils::get_first_n_field_elements(200);
  vec_GF2E b_ntl;
  b_ntl.SetLength(100);
  for (size_t i = 0; i < 100; i++)
    b_ntl[i] = a_ntl[100 + i];
  a_ntl.SetLength(100);

  field::GF2_128 result = dot_product(a, b);
  GF2E result_ntl;
  NTL::InnerProduct(result_ntl, a_ntl, b_ntl);
  REQUIRE(result == utils::ntl_to_custom<field::GF2_128>(result_ntl));
}

TEST_CASE("Matmul and Transposed Matmul have same result GF(2^128)",
          "[GF2_128]") {
  alignas(32) constexpr static std::array<uint64_t, 2> m1[128] = {
      {{0x17ac9f98c8ce128d, 0x90a8ece6d2c5f35f}},
      {{0x88ebc82715f1c6ba, 0x63752b5d28cb21ff}},
      {{0x9ab0e58883f54f2c, 0x5eb03a6cac12892d}},
      {{0x96fdc8e7a1d2354e, 0x5b2904611e00358f}},
      {{0x31cc6a8201511e4f, 0x2ba15076e439038f}},
      {{0x2b806e7b4808b44f, 0xa8caefcb7ca40112}},
      {{0x2920a0868145f039, 0x5007502410d1db9c}},
      {{0xd50c91941a3dea5c, 0x9634561cbe67716a}},
      {{0x5502d1a6cbcfb4f8, 0x883ffb32ff8413e1}},
      {{0x7b0ac8ff1abe6c6f, 0x2223ef19314728b8}},
      {{0x951cbd85fdf20821, 0x9e24a64b07e58e03}},
      {{0x1472caced3157923, 0xaea9b2859c7a58bc}},
      {{0xe7d622bd4715a9b1, 0xc4812a2e66f56fd4}},
      {{0x8362ca2cbcf6d898, 0x21771040193f8717}},
      {{0x8063c141e97998f5, 0xbba326eda3100097}},
      {{0x9295f585b676d59, 0xabdde1d4ae2a3f63}},
      {{0xb8083ecda8a4a7d8, 0xa4fb09c7d1fc9d4a}},
      {{0xcce70915a5937d08, 0x22a3e307d3baa6b9}},
      {{0xa98686f6136f08eb, 0x8215b4adfcd0881b}},
      {{0x252fb3910d8e342e, 0xbc9c73c503744226}},
      {{0xf338be296147cfdc, 0x2f24c31e4ddcc846}},
      {{0x3c9fa9dcc4ba1add, 0xc27669314cac743d}},
      {{0xbebb96c3df3650f4, 0xd549899b7a1b0246}},
      {{0x4755a727ce943e04, 0x9b265ae32ae7c0d2}},
      {{0x15f7a16ad6e98e16, 0xf5a77d5a9fd86b16}},
      {{0x94644357ab7924ba, 0x299675378b7a9f6a}},
      {{0xe3bf0e4550f0f74c, 0xb304d13ba69b2b84}},
      {{0xd0eeefa17abd4811, 0x3c9c02cce4afee78}},
      {{0xc07ec4f5ac55ca70, 0x2ade58f121175290}},
      {{0xbe4afde8c6c79bf2, 0x69943d5e9268734c}},
      {{0xad57791e0e4bbc35, 0xb5d9899c0717115f}},
      {{0x7aaecde97d2e99f5, 0x7803e4cae9c9d586}},
      {{0x3bdae6ecca50d896, 0xabf07401f9a37d4}},
      {{0xd678da6dad9ca2c6, 0x4fe46be9e4b7b734}},
      {{0xa5b05d129564be01, 0xe531af7f11c6fa0c}},
      {{0xc76ea6c762df8373, 0xf17689f8d623ac63}},
      {{0x23be7d874c957472, 0xfb325ad872654e7b}},
      {{0xb040f411ad7f8c93, 0x1910929b681859ca}},
      {{0xf757649527eedf38, 0x53b997ff27ce335f}},
      {{0x151ac35c4d487faf, 0xc12a280b68c37152}},
      {{0xe19d19e1a047376a, 0xf600bb6f7c5dd74}},
      {{0x1207b78cbbd93911, 0x78a0fc32966e0385}},
      {{0x87f69340d91432fe, 0xb97947faca9e0111}},
      {{0x9a9b2e6ae6c7cd04, 0x591ea4bb5b21adda}},
      {{0x3794fdf8f3664e53, 0x5054991f0f3e30a5}},
      {{0xb47805e690dbd7f6, 0x513112904cbbc211}},
      {{0xaa06292cc449ef16, 0x42a51cbe1cc157fa}},
      {{0x44c46c615d375558, 0x89ba01f4c3d49b12}},
      {{0xe1d5f5ac54b9f794, 0x7a23a7074bc92431}},
      {{0xd6784c1b4cb9cf87, 0x3106d1ba95b56f4}},
      {{0xf3a4635ca2f4ab4f, 0xd9d551cfe895ad67}},
      {{0xf7a1ad14a37402ee, 0x19bccb624e7c32ff}},
      {{0x791b58004bad97f1, 0xc00f1902a1f2ec37}},
      {{0x4b4a76eaec4d3db9, 0xbeb56adb11b51844}},
      {{0x97d0231da0b0b0ba, 0xae03b5018224f841}},
      {{0x805d161cd514c4a4, 0x294f1e558d09fde0}},
      {{0xdba675be2a901544, 0x2a8ed7967b7b685d}},
      {{0xd8e97127af98d957, 0x8df906e5f61619f6}},
      {{0x401641b434f62c77, 0xb44011c9ab812675}},
      {{0xd0efc77be26ea5eb, 0x4ceba4c14fb924e8}},
      {{0x5678c1b5e8d3e55e, 0x99babbaa05c284ac}},
      {{0x6c6aa09a94b87e07, 0xf3e9c7bf660de662}},
      {{0x40f8e958bce39d62, 0x6a5ee4dd5be8c8a8}},
      {{0xe68a1d0b2982f6bf, 0xcb5705b2ca3da39e}},
      {{0xc2c52e3d96b39512, 0xf0f52571c2229df8}},
      {{0x9fe7de4c36ff49c, 0x68da742712d51f38}},
      {{0xa9c9dc31395cf250, 0xe5333c5b1cb0361c}},
      {{0xc678148b2a0781ee, 0x3141c62d32ac7102}},
      {{0xa76bd5e1bf97abc0, 0x4eb2e82a361096c2}},
      {{0x1fa345a6106be1c3, 0x8c48e1146fcd5f4b}},
      {{0xd5f279e907351518, 0x97c5c30f25e18272}},
      {{0x460d340fd29b3354, 0x948108ccec138c79}},
      {{0x87f19c59114bc886, 0xdad7a695e0c876bb}},
      {{0xdc358c2cc7b36483, 0xbb6497c6d3ff1561}},
      {{0x4842491f431b3f00, 0xc2fa8cd2517e7142}},
      {{0x8d6b25a7ca346f7f, 0x9edea5af485971f8}},
      {{0xfb496477d31db721, 0x88bac8e374a1ed82}},
      {{0x12ea001c22833f3a, 0xc95836025f325269}},
      {{0x3e1222764fc986b3, 0x7e1ca7ddd9f5d616}},
      {{0x66ff0db0559f5aba, 0x6eed0a70621d1ff2}},
      {{0x5262026cdf4128ba, 0xadbab5f01a77cd24}},
      {{0x8117f8aed99905b3, 0x4b2c7061023a901a}},
      {{0x7ee68ecf8ba10865, 0x2852e829dde347a9}},
      {{0x17414b8a5432ffdb, 0x6525d3984d29af61}},
      {{0x368caeb137f64e2c, 0xf1d8b9fe78d538b}},
      {{0xb84d1960637962a0, 0xeb760ffa1f052063}},
      {{0x40068e0949da49fc, 0x86ea3249de54395b}},
      {{0xc88473c4720d3753, 0xe3b662d24b4a1914}},
      {{0xe7f0b44d35980297, 0xa3773ac63b4ffd99}},
      {{0xd23b04ad8a0e0f1b, 0xe55cc31909f90893}},
      {{0xf4eb9396dbcfd490, 0x42021ba7ffccd7fd}},
      {{0x8bc6259008ed2737, 0xe81d49902f52db33}},
      {{0x9cef40c7f2c12208, 0x65719d18de807510}},
      {{0x73319b5b26897dcc, 0x8021bbaaa28f6351}},
      {{0xa731adaa9a5ef72d, 0xb3fa5e8d221b5c53}},
      {{0xd3bb9f92bebfdcd, 0x926e67808242c752}},
      {{0x436a3644c31f7f15, 0xd89d8678f8a7d18}},
      {{0x9d425f9f4e0259d, 0x3b3c900c0fc5c604}},
      {{0x3fdde57bf6b9193a, 0x975b589f14f7095c}},
      {{0x15703c6427ddec62, 0xe842873d6a43b579}},
      {{0x14486ab7e4a2f723, 0x87b27ed19e0e88eb}},
      {{0x7d5518573923dd7a, 0xe702b92ef9f510d1}},
      {{0xc0c932581f6d495f, 0x32fdf46880280b5b}},
      {{0xcb8e3c58a98bc307, 0x62e1edcb9c4c653a}},
      {{0xee576ae3d752ac8, 0x58ab32d6fdb0c654}},
      {{0x4ba1cf3500bef78a, 0xf210700d3d50b6a6}},
      {{0xd3ff30faf55c6c30, 0x1519f46412d678b2}},
      {{0xbd142fd162903960, 0x1ee19a1d41d6beaf}},
      {{0xa62342f2a6e4a28d, 0xff2280fcdb8f51e3}},
      {{0xb4201fed85d80f3b, 0x4f71afd6e086a601}},
      {{0x12458667e2964e13, 0xf1b57d173060ca5f}},
      {{0x9def2b7fb1ffc03b, 0x841791aad69b4332}},
      {{0xbec7019891d8f2e7, 0xa404dd97ad4e2416}},
      {{0x250a12889ab81f1b, 0xad3b4edcb3bc9c9d}},
      {{0xb2172de68dd3b03f, 0xc7c875007cce7bb1}},
      {{0xafa21c5e53a4f05f, 0x60ff6eb34ba31a55}},
      {{0xfed07bb816011f46, 0xa78b28c29a9f3142}},
      {{0x57289a54a4b55023, 0x49594351b0652280}},
      {{0x7b2c072a73bf1475, 0x80b8ef6be79493ca}},
      {{0x9d2f2a034c30be45, 0x1044c59ae04d1741}},
      {{0x29b19b4d370f6849, 0x61e60d1b28fcd1a3}},
      {{0x871b25ffdabcefbd, 0xd4f4617fd9f7ac39}},
      {{0x23f85d6b903498a2, 0xe34cf4e39edc2b4e}},
      {{0x6213d79ac853e08f, 0x4bbf90b0dbbb9031}},
      {{0x8400e45335f6aad4, 0x9fd3e070c1524665}},
      {{0xdfd377fcf66ec92d, 0xb8a688e086d9f362}},
      {{0x63b48ec07ba8f23, 0x94600442dd584c5d}},
      {{0x2064949e75839ed0, 0xcbf0171494c5478}},
  };

  alignas(32) constexpr static std::array<uint64_t, 2> m1_transposed[128] = {
      {{0xae3612acc824de71, 0x6beff0d3cb8e5a20}},
      {{0xfe4e75bb230c0a3a, 0x4c3fe2fc0b8beb29}},
      {{0xb78f6c83c5f842bd, 0x3add10c3e954098a}},
      {{0x986c85c0063fa3ff, 0x2b0eb366f259a84a}},
      {{0x9671f679fb71f1c2, 0x924ee4670fcbe8c7}},
      {{0xccf825d8f24c5f46, 0x6665ac3c4877f808}},
      {{0x5f1cb51ab475c3b8, 0x91d90968a0cc08bc}},
      {{0x88fb24a3a2757103, 0x9e011302a56bc33a}},
      {{0x5b37ebc8a413980c, 0x62122af7eaca3cf9}},
      {{0xa01f75ce35b10097, 0xd29373915bb8fc94}},
      {{0xfdb3f9f4479b833e, 0xc2d2663bee9a7e43}},
      {{0x66265ae5f9b6fe94, 0xf7926d6da25dad10}},
      {{0xe371a7d5e4ea6979, 0x84ff0a35e488b4c7}},
      {{0xbc654796468b9be8, 0x1b8d1f1bf8a93eb6}},
      {{0xb283f8d11c52aac6, 0x2b29c6f9e4788b26}},
      {{0xdad7686ff51171e2, 0xfe8d92b8c408513f}},
      {{0x5033eb387b16d9d6, 0x897481edbca7f7fb}},
      {{0xdc00b968e07ea709, 0xf944c2b1c658a7bb}},
      {{0xcbc9d7eb8ddbbc5, 0x3768d7494e90985e}},
      {{0x2a3362eacb2c43a1, 0x6343a6cdefe2d5a6}},
      {{0x37cfa63b1ee27e9e, 0x5ee7ef0d417a9ed5}},
      {{0x6c5f90648f65e686, 0x76ea9376883c0a63}},
      {{0x5c2c7bed7714e55f, 0x3805b54adc714126}},
      {{0xf7572a5a2dab270f, 0xd26ffa9ebd56e291}},
      {{0x829896e6825edd5e, 0xd14da5e98577d756}},
      {{0xb1c1a496bc49b84, 0x635a584df6b57edb}},
      {{0x66a3c8f6f1ea3402, 0xf1b4355e2119c251}},
      {{0xd33286b3dac9e7a1, 0xa8601e0ce47481c}},
      {{0x6481b6048d44ae82, 0xb75b8566559b91b5}},
      {{0xdf6c1b6a9a136408, 0xb160ddbeb1b0201c}},
      {{0x18b3dc99adf0dd21, 0xaac84c1714ebde82}},
      {{0x7aec7f2733e36d4d, 0x2e27f49756071a93}},
      {{0x9a42817a9edb562a, 0x1780ea36b3541ddd}},
      {{0xab22281c43c40b7a, 0x9eccd534740e5ca8}},
      {{0x17cd62db56a73fca, 0xe32ce33917877ea3}},
      {{0xe9e75a83e131ba25, 0xef5ba5c6e34f27c9}},
      {{0x7dce10e4522e92a1, 0xba399ef6ac10f505}},
      {{0x1f21f903b994332a, 0x6654f71ec233da77}},
      {{0x4824bd8bb765ca28, 0x772cfcefb1a55152}},
      {{0x35213359b86d1fdd, 0xea173d12de9e887a}},
      {{0xdf4d7794ebaac585, 0x2f55aa06eca88c72}},
      {{0x8e40e8b0eddb831, 0x29f2fb5124dd4001}},
      {{0x89abba7dbcd58425, 0xbe4c6b8f4b549bbf}},
      {{0xc01ad916ec33ae3b, 0x45bcaab8e07e8747}},
      {{0x83b1173660598581, 0xad3a25e9a5a201de}},
      {{0x636dda7969b91474, 0x32948ddfc99258c3}},
      {{0x5f3790f7fa00eb3e, 0x7c101314108a1476}},
      {{0x780916abb9fc6fcf, 0x99204204e5560314}},
      {{0xa990b4045eac00a, 0x6b85d764f62a9bb5}},
      {{0xad304ed9fd6e7b02, 0x6a8f94819e47ec72}},
      {{0xd85d758dfae1499, 0x80c5cda618f68283}},
      {{0xfab2299bbc79869b, 0x46e284d59630b89e}},
      {{0x54d33dd755f01c0c, 0x6f140c2ee302c34a}},
      {{0x7b0e241e9f5ae84f, 0xc5e8b709f705ab7a}},
      {{0x7ae3a46b7b82781a, 0xa411c57f1d2dbd5f}},
      {{0xcb4d9d158d66103f, 0x251987c61d94a167}},
      {{0x17d15dd459cb7f1, 0x27ea8eafe90a1976}},
      {{0x916e5e5ba4d0322d, 0x6e7d57856b1df1b9}},
      {{0xb04ab4ce63ea1d89, 0x72bbb93cd51ccbf8}},
      {{0x23304801e0678266, 0x21d98ba698a45e26}},
      {{0x1b5e3ae3ab710f9d, 0x20f5ec3c363d7260}},
      {{0xa01d7175e47d1270, 0x8d5f38246534d014}},
      {{0xff3f814a9c921380, 0x287006e127c596c9}},
      {{0x8bcf6d6e7e57748e, 0x329dbcc05fa21b5d}},
      {{0x55d36584026e51f, 0x5b8e78786f7c23a0}},
      {{0xa21cc8f8c3dde4bb, 0x2551ded0ca72d578}},
      {{0x973e1347e578785f, 0x540b4b0604814004}},
      {{0xd90848746a270adf, 0xc64248dd055629a7}},
      {{0x871bedd359a67a63, 0xca0fc5edffc2c9c7}},
      {{0x7e9f511a0a2a8b86, 0xbb049e980c2dabc3}},
      {{0x2fee49f96ad19183, 0xf4d8517ce468aef1}},
      {{0xda8a5a2194825b5a, 0x1661e3007149911}},
      {{0x8284cfe3e701b1ff, 0x25d490cdbddd9e2b}},
      {{0xa40ae2573f4ab551, 0x34eceb42ac1ce176}},
      {{0x3c97491b8a23b408, 0xd2832b8bd50dd3b7}},
      {{0x43f4893c0f159e44, 0x460e4c554bc990a3}},
      {{0x2ead1e7f22189c9, 0xa9de1e295dd2ef3f}},
      {{0xaddd18cf2d22928b, 0x26352e8931681d0c}},
      {{0x61d261b4b9b818c1, 0xf104d583fd157d28}},
      {{0xf0d4a90e8a972445, 0x2b426b1a8d0b50d1}},
      {{0xada7699adcc036d3, 0x2ab8902e633ddae2}},
      {{0x131236cf5ec2aa86, 0x1a1dbc1de9872681}},
      {{0xa26c975658b937a1, 0x87f73cb62571c62a}},
      {{0xe98b3661af73a812, 0xed9790d1679a8f28}},
      {{0x8b3eb423575f7854, 0x7f528f244a43ee96}},
      {{0xc9783a1a2aabbcb0, 0xb2a4164020f764d}},
      {{0x511bc3d4a39d1ec3, 0xf7a54eae8fc54f62}},
      {{0x5c35e5c78db71563, 0x2f5ebd273614536e}},
      {{0x5db39945d31b6700, 0xda4b1b230fbc6660}},
      {{0xef499f5967cad589, 0x2c5a941bfdf3a23b}},
      {{0x3a88734b4d349dbc, 0x644583971c7c30f4}},
      {{0xcd8f7ca183f4a9ae, 0xcf1d13bb1fed68a4}},
      {{0x43204b1d21472be9, 0x4e36d7b41565761e}},
      {{0x271601f29cc4d3b6, 0x1e763286d1091f8}},
      {{0xeb0dadba88771131, 0xdaccb92814dcffa1}},
      {{0x86d6870aaf07c995, 0x7ef3b1f1b4544381}},
      {{0x6ee718e616ef4e2a, 0x87694a9d4656594f}},
      {{0xb13f5fe4a7d31531, 0x47d9e1a525b03e56}},
      {{0x6385d1446a1fd8d7, 0x2037f2f45104bea}},
      {{0x74265cfeed5456a6, 0x3c29aee727c48dc}},
      {{0xe1a2ff7c77708392, 0x9bab791c1ab9c525}},
      {{0xb208cf4e16a4515d, 0xbe4894692427981b}},
      {{0x4eac845fb989e43f, 0xf67235d101e3d685}},
      {{0xff24ed7ad8cdc821, 0x2c9bb194edb95f80}},
      {{0xb55f954f677b8322, 0x83e5e0a8be394a61}},
      {{0x33a92577089a5fa6, 0x6a2918e7f8e348}},
      {{0xebc34e45a30446a9, 0x45cf64d8d0216f0f}},
      {{0x10ba539e71e11327, 0x215b68b57d349494}},
      {{0x15d47270378c29d4, 0xc05cf77754b2206}},
      {{0x58630a86a32edf27, 0x165c67f0a1c76937}},
      {{0x612e061297ba83f1, 0x16ef46d5ca8e107a}},
      {{0x79491a6cc4568f21, 0x3cc1bceb321d5f78}},
      {{0xaaf56445c147fb5a, 0x983aedc5391881cd}},
      {{0xd9d1889993a36360, 0xb91a913cc5e51d16}},
      {{0xc1bc580b3fbca5c2, 0xaf89c0428bbacb41}},
      {{0x7b988cc158498929, 0x8c7e0547ca53fc22}},
      {{0xd22ebc7d7a2da186, 0x9a6ae6565bb57d17}},
      {{0x3a29e7df01b36f9f, 0xeb4a79d2f1eb9615}},
      {{0xee84150a5061a022, 0x57ac28ccd364af6b}},
      {{0x3b2cc2437b0bd835, 0xbb5c49d140c19dd3}},
      {{0xb28eadfe67d0e01a, 0x1d36743753bb224c}},
      {{0xe163415314b6ce9e, 0x1c143af6c5f2cf50}},
      {{0xe60010649591c84, 0xd217bc351259c8f4}},
      {{0xdbed8f33ba98cd3c, 0xb822390b0837fb32}},
      {{0x342d3e78cdc844cd, 0x72805f46c0004bc9}},
      {{0x65e1061cff1bea32, 0x251b52ea5badc20f}},
      {{0xe8157adea160104e, 0xf2c73a81eaae517}},
      {{0xb674849c45eddda1, 0x7657d23cebe13fe5}},
  };
  field::GF2_128 v("0x0123456789abcdeffedcba9876543210");
  field::GF2_128 result = v.multiply_with_GF2_matrix(m1);
  field::GF2_128 result_transposed =
      v.multiply_with_transposed_GF2_matrix(m1_transposed);
  REQUIRE(result == result_transposed);
}

*/