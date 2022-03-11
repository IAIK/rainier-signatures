#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../field.h"
#include "utils.h"

#include <NTL/GF2EX.h>

TEST_CASE("Constructors for GF(2^192)", "[GF2_192]")
{
  field::GF2_192 a;
  a.set_coeff(0);
  a.set_coeff(1);
  a.set_coeff(2);
  a.set_coeff(3);
  a.set_coeff(4);
  a.set_coeff(5);
  a.set_coeff(6);
  a.set_coeff(7);
  a.set_coeff(11);
  a.set_coeff(12);
  a.set_coeff(14);
  a.set_coeff(16);
  a.set_coeff(19);
  a.set_coeff(20);
  a.set_coeff(23);
  a.set_coeff(25);
  a.set_coeff(26);
  a.set_coeff(29);
  a.set_coeff(30);
  a.set_coeff(31);
  a.set_coeff(37);
  a.set_coeff(38);
  a.set_coeff(40);
  a.set_coeff(45);
  a.set_coeff(47);
  a.set_coeff(48);
  a.set_coeff(50);
  a.set_coeff(51);
  a.set_coeff(53);
  a.set_coeff(56);
  a.set_coeff(57);
  a.set_coeff(60);
  a.set_coeff(62);
  a.set_coeff(64);
  a.set_coeff(66);
  a.set_coeff(68);
  a.set_coeff(70);
  a.set_coeff(72);
  a.set_coeff(76);
  a.set_coeff(84);
  a.set_coeff(85);
  a.set_coeff(87);
  a.set_coeff(88);
  a.set_coeff(90);
  a.set_coeff(92);
  a.set_coeff(97);
  a.set_coeff(98);
  a.set_coeff(100);
  a.set_coeff(101);
  a.set_coeff(102);
  a.set_coeff(103);
  a.set_coeff(104);
  a.set_coeff(105);
  a.set_coeff(107);
  a.set_coeff(109);
  a.set_coeff(110);
  a.set_coeff(111);
  a.set_coeff(113);
  a.set_coeff(114);
  a.set_coeff(115);
  a.set_coeff(117);
  a.set_coeff(118);
  a.set_coeff(121);
  a.set_coeff(122);
  a.set_coeff(123);
  a.set_coeff(124);
  a.set_coeff(125);
  a.set_coeff(126);
  a.set_coeff(127);
  a.set_coeff(128);
  a.set_coeff(129);
  a.set_coeff(131);
  a.set_coeff(135);
  a.set_coeff(137);
  a.set_coeff(140);
  a.set_coeff(141);
  a.set_coeff(143);
  a.set_coeff(148);
  a.set_coeff(150);
  a.set_coeff(151);
  a.set_coeff(154);
  a.set_coeff(158);
  a.set_coeff(159);
  a.set_coeff(165);
  a.set_coeff(168);
  a.set_coeff(171);
  a.set_coeff(172);
  a.set_coeff(173);
  a.set_coeff(174);
  a.set_coeff(176);
  a.set_coeff(177);
  a.set_coeff(179);
  a.set_coeff(182);
  a.set_coeff(188);

  field::GF2_192 a_int(
      std::array<uint64_t, 4>{0x532DA160E69958FF, 0xFE6EEBF615B01155,
                              0x104B7920C4D0B28B, 0x0000000000000000});
  field::GF2_192 a_str("0x104B7920C4D0B28BFE6EEBF615B01155532DA160E69958FF");
  REQUIRE(a == a_int);
  REQUIRE(a == a_str);
}

TEST_CASE("Basic Arithmetic GF(2^192)", "[GF2_192]")
{
  field::GF2_192 zero;
  field::GF2_192 one(1);
  field::GF2_192 x(2);
  field::GF2_192 x_2(4);

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
TEST_CASE("Modular Arithmetic KATs GF(2^192)", "[GF2_192]")
{
  field::GF2_192 a, b, ab;
  a.set_coeff(0);
  a.set_coeff(1);
  a.set_coeff(2);
  a.set_coeff(3);
  a.set_coeff(4);
  a.set_coeff(5);
  a.set_coeff(6);
  a.set_coeff(7);
  a.set_coeff(11);
  a.set_coeff(12);
  a.set_coeff(14);
  a.set_coeff(16);
  a.set_coeff(19);
  a.set_coeff(20);
  a.set_coeff(23);
  a.set_coeff(25);
  a.set_coeff(26);
  a.set_coeff(29);
  a.set_coeff(30);
  a.set_coeff(31);
  a.set_coeff(37);
  a.set_coeff(38);
  a.set_coeff(40);
  a.set_coeff(45);
  a.set_coeff(47);
  a.set_coeff(48);
  a.set_coeff(50);
  a.set_coeff(51);
  a.set_coeff(53);
  a.set_coeff(56);
  a.set_coeff(57);
  a.set_coeff(60);
  a.set_coeff(62);
  a.set_coeff(64);
  a.set_coeff(66);
  a.set_coeff(68);
  a.set_coeff(70);
  a.set_coeff(72);
  a.set_coeff(76);
  a.set_coeff(84);
  a.set_coeff(85);
  a.set_coeff(87);
  a.set_coeff(88);
  a.set_coeff(90);
  a.set_coeff(92);
  a.set_coeff(97);
  a.set_coeff(98);
  a.set_coeff(100);
  a.set_coeff(101);
  a.set_coeff(102);
  a.set_coeff(103);
  a.set_coeff(104);
  a.set_coeff(105);
  a.set_coeff(107);
  a.set_coeff(109);
  a.set_coeff(110);
  a.set_coeff(111);
  a.set_coeff(113);
  a.set_coeff(114);
  a.set_coeff(115);
  a.set_coeff(117);
  a.set_coeff(118);
  a.set_coeff(121);
  a.set_coeff(122);
  a.set_coeff(123);
  a.set_coeff(124);
  a.set_coeff(125);
  a.set_coeff(126);
  a.set_coeff(127);
  a.set_coeff(128);
  a.set_coeff(129);
  a.set_coeff(131);
  a.set_coeff(135);
  a.set_coeff(137);
  a.set_coeff(140);
  a.set_coeff(141);
  a.set_coeff(143);
  a.set_coeff(148);
  a.set_coeff(150);
  a.set_coeff(151);
  a.set_coeff(154);
  a.set_coeff(158);
  a.set_coeff(159);
  a.set_coeff(165);
  a.set_coeff(168);
  a.set_coeff(171);
  a.set_coeff(172);
  a.set_coeff(173);
  a.set_coeff(174);
  a.set_coeff(176);
  a.set_coeff(177);
  a.set_coeff(179);
  a.set_coeff(182);
  a.set_coeff(188);

  b.set_coeff(1);
  b.set_coeff(3);
  b.set_coeff(5);
  b.set_coeff(7);
  b.set_coeff(9);
  b.set_coeff(11);
  b.set_coeff(15);
  b.set_coeff(17);
  b.set_coeff(20);
  b.set_coeff(23);
  b.set_coeff(25);
  b.set_coeff(26);
  b.set_coeff(32);
  b.set_coeff(33);
  b.set_coeff(34);
  b.set_coeff(39);
  b.set_coeff(42);
  b.set_coeff(43);
  b.set_coeff(45);
  b.set_coeff(48);
  b.set_coeff(50);
  b.set_coeff(51);
  b.set_coeff(52);
  b.set_coeff(53);
  b.set_coeff(54);
  b.set_coeff(55);
  b.set_coeff(56);
  b.set_coeff(58);
  b.set_coeff(64);
  b.set_coeff(66);
  b.set_coeff(68);
  b.set_coeff(70);
  b.set_coeff(71);
  b.set_coeff(73);
  b.set_coeff(74);
  b.set_coeff(76);
  b.set_coeff(82);
  b.set_coeff(83);
  b.set_coeff(88);
  b.set_coeff(89);
  b.set_coeff(92);
  b.set_coeff(93);
  b.set_coeff(94);
  b.set_coeff(96);
  b.set_coeff(97);
  b.set_coeff(98);
  b.set_coeff(99);
  b.set_coeff(101);
  b.set_coeff(104);
  b.set_coeff(107);
  b.set_coeff(108);
  b.set_coeff(110);
  b.set_coeff(112);
  b.set_coeff(113);
  b.set_coeff(115);
  b.set_coeff(116);
  b.set_coeff(118);
  b.set_coeff(119);
  b.set_coeff(120);
  b.set_coeff(121);
  b.set_coeff(124);
  b.set_coeff(127);
  b.set_coeff(129);
  b.set_coeff(130);
  b.set_coeff(132);
  b.set_coeff(133);
  b.set_coeff(136);
  b.set_coeff(142);
  b.set_coeff(144);
  b.set_coeff(145);
  b.set_coeff(146);
  b.set_coeff(150);
  b.set_coeff(151);
  b.set_coeff(152);
  b.set_coeff(153);
  b.set_coeff(157);
  b.set_coeff(158);
  b.set_coeff(162);
  b.set_coeff(164);
  b.set_coeff(166);
  b.set_coeff(167);
  b.set_coeff(168);
  b.set_coeff(170);
  b.set_coeff(171);
  b.set_coeff(177);
  b.set_coeff(178);
  b.set_coeff(179);
  b.set_coeff(180);
  b.set_coeff(182);
  b.set_coeff(184);
  b.set_coeff(185);
  b.set_coeff(186);
  b.set_coeff(187);
  b.set_coeff(189);
  b.set_coeff(190);

  ab.set_coeff(1);
  ab.set_coeff(4);
  ab.set_coeff(6);
  ab.set_coeff(7);
  ab.set_coeff(9);
  ab.set_coeff(10);
  ab.set_coeff(11);
  ab.set_coeff(12);
  ab.set_coeff(13);
  ab.set_coeff(15);
  ab.set_coeff(19);
  ab.set_coeff(20);
  ab.set_coeff(21);
  ab.set_coeff(27);
  ab.set_coeff(29);
  ab.set_coeff(31);
  ab.set_coeff(32);
  ab.set_coeff(34);
  ab.set_coeff(35);
  ab.set_coeff(39);
  ab.set_coeff(40);
  ab.set_coeff(43);
  ab.set_coeff(44);
  ab.set_coeff(47);
  ab.set_coeff(50);
  ab.set_coeff(51);
  ab.set_coeff(52);
  ab.set_coeff(53);
  ab.set_coeff(54);
  ab.set_coeff(58);
  ab.set_coeff(60);
  ab.set_coeff(61);
  ab.set_coeff(63);
  ab.set_coeff(65);
  ab.set_coeff(67);
  ab.set_coeff(69);
  ab.set_coeff(70);
  ab.set_coeff(72);
  ab.set_coeff(74);
  ab.set_coeff(76);
  ab.set_coeff(81);
  ab.set_coeff(82);
  ab.set_coeff(83);
  ab.set_coeff(84);
  ab.set_coeff(90);
  ab.set_coeff(91);
  ab.set_coeff(96);
  ab.set_coeff(98);
  ab.set_coeff(99);
  ab.set_coeff(101);
  ab.set_coeff(102);
  ab.set_coeff(103);
  ab.set_coeff(106);
  ab.set_coeff(107);
  ab.set_coeff(108);
  ab.set_coeff(109);
  ab.set_coeff(112);
  ab.set_coeff(115);
  ab.set_coeff(116);
  ab.set_coeff(117);
  ab.set_coeff(118);
  ab.set_coeff(119);
  ab.set_coeff(123);
  ab.set_coeff(124);
  ab.set_coeff(125);
  ab.set_coeff(126);
  ab.set_coeff(127);
  ab.set_coeff(130);
  ab.set_coeff(133);
  ab.set_coeff(135);
  ab.set_coeff(136);
  ab.set_coeff(137);
  ab.set_coeff(139);
  ab.set_coeff(140);
  ab.set_coeff(141);
  ab.set_coeff(142);
  ab.set_coeff(143);
  ab.set_coeff(144);
  ab.set_coeff(145);
  ab.set_coeff(146);
  ab.set_coeff(147);
  ab.set_coeff(148);
  ab.set_coeff(149);
  ab.set_coeff(150);
  ab.set_coeff(152);
  ab.set_coeff(153);
  ab.set_coeff(155);
  ab.set_coeff(158);
  ab.set_coeff(162);
  ab.set_coeff(163);
  ab.set_coeff(164);
  ab.set_coeff(166);
  ab.set_coeff(167);
  ab.set_coeff(168);
  ab.set_coeff(171);
  ab.set_coeff(172);
  ab.set_coeff(173);
  ab.set_coeff(174);
  ab.set_coeff(175);
  ab.set_coeff(177);
  ab.set_coeff(178);
  ab.set_coeff(179);
  ab.set_coeff(180);
  ab.set_coeff(182);
  ab.set_coeff(187);
  ab.set_coeff(188);
  ab.set_coeff(190);
  ab.set_coeff(191);

  field::GF2_192 a_int(
      std::array<uint64_t, 4>{0x532DA160E69958FF, 0xFE6EEBF615B01155,
                              0x104B7920C4D0B28B, 0x0000000000000000}),
      b_int(std::array<uint64_t, 4>{0x05FD2C8706928AAA, 0x93DB592F730C16D5,
                                    0x6F5E0DD463C74136, 0x0000000000000000});
  REQUIRE(a == a_int);
  REQUIRE(b == b_int);

  field::GF2_192 ab_calc = a_int * b_int;
  REQUIRE(ab_calc == ab);
}

TEST_CASE("NTL to_bytes = custom to_bytes GF(2^192)", "[field]")
{
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_192);
  field::GF2_192 a, b;
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
  std::vector<uint8_t> buffer_c(field::GF2_192::BYTE_SIZE);
  BytesFromGF2X(buffer_c.data(), poly_rep_c, buffer_c.size());
  const GF2X &poly_rep_d = rep(d_e);
  std::vector<uint8_t> buffer_d(field::GF2_192::BYTE_SIZE);
  BytesFromGF2X(buffer_d.data(), poly_rep_d, buffer_d.size());

  std::vector<uint8_t> buffer_a(field::GF2_192::BYTE_SIZE);
  a.to_bytes(buffer_a.data());
  std::vector<uint8_t> buffer_b(field::GF2_192::BYTE_SIZE);
  b.to_bytes(buffer_b.data());
  REQUIRE(buffer_a == buffer_c);
  REQUIRE(buffer_b == buffer_d);
}
TEST_CASE("NTL to custom conversion GF(2^192)", "[GF2_192]")
{
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_192);
  field::GF2_192 a, b;
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

  field::GF2_192 ab = a * b;
  GF2E a_ntl = utils::custom_to_ntl(a);
  GF2E ab_ntl = utils::custom_to_ntl(ab);
  GF2E b_ntl = ab_ntl / a_ntl;
  field::GF2_192 b2 = utils::ntl_to_custom<field::GF2_192>(b_ntl);
  REQUIRE(b == b2);
}
TEST_CASE("Custom fast inverse GF(2^192)", "[GF2_192]")
{
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_192);
  field::GF2_192 a;
  a.set_coeff(130);
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

  for (size_t i = 0; i < 1; i++)
  {
    field::GF2_192 b = a.inverse();
    field::GF2_192 c = field::GF2_192("0x478e620c7de407c844d02bd0c8f51295d464b471059a5e91");
    REQUIRE(b == c);
  }
  // BENCHMARK("GF inverse") { return a.inverse(); };
}
TEST_CASE("Custom slow inverse GF(2^192)", "[GF2_192]")
{
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_192);
  field::GF2_192 a;
  a.set_coeff(130);
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

  for (size_t i = 0; i < 1; i++)
  {
    field::GF2_192 b = a.inverse_slow();
    field::GF2_192 c = field::GF2_192("0x478e620c7de407c844d02bd0c8f51295d464b471059a5e91");
    REQUIRE(b == c);
  }
  // BENCHMARK("GF inverse") { return a.inverse_slow(); };
}
TEST_CASE("NTL inverse == custom GF(2^192)", "[GF2_192]")
{
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_192);
  field::GF2_192 a;
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

  field::GF2_192 b = a.inverse();
  field::GF2_192 c =
      utils::ntl_to_custom<field::GF2_192>(inv(utils::custom_to_ntl(a)));
  // std::cout << utils::custom_to_ntl(a) << ", " << utils::custom_to_ntl(b)
  //<< ", " << utils::custom_to_ntl(c) << "\n";
  // std::cout << utils::custom_to_ntl(a * b) << ", "
  //<< utils::custom_to_ntl(a * c) << ", "
  //<< utils::custom_to_ntl(a) * utils::custom_to_ntl(c) << "\n";
  REQUIRE(b == c);
  REQUIRE(a * b == field::GF2_192(1));
}
TEST_CASE("NTL interpolation == custom GF(2^192)", "[GF2_192]")
{
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_192);

  std::vector<field::GF2_192> a =
      field::get_first_n_field_elements<field::GF2_192>(100);
  vec_GF2E b = utils::get_first_n_field_elements(100);
  for (size_t i = 0; i < 100; i++)
  {
    REQUIRE(a[i] == utils::ntl_to_custom<field::GF2_192>(b[i]));
  }
  std::vector<field::GF2_192> a_from_roots = field::build_from_roots(a);
  GF2EX b_from_roots = BuildFromRoots(b);
  REQUIRE(a_from_roots.size() == (size_t)b_from_roots.rep.length());
  for (size_t j = 0; j < a_from_roots.size(); j++)
  {
    REQUIRE(a_from_roots[j] ==
            utils::ntl_to_custom<field::GF2_192>(b_from_roots[j]));
  }

  std::vector<std::vector<field::GF2_192>> a_lag =
      field::precompute_lagrange_polynomials(a);
  std::vector<GF2EX> b_lag = utils::precompute_lagrange_polynomials(b);

  REQUIRE(a_lag.size() == b_lag.size());
  for (size_t i = 0; i < a_lag.size(); i++)
  {
    REQUIRE(a_lag[i].size() == (size_t)b_lag[i].rep.length());
    for (size_t j = 0; j < a_lag[i].size(); j++)
    {
      REQUIRE(a_lag[i][j] == utils::ntl_to_custom<field::GF2_192>(b_lag[i][j]));
    }
  }
}
TEST_CASE("NTL dot product == custom GF(2^192)", "[GF2_192]")
{

  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_192);
  std::vector<field::GF2_192> a =
      field::get_first_n_field_elements<field::GF2_192>(100);
  std::vector<field::GF2_192> b =
      field::get_first_n_field_elements<field::GF2_192>(200);
  b.erase(b.begin(), b.begin() + 100);

  vec_GF2E a_ntl = utils::get_first_n_field_elements(200);
  vec_GF2E b_ntl;
  b_ntl.SetLength(100);
  for (size_t i = 0; i < 100; i++)
    b_ntl[i] = a_ntl[100 + i];
  a_ntl.SetLength(100);

  field::GF2_192 result = dot_product(a, b);
  GF2E result_ntl;
  NTL::InnerProduct(result_ntl, a_ntl, b_ntl);
  REQUIRE(result == utils::ntl_to_custom<field::GF2_192>(result_ntl));
}

TEST_CASE("Matmul and Transposed Matmul have same result GF(2^192)",
          "[GF2_192]")
{
  alignas(32) constexpr std::array<uint64_t, 4> m1[192] = {
      {{0xd84336c885addb60, 0x4ae24caf9caef2f9, 0xf84e03121d13e134, 0x0}},
      {{0x7f6622e9b6ae69f7, 0xe8e2308534b2f978, 0x798ed4b51481c924, 0x0}},
      {{0xfafe8777c4794bc0, 0x5932357058b8d3b7, 0xb992587066d9f7f, 0x0}},
      {{0x7f6996a1313239f3, 0x9f4c5788f25d186a, 0xb5d43ec2bb689646, 0x0}},
      {{0x7ea5f9e10136cfaf, 0x8269b6a78e11a1cc, 0x7191cf19bf178b0a, 0x0}},
      {{0x3ad67cff0786e829, 0xdcf493c5327c150d, 0x19659bedb4649bc0, 0x0}},
      {{0x258aa55298fac8c1, 0xb83d686029e5e78, 0xc6cb855504362ad1, 0x0}},
      {{0xac92553e36f69a15, 0xc9a55cb04c5db78d, 0x1d971d49f7a1a0f9, 0x0}},
      {{0xb55bc5af65fce7f3, 0x506c11d9f9cff996, 0xf68a2616df63dc8f, 0x0}},
      {{0x801cd76cd81973c7, 0x3b07b26a4cee93e1, 0x4203cfa67bfa0c59, 0x0}},
      {{0x259315d81c96e99e, 0xc4dbd15bf080073d, 0x53d94e48b935d698, 0x0}},
      {{0xbba1e3be018d37c5, 0x6aa4134d817728ba, 0xb37f0745201439f9, 0x0}},
      {{0x645711225acdab28, 0x246f6dd1da965c10, 0x9795e6354ebf6bab, 0x0}},
      {{0x89a6f151a53fe2f4, 0xe9eb7d72ee38b1fd, 0xb0b6218161a0c422, 0x0}},
      {{0x665add2ce9cf638, 0x27a61a56636f5e4a, 0x9cfee1849001a2d6, 0x0}},
      {{0x8b2e30bd47a86af7, 0x87a8eaf1bfcc8e6, 0x5c305bdc422ca5a5, 0x0}},
      {{0xe12e4e0baa06dc9c, 0x7831e388160758e, 0x4859ed0f58214ca1, 0x0}},
      {{0xdd20238a20152330, 0xaa72e593685cdbcf, 0x586c9efdfb8ad618, 0x0}},
      {{0x5869c5c0d0b6520f, 0x55940da65d573669, 0x88cb0323e018aee6, 0x0}},
      {{0xce4116bb21472ab5, 0x1d62c9337c726ece, 0xcd0af7e6d4e58832, 0x0}},
      {{0x49523a2c7c303663, 0xd312050150f521c3, 0xf466bea0839fbd4c, 0x0}},
      {{0x335d60886c0410a6, 0xbfcfcdf1799bb913, 0xa2878b5aa03d8fd3, 0x0}},
      {{0x9cc36b228d36d851, 0x164b48d08be523d7, 0x440b96802650a8ac, 0x0}},
      {{0xd4c204c0caa53795, 0xae34acc8a8a0ebb4, 0xcb37a09a2197ddde, 0x0}},
      {{0x95e0ec9b83a33187, 0x7e71c0bae2688bcd, 0x9217b69a945de6a0, 0x0}},
      {{0x35750bf652615a74, 0x602c4dd091e27a34, 0xe014874f8d09e66e, 0x0}},
      {{0x3e8db352c3af7b8d, 0x1b05d65d0259fef8, 0x1da545823f45253a, 0x0}},
      {{0x373657f736054fcf, 0xe077a0617d8800a, 0x68cee20c4420fc26, 0x0}},
      {{0xd1f5f254171bed3e, 0xd6fc619f28a3a0d, 0xa2ea2c6635e839ff, 0x0}},
      {{0xf497fbb7e3550a88, 0x2cb57ac9a9efeb53, 0x30a495400f9c69c9, 0x0}},
      {{0x45f65ed6975c6bfd, 0x3e1ffcf903488b54, 0xb576fa9d0c2ee6c4, 0x0}},
      {{0x6c11fb27d0e9d58, 0x8bfa191cbf860228, 0x695902fff7c28475, 0x0}},
      {{0x42123553d5f91549, 0x5ae8068141b41987, 0xe1b90506df872571, 0x0}},
      {{0x60bbe8eb5f718b8e, 0x697cf78a9ee5efa8, 0xfbce87cb882a3396, 0x0}},
      {{0x72433866c9b82cf1, 0x19d301674634bcbe, 0x3a7662e365c7dce, 0x0}},
      {{0xc7d27911fc7ddc17, 0x6fed79e9d8870c7d, 0x6ef17421d734dbe3, 0x0}},
      {{0x7a8e2438e018eea5, 0xf929e244b29c7484, 0x3a65f14e9dee5130, 0x0}},
      {{0x435dae43df2428f5, 0x1ba9795babf3e3dc, 0x7dee3af691cbd234, 0x0}},
      {{0xb54a02abc14a3c19, 0xd3667cfb21051d3d, 0xa890bc1ce41d26b9, 0x0}},
      {{0x5338759b1d4c9e82, 0x87f2cdb1d81c7a6a, 0x3fa8a4e5b30dab8b, 0x0}},
      {{0x2eec830dc0e0d4ed, 0xd466177b7fed971e, 0x4623b745b8c59ef1, 0x0}},
      {{0x140742155b948c54, 0x9466753c0dd7fecd, 0x31768702693c38f3, 0x0}},
      {{0x3989ed65b9fc773a, 0x5563c5e151467980, 0x5e90e82b6d767edd, 0x0}},
      {{0x85780974c54ecfa7, 0xd397c0c4c60ce14d, 0x67318c846da848d7, 0x0}},
      {{0x7bd882b4d7483fc6, 0x27664d999fa4ed3a, 0x84279ac87fb018d7, 0x0}},
      {{0xbe02943924c1b944, 0x1e13ea049e35f9ca, 0xc33576c7e78337f1, 0x0}},
      {{0xbb158a0280642454, 0xa70d72eec39f6fe8, 0xe47fb26741f8d9a1, 0x0}},
      {{0x9ed27b0c9c506b7a, 0xae7f203ff6e75683, 0xe0259de854e84800, 0x0}},
      {{0xe746e926b0ffd68, 0xf8a3567cac11ae73, 0xf276970ce67ba987, 0x0}},
      {{0xd441329ab9020a93, 0x73db66524e2d1375, 0xfb920a20eeb2907a, 0x0}},
      {{0x40ccb87a0dc40599, 0x3f9cabaddba43c5e, 0xc8097d147b10b6c2, 0x0}},
      {{0xa64982499a36c9c0, 0x49c259c115c32e74, 0x492ceb98929463db, 0x0}},
      {{0x8a24c0d75cd94338, 0x53bea3352dd499f0, 0xdf5035a704dc4f48, 0x0}},
      {{0xbb8885a51a607332, 0x913bc5c12baeba1a, 0xbfb9433f463621c9, 0x0}},
      {{0x32f9fde273f1d002, 0x85d9a1232fe19823, 0xfbbca1133f13a2c, 0x0}},
      {{0xfd92aab82f2f964d, 0xf1bb736c8fb6fa52, 0x37391cbf75533ecb, 0x0}},
      {{0xc461936d95b461c3, 0x59c865408c130afa, 0x887fb2237fe2e411, 0x0}},
      {{0xb07d894b091802a8, 0x3d7442a523ab6419, 0xd4f3077010218283, 0x0}},
      {{0x37f5684766388839, 0xfd00e8a0459a5c23, 0x6eb3fb2a6d349bce, 0x0}},
      {{0x43e1b309c0434323, 0x16ec44f526cf20ec, 0x4d262d35e2637b61, 0x0}},
      {{0xfc2dfcd3a49c2269, 0xc55a8c89ffeb4a02, 0x306c5fcad79f782c, 0x0}},
      {{0x3604e39d07a45bba, 0x2a7bb495392b440c, 0xd7e09794ec792864, 0x0}},
      {{0x2fa6482b23e3a63e, 0x8035d6fad7925d69, 0x7bb7e7547e7db10d, 0x0}},
      {{0x38ace222f3e2a107, 0x76ffef97b009cb2c, 0x2816074b344e25d8, 0x0}},
      {{0x8ced51804b02a1d1, 0xeccfc5e42bbb472b, 0xe68b132ffa8401c4, 0x0}},
      {{0xe1e5709ed1e79002, 0x7d723a43bea68de1, 0x87546f24380fe83f, 0x0}},
      {{0x63036de558f87e45, 0xf9d02c737460994c, 0x4195863241badbf1, 0x0}},
      {{0xa3b1f3c958432df6, 0xfd22ccfb8fedfaa5, 0xa1783a42395831ee, 0x0}},
      {{0x837731112a81a2cf, 0xb1ccacae5143cc74, 0x480a9a287331d8d6, 0x0}},
      {{0xaf8d2b118f7764b9, 0x3a8fcd39ae23c1ad, 0x5421c97c965a757, 0x0}},
      {{0x74e9a276d725239c, 0xeffdbff0ea98b267, 0xbecec2afe60f8c1a, 0x0}},
      {{0xe01df7daf1478592, 0x23070762dc63e1d9, 0xa653b854bc807308, 0x0}},
      {{0xbe196a3dddb91b8, 0xe105245623f0b60f, 0x86a0507f9268b879, 0x0}},
      {{0xfa15ca6482d0a2a8, 0x8ea1e2363338b706, 0x87fe9a4fc2f599b7, 0x0}},
      {{0xe6da66c4dbc98c67, 0x7b9e57831e6e45d7, 0x648a8159f39f2beb, 0x0}},
      {{0x23134716acb2991e, 0x7a1aa233443aed17, 0x9846fba27f5cda2d, 0x0}},
      {{0xcc814da4c897e68, 0xed9b1d28df114a97, 0xd154741902781d5d, 0x0}},
      {{0xda41a0969cf0a5a4, 0xf68741047dc280a6, 0x1b1ddd76015c510, 0x0}},
      {{0xbc6c887a02210adb, 0xd625111774d32d2e, 0xfe7e8ab0a2f47cbd, 0x0}},
      {{0xbc1c202d9bcdd2f9, 0x46e3a1bcd31c0746, 0xa4bbbbd1678c36fa, 0x0}},
      {{0x8da2302fcc3cbb6d, 0xedd7c027586d05d6, 0x140937f9ebfe8f52, 0x0}},
      {{0xb7cd3a4e9d831b33, 0x47afd36da2122ece, 0x913e33792f0786b3, 0x0}},
      {{0x17d4cf8676a32981, 0xb07f316cd7acaf40, 0xdaaadfe0c651ca52, 0x0}},
      {{0xe77f0bb86fc5f281, 0xefce9db1df15ae92, 0xcafb12a46573eb7b, 0x0}},
      {{0x1b5efad8b14daf3, 0x9ee3b9edced8d4a0, 0x214635165f0a840c, 0x0}},
      {{0xd60a867674301246, 0xc34d60f8993ee9a3, 0xce9f2d1cc51b0304, 0x0}},
      {{0x613a3d62c4da3fbb, 0x6bc5253b90958ef8, 0x8d7a2bc120fbd573, 0x0}},
      {{0xee53be677b1bb9e0, 0xed24b50dc432dacb, 0xc8b65baeef720c99, 0x0}},
      {{0x3d1b57670aed3416, 0xdbdd947aa4b11a7e, 0x5ff438c11fafdbf0, 0x0}},
      {{0xfcb62fd0d1ca47be, 0xfba85a98572b6aa2, 0x8e579ff4cc5bf491, 0x0}},
      {{0xb15e26d103910ed3, 0x2bc76ef2adf8edc, 0x17301296f6b41f92, 0x0}},
      {{0xa63dd14288bf6c3b, 0xf718269ff9f509c5, 0xf77a7680f5aa65cd, 0x0}},
      {{0x9666cd73a2b7c653, 0x44738ebfa1674229, 0x12a582abc29c2240, 0x0}},
      {{0x7aeda97502397ae3, 0x55dce455e9237a40, 0x64f41f8a100e0d5d, 0x0}},
      {{0x366bf9edca8e5b3c, 0x6378ac04eb7ee866, 0xb438979df7ad159b, 0x0}},
      {{0xd3f805aedc4045f6, 0xe1fcc01f31e4901d, 0xebfc7efb080aea57, 0x0}},
      {{0x1c8b69618e9757b8, 0x6ad1f79fdca0e5cb, 0x7528120aca5a6cf4, 0x0}},
      {{0xc210d0bcffbd4e1c, 0xfc947dca8b1eaf0a, 0xd4c4078373762e4a, 0x0}},
      {{0x7094ae738e9662a, 0x1d4fb48d1f0b4b71, 0x9361e8c7d12e745, 0x0}},
      {{0x823da6ac9b77490b, 0x895588485617e80d, 0x656f2b80154fe217, 0x0}},
      {{0x75cfcd76817cc7e4, 0x351de1b0f2518704, 0xe2ee4195a21f2ad2, 0x0}},
      {{0x58bd52779eff383d, 0x620777501bd8ed34, 0x7b71909b5231eb2d, 0x0}},
      {{0x5f50d27694a73380, 0xc2ada363ddb780ab, 0xf427fc49b9ec373c, 0x0}},
      {{0xffa8f0be43a443e5, 0xf00e836172f42f19, 0xd419189329c42fd2, 0x0}},
      {{0x845f2e02aed78a30, 0x709fa1286583d0eb, 0x3b2e5558ad8defcf, 0x0}},
      {{0x28c04c1f87ddd02c, 0x5b756c020e5c8b19, 0x4f59f6fd089687d1, 0x0}},
      {{0xd1b1e34bdfce1b9c, 0xa06c1e4520d75d85, 0x8927bab3551f1e1e, 0x0}},
      {{0xc6d22d7b18678901, 0xda87c87f129c386a, 0xab34bc11740cae31, 0x0}},
      {{0x2330fc26198d31cd, 0xe1ab5270d249963c, 0xc08a14a8c7ab4783, 0x0}},
      {{0xd0d8c74dcbe1a232, 0xcc1c3217d9cad0ba, 0xb22a6d6b18292c1, 0x0}},
      {{0xc7d1bd756a3d266e, 0xa2657fc1eb3aa6c4, 0x32c5d0ca0614aa87, 0x0}},
      {{0xabcc121a4a5dbf72, 0x5917b86cb0d15dde, 0xdfe423ec18a8d908, 0x0}},
      {{0xa82de9fcf15a5319, 0xd8f3411baa1b1ad1, 0x7d3d0a2988dfc1f4, 0x0}},
      {{0xff1ad96f3f5ebe00, 0xa259aeda8714ab61, 0x35650eeaf1aaf283, 0x0}},
      {{0xbc0f2eb6999efe08, 0x8a7942885c02a8a7, 0xb3425f50776e4e93, 0x0}},
      {{0xe428315430278da3, 0xca8b85905a22e7fe, 0x603ffd0da37ff41a, 0x0}},
      {{0x44785180e67a666f, 0xdd25c88b7180457b, 0x11c1e9acd732b964, 0x0}},
      {{0x772c2e76553a3dac, 0x760543ff6207a554, 0x1430c363958657a9, 0x0}},
      {{0xe630441f17edf714, 0x5878d21de55751d3, 0x966144fdf16315f1, 0x0}},
      {{0xb9e1156a802dd4cd, 0x2d00af8ec589cd7e, 0x3d627f5b95fa856b, 0x0}},
      {{0x1928c421a2eb37fe, 0x94d20afde4f46d0e, 0x95808d0f574dfba7, 0x0}},
      {{0x520f340f8cef8c5e, 0xe0425587d20218a4, 0xf8594184cd82867, 0x0}},
      {{0x87c10e7db56d7fb1, 0xf6164c9defe3da57, 0xfceee895a4d565b4, 0x0}},
      {{0xf6f22e048efa3b1a, 0x5206b200a3be6e22, 0xad5fa1ba7f6f2635, 0x0}},
      {{0xa81a0ed21a126476, 0x67798000cd1e106f, 0x297fb521a425ff8e, 0x0}},
      {{0x4e725afa8cd64f33, 0xbbbf7a784154f3b9, 0x3590b3746cecb611, 0x0}},
      {{0x78134f0c9e6a1e9d, 0xb3ed6fcd7a4c534a, 0x72f0e22fac9edacf, 0x0}},
      {{0x531465fe32e1a773, 0x467a22fbaa72c624, 0xa4880e8f629af388, 0x0}},
      {{0xd08a30699480a844, 0x1d9edfaf74157a5a, 0xd88e3f501477c79, 0x0}},
      {{0x4d628abbb8a0f99b, 0x7d25230c49c11677, 0xa6b033f98d51f5e4, 0x0}},
      {{0x42cf1d188fe93ec2, 0x374e5a910a0e656, 0x8ac6f0332960af4e, 0x0}},
      {{0x52c3b5a2cdc66b4a, 0xbeba2ac6d22d890b, 0xcf041703ab7d71f7, 0x0}},
      {{0x3b2b306ccf788eb7, 0x461fc8a4c1fdaa24, 0x15aefa52ed0a2320, 0x0}},
      {{0x34e0f9022d6b16dc, 0x6250e4976d63e5ae, 0xce03b2b7499ec6b1, 0x0}},
      {{0xebef5d39a7e1f6d5, 0x48b847469c3a435b, 0xd653ad6467867d7d, 0x0}},
      {{0x5041c2d05223266d, 0x28275c1e84adcb83, 0x51f810b3e04a1091, 0x0}},
      {{0x2b4238bea8920803, 0x4add3d59bb1c2868, 0xc63cdc9490fc53d5, 0x0}},
      {{0xd46f184324f9d324, 0xf78dc62774c688, 0xdccfbfbb49fd80, 0x0}},
      {{0x672b084cf3ed00f8, 0x97bccf0cff32df20, 0x67ab6ca45b550e27, 0x0}},
      {{0x911d8662a00be89d, 0x1269d8c7481b1242, 0xa57ddca8bc3aa5b0, 0x0}},
      {{0x6de4e56059673da1, 0xa1d0f8e0abc86b02, 0x7dd0398a1e0b9d41, 0x0}},
      {{0xb7fd7c4dc3e30eda, 0xaba9318644a46b74, 0x41d1e620285656f9, 0x0}},
      {{0x6a6b0b27f4b13c67, 0x990f5da8486567f6, 0xe6ff59b03f819de2, 0x0}},
      {{0x2dc51070c34f1a4d, 0x180d66db82dd589e, 0x904ff4bad90d0eb4, 0x0}},
      {{0x8724a371b683d584, 0xf1940e922c3bf709, 0xe79ff6b93c6e7ece, 0x0}},
      {{0x89f001182da592f9, 0xa05ee7eb3578fda7, 0xba813a9f3a340a2, 0x0}},
      {{0x9ee7880ff5f1e25e, 0x499729bd8c4601db, 0x2a60c684a216cd67, 0x0}},
      {{0x40ae43e39035be55, 0x2140ea4de9868273, 0xfe49b7221687b170, 0x0}},
      {{0xd7ddee33415d215c, 0x6b40328a04ab10f0, 0x69626a3b05915e89, 0x0}},
      {{0x34637dc2ec421de3, 0xa3e0733a211a2543, 0x6d1f75d0b824481e, 0x0}},
      {{0x5de4a937bab252fd, 0x490414aa314c385b, 0x501a7d1035230d15, 0x0}},
      {{0xcf83186f4d827ffa, 0xd95848bb0410645d, 0xb29d488525fb636d, 0x0}},
      {{0x76922a19c5f0b7ae, 0xd4308f29e25bb70d, 0x26d81858713f66ef, 0x0}},
      {{0xfc1d0f917dd5cef4, 0x698a31486dfcbe24, 0xb30b9e2800433e01, 0x0}},
      {{0xd1ea94a9629007dd, 0x72cf9a97ac9eea7, 0x36c1a18c6cef4f48, 0x0}},
      {{0x2911b790425fa03c, 0x7e09da5d1c3fee2d, 0x22c51258cf6dd4a6, 0x0}},
      {{0x8cb50b4d949deea1, 0x7391780a4eeb3556, 0xa1a90fa7d73abf13, 0x0}},
      {{0x4856a7dc831b0c0e, 0x70e7a101de06b66e, 0x5ff701902675726d, 0x0}},
      {{0xa4c79b69cf2131f, 0x2cc03b0380a03c91, 0xd4e3b3ef39d96deb, 0x0}},
      {{0x84f8df0bd4db53c3, 0xad51026bc7bc73cd, 0x2e1fc0529da94924, 0x0}},
      {{0xba4d5de312904fe7, 0xb26d979057f17d0a, 0xf24dd0acb71e3e41, 0x0}},
      {{0xc9825e1cdec169a, 0xa11dd50fa0efe839, 0xa63736c086f09e1e, 0x0}},
      {{0x6adf3abb6131c2f6, 0x2555dea27b993e67, 0x522b28033fb855f4, 0x0}},
      {{0xd9694a13c8e5cb5a, 0x5b2a35ae82a597b4, 0xdebbd6c58d8b3b2d, 0x0}},
      {{0xc6e323176516c0f0, 0xcb53a7d4cf2120fe, 0x888009602915c860, 0x0}},
      {{0x741a8d41ddaf53aa, 0x4af8228e4e6ea6f4, 0x1403b8924f9876e0, 0x0}},
      {{0xe3321da01107ff3, 0xc4618c65f966dede, 0xe4681ec3bc3f23fb, 0x0}},
      {{0x3a500a27cb45e8fd, 0xb4d7c203142efb36, 0x82749ff1c34cb2a1, 0x0}},
      {{0x17ded07df4d246da, 0x8e72c09900fe30a2, 0x949eae43a4870c6, 0x0}},
      {{0xfd71256d1dd1f893, 0x2caa8a145d572329, 0x369bcd19daaa08e8, 0x0}},
      {{0xd5c15c71b9c0139, 0xa6c792efaf31305, 0xf19cb1c67fe0590d, 0x0}},
      {{0x2ee9ea2b586afb4, 0x10d1a126a297f9c4, 0x71845de19dc42815, 0x0}},
      {{0x5edf6ea3926251ea, 0x515130d8ca62521, 0x63df45909b1b6340, 0x0}},
      {{0x1ea40e67f55c71ee, 0x1114ab7b74ed056b, 0x90f2f0f4f19922b2, 0x0}},
      {{0x88d7dd0c34825d3a, 0x3f0a77cc365435bc, 0x33a069fd4fbf179b, 0x0}},
      {{0x294a86a529fc9e56, 0xdfd7827da696b97c, 0x6058d44fa5a0f50f, 0x0}},
      {{0x45674e90cff66b60, 0x1a6b95ecc082b979, 0xe247d96285ae41c9, 0x0}},
      {{0x7ec7a1ed239b30f, 0x3b6a9e025ff7d1e6, 0x14a4eb3a597f6ec5, 0x0}},
      {{0x7901f1d5ca2587cc, 0xca35cb81a9973273, 0x1784a808285c4371, 0x0}},
      {{0x57873c303e2dc8e6, 0xad253867d17716bc, 0x5b91d702f5f4cb17, 0x0}},
      {{0x5987cdd0c7fba43d, 0x66fbaee7aea20641, 0x15984e7d362592af, 0x0}},
      {{0xfffd4cef6b2cd26a, 0xe9c05ce45bc2e6be, 0x63279716d718ec16, 0x0}},
      {{0xe855884b82a9b4f0, 0x8fce116618be10e2, 0x120b95d97cf29ccf, 0x0}},
      {{0xc90409347dd037cc, 0x1dda4c1b2721d0f8, 0xe189038a30a53c21, 0x0}},
      {{0xe49de11abb42ece8, 0x768a4604334e6df9, 0xca62bdaed16fe138, 0x0}},
      {{0xd74b7f1e66288f46, 0xf2aeeff768b686ed, 0x773f0e307ee756f7, 0x0}},
      {{0x14a1d6b0638ab600, 0x424c1bd8e0c89a93, 0x9020531256beb848, 0x0}},
      {{0x41cd1ecfa001f757, 0x8bcb350c841dd281, 0x8050a12d7da0bdac, 0x0}},
      {{0x62ba4ef98469f4b, 0x80be1d08ff87935b, 0xcaa8a33588916f54, 0x0}},
      {{0xe55dca4408bf3403, 0x4155e1de46227578, 0x180dd8bc0c183efb, 0x0}},
      {{0xa8aed2c003a0cdfb, 0xb85b14aa9b7e4a25, 0xdbf3d69610b4a709, 0x0}},
      {{0x8d053d0fd2de9549, 0x8c8d3ab061665269, 0xb21c1e59585a43db, 0x0}},
  };
  alignas(32) constexpr std::array<uint64_t, 4> m1_transposed[192] = {
      {{0x9d86097d4ddc8bfa, 0xe49918a83c5fc435, 0xf81206c1d46ad9d2, 0x0}},
      {{0xe9629c8a1934871a, 0xbb18e00cbf724c9a, 0x7a2af36fe1a4611e, 0x0}},
      {{0xc0807b3a5fadae92, 0x53f056b2c3212c5c, 0xa9ea8856f5dcaf1, 0x0}},
      {{0x76958543fc055430, 0x4bb5562f4a41db70, 0xd1b675aa6dd6acaa, 0x0}},
      {{0x6436c66cd2cbe58a, 0xff41a523df52c9e9, 0x4850cfde4ede2c72, 0x0}},
      {{0x7e318d34523af13b, 0xb538e3b5ead3b728, 0x41797cf51be25690, 0x0}},
      {{0x1189f325ca50ab4f, 0x9390d090b4b1d41d, 0xdbedb1dd86fee4ed, 0x0}},
      {{0x230e19b66da9af5e, 0x45a814d1a6dce3f9, 0x41cc3bf797e33c76, 0x0}},
      {{0xa93dbc03dd821f1f, 0xad699cd9c2c729c9, 0xda877c69c5b1120a, 0x0}},
      {{0x7ab29c926e9efb95, 0xed57e5d7767bd254, 0x1ea7896fd7cea2fc, 0x0}},
      {{0x40855fdd98914910, 0xf7fec0179f4034ac, 0xffd4c94337a970f4, 0x0}},
      {{0x240bbafefe4994ff, 0x6e2e8d2a6cd75c0c, 0x5309cac932a8f91f, 0x0}},
      {{0x20e135c987f54a89, 0x4de7966161fb9906, 0xbce2f262c1ebd266, 0x0}},
      {{0xd121f474559aff2a, 0x9d76f06429cd327d, 0x2dd32ac0199c58cf, 0x0}},
      {{0x29798d185e45e777, 0x34d5029ffa189024, 0x492973fd92c50a4a, 0x0}},
      {{0xc4c92b9a904175f1, 0x82ceab101099af93, 0xdf7e8a9c1b0f0a53, 0x0}},
      {{0x48d1200b3f8a3a05, 0x87c8fb6f3d8ed5fa, 0x285e02acba1ffee4, 0x0}},
      {{0xc88b0840954d24fa, 0x7b3f0d695ac609ab, 0xb5115930e8e1b9a8, 0x0}},
      {{0x318d4ea8ecef7db3, 0x26cedffb591980e2, 0xb02dacba1a1a9408, 0x0}},
      {{0x16911cddd400fb47, 0x4ff7d6366bc19504, 0xa67aa422b8108e34, 0x0}},
      {{0x1758861f705667dc, 0x3837c33b3cf12b24, 0xa093a755ff5c4310, 0x0}},
      {{0xe5e8452f07d4a1df, 0xcff868fe39256866, 0x627f902e414e76f6, 0x0}},
      {{0xc874fdcb620811c4, 0xef53af3c8348a7ae, 0x9191b38acb34b67c, 0x0}},
      {{0xf15427050584dde3, 0xab4437e75f4ebf16, 0xe4d1cf2bd7c7674f, 0x0}},
      {{0xe3c71ee7f548a939, 0x467369a069a85e3, 0x45b1aef62396b47c, 0x0}},
      {{0xe4e912227f81d0a2, 0xd952e7ab759cc671, 0xc77f14812c41a4d4, 0x0}},
      {{0x3594b8abd870e5a7, 0x6e720763806f3960, 0x2996b32d3a7427d, 0x0}},
      {{0x2bf86ae80f15640, 0x7a06fd2fc99bbd3d, 0x31ad86aa42e2113e, 0x0}},
      {{0x817a96abda1416ca, 0xd46f1c6e82a6a5ce, 0x918a7f21d24d5483, 0x0}},
      {{0xd4c32418a83b218a, 0x851b410610ac0890, 0xfa8e91406674f62, 0x0}},
      {{0x8c511b7fa6b4d304, 0x31e482c2ed15cf, 0x86b721be8fb4f498, 0x0}},
      {{0x990add7d65c56247, 0x6f95277bda53afe2, 0x995739aaf16ded5f, 0x0}},
      {{0x7f3827eb2909a13e, 0x7426e257591813c, 0x9864b7bf97dd6243, 0x0}},
      {{0xd65740e7ef4b59e4, 0xb2e69ff499e779c2, 0x9b623cddc0fc4b2a, 0x0}},
      {{0x25309f047a108ba4, 0xce6f72fee1b7ae46, 0xbaa6e79070c46510, 0x0}},
      {{0x6b8ea1d2013b8fa3, 0xe6c3ae8ac01bd08a, 0x9b624344b5862557, 0x0}},
      {{0x30973a99ff08ece4, 0xb46dcaf2362878f2, 0x79f015c6b5381c6, 0x0}},
      {{0xc1e43c56aa589bbe, 0xa5a758fff1f9c344, 0x14a8bb8744d9d95b, 0x0}},
      {{0x175c0c275e846677, 0xb4ab6c757fe256cc, 0x7874276330a9be91, 0x0}},
      {{0x30f310c2ebaecd3b, 0xb015008ec61c358f, 0x5c359c476e28018a, 0x0}},
      {{0x2b608d89ae467fd4, 0xc09b6c11fb5c08bd, 0x83944673fa6b506c, 0x0}},
      {{0xa98bd360fe5b0a0f, 0x7c24a56c07be0fe8, 0x6e03b89cbb194882, 0x0}},
      {{0x106124b1c98d47ed, 0xdfe47b1897f41d84, 0x9e39fe23ae30384c, 0x0}},
      {{0x56c5cc2ee3514030, 0x7c275b1572de4224, 0xaafb78add3f46766, 0x0}},
      {{0x1946a08dfc18b6b9, 0x229ad0e249c3119b, 0xce0e4d05cca0a37d, 0x0}},
      {{0xbcc784bf3572e873, 0x8a2d5d8966d3a4fe, 0x930e125669713139, 0x0}},
      {{0xf451868a79652bb0, 0xe15336f759140e8f, 0x67375109c03830e0, 0x0}},
      {{0xbbfc752235046b5c, 0x10374da78b463c8, 0x7554c920ac5518aa, 0x0}},
      {{0x1f4a4626b66c5d19, 0x4685453d699a2bff, 0xbf7d525d1ab4eedc, 0x0}},
      {{0x4080a25f68d1b5e7, 0x7a06091157e90c14, 0x5219d97425ac475f, 0x0}},
      {{0xf61543307e21f236, 0x822581383e1ec2b3, 0xe9fb7d05725dba44, 0x0}},
      {{0x926c1df20425834c, 0x133fa1bded6ad4e1, 0x7b229d2fc6186e55, 0x0}},
      {{0x6c1d8ab7a3017a4, 0xf8527d6a8fdc8e98, 0x216057e6bb122800, 0x0}},
      {{0xdf5109825b07e81e, 0x29f914a8fa59415b, 0x54232a58946f7672, 0x0}},
      {{0xf4f996cd3fc512f, 0x2c90eb50f48e7553, 0x2a63df9de476f3ee, 0x0}},
      {{0xcce4951af5c02cf4, 0xc80eeb1a217156b, 0x4d3a791695deb06d, 0x0}},
      {{0x4ca05ce85b33ad4a, 0x85a2d4d4855f093e, 0xaabf87080cd3bd52, 0x0}},
      {{0x6c79f1bd8c28c83e, 0xae62d8cef8ae2f3c, 0x122a39d54195655c, 0x0}},
      {{0x758bab48efca55da, 0x2c7e49d55bafd461, 0xb72b377293f5b622, 0x0}},
      {{0xd0b1f510045ea8bf, 0x718782e12381f321, 0xc0f4f6cf7ac6d152, 0x0}},
      {{0xb6e2f6d43fe6093f, 0xcba624f1f726e240, 0x63c33a907742ab9, 0x0}},
      {{0xf6e875562e211dfe, 0x58ef92906fcaceee, 0x616482a50b20f570, 0x0}},
      {{0x198610bf709f101f, 0xea7a6cf2a2e826c6, 0x2bfd123c27d856cf, 0x0}},
      {{0x13bae84831cbab85, 0x1ccfed8a9eabe6bb, 0xe3e0421996972a41, 0x0}},
      {{0x46438a49317626a5, 0x345707cd98a01deb, 0xdf153606cdef00ca, 0x0}},
      {{0x15e5b185287bc90c, 0x5ddca94343abff41, 0x146621d5346ed8ef, 0x0}},
      {{0xa80e0b7d53cba5b4, 0x97acd438cd03ff7c, 0x422accfcbf82e036, 0x0}},
      {{0xeb247bee9d0f6cfb, 0x7198bbcb95c241a5, 0xb3a9e253a9c58369, 0x0}},
      {{0x3bf116c66e03d47, 0x24f9b2a485491c90, 0x35adc0fa50dce047, 0x0}},
      {{0xcd5b50ce8684ae4f, 0xba9e39645370607b, 0xe3eff3be2e1a6532, 0x0}},
      {{0x499f6aa8655ee25b, 0x54fbc9056dc784d6, 0xb3d7a874b0fc6947, 0x0}},
      {{0x910e63705dbab95, 0x224de5410efb34aa, 0xfea4978c416c2a0, 0x0}},
      {{0xc0127d6361f327b6, 0x61fa86b70825cea7, 0x3103fe89912774e8, 0x0}},
      {{0x91abc3a2f7ce46c5, 0xec0b529637ce9349, 0xde3c06ecaf097ed7, 0x0}},
      {{0x660dd35e040d54e0, 0x89b8d4b3045fcf13, 0x2338706d7fa34626, 0x0}},
      {{0xd5fd76cf77aad94a, 0xf878eae6fee581e, 0x450188c74e42b599, 0x0}},
      {{0x44f6a7d5162773ef, 0x7641bd00a190034c, 0xbccfcdcdf3538c03, 0x0}},
      {{0xaad7eb636fd2993, 0x292e48ab622e4bc8, 0x2125dbb7ffe37135, 0x0}},
      {{0xf680feb2268bd147, 0xedd8a52d72b01cb9, 0xe9a208c38c83f6e5, 0x0}},
      {{0x80f13b266da2a397, 0xa4ae737bc4fc2bfe, 0x1ea388ea2f0b06bc, 0x0}},
      {{0xbb4be36a24744998, 0x4e1955c3f4950b9, 0x188e2e1f1d11c8bb, 0x0}},
      {{0x7fa8c628b22c5b43, 0x9e6d654e76a26cb3, 0xf37f9fe2393d0c60, 0x0}},
      {{0x8b6ffdfa056dbe9, 0x79620ecadc6d840a, 0xdb4efbeaaa4ce399, 0x0}},
      {{0xbe2249907d22e3ed, 0x58817a2646358e49, 0x4d4021a69f7399d8, 0x0}},
      {{0x459162b50c3eb8fe, 0xb943cefa4dfadb41, 0x4a4ecf058ba38f51, 0x0}},
      {{0x32e6b12723d9ea27, 0x8d0840c1fba50faf, 0xe2da35fbda1366fc, 0x0}},
      {{0x185887226f5fcba8, 0xe540b6b0dc11659c, 0xc52a67631746d232, 0x0}},
      {{0x5efcd33bbaf09747, 0xd90ade18d54614b, 0x1677bd0fd618b096, 0x0}},
      {{0x76fc5761ea65c900, 0x3cd26166fa2cb319, 0xd1ae0255826a1732, 0x0}},
      {{0x5ae6f936dd40f078, 0xce2b5abe461e976b, 0x71b2cc3db5009708, 0x0}},
      {{0x5ddbbb06880c2293, 0x15c6034d039c7cae, 0x3892f2b1ba9726e1, 0x0}},
      {{0x31f733aaa0eeb395, 0xd40d62676c3934eb, 0x527616743e0d5d62, 0x0}},
      {{0xf00cb59a9a3c952f, 0x421cb8fd8a6df696, 0x516a66c52c42054d, 0x0}},
      {{0xba718170b1aa652a, 0xcd71c590fd026367, 0x9794ec46076b1721, 0x0}},
      {{0x5406cd8d113e778c, 0x77fc71d96a9df8d4, 0xb62b2675b7086c3b, 0x0}},
      {{0xd185f8bab3c13d19, 0x9fc3f05379fe90ea, 0x5c1d9c5ae10c95d8, 0x0}},
      {{0xba7c95ed743a9d33, 0xc7716cc5bcdb4c2e, 0x29cb1c2ed8e8925, 0x0}},
      {{0xc042c166090ee651, 0x82b32a439d414f9e, 0x62da2caed0f3aae9, 0x0}},
      {{0xaa95ea148c04c873, 0x47e0ac05fc97e311, 0x2b79de7a080c2efb, 0x0}},
      {{0x5085d36af5818f09, 0xe5f7890f9ff69038, 0x7c81f52a9ffec587, 0x0}},
      {{0xe81393e0d76b7584, 0xa56b3831bb68cb6c, 0xa680a31108a581a0, 0x0}},
      {{0x4ed5c7cc412da295, 0xa12099d0157f9afd, 0xc279ac4c85e65015, 0x0}},
      {{0x49ab4d7c66e07f24, 0xe122dcea253601cf, 0x2679e0508a0a9b48, 0x0}},
      {{0xfe2c5ccb63e691fb, 0xc7be40171e388459, 0xe635413d04d7fa3d, 0x0}},
      {{0x81fc17ae823e3d2c, 0x42a941f300def4e1, 0x3e457c1b67266747, 0x0}},
      {{0xc29761133c01ca78, 0xe9e674e11e020ec2, 0x8716f2b5c93b844b, 0x0}},
      {{0xf92317c356b7b0dd, 0x468a46277dc815fd, 0x5bb3405f0143c7e5, 0x0}},
      {{0x940c30e8eaedf081, 0x6592ce0a5218107e, 0x96be26445d8d5f99, 0x0}},
      {{0x6089436aec016ffe, 0x2a40f427079e5442, 0xdc6b540f5e707981, 0x0}},
      {{0xa5d6e27a68823216, 0xe882e3776cf48b56, 0xaa186c38763eb12e, 0x0}},
      {{0xcfab7efa7f6a34c9, 0x66755a33a6232629, 0x23a445861caadcf5, 0x0}},
      {{0xf4742c9255aa8670, 0x18da89ddf19b8a79, 0x2217abd72d0a1e35, 0x0}},
      {{0xe0e3ec3c7d6136d0, 0x703fdb7d1177f3e1, 0xe81d98d7b804eb92, 0x0}},
      {{0xb0bbbfc4d87bf647, 0xaf0999a4101fbcab, 0x5bd3c39822064299, 0x0}},
      {{0xca14db4a7ea45ba8, 0x6c30effea5ef65f1, 0xb64cb4872447c797, 0x0}},
      {{0xb9f6c03bd260b518, 0xf04e35d4ef2e1c71, 0xdfd3462b0e82ed59, 0x0}},
      {{0xf2f6a886e1968424, 0xb547a31bfd051c46, 0x7094b9b69187177d, 0x0}},
      {{0xeab197fbb38af9b7, 0xf0555640d696c24a, 0x121f076925202ece, 0x0}},
      {{0xbb4a97cf916ab53b, 0xd347460df17d8057, 0x6cf38df5e0ba1b24, 0x0}},
      {{0x89df08ada0256ce3, 0x61091943a75bb675, 0x9bf08aa072253749, 0x0}},
      {{0x17fe5cfe943d62cc, 0x7090921cebeb15de, 0x28eaf01e96fd7407, 0x0}},
      {{0xa816f8e9cdf34a59, 0xfc2e4a614f7aeee0, 0xf57c5391c302d3c, 0x0}},
      {{0x9e44f78879ed5428, 0x95b02016389bf24b, 0x81d8d3c4cd00041b, 0x0}},
      {{0x270da03ffdaaaaef, 0x20ddaa0f03d91e6f, 0xc8efc738cad4e1cb, 0x0}},
      {{0x8fb72f75457c032c, 0x6d718b962b146c3e, 0x4383e8893981cc0b, 0x0}},
      {{0xa687d01a63a27a02, 0x76a255b3cacd3dff, 0x433a4287fa3b30aa, 0x0}},
      {{0x959b0d5b03142da7, 0x9e79bbe3fbebfd4f, 0x273480783bd50172, 0x0}},
      {{0x54e1cbd080b224ba, 0x671f7cca8bbd735d, 0xda6c81d381a37408, 0x0}},
      {{0x4ba97fc9b0219bc4, 0x6be67b2ceaca5f26, 0xe2dfccc973d435e9, 0x0}},
      {{0x68f1a8e1eac711c, 0x538e559ac44f867a, 0xa278e1425927440c, 0x0}},
      {{0x74411c26dad4c10f, 0x5f11456da8305a3b, 0x1a7a8d0ea9e5854e, 0x0}},
      {{0xd4fa04c436d21f94, 0xd0a885626898ddca, 0xed51c64a65b12045, 0x0}},
      {{0x810a3f7394aa4ec5, 0x2c4d0ed9e7cff376, 0xb32c68461068a9e9, 0x0}},
      {{0x384263799f4db887, 0xff10861014acf0e, 0x2b9422fce98eec7b, 0x0}},
      {{0xacbe3f0df2b44aec, 0x42d12397b94d953d, 0xb6471375658d714f, 0x0}},
      {{0x86ad7fce71e5dde0, 0xd56773914f82c61d, 0xaa5363e44913ebaa, 0x0}},
      {{0xcc39609f34b09837, 0x95f193e46d6936ad, 0xd90dd44cd4cc5b5e, 0x0}},
      {{0xedc25ea4326547c, 0xf9267ffe952f8ca4, 0xf21e70eb3791a534, 0x0}},
      {{0x81942545cfb7a70c, 0x3cec1fc76ed3f060, 0x7ae2c0275f55fe67, 0x0}},
      {{0x3cd1df8c38fd1b76, 0x5314cdb3a58d5f56, 0x3cea0e1bd675d645, 0x0}},
      {{0x5cc6773e18920d2c, 0xf17aa4404740db9c, 0x2ed0c5af3a1973cb, 0x0}},
      {{0xf9ed26c77f54d8c1, 0xbf1a49ff9a08c5aa, 0x7da2b9e973890a5f, 0x0}},
      {{0x1918cc3c6b833503, 0xd52f912d8b4c6896, 0x932f9534edb7236b, 0x0}},
      {{0x470741a8cbfee5bf, 0xf19beb2c835f2b76, 0x4d788092180c5a26, 0x0}},
      {{0x7ac121e107b95597, 0x1d491538436e2672, 0x13927058efdad60b, 0x0}},
      {{0x99a32433c0921351, 0xc8ff361fabfb0446, 0x8743524917cf38f1, 0x0}},
      {{0xd43807dd65b89c74, 0x7d2d4fda7503ee63, 0x479f48d12d2da569, 0x0}},
      {{0xf011caf67336920c, 0xeb8f9d59fb719d4e, 0xa52773eddd819bb8, 0x0}},
      {{0x74ff564c21f41e51, 0xc699463716ed7e1c, 0xf46e707771942d2a, 0x0}},
      {{0x6f63de1a5829b7ec, 0x38de90624dc95334, 0x4fdbc646bde3090c, 0x0}},
      {{0xe9d1c5349548032c, 0x2fcd00cb02cd5b28, 0x834e0d826e81278f, 0x0}},
      {{0x115af931b09a3282, 0xe6a3b3c05d41c685, 0x5ec9ee2ec49a4160, 0x0}},
      {{0x15c47eb9b6922799, 0x9fe35ce49bb8c3c, 0x92bfcbdd9d2c67f, 0x0}},
      {{0x596f308da452939c, 0x891c50335597df51, 0x63057a7380e5648, 0x0}},
      {{0xf5b3bc5dff4811f7, 0x7fb45d0c4fbe88c0, 0x2e79cc6fbcd95852, 0x0}},
      {{0x65061f1366031719, 0x6a0183c5839308ab, 0xba465f7ccc21fe3e, 0x0}},
      {{0xd3cc91bd950b47bb, 0x9f6ac6e6d100d9b, 0xcffa3f45d16bdf00, 0x0}},
      {{0xedc73fc494e62eb8, 0xfc4e29d64ccbecdb, 0xadca55565e76adc, 0x0}},
      {{0x7da7fe49880fb380, 0xab561c275ebdae75, 0x8f6a66a01d0284f0, 0x0}},
      {{0x380b21fb833e45b8, 0x54fb31515ea547e1, 0x1129bacb98268b9a, 0x0}},
      {{0x89f0658ac20738f6, 0xd5e90ef2d143b761, 0x9850cacc509302af, 0x0}},
      {{0x95b0663797ad030d, 0xc9a264a3b4902b6d, 0x45ab8464d01892bc, 0x0}},
      {{0x68b569f5da0bdb66, 0xe558a21446b823e3, 0x7930e50954840761, 0x0}},
      {{0x94a99456cba384b0, 0xcbdbd365f0a31751, 0xa9d6c2014f139a02, 0x0}},
      {{0x6aec0060c1a29153, 0x2ec42fb0c633f5a4, 0xf67272a0a971c3b7, 0x0}},
      {{0xfb2c4ac901e1222, 0x78739600928f4957, 0x3b136991521beee7, 0x0}},
      {{0xd200f1b2b22a8ce8, 0x20e6e3408347a788, 0x8051eddac9200053, 0x0}},
      {{0x3098b8a2c5dae22e, 0x8c52f6beffcde860, 0x61c07deb74a7dfa3, 0x0}},
      {{0xfe3d8313262deaf5, 0x39bc811a62f7ac03, 0x1deb5e90746a524b, 0x0}},
      {{0xf76b7326cb7e9f39, 0xe0a7a60ffecfca5f, 0xd6ba01ca5a1f223b, 0x0}},
      {{0xfa95abcf375b1fde, 0x93ce3b46ea353026, 0xc3789aca126daf48, 0x0}},
      {{0x1cce9c60503386b8, 0x859f0ccca3e4eaba, 0xa3174bf413d05f50, 0x0}},
      {{0x3595f178615a80aa, 0x328c5fe5ef9fbbb9, 0xe569aceb4b6bd9be, 0x0}},
      {{0x4d1c65fc5999710c, 0x7c98ae488973988a, 0x190665264479b477, 0x0}},
      {{0x546c241c4c09d612, 0x44fc435088843942, 0x641bfb0980f5ef15, 0x0}},
      {{0x6549dfd26bfb5272, 0x7f386e605204eed4, 0x796fa7a9c60dab75, 0x0}},
      {{0x47e4f91d85e51ef4, 0x1a5b46e81229a085, 0x62e9132ffea9ec60, 0x0}},
      {{0xcf43532659fc6bc3, 0x1c8c355c0afecef1, 0x4361322ee271c474, 0x0}},
      {{0xd909f2366fb278ab, 0x1e0bcd5eb3b25a46, 0xa2271c83a8a1cb1c, 0x0}},
      {{0x11ec40a3984f4d47, 0x9c091399c86fc659, 0xb2d0974d93ebcf91, 0x0}},
      {{0xc7f36e49c381fc9c, 0x78290aa4efeaf28e, 0xca18b68aa1e17bc2, 0x0}},
      {{0x7fe9fbbd7492e820, 0x54ebad7dfdcee308, 0x572260ce70164d92, 0x0}},
      {{0x3311423ad8174c69, 0x5cd6c23aab585aea, 0x4901b1c16d1cfac4, 0x0}},
      {{0x666204ef3c2475de, 0xe710d012b1aca745, 0x509e7e187d837697, 0x0}},
      {{0x68fa2aa7c4881cbe, 0x3b97af2d8d52322e, 0x42bc5d0032333c99, 0x0}},
      {{0x64f32d9e11a01f44, 0x4244eb309f2c43c3, 0xd36d528faf8f456e, 0x0}},
      {{0x2ef05da84458d1c8, 0xafe382cb6f61c7e3, 0x216026ae5295d7b, 0x0}},
      {{0xcd7e04fa8c8fc0a7, 0x1e81af2483ec4850, 0x71080118a03e102d, 0x0}},
      {{0x72b306b26512fdbb, 0x65f7c1e35d075840, 0xe65e6e2d66c890d0, 0x0}},
      {{0xd4a3cafbfa30291b, 0xfc8f4979e810c4c9, 0x82a1de439fbd5c02, 0x0}},
      {{0x6e1fed2b8adb8753, 0x440992fba9ac5415, 0x53a99c4d607975e8, 0x0}},
      {{0x2337f04353bc7949, 0x8d449cd2caeedbcb, 0xdd8124db5289c96e, 0x0}},
  };
  field::GF2_192 v("0x0123456789abcdeffedcba98765432100123456789abcdef");
  field::GF2_192 result = v.multiply_with_GF2_matrix(m1);
  field::GF2_192 result_transposed =
      v.multiply_with_transposed_GF2_matrix(m1_transposed);
  REQUIRE(result == result_transposed);
}