#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../field.h"
#include "utils.h"

#include <NTL/GF2EX.h>

TEST_CASE("Constructors for GF(2^256)", "[GF2_256]") {
  field::GF2_256 a;
  a.set_coeff(0);
  a.set_coeff(1);
  a.set_coeff(2);
  a.set_coeff(3);
  a.set_coeff(6);
  a.set_coeff(8);
  a.set_coeff(10);
  a.set_coeff(12);
  a.set_coeff(13);
  a.set_coeff(14);
  a.set_coeff(20);
  a.set_coeff(22);
  a.set_coeff(23);
  a.set_coeff(24);
  a.set_coeff(26);
  a.set_coeff(28);
  a.set_coeff(34);
  a.set_coeff(36);
  a.set_coeff(39);
  a.set_coeff(40);
  a.set_coeff(41);
  a.set_coeff(44);
  a.set_coeff(45);
  a.set_coeff(46);
  a.set_coeff(47);
  a.set_coeff(48);
  a.set_coeff(49);
  a.set_coeff(50);
  a.set_coeff(51);
  a.set_coeff(54);
  a.set_coeff(55);
  a.set_coeff(58);
  a.set_coeff(60);
  a.set_coeff(61);
  a.set_coeff(63);
  a.set_coeff(65);
  a.set_coeff(66);
  a.set_coeff(70);
  a.set_coeff(74);
  a.set_coeff(77);
  a.set_coeff(78);
  a.set_coeff(79);
  a.set_coeff(80);
  a.set_coeff(82);
  a.set_coeff(83);
  a.set_coeff(84);
  a.set_coeff(85);
  a.set_coeff(86);
  a.set_coeff(87);
  a.set_coeff(88);
  a.set_coeff(89);
  a.set_coeff(91);
  a.set_coeff(93);
  a.set_coeff(94);
  a.set_coeff(95);
  a.set_coeff(96);
  a.set_coeff(97);
  a.set_coeff(100);
  a.set_coeff(102);
  a.set_coeff(103);
  a.set_coeff(105);
  a.set_coeff(108);
  a.set_coeff(109);
  a.set_coeff(110);
  a.set_coeff(112);
  a.set_coeff(113);
  a.set_coeff(114);
  a.set_coeff(115);
  a.set_coeff(118);
  a.set_coeff(119);
  a.set_coeff(120);
  a.set_coeff(122);
  a.set_coeff(123);
  a.set_coeff(126);
  a.set_coeff(129);
  a.set_coeff(132);
  a.set_coeff(133);
  a.set_coeff(134);
  a.set_coeff(135);
  a.set_coeff(136);
  a.set_coeff(137);
  a.set_coeff(138);
  a.set_coeff(139);
  a.set_coeff(141);
  a.set_coeff(142);
  a.set_coeff(143);
  a.set_coeff(145);
  a.set_coeff(146);
  a.set_coeff(148);
  a.set_coeff(153);
  a.set_coeff(155);
  a.set_coeff(157);
  a.set_coeff(168);
  a.set_coeff(169);
  a.set_coeff(170);
  a.set_coeff(172);
  a.set_coeff(176);
  a.set_coeff(179);
  a.set_coeff(183);
  a.set_coeff(185);
  a.set_coeff(186);
  a.set_coeff(188);
  a.set_coeff(189);
  a.set_coeff(190);
  a.set_coeff(193);
  a.set_coeff(194);
  a.set_coeff(197);
  a.set_coeff(199);
  a.set_coeff(202);
  a.set_coeff(203);
  a.set_coeff(204);
  a.set_coeff(205);
  a.set_coeff(207);
  a.set_coeff(208);
  a.set_coeff(209);
  a.set_coeff(211);
  a.set_coeff(212);
  a.set_coeff(213);
  a.set_coeff(215);
  a.set_coeff(216);
  a.set_coeff(218);
  a.set_coeff(219);
  a.set_coeff(222);
  a.set_coeff(230);
  a.set_coeff(233);
  a.set_coeff(234);
  a.set_coeff(237);
  a.set_coeff(238);
  a.set_coeff(240);
  a.set_coeff(241);
  a.set_coeff(243);
  a.set_coeff(248);
  a.set_coeff(252);
  a.set_coeff(255);

  field::GF2_256 a_int(
      std::array<uint64_t, 4>{0xB4CFF39415D0754F, 0x4DCF72D3EBFDE446,
                              0x768917002A16EFF2, 0x910B66404DBBBCA6});
  field::GF2_256 a_str(
      "0x910B66404DBBBCA6768917002A16EFF24DCF72D3EBFDE446B4CFF39415D0754F");
  REQUIRE(a == a_int);
  REQUIRE(a == a_str);
}

TEST_CASE("Basic Arithmetic GF(2^256)", "[GF2_256]") {
  field::GF2_256 zero;
  field::GF2_256 one(1);
  field::GF2_256 x(2);
  field::GF2_256 x_2(4);

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
TEST_CASE("Modular Arithmetic KATs GF(2^256)", "[GF2_256]") {
  field::GF2_256 a, b, ab;
  a.set_coeff(0);
  a.set_coeff(1);
  a.set_coeff(2);
  a.set_coeff(3);
  a.set_coeff(6);
  a.set_coeff(8);
  a.set_coeff(10);
  a.set_coeff(12);
  a.set_coeff(13);
  a.set_coeff(14);
  a.set_coeff(20);
  a.set_coeff(22);
  a.set_coeff(23);
  a.set_coeff(24);
  a.set_coeff(26);
  a.set_coeff(28);
  a.set_coeff(34);
  a.set_coeff(36);
  a.set_coeff(39);
  a.set_coeff(40);
  a.set_coeff(41);
  a.set_coeff(44);
  a.set_coeff(45);
  a.set_coeff(46);
  a.set_coeff(47);
  a.set_coeff(48);
  a.set_coeff(49);
  a.set_coeff(50);
  a.set_coeff(51);
  a.set_coeff(54);
  a.set_coeff(55);
  a.set_coeff(58);
  a.set_coeff(60);
  a.set_coeff(61);
  a.set_coeff(63);
  a.set_coeff(65);
  a.set_coeff(66);
  a.set_coeff(70);
  a.set_coeff(74);
  a.set_coeff(77);
  a.set_coeff(78);
  a.set_coeff(79);
  a.set_coeff(80);
  a.set_coeff(82);
  a.set_coeff(83);
  a.set_coeff(84);
  a.set_coeff(85);
  a.set_coeff(86);
  a.set_coeff(87);
  a.set_coeff(88);
  a.set_coeff(89);
  a.set_coeff(91);
  a.set_coeff(93);
  a.set_coeff(94);
  a.set_coeff(95);
  a.set_coeff(96);
  a.set_coeff(97);
  a.set_coeff(100);
  a.set_coeff(102);
  a.set_coeff(103);
  a.set_coeff(105);
  a.set_coeff(108);
  a.set_coeff(109);
  a.set_coeff(110);
  a.set_coeff(112);
  a.set_coeff(113);
  a.set_coeff(114);
  a.set_coeff(115);
  a.set_coeff(118);
  a.set_coeff(119);
  a.set_coeff(120);
  a.set_coeff(122);
  a.set_coeff(123);
  a.set_coeff(126);
  a.set_coeff(129);
  a.set_coeff(132);
  a.set_coeff(133);
  a.set_coeff(134);
  a.set_coeff(135);
  a.set_coeff(136);
  a.set_coeff(137);
  a.set_coeff(138);
  a.set_coeff(139);
  a.set_coeff(141);
  a.set_coeff(142);
  a.set_coeff(143);
  a.set_coeff(145);
  a.set_coeff(146);
  a.set_coeff(148);
  a.set_coeff(153);
  a.set_coeff(155);
  a.set_coeff(157);
  a.set_coeff(168);
  a.set_coeff(169);
  a.set_coeff(170);
  a.set_coeff(172);
  a.set_coeff(176);
  a.set_coeff(179);
  a.set_coeff(183);
  a.set_coeff(185);
  a.set_coeff(186);
  a.set_coeff(188);
  a.set_coeff(189);
  a.set_coeff(190);
  a.set_coeff(193);
  a.set_coeff(194);
  a.set_coeff(197);
  a.set_coeff(199);
  a.set_coeff(202);
  a.set_coeff(203);
  a.set_coeff(204);
  a.set_coeff(205);
  a.set_coeff(207);
  a.set_coeff(208);
  a.set_coeff(209);
  a.set_coeff(211);
  a.set_coeff(212);
  a.set_coeff(213);
  a.set_coeff(215);
  a.set_coeff(216);
  a.set_coeff(218);
  a.set_coeff(219);
  a.set_coeff(222);
  a.set_coeff(230);
  a.set_coeff(233);
  a.set_coeff(234);
  a.set_coeff(237);
  a.set_coeff(238);
  a.set_coeff(240);
  a.set_coeff(241);
  a.set_coeff(243);
  a.set_coeff(248);
  a.set_coeff(252);
  a.set_coeff(255);

  b.set_coeff(1);
  b.set_coeff(2);
  b.set_coeff(7);
  b.set_coeff(8);
  b.set_coeff(10);
  b.set_coeff(11);
  b.set_coeff(12);
  b.set_coeff(13);
  b.set_coeff(14);
  b.set_coeff(15);
  b.set_coeff(21);
  b.set_coeff(22);
  b.set_coeff(23);
  b.set_coeff(24);
  b.set_coeff(25);
  b.set_coeff(26);
  b.set_coeff(27);
  b.set_coeff(28);
  b.set_coeff(29);
  b.set_coeff(30);
  b.set_coeff(31);
  b.set_coeff(32);
  b.set_coeff(33);
  b.set_coeff(35);
  b.set_coeff(36);
  b.set_coeff(37);
  b.set_coeff(38);
  b.set_coeff(39);
  b.set_coeff(40);
  b.set_coeff(42);
  b.set_coeff(44);
  b.set_coeff(47);
  b.set_coeff(48);
  b.set_coeff(52);
  b.set_coeff(54);
  b.set_coeff(55);
  b.set_coeff(57);
  b.set_coeff(60);
  b.set_coeff(63);
  b.set_coeff(67);
  b.set_coeff(69);
  b.set_coeff(70);
  b.set_coeff(71);
  b.set_coeff(73);
  b.set_coeff(74);
  b.set_coeff(75);
  b.set_coeff(78);
  b.set_coeff(80);
  b.set_coeff(83);
  b.set_coeff(85);
  b.set_coeff(87);
  b.set_coeff(90);
  b.set_coeff(91);
  b.set_coeff(94);
  b.set_coeff(96);
  b.set_coeff(97);
  b.set_coeff(100);
  b.set_coeff(102);
  b.set_coeff(106);
  b.set_coeff(109);
  b.set_coeff(110);
  b.set_coeff(111);
  b.set_coeff(114);
  b.set_coeff(115);
  b.set_coeff(117);
  b.set_coeff(118);
  b.set_coeff(120);
  b.set_coeff(122);
  b.set_coeff(124);
  b.set_coeff(126);
  b.set_coeff(127);
  b.set_coeff(131);
  b.set_coeff(132);
  b.set_coeff(133);
  b.set_coeff(135);
  b.set_coeff(138);
  b.set_coeff(141);
  b.set_coeff(143);
  b.set_coeff(144);
  b.set_coeff(145);
  b.set_coeff(150);
  b.set_coeff(153);
  b.set_coeff(154);
  b.set_coeff(156);
  b.set_coeff(157);
  b.set_coeff(160);
  b.set_coeff(161);
  b.set_coeff(166);
  b.set_coeff(167);
  b.set_coeff(172);
  b.set_coeff(173);
  b.set_coeff(174);
  b.set_coeff(175);
  b.set_coeff(176);
  b.set_coeff(177);
  b.set_coeff(179);
  b.set_coeff(180);
  b.set_coeff(182);
  b.set_coeff(184);
  b.set_coeff(187);
  b.set_coeff(189);
  b.set_coeff(190);
  b.set_coeff(200);
  b.set_coeff(201);
  b.set_coeff(204);
  b.set_coeff(206);
  b.set_coeff(207);
  b.set_coeff(208);
  b.set_coeff(209);
  b.set_coeff(210);
  b.set_coeff(211);
  b.set_coeff(213);
  b.set_coeff(214);
  b.set_coeff(217);
  b.set_coeff(218);
  b.set_coeff(219);
  b.set_coeff(221);
  b.set_coeff(222);
  b.set_coeff(223);
  b.set_coeff(225);
  b.set_coeff(227);
  b.set_coeff(228);
  b.set_coeff(230);
  b.set_coeff(232);
  b.set_coeff(238);
  b.set_coeff(242);
  b.set_coeff(244);
  b.set_coeff(246);
  b.set_coeff(247);
  b.set_coeff(248);
  b.set_coeff(249);
  b.set_coeff(250);
  b.set_coeff(251);
  b.set_coeff(252);
  b.set_coeff(253);
  b.set_coeff(254);
  b.set_coeff(255);

  ab.set_coeff(2);
  ab.set_coeff(4);
  ab.set_coeff(10);
  ab.set_coeff(12);
  ab.set_coeff(14);
  ab.set_coeff(15);
  ab.set_coeff(16);
  ab.set_coeff(17);
  ab.set_coeff(18);
  ab.set_coeff(19);
  ab.set_coeff(20);
  ab.set_coeff(21);
  ab.set_coeff(22);
  ab.set_coeff(25);
  ab.set_coeff(29);
  ab.set_coeff(30);
  ab.set_coeff(31);
  ab.set_coeff(34);
  ab.set_coeff(42);
  ab.set_coeff(46);
  ab.set_coeff(47);
  ab.set_coeff(51);
  ab.set_coeff(55);
  ab.set_coeff(58);
  ab.set_coeff(64);
  ab.set_coeff(65);
  ab.set_coeff(66);
  ab.set_coeff(67);
  ab.set_coeff(70);
  ab.set_coeff(71);
  ab.set_coeff(73);
  ab.set_coeff(74);
  ab.set_coeff(75);
  ab.set_coeff(77);
  ab.set_coeff(78);
  ab.set_coeff(81);
  ab.set_coeff(82);
  ab.set_coeff(86);
  ab.set_coeff(88);
  ab.set_coeff(89);
  ab.set_coeff(92);
  ab.set_coeff(95);
  ab.set_coeff(96);
  ab.set_coeff(97);
  ab.set_coeff(101);
  ab.set_coeff(102);
  ab.set_coeff(103);
  ab.set_coeff(104);
  ab.set_coeff(106);
  ab.set_coeff(107);
  ab.set_coeff(111);
  ab.set_coeff(112);
  ab.set_coeff(117);
  ab.set_coeff(119);
  ab.set_coeff(124);
  ab.set_coeff(126);
  ab.set_coeff(129);
  ab.set_coeff(132);
  ab.set_coeff(133);
  ab.set_coeff(139);
  ab.set_coeff(142);
  ab.set_coeff(143);
  ab.set_coeff(144);
  ab.set_coeff(146);
  ab.set_coeff(148);
  ab.set_coeff(150);
  ab.set_coeff(151);
  ab.set_coeff(152);
  ab.set_coeff(153);
  ab.set_coeff(155);
  ab.set_coeff(157);
  ab.set_coeff(159);
  ab.set_coeff(160);
  ab.set_coeff(162);
  ab.set_coeff(164);
  ab.set_coeff(168);
  ab.set_coeff(169);
  ab.set_coeff(170);
  ab.set_coeff(171);
  ab.set_coeff(173);
  ab.set_coeff(176);
  ab.set_coeff(177);
  ab.set_coeff(183);
  ab.set_coeff(185);
  ab.set_coeff(188);
  ab.set_coeff(189);
  ab.set_coeff(190);
  ab.set_coeff(191);
  ab.set_coeff(192);
  ab.set_coeff(196);
  ab.set_coeff(198);
  ab.set_coeff(199);
  ab.set_coeff(203);
  ab.set_coeff(204);
  ab.set_coeff(205);
  ab.set_coeff(208);
  ab.set_coeff(209);
  ab.set_coeff(213);
  ab.set_coeff(214);
  ab.set_coeff(215);
  ab.set_coeff(220);
  ab.set_coeff(222);
  ab.set_coeff(224);
  ab.set_coeff(226);
  ab.set_coeff(229);
  ab.set_coeff(230);
  ab.set_coeff(231);
  ab.set_coeff(234);
  ab.set_coeff(237);
  ab.set_coeff(238);
  ab.set_coeff(240);
  ab.set_coeff(241);
  ab.set_coeff(244);
  ab.set_coeff(255);

  field::GF2_256 a_int(
      std::array<uint64_t, 4>{0xB4CFF39415D0754F, 0x4DCF72D3EBFDE446,
                              0x768917002A16EFF2, 0x910B66404DBBBCA6}),
      b_int(std::array<uint64_t, 4>{0x92D195FBFFE0FD86, 0xD56CE4534CA94EE8,
                                    0x695BF0C33643A4B8, 0xFFD4415AEE6FD300});
  REQUIRE(a == a_int);
  REQUIRE(b == b_int);

  field::GF2_256 ab_calc = a_int * b_int;
  REQUIRE(ab_calc == ab);
}

TEST_CASE("NTL to_bytes = custom to_bytes GF(2^256)", "[field]") {
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_256);
  field::GF2_256 a, b;
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
  std::vector<uint8_t> buffer_c(field::GF2_256::BYTE_SIZE);
  BytesFromGF2X(buffer_c.data(), poly_rep_c, buffer_c.size());
  const GF2X &poly_rep_d = rep(d_e);
  std::vector<uint8_t> buffer_d(field::GF2_256::BYTE_SIZE);
  BytesFromGF2X(buffer_d.data(), poly_rep_d, buffer_d.size());

  std::vector<uint8_t> buffer_a(field::GF2_256::BYTE_SIZE);
  a.to_bytes(buffer_a.data());
  std::vector<uint8_t> buffer_b(field::GF2_256::BYTE_SIZE);
  b.to_bytes(buffer_b.data());
  REQUIRE(buffer_a == buffer_c);
  REQUIRE(buffer_b == buffer_d);
}
TEST_CASE("NTL to custom conversion GF(2^256)", "[GF2_256]") {
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_256);
  field::GF2_256 a, b;
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

  field::GF2_256 ab = a * b;
  GF2E a_ntl = utils::custom_to_ntl(a);
  GF2E ab_ntl = utils::custom_to_ntl(ab);
  GF2E b_ntl = ab_ntl / a_ntl;
  field::GF2_256 b2 = utils::ntl_to_custom<field::GF2_256>(b_ntl);
  REQUIRE(b == b2);
}
TEST_CASE("NTL inverse == custom GF(2^256)", "[GF2_256]") {
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_256);
  field::GF2_256 a;
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

  field::GF2_256 b = a.inverse();
  field::GF2_256 c =
      utils::ntl_to_custom<field::GF2_256>(inv(utils::custom_to_ntl(a)));
  // std::cout << utils::custom_to_ntl(a) << ", " << utils::custom_to_ntl(b)
  //<< ", " << utils::custom_to_ntl(c) << "\n";
  // std::cout << utils::custom_to_ntl(a * b) << ", "
  //<< utils::custom_to_ntl(a * c) << ", "
  //<< utils::custom_to_ntl(a) * utils::custom_to_ntl(c) << "\n";
  REQUIRE(b == c);
  REQUIRE(a * b == field::GF2_256(1));
}
TEST_CASE("NTL interpolation == custom GF(2^256)", "[GF2_256]") {
  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_256);

  std::vector<field::GF2_256> a =
      field::get_first_n_field_elements<field::GF2_256>(100);
  vec_GF2E b = utils::get_first_n_field_elements(100);
  for (size_t i = 0; i < 100; i++) {
    REQUIRE(a[i] == utils::ntl_to_custom<field::GF2_256>(b[i]));
  }
  std::vector<field::GF2_256> a_from_roots = field::build_from_roots(a);
  GF2EX b_from_roots = BuildFromRoots(b);
  REQUIRE(a_from_roots.size() == (size_t)b_from_roots.rep.length());
  for (size_t j = 0; j < a_from_roots.size(); j++) {
    REQUIRE(a_from_roots[j] ==
            utils::ntl_to_custom<field::GF2_256>(b_from_roots[j]));
  }

  std::vector<std::vector<field::GF2_256>> a_lag =
      field::precompute_lagrange_polynomials(a);
  std::vector<GF2EX> b_lag = utils::precompute_lagrange_polynomials(b);

  REQUIRE(a_lag.size() == b_lag.size());
  for (size_t i = 0; i < a_lag.size(); i++) {
    REQUIRE(a_lag[i].size() == (size_t)b_lag[i].rep.length());
    for (size_t j = 0; j < a_lag[i].size(); j++) {
      REQUIRE(a_lag[i][j] == utils::ntl_to_custom<field::GF2_256>(b_lag[i][j]));
    }
  }
}
TEST_CASE("NTL dot product == custom GF(2^256)", "[GF2_256]") {

  utils::init_ntl_extension_field(utils::NTL_INSTANCE::GF2_256);
  std::vector<field::GF2_256> a =
      field::get_first_n_field_elements<field::GF2_256>(100);
  std::vector<field::GF2_256> b =
      field::get_first_n_field_elements<field::GF2_256>(200);
  b.erase(b.begin(), b.begin() + 100);

  vec_GF2E a_ntl = utils::get_first_n_field_elements(200);
  vec_GF2E b_ntl;
  b_ntl.SetLength(100);
  for (size_t i = 0; i < 100; i++)
    b_ntl[i] = a_ntl[100 + i];
  a_ntl.SetLength(100);

  field::GF2_256 result = dot_product(a, b);
  GF2E result_ntl;
  NTL::InnerProduct(result_ntl, a_ntl, b_ntl);
  REQUIRE(result == utils::ntl_to_custom<field::GF2_256>(result_ntl));
}

TEST_CASE("Matmul and Transposed Matmul have same result GF(2^256)",
          "[GF2_256]") {
  alignas(32) constexpr static std::array<uint64_t, 4> m1[256] = {
      {{0x9134a7fae335664, 0xe9389339f9b0017f, 0xee0007084c8db195,
        0x4ace0b143fdd2a3d}},
      {{0xb0d15e4d6f27c570, 0x2f018da210ca8a89, 0xddbfd5a71c8c3d1a,
        0xb6be34664f55af7}},
      {{0x304cb4672115ce3e, 0xd9b43b255ba3dda5, 0x883f5b29535c7512,
        0x8f861a9f22dd2b83}},
      {{0xc23ece3eb21bdf37, 0xc10b1fa368721f7f, 0xb0268ded75881396,
        0x66e5cb11797ba3a5}},
      {{0x28c6ea59445792ee, 0x53b70359916d3d2b, 0x37edf7878d666fc6,
        0x43ab27c91734cd7b}},
      {{0x3f4feb871174560f, 0x39c655dd7c7fd8ea, 0xe73892368d0535e,
        0x9ec978489475c1a5}},
      {{0x95b12f13daf98ffe, 0xf7cf856db2c39f2f, 0x68960868d0f089af,
        0xb26807bb7647a2c1}},
      {{0xaab968ed8933f404, 0xa240794fa2e2d448, 0xd17cae968cc1ba02,
        0x6e79cc7d873bf949}},
      {{0x6a631aa4879a355d, 0xab23af41f5b78b2b, 0xe0202eca8cbd6fe7,
        0x9357d868fafe933c}},
      {{0x36cbc6c253bcf2d2, 0x6dcaf27ef1ae4d70, 0x8b03165dad40a225,
        0x70ec832fd48f94af}},
      {{0x1b12ef83b7bcd5c2, 0x9444016943be7371, 0xbe6d28196b21e1a,
        0xe821bfef84a8b01a}},
      {{0xdff2995b020b9b75, 0x32d899f2263f1c13, 0x516e27ff2c3be4ec,
        0x963f0aef0273134b}},
      {{0x7a774b643339d790, 0xed5375addda736aa, 0x94dee8264fdd7e5f,
        0x81ac3bee029cfcfe}},
      {{0xddc35cb875f18fe3, 0xbcc02102dfa3921e, 0x86dff73ba721a491,
        0xdd0e8b51713d56c2}},
      {{0xf8885a6ac55dbc7, 0xd9d713df11e50352, 0x45d97e7e60c15453,
        0xf7a362b088c727f7}},
      {{0x225a2941a136115e, 0x5d34a837fc0f7f0d, 0x80c1e40345007102,
        0x6387331f76f4119f}},
      {{0x69dc15df2cd70fb7, 0xae066428489a6d1f, 0xd147af7f9d12d4a8,
        0xae5ecb2634b41ce3}},
      {{0x3f233c4fcb689383, 0xa150a9107a2be1c2, 0xa1f025ef79cb9270,
        0xc90dfa565d6fc705}},
      {{0xaf44d6c5ad596ea6, 0xa8bc0512094d6a20, 0xe4cf61a9a6b33d8d,
        0x36b7b29e632d9b2f}},
      {{0xb56796dce7b41ed7, 0xe51bbbee7c1359a8, 0xebe4bd42282d5f13,
        0x13432f11bca6599}},
      {{0x8133b664a10c2d89, 0xee6276800049984, 0xe11edc106d90433d,
        0x36d4b15068fae5e4}},
      {{0xda9029403e5a8eda, 0xbf2846ac21298cae, 0xe1113d52ebc397c2,
        0x186f8c93d6e84f45}},
      {{0x5150cfd1769a5639, 0xb5f5a5ec18bfe8b9, 0x37e7c1b76817971,
        0x3173a2acb8624978}},
      {{0x891fdc980b611b4e, 0xe5618397772b549e, 0xf66e68528d1092b8,
        0xf5c715afda2bafdd}},
      {{0x32d7ca02887f471e, 0xb7a1401e5a1488f9, 0x61a7000a77034456,
        0xf0e069f65035b9cf}},
      {{0x40ea0862179e89a8, 0xfaa3b810d0af07f2, 0x9fd59868e9806901,
        0x9f1e71af5c9e8885}},
      {{0x41e85a48cc5a88ea, 0x84b5b602bb6b6d25, 0xccaebb4d26cb7783,
        0x459fa00d0394763b}},
      {{0xb26e60b9e756db40, 0x3eb8fa7b0a5edaee, 0x71d0be184c4cc031,
        0xe90aad6b1d41bebd}},
      {{0xd549d2ef6d4af2c4, 0x271ea8d96a993f55, 0x8a82468fbd0c55f9,
        0xd57e18ff70e63315}},
      {{0xbbb528290dbbafab, 0x7121c20d1e1aea83, 0xb27e270c2bf8fd8b,
        0x174b2e67c63c4de8}},
      {{0xda1dc6d0ae009800, 0x43c16cdab7e198a5, 0x2214a28fa57d66ea,
        0x335f9ae935fa369a}},
      {{0xe70f4269a88664fe, 0xfc08beb8f034babb, 0xc3c0e4b56425f64d,
        0x7f8e5d45da4fc5b8}},
      {{0x78b941889fc8fe2d, 0x57c4cc4f8433c431, 0xc1d81822f010fd61,
        0x81ea7f145ac33333}},
      {{0x19ff29388c35b55d, 0x8520241a71ad0b47, 0xcfcac19e0ec3fceb,
        0xe67f1be40a8316d8}},
      {{0x73a5c8f4c69ab6f2, 0x439b7425bd44b8bc, 0x854fe9ddacb08a6,
        0xc0d6b7ade6a5effd}},
      {{0xbc34ced1bde240de, 0x3f22951a44ad98f0, 0xa6d38b0e59a8b4b6,
        0x3f096617ef3d096e}},
      {{0x2f722516d5431a39, 0x94606e81c9d99397, 0x2d9eea3cedea74c1,
        0x9db424625094f48f}},
      {{0x8ce820cbd457eae3, 0xd1f4890f04a6fe7c, 0xcee9b76734b99f68,
        0x40f59a885547bc9c}},
      {{0x1313f2c6aac9b7d7, 0x702addf795e340b7, 0x54836a4f8f69827c,
        0x7ff8d14431336b5a}},
      {{0xbd0a1410e83ea084, 0x6d0273b84aa96c9a, 0xab5a8d19bdaff3ca,
        0x138635851db2f16e}},
      {{0x993918700e34e1b8, 0x10d00b67d57d7060, 0x48196485ee197c3f,
        0xbea1c3cd0ac0405a}},
      {{0x733aa94281837d28, 0x965e0898e2f88cda, 0xdb3322f2b30141c5,
        0x910c7a606458fb25}},
      {{0xf8ff9c515518541d, 0x5a99b9a36f360b5, 0xf2521f116b3d4fd9,
        0x46972c3e9bcdd246}},
      {{0x8752151eb404e616, 0xe192f41b9048adc6, 0xeb30eb535132f50,
        0x33f46a925a2ab0b7}},
      {{0x70ffb8509a39a8ca, 0x32ae4163d00b9ec7, 0x595b0dcc09918d75,
        0x50c35efd6b748fed}},
      {{0x4dbce84745a3e8ce, 0x866450c75cfca41a, 0xdd8193b63e825161,
        0x5f9d04531c11dba7}},
      {{0x59a087427b935387, 0x3c06589346babdb8, 0xb086d45f5e5a4bd,
        0xc71743d06169c336}},
      {{0xa397ef5ca8afc057, 0x40bcb3fc9985c91, 0xd69c4f9d9f9ceb4b,
        0xb93e4796ec23f455}},
      {{0x3d6793c88e2dd221, 0xb2544c104a499901, 0xabd2406926f6d447,
        0xb29803a20605d988}},
      {{0x64652949dbe5fdc4, 0xafe4b91f624e7ee, 0xc4097977e073af61,
        0xfb2830f871a76277}},
      {{0x15eda38cff585113, 0x84227fa7400368fa, 0xc3c2ea8599197db,
        0xb9df5e784541a4cd}},
      {{0x35448feccdbf36c8, 0xb73b1d2c61be5252, 0xd2609facdbbd2b25,
        0xe61d378090bbd941}},
      {{0x317a15fa6fca21c6, 0x29364d686b55eced, 0x391288d594c5cb2,
        0x8cf18c5c279e9cb5}},
      {{0x4c5a9d65f98e46f4, 0x4fffc6ac4e0a4ff2, 0x6edd67c3cc7c1836,
        0x3c2ab63fe8e2b0d9}},
      {{0xc36fa0786937f90c, 0x4a65d4e2f88958de, 0xd29754dcb44777ef,
        0xeb68500f21e56df1}},
      {{0xf0bf2b254ea10df2, 0x1ac5a09948c9ffc3, 0x1540adc7860f0f7f,
        0xfa6df926f432a08a}},
      {{0xfec14fd5bd8c6962, 0xf1fad324dab474f2, 0xe87776e562d7f675,
        0x79f86fe4b043e206}},
      {{0x7aa36cdb1d5d51a, 0x25b0e2df2d92f3ac, 0x15361f606b8f2ed9,
        0x50107795e9a8385c}},
      {{0x7f8000d7f072eed8, 0x45358bdff86b8565, 0xca6c3f87c4dabd9e,
        0xe1e3e26933f8b63}},
      {{0xe9c4d0009cc1e912, 0x198b8c0d3481360a, 0x70e00e82737407de,
        0x14a301ed2675785a}},
      {{0x6480a4d6827b366e, 0xc3b65335a014ecf, 0xc13ed3c6462f3e0b,
        0x65395526bf2e5f9d}},
      {{0x51678802e6769d4, 0x3b978e4997edbe4a, 0x8b386fdd4076fed3,
        0xa9b9346df1520f95}},
      {{0x2f5b4d86d1fc46b2, 0xd2def05d1733b6a3, 0x78c59d731eec0252,
        0x460c3faa2d81b0df}},
      {{0xa17bc8bf5145789f, 0x15a2503cce79c7d9, 0xf6f3bb3df135803f,
        0xb0acb6f9905460be}},
      {{0xfe815158e3743079, 0xc6c695cef6bb1b9b, 0x4a885b179a594aac,
        0x2d52e616f6e5916}},
      {{0xae7396c60b4fe2b, 0x5819b85d721428fc, 0x3e367ad0b3dc0e80,
        0x848d8e674b2035d1}},
      {{0x70a6116f5f18415, 0xe594b4a6c48e5337, 0xa0f50cb4655c2159,
        0xb3f2f04d6aebf1cd}},
      {{0x4615986d33e7183b, 0xb196d778ba9a0f27, 0xfe1cddfff5fb3b2d,
        0xbe39deac90fb017a}},
      {{0xbb78ee9e6d09c2f4, 0xa6d5fe6311caa25b, 0xfd9f9297cf49d16a,
        0xad96b23bdbfd575c}},
      {{0x9082821d4b9382b8, 0xabedc85cb10ac471, 0x57f848e8505f5c48,
        0x18b53668174d534e}},
      {{0x6b9c8825a480be68, 0x5bbc7c8466f8013c, 0x7a6186adc9733e1a,
        0x6147c8ab1dd140f6}},
      {{0x3a2c3b4c80d8c290, 0xabb74035885a8184, 0x60d871ee5e02690a,
        0x6a8b6e57f5b0a510}},
      {{0x7bebc0a06b00821, 0xa9db39f796f2cf85, 0xc24f09483f01ce43,
        0x39750efb0563c73c}},
      {{0x5bfebf281218a2df, 0x22b21413c0df1242, 0x256346b68af940cd,
        0x413ca9324e11869c}},
      {{0x5a6b2ba12d5365f2, 0x3ebc67b724f118e1, 0x794a4a50b5264c7c,
        0x2e77107ba465cbcd}},
      {{0xc33b045967c5491a, 0x21528dda5c5f87ce, 0xbc5027b0bac11e3d,
        0x49bac17b7d37faf7}},
      {{0x643822899fc99f1f, 0xa9be422d1605a3a5, 0xfed895045e5acdf4,
        0xa3d6a91a210e7b3e}},
      {{0x3e32252040fba384, 0x7d9d3e125d6f54a2, 0x6ab77d2cf39916c2,
        0x5afe95976e5e5f01}},
      {{0x6cd5c934551cdd98, 0xc2fcde887d25d76, 0x8bc3c2737dc50448,
        0xfa5ec59e5d21fd6f}},
      {{0x4424a07adaa737e, 0x2d4ad4c37188e0c2, 0x84ec9efbcf8aaaf0,
        0x66c23788aa8f781d}},
      {{0xc04e962dfd0cb98, 0xced20af6b431cfde, 0x561ca7ae1830c5d6,
        0x1098b45514298556}},
      {{0xd457a758ccd20c1d, 0xfc41e49cdb19932a, 0x8e6c349d10da13c4,
        0x3c204d8087e81ca}},
      {{0xc387b6a627bb2e10, 0x7cb9b22487c590e7, 0xdb427700c35f8e81,
        0xfbaa2909e8ad8a0d}},
      {{0xd882a5303a1617a0, 0xd7160e3ce8228083, 0xe9ff713520befc6e,
        0x188eb848ab0516c2}},
      {{0x6fbd142d6eecfb71, 0xd074aa94bc609698, 0xe7fc792eb6eea416,
        0xa933594a51316484}},
      {{0xbb1caf569f0e886, 0x6a1497386226cd43, 0x3918620cda246952,
        0x541064f41d8d962f}},
      {{0xf25bc483fe7b5358, 0xf0dec745f5c51274, 0x8c89c540b47274d8,
        0x126ed584ec995e15}},
      {{0x63c6c450596f86eb, 0xdd3885a2163b6570, 0x2249dfbbd91f29d4,
        0x588a01af907c661}},
      {{0xf5cb31136fc885fe, 0xed1c1ade007ee872, 0x672a1656a23562ea,
        0xf16c3194f04b8d5}},
      {{0xbdf7ccaf80dff64e, 0x2edb2ef4f2466a82, 0xc003ec0bd0347b4d,
        0x4d26d96ed32bfbde}},
      {{0xacafcf2ebb5148e0, 0x43fb4b89aaf32b36, 0x280a61b16689a5a4,
        0x7330eaef3d7cf285}},
      {{0xd2f3c6b291301ea4, 0xf381405b4e3412fa, 0xc573e64f1045de04,
        0x4bd1fa8e94df3b61}},
      {{0x624c7dab544f1bc0, 0xd5abbf56eaebf34b, 0xc32ec9a01824b40e,
        0xb8e0cd1a3fe494e5}},
      {{0xe6f24df9a02ea6c2, 0xcb0cc0b5db7a7300, 0x824691637496c965,
        0x2f1125a65f1d1c45}},
      {{0xcfbf19190f2c11b2, 0x69241ee340501664, 0xa619286c1db96b9f,
        0x38a273851a706f30}},
      {{0x1d6c44564d11eab2, 0xcab3e37b37eb16c2, 0xe0adae7ae78e57ff,
        0x468bc3e0f69a772b}},
      {{0xe132699d2497a75c, 0x4eb9a2cdad477913, 0x177442ade2fd214,
        0xd0700271481ed321}},
      {{0xa9095782021fe45c, 0x643e66d1cc632c63, 0x622b27c0eb342b11,
        0xe9258bd6dbab6329}},
      {{0xa0105f3428712204, 0xab9efca0172a16b2, 0x182a9bdc9cc84240,
        0x7909de22eadfd4e4}},
      {{0xdc3f9b32ebf1aa1e, 0xd091d3cdec12b06b, 0xde2f3d0021186b2b,
        0xa602d97d49140ce1}},
      {{0x4df268fd836c3604, 0x5700903c2b290aeb, 0xe40e03918d7c44ec,
        0x53611e6f21660dc3}},
      {{0x53a68c92dcba2bba, 0x440f439065a6bea3, 0x64f78e921d4691a6,
        0x477e2998e24ecf99}},
      {{0xbccdc214b4773ea6, 0xb661c788861af5d2, 0x65d694bdc9c8a8c7,
        0x14609a6d6afd6d11}},
      {{0xf16dc776d6cdcbb9, 0xfc26ce2eb2e5c4b4, 0x2757614b97fcd989,
        0xd25ff34c8c1d303a}},
      {{0x1cbf0ea5594fd454, 0xdf14df1fed491d9b, 0x89b50f5fed7bc057,
        0x12a55a4fd7125a22}},
      {{0xaa3ec1d56310ff98, 0xcfe79e8b37f981cc, 0x53ee5ed96bb4091,
        0xe5abb256d80b0810}},
      {{0xbc3c41b7ac0cdcaf, 0x56c2d229e3dd9503, 0x5a21b7b239da7cf,
        0x6fa7382eebeecc33}},
      {{0xb89fde76ee50f243, 0xaef5147ca7f826de, 0xe99debcca2ecf043,
        0xf8c18768dcedf9c}},
      {{0x9d72e1c9b267efd7, 0xcc0565cc69c2d4f3, 0x29697c5a70c53d90,
        0xff38268b8fb19a17}},
      {{0xb2ce215dde89126e, 0x94faec3fd4acc441, 0xbbb43f273330738d,
        0x2cd9afbc81862262}},
      {{0xe3a67da38f0d08b3, 0x962316147da70dd5, 0x673cb9a2235270fc,
        0xa2af5c456dafa2d9}},
      {{0xee4e318013f681ed, 0x709e74713363017, 0x856311a640082ccd,
        0x6056efd283017e3f}},
      {{0xc7e8f8f99c7e8e8b, 0x3cb8b1b97160d679, 0xae94188e43565ff5,
        0xb976fc412eb84774}},
      {{0xa01c8e8ff40286b6, 0x3e41e4d470c00ff6, 0xe4d40faa9e67112f,
        0x105613838003aea}},
      {{0x41c9ee910ee5b99d, 0xb2c0543321d7388, 0xcc3d3563a8870340,
        0x25254db6171c7961}},
      {{0xd7a163ed21ffd38a, 0x6f0a4f97ec4559b9, 0xfc8df9d78362fc65,
        0x32b437813b99cb82}},
      {{0x5a44db667351c34, 0x1f8025297541d0e2, 0xc2807bf819a0b08c,
        0x4b728386d754d249}},
      {{0xc48feb54d4c78764, 0x1d757e7c3e37a25e, 0x76a7b8b7d2dc3f9a,
        0x73763ddedc265e87}},
      {{0xeccc9818d3d0faec, 0x8584f34a7459383f, 0x56df36001905448b,
        0x11057434f9661d38}},
      {{0x75f4523ed64cf6d8, 0xc7cb919a910b8a2f, 0x3e8f2a926a931a5e,
        0x613cd62552874522}},
      {{0x32f88032d5d6ea4d, 0xeb656452f4994a83, 0xeaacb69ee69583d6,
        0xbe3fee5b1464cb03}},
      {{0x49e0ca4ad838fc99, 0xed8c45e427c2b79a, 0x15ad034bb299553b,
        0x3e8f98ef87e76927}},
      {{0xb56f90dc18677027, 0x408697b5c6c7621, 0x7b5abdcbacfe7382,
        0x950aa7d9862f75c5}},
      {{0x592bbb7c09fa45d1, 0x2f0e96cdd23344d2, 0x2158525c2028f7e2,
        0x3a3e5fa288244e92}},
      {{0xd1decea4a0e3204e, 0x563f20fd619f782e, 0x28ea59aebdfa74,
        0x6bb93f97f970c025}},
      {{0x846c663fbb1abe3, 0x67f21c77eac749a7, 0x5651104f465100cf,
        0x748f550525f09cee}},
      {{0x12a4125b2092787f, 0x51051dd03a1b79e3, 0x46e47d71253f2ff7,
        0xbd253087e9dc428a}},
      {{0x682679307686736a, 0xcbbbf915266c8420, 0x4b4516b5f53929dc,
        0x81c4894042c1f12d}},
      {{0x4b054b7c3735d3, 0xb3f521e5fdfadb47, 0x83579b8d3b2662b8,
        0x596c88912d288f73}},
      {{0x100121b020a1cea0, 0x812bd74602bd995a, 0xbb9c72a802c55f43,
        0xc4d170ba1ec8b8f1}},
      {{0xed46f1574777918e, 0x315f25e722843018, 0x5121fc759a3539f1,
        0x6845457845fe9658}},
      {{0xc4fb246e109c9b73, 0xe212e13ab24e9944, 0x8540378d50fb7f14,
        0x2acc7ef145031f75}},
      {{0x67309d6b6f74222e, 0xf250c50714ae6de, 0x681a586cebcc3809,
        0xfc82d3a2ac811111}},
      {{0x7a82f0371e74d0c, 0x82b998313f4fa4dd, 0xad95e7a4d7b0a29f,
        0x288609a167d0f288}},
      {{0xfcc3155dfd9c9c9a, 0xedec5c6ff3dc6c2b, 0xb414c63abe2fc175,
        0xd3fbf14a4b1ee092}},
      {{0xa09f8b6da09d65cc, 0x3bb3179f78809cb7, 0x4c03776fbaa44bb2,
        0x4ee43bb0884003b8}},
      {{0xf48e6da7777f413a, 0x2f75d4ccf7f6aa98, 0x2621da650dd0db73,
        0x9492ec214cf06ba7}},
      {{0xcbb869ebdda52bcf, 0xf326440077f04321, 0xa876dad1b4c578d4,
        0xc3a9e81ffb90623b}},
      {{0x72f6a91666c5f798, 0x6ce1fe158fc409ad, 0x16761e9aca560533,
        0xdc5142cec115a858}},
      {{0x69154baa5af00537, 0xa25b109452230ac4, 0x4f75ce5d73a5b4ba,
        0x73a1e7612486b7b6}},
      {{0x8f2967142287aaad, 0xf1fd3e0c0b2fc82f, 0x3c1fe4674f274c7b,
        0xe2cab330bcc5de3}},
      {{0x22204d7210ab16e, 0xcbbd29b522cc5782, 0xf2f1e94f92a6846a,
        0x9ad253a1b6ba4018}},
      {{0xc399f79e58126bb, 0x29ec2c78d79796d9, 0xf64e28574a5adf39,
        0x71c122d843744de6}},
      {{0x1b5f6edcdacf09d8, 0x59788e1bb4208fb0, 0xf0c4062b06822378,
        0xfaf9b774b7c8c64d}},
      {{0xd603c3b47d8c268c, 0x9bd1980ba50f67f, 0xec2e62d051ffbeef,
        0x7111cb22cf40a5ff}},
      {{0x66ab54b80214e1a4, 0xbfef9a55aa231838, 0x6f61db4c67550152,
        0x86f90428d12103d4}},
      {{0x920f57ced8bb9e7a, 0x30253db8a0b1bb4e, 0xe1c0de79774d8bb6,
        0xe398ddfd5c0f7b6d}},
      {{0xbada57cabdeea94, 0x1801fda1e91b9abe, 0x1566e3da838f7b54,
        0x84624ffa9b28023a}},
      {{0xa44b265f7ba00b64, 0xbbe42bb5ab5ff381, 0xf043d84259e96ed3,
        0x535bce04f6ae1c6f}},
      {{0x3d8e56edfa76faac, 0xa8616488583fc588, 0x396b8201a2202284,
        0x4aee19765819a167}},
      {{0x3406eb4f32ad2499, 0x2342785dd09af8c0, 0xe8f3597399581c0d,
        0xb6458ebcdba0ac05}},
      {{0x931f6b4bf3124341, 0xca089032d1ad57c8, 0x2997b178e0f579f2,
        0x939b8767836aa3a0}},
      {{0x3ea0a37ce7262baa, 0x9abc856b59d0714e, 0xa09956da34322355,
        0x53aa4526371dc9bb}},
      {{0xb0ef6025608c4de3, 0xf780ad5f07a3a0d7, 0xc448420479e96cd8,
        0x2abc0d7bba6d1d2b}},
      {{0xcd258f5e0a910c3, 0x278fd9ed1b68e63b, 0x84faa07d5dce3658,
        0x4b643fad7287bc35}},
      {{0xc945ad4aa6eb213a, 0xf0b1221b686f0a93, 0x80a3d27d7b6b24d1,
        0xc1a1d62b5ee9b040}},
      {{0xfed5e42f2543e30c, 0xaec9d80ead834bc1, 0x2323f838e04c3957,
        0x4548e9248cbe9835}},
      {{0xc1552d8783201f91, 0x94b8964fc24f6573, 0xdaefebd1ee198e83,
        0x7bb8944aaae72a1d}},
      {{0xda3c34a2f7d0a3ea, 0xb335ca0e642661d2, 0xf086a41bfe6ab287,
        0xffa872d9ba3e3c6f}},
      {{0x3c8952f9fec0be95, 0xe55946ca5af1e52, 0x84301cfa6d59d771,
        0x8a3c157be80ccaf8}},
      {{0x23f3df554cdae4f8, 0xcd4bca3c43105ac6, 0xccf106812f959d27,
        0xcba65dc35c95263e}},
      {{0x793f2f0d677e4862, 0xbb9d4ae897191013, 0xe44bcfc4217f397a,
        0x4a5e71f577fb1a9a}},
      {{0x31e4a21989241ca, 0x8fa2a26dddef8a1a, 0xa8c381f19bf13d46,
        0x4ed13213fd79c18b}},
      {{0x2f3365c7908653a8, 0x63d948e0439fa305, 0x5d98639df3f8387e,
        0x34edbdbf4ebcc1}},
      {{0x906bd589a429afa3, 0xd7be57f43fed7978, 0x4cfd1c82e8b4bdcc,
        0x846589c34a60e945}},
      {{0x3518a3468fd07e9e, 0x647d21c7b9dba7e, 0xa4f13e8d14b4e6e8,
        0x9abdb1a497cf7aa3}},
      {{0xc35cc1ea7cde4172, 0xd74553d61b77b494, 0x199c0bdf989c5653,
        0xf2d57871dae95ce4}},
      {{0x67bf652b2c349b04, 0x638e45ddb42d2c6c, 0xfc64e3ffc465f8ea,
        0x1c6e783cc6640c1e}},
      {{0x7a0fe5fc13dde607, 0x628c0f066f1ebaa6, 0x35e4cc0bb80b2a5b,
        0xd8ced0abb17454ff}},
      {{0x725d46bf24ec08cc, 0x6f0e3759a880d8a7, 0x6513d3feed5a1741,
        0x1e6182518e3a888}},
      {{0x56a42f686395b573, 0x2cbf16d95f322efd, 0x347dbd8994056594,
        0x36715c1b304c4bbc}},
      {{0x9b41e1b9b7b607b5, 0x97f16eae27a4db47, 0x49fd1e466ab12d90,
        0xa9b9eecaee3b8700}},
      {{0xfe841bc6ad31b50a, 0x832aa5cdfdd6fb08, 0x9f2e16c344146264,
        0xb91ff41168b25dc2}},
      {{0x3cfd1b38677318c, 0xceff69c6430e8327, 0xb5dce4941a487795,
        0xbba3974b7ec98a6b}},
      {{0x9a79dd8833f9fd28, 0x45f00ae1bb1ca3a5, 0x3eb4f12799bf82b2,
        0xfecdbba8cc9d69f1}},
      {{0x77c562dc3f2af4b0, 0x9c496377c28c5349, 0xb25d596e43195ca7,
        0x734b123a366da24d}},
      {{0xf167251191562550, 0xe7e5e8f16e9623ee, 0x82ba3d64a22fcf80,
        0x2f456ce64e67220b}},
      {{0x28ffe7a88b3fdcff, 0x93def051ea890ecd, 0xaf4351aae83ee49a,
        0x9681eeda43c5a06}},
      {{0x42515a00cda00138, 0x3dee6b5339f72d63, 0xbf39adfdefdc4b03,
        0xa001a1327416919a}},
      {{0xdfc881f12f4637f2, 0x50910b0c6914213d, 0xacf8ee7949693c95,
        0xbef00de14dd7e88f}},
      {{0x7c7dac4b6a34cc6e, 0x2a9052541c46bf77, 0xdc069486f355faee,
        0x50cfdf8eb23e9791}},
      {{0x61a6ec4cdd2142fb, 0xc63d4cc1e7193551, 0x36bf4a269c818fbc,
        0x470b8886037fc94c}},
      {{0xbcc0f233abff764, 0x12eb0e4e7e7cea86, 0x13ae5aa035530934,
        0xff8a97ba68809e20}},
      {{0x5432b8a203b62d77, 0xa164dfaeb5704387, 0x3a7e61cd3340c127,
        0x5252e770167959a9}},
      {{0xca12afff0017ad80, 0xbdb81ae0c9c7706d, 0x5a51ac36e2ff942c,
        0xa239baf18e425799}},
      {{0x1a0a7f34ad03a660, 0x19e30a179246726b, 0xa465092a528f05d2,
        0x3eb24fcc96c9f637}},
      {{0xc5210e7d3059e18d, 0x52fa42d688c0fe5e, 0x3c40544d5d5dbdd3,
        0x2da8d892165cca70}},
      {{0xbac8f596e645d195, 0xd94f0994485ebc2e, 0xbb049c9b680b54a9,
        0xe88ac02feccdf173}},
      {{0xbbee1b248708f3bb, 0xf1ca47f77b7ef058, 0xae343a7c5afa761d,
        0xe9a0865de81ea1ab}},
      {{0x725029abe2347437, 0x3e46f02732875d96, 0x5089284ede60c945,
        0xcb13005b3b6df19}},
      {{0x2c4b628a34c926f6, 0xd702a98390854907, 0xfcdeea4ca3fed0e6,
        0xd1c40ae0a16a0529}},
      {{0xeab860cf6827c5fa, 0x8d2bd44ea03b3b54, 0x9c02feafed78cea0,
        0xdfe252a5cfecad05}},
      {{0x8fdaea3feaa9e2ad, 0x6723c82f3aef9e1f, 0xdfb947cb6d356f7c,
        0xf4db9daf944f4b80}},
      {{0x5f2758016e03f1b, 0xd0e135028f0a2574, 0xef3ccdea58b35861,
        0xa7ac3d3d136c1093}},
      {{0x43b66bb135ebcbe5, 0x8e2d59a793425406, 0xada9b6d9ed8a1f67,
        0xb8a8bc2e397e486e}},
      {{0x1b1438d7c93a1004, 0x8bb2d98f616e9bd4, 0x8349425143d6993,
        0x7f6393ed47aa8993}},
      {{0x9860fb38caf8ec9a, 0x2b5227b2c2d704f9, 0x771bfa315106e81f,
        0xe3443dde45d09ace}},
      {{0xddaf5e99bc9ac353, 0xad1258c1bec22672, 0xea28ec4d6789e9b0,
        0x706683bbdcd44af9}},
      {{0x1ef1309d184b424a, 0xb2eff1d6c61b339e, 0xf208a71db048e5b6,
        0x70cb77904a2d5ef7}},
      {{0xa639c8601dea733f, 0xf8378b68ee96da08, 0x731623527b41b8a5,
        0x6b9dc475719c84db}},
      {{0xee18e0080d250bf3, 0xfb33158f5c59c919, 0xa8eb67680f9544ac,
        0xbc36b130df2bf600}},
      {{0x8352218dba48134e, 0x79ec2942a9de0cc4, 0x6e4c2f7579f35544,
        0xa3ffc277cd84e652}},
      {{0xf720624f7621aa3f, 0x33fadfd7052e3180, 0x58a486a865ff26a7,
        0x1be6c6f0379a0092}},
      {{0xd7c2d1fdae7588c4, 0x64dda435353669e2, 0xc601efd335c35f47,
        0x11e1f952585af1fe}},
      {{0x98a0e00b5d8866c1, 0x18c14e82c76d2508, 0x92320cf06cf79f2b,
        0x1f7fe68337d076db}},
      {{0xd8e123af8422313f, 0xa6fac0d04cf97a5e, 0xf0ec14663a30751c,
        0x3cb5c450bdb38799}},
      {{0x5e1597bd2bb06b25, 0xe731caf6af94bef4, 0x96e26f66b736a634,
        0xd5c823d6724584d2}},
      {{0x2cc84789573b5d19, 0xbb2d7180f71edd66, 0x6c1351bd49aea5ed,
        0x553cceb18e8b7e1e}},
      {{0xcf825a3e5b603810, 0xf7b1daf128ae2f89, 0x2be7be15adb5a9f6,
        0x7f0342752624f122}},
      {{0x9e0e2ad9f26f34ac, 0x61ecd9948dc02805, 0x5e30b9fb2b07c4b3,
        0xed6d99f82039ddc1}},
      {{0x72d34504048c9edb, 0x6308702b191f4a05, 0xb7265476d28265d3,
        0x45351ce6890a83cf}},
      {{0x703d40f3dfa42cbf, 0x5149f0b6d25e1a90, 0x39c0f64246aad827,
        0xe238a941d943f4b8}},
      {{0xa81198e1f00d09e0, 0xa801a2b513a7a201, 0x4a7fbbfe3dddb98a,
        0x233f5ee53e40b7e7}},
      {{0xfde8a945aa6953b, 0xdffe411c473a4a1c, 0x19294a53e418eca7,
        0x90b96986931ec993}},
      {{0x408b2c1ff7d9d8f9, 0x8d7550a22406b60d, 0x9b1f7c338d35c4bd,
        0x8ad7d1ef75a72e3c}},
      {{0x53dcc77763159c8, 0x832c223d98bddbb5, 0xca7e409fabf3cd5,
        0x9438d036e8f053eb}},
      {{0x7d6e53553e3205ae, 0xc8bcee7a251ea826, 0x68c0b31413cdf90f,
        0x8b8ddf1630cc343b}},
      {{0x1a2755e344cc9f6e, 0xffcfbd259bb3c300, 0xd73e53d07867b175,
        0x859685a0be41764f}},
      {{0xa579b179b21b0d8c, 0xf0670eb6cc196204, 0xc5037ef45f628bac,
        0xa5aeab7307449eea}},
      {{0xf3afea03058a2f39, 0xe63c64dc1a659296, 0xddc9f69402f9fbe7,
        0x27d6a3411ba8bf6a}},
      {{0x6477afd0d6743ed7, 0x39a60e0e6f907a25, 0x4ce365ff7e0efb70,
        0x7a3df704f5f5fe17}},
      {{0x32dcf88e818d2215, 0xd6c5c90935301c0, 0x84341419887cd53e,
        0xee11abeac7132928}},
      {{0xf1ed26116088a978, 0x6c242a80db33a595, 0x49cdab4f95fc0350,
        0x48bf7f0af1f6716b}},
      {{0xd94307f3c10302e5, 0x2a02d2feb08af03c, 0x8412ccd55c83728c,
        0x775adab6747e89b9}},
      {{0x4a6c3f6449f42607, 0xa4b5a820b4a3961, 0x3d9c7836243506b4,
        0x2d520b495a50609e}},
      {{0x48b2c87566c7bb57, 0x60fe0111dc90b7fc, 0x5beab11405d922eb,
        0xf348a72c4a8c6e64}},
      {{0x5298a65e46d85644, 0x873e4c27c8824dec, 0xf8271d2e2a8ce8ba,
        0xf609b703ac41b01f}},
      {{0x13e5f5efe81bbfd7, 0x97a84c831885ec01, 0xd30fae6dfceed505,
        0x57b4b9f24e1aafb8}},
      {{0x39b09a6fcf6d9f3c, 0x6df78bf3475c346f, 0x5f7c8db7dcf5a66c,
        0x546efc45bcf9088f}},
      {{0xd3d71ef1c18be0d6, 0xe6712aad4da7cc8d, 0xc00f3a327711225a,
        0x8cf96309b93aaad}},
      {{0x78ad9b3ab165f893, 0xc472d5b7827622ec, 0x5d9e7483634bab75,
        0xc59a5ed494311228}},
      {{0x4e37dbb878e8db1c, 0x643a5ed942572ea5, 0x57a29791db34c8a0,
        0x8016f8e76eb5302}},
      {{0xc655795e47e92e28, 0x72cfbec8571867a7, 0x6ca771ed586bb480,
        0x404d6d4a225af4a3}},
      {{0x6525292a3ff92eda, 0xfb3564a48475822e, 0x2f02ae5a7810273a,
        0xa5789e626fb901dc}},
      {{0xe2019f4fe7307270, 0xd80f652a186dc953, 0x40a1b4882c245fa8,
        0xc5ce4ad96dd94aab}},
      {{0x90ed6ae287259775, 0xfb1c4167fdb268ae, 0xf57dc6bd76c1ad70,
        0x9835e97a696c0143}},
      {{0xc4dcc06be08d1a4c, 0x21fa553dca92eaef, 0xa11c68d1d75d8eeb,
        0xcccd17babe196a5f}},
      {{0x38c78a3b7d3c29fc, 0x9bab65a299224b48, 0xd1ff1d625725029b,
        0xd90618e2d6e2972}},
      {{0xd2ab59f0a8966f58, 0xda55b2993ca3fa4f, 0xd424b3c1febee763,
        0x3e73d0b03ac06ed9}},
      {{0x77f8bcffd03152a0, 0x564c241b1e3a8a13, 0x192bc1704c4671b0,
        0x1108f52c36a066fa}},
      {{0x149f4fa84bc7765e, 0x9e615f8e62b36fc3, 0xf7d1408f7b6c1103,
        0xd38df64899e78a20}},
      {{0xb6a3a13a28cf7cf9, 0xae626039bc66b302, 0xed15c28222074929,
        0xa0f5ed37c5377398}},
      {{0xfa4773363d8d0b7f, 0xdc52e0d320262526, 0x81f522518b26e9e9,
        0x1d1f83f23a536b40}},
      {{0x8e8f1f0e6a434d0e, 0x6b1a3d9eb7dee879, 0xcc1f4ed70ec52209,
        0x23860f21fdc4305b}},
      {{0xce67d0ea18c5471c, 0xea1f7b7d127e6a51, 0xac0955a3ec3d178e,
        0x55554fbe052d4698}},
      {{0x8e8e444a86625da4, 0x19c54766212b2b14, 0xd83cb5ffb48490d9,
        0x1f562777adef0fa0}},
      {{0xaaa9c75bc4c6901d, 0xa179ac9442f8da04, 0xb2f5d11573bbcf9f,
        0x19aef2239e08a075}},
      {{0x9a32c7c2124b5e82, 0x447daf460c4fe1b8, 0x662b1c4d9ad3d4ef,
        0x9eaef1dff6861fca}},
      {{0x1bdd19d91bccf06a, 0x10339aaa2f256865, 0x95dd90a939a9fbd4,
        0xf45478077bcb958e}},
      {{0x6da5766a73f5487d, 0x706127cd30dae435, 0xdef178382160f64f,
        0x714d531c525a7a38}},
      {{0x1293d70f9520e432, 0x9c5e6a0f79ac4200, 0x9f9230c64f1a1734,
        0x390745a778094d73}},
      {{0x6321ea8ee017aeae, 0x9d85a4b38b382375, 0x7fb7ce35285b9dad,
        0xc994310dabc09d27}},
      {{0x518f4440c5999088, 0x4cc1bbabfc6ea65d, 0xd4d485b291eff8d,
        0xc5fa18ab60a088d0}},
      {{0x475c185d3de4c534, 0xb597ab0415fb9775, 0xcb8f99db7b9d1378,
        0x6521d1fe3b7c3e05}},
      {{0x337f079dce1215f6, 0x591aa421f6895c39, 0xaa2587a273163d98,
        0x360ff94cbd910c40}},
      {{0xbc703c82b6f79496, 0xca9d2b961bc7651c, 0xc6ca5f527f880fc0,
        0x93f838a4b18c997a}},
  };
  alignas(32) constexpr static std::array<uint64_t, 4> m1_transposed[256] = {
      {{0x8005c473205b6928, 0x6f05dc800092130f, 0x3ca20d10a6c05a09,
        0x246084bb86cf5a7}},
      {{0xdb94f86ca5afe67c, 0xf40b7c68e3a09e0a, 0xf0ba15764f046b5d,
        0xcd8d026b132c27f2}},
      {{0xb072eccb918dc9fd, 0x5576b55f0b22b214, 0x6cd22ba0903b3ab4,
        0xea7d38bfb70a6e8d}},
      {{0x9648371ba7f08174, 0xd3cda6ab03c3da6b, 0x9436722d5965f7f4,
        0x1b5f73904feea6d3}},
      {{0xeea48d5e81699b4e, 0x4a9653abc157debd, 0xf8af8c61a84ccd49,
        0xe6576efa786da5b2}},
      {{0x51a10335a645285f, 0xe472e4e0cd98857b, 0xf2fecc5b4b36791a,
        0x6f26ad10cb7a6585}},
      {{0x35bab06e9ca8ef53, 0xf9e0b90337d08651, 0xc2fb06474694a289,
        0x43077e2ed2d41b64}},
      {{0xe4ba71ecb63f7650, 0x2acfd6e0fda966b0, 0xdd2aaa3de76bd6c7,
        0xd8a2a26895de1915}},
      {{0x2bd643422b93fd4a, 0xa82c92a15159fc00, 0x9dcd7cdc7b92afad,
        0x603c689a4fb0e3a6}},
      {{0x5429487539ef7a7d, 0xa1eb3afdbaddb2f2, 0x526809b8f1bd561a,
        0x895df9fba0457e7}},
      {{0x56aa0e47a17d35ef, 0xab317532b8e5446, 0xe3dbdd31a2454ce3,
        0xecbb4b1d1f2e9012}},
      {{0xadc232316ebd684c, 0x635556e89c37594a, 0x19242b2a33c926a,
        0xaae73da5eddcd16}},
      {{0x924f465758cadfb9, 0xc6dc2f505a58d04b, 0x384af4a8a424244d,
        0xd1e39cde12e7a28a}},
      {{0xbd5a3be7b0140380, 0xf7c41a7fa234a643, 0x77c9f531d96b7691,
        0xd03676b780b7493}},
      {{0xef67ef29994456af, 0xcfc81f828671cc92, 0xbc72c16f12aa05a2,
        0x27bbc4e400c0d0f5}},
      {{0xe43b9e77e227ede, 0x23ef9f8ba3b172f6, 0x9f52d591d02e344e,
        0xbd4008fa42640c35}},
      {{0xbacbf272218578df, 0x343c71cf96c43c3c, 0xcf6275101c44d7a7,
        0x9a9f9b7aa4d28d45}},
      {{0x3478e2bcbf61899b, 0xdd2b916332cea428, 0x83cba84f19acb125,
        0xc8eb402a8d22a0ec}},
      {{0xe36b89a28b19c636, 0x85bdd5d37298480b, 0xa9db2fca036b97fd,
        0xab577853323e0900}},
      {{0x513d94c537761f48, 0xa8965b273d4f290, 0x5442c3530e4da1c8,
        0x118633bc6e5692fd}},
      {{0x564c55a62f6df7fd, 0x6b598a6f8e6f67a7, 0x25d37de740ae09dd,
        0xda00e60d15c0c838}},
      {{0x74cbb18a218ab6e3, 0x3e1d907c68f4a10f, 0xa0f6fa922d740b37,
        0xa620afd111abed9f}},
      {{0xfe1600791da76070, 0x1ded99dc17f33c8d, 0x4c096363d8288d34,
        0xa3fb03d712430ad6}},
      {{0x4bbae24da2492740, 0xf96ca0a90337b9ee, 0x40c44f6dce5ddeea,
        0xb35753a76a6c50b7}},
      {{0xc37e66193a9eb7a6, 0x2958c318cda5dc3d, 0x12afdd2271996374,
        0x37052f71a849d18c}},
      {{0x309751454aea1f4b, 0xa0d4fa9a455d1b29, 0x38daed22e9fa9d14,
        0xc3a90f1615ebce13}},
      {{0x299d2d3f7e6d6513, 0x81b76ce1d157dd54, 0x5a2cbaf3d9014755,
        0xf4642f161bccbda6}},
      {{0x29ffd1cbf5a740c3, 0x2e056d2cc5fb9430, 0x827e90e5803d8a51,
        0x611f629901295bf9}},
      {{0xcf265c3902603668, 0xa7e3b1e01cc9520c, 0x4461c94cc0f58b69,
        0xa794a2c015fb96e6}},
      {{0x2774c8c8d87df40f, 0xf01a1e4d257c8c5f, 0xee58ded2dff975f3,
        0xaa0e76ca45d24e25}},
      {{0xc4fe64b41c4a2252, 0xa3f22ba891f36837, 0xa8340443c7b5cf75,
        0x5a49b5bfd2fb9419}},
      {{0x5f2f9affcd1ec5c9, 0x33e37cf82e4390c5, 0x3a27383cedacc2c0,
        0xdc60dc78b45a2a39}},
      {{0x87a22428b8478cf7, 0x600f771173709c68, 0xa5592a9fb6f063f5,
        0x6540b43acfdafe6d}},
      {{0xd4106a7013034e6d, 0x63924caa9f458114, 0xe9d032e878d42f3d,
        0x8efebf5caac93409}},
      {{0xd7aca854101f51af, 0x1cba2fd58634c0fe, 0x9f20932b377db5cc,
        0x6c0c851f21e56e49}},
      {{0x825f8823bc8b289b, 0x4ecb301176121bbb, 0xe532cfd299fecad9,
        0x6f7bb7dc2443ff71}},
      {{0x95509d9e48c92859, 0xcdf52efde9aa4835, 0xf09ab01851bf446,
        0x6146e1e6d5eb487d}},
      {{0x80f80106ba10718d, 0xb9994d9c3e3d664a, 0x37ca2fc4d72b4b9a,
        0x217fafb86996895}},
      {{0x177bf76cd67f9a97, 0x6e293a90a0a3088b, 0x853895698dfce2dd,
        0x33f0dd3f979a0c88}},
      {{0xf71d006d58cd67a0, 0x141fd7333a641410, 0xe98afb58e427ab02,
        0xc991c8a8b23aea6e}},
      {{0x41bfca130061dc60, 0x8838f68f750b6687, 0x3b4b7dfb29cd5ff7,
        0x45cf47c99704ea16}},
      {{0x38dc048d55c177b, 0x7aae09ce0c2696b0, 0x5746962781f5d8a0,
        0x4ecd2cf5d923e435}},
      {{0x5338cc9840df664e, 0x301649a6bede2b10, 0xf73479b783ef179,
        0xd6e9842dd2c4c022}},
      {{0xe1aab70e27e2bdfb, 0x9a77493d7621c7da, 0x37f454072cc0cfb0,
        0xa909eff338f300bd}},
      {{0x2a311dc0149f2906, 0xccc1c80e5114038b, 0x1a847011c4264054,
        0xa71cc5f92711487a}},
      {{0x32c6b272283284f4, 0x882df011110f3796, 0xebb38daa7bd8972e,
        0x8a068b0d7c42375f}},
      {{0xe900a04dddc436bb, 0xb2bd5ed7bee1c015, 0xca26ebdd96e79b04,
        0x1ef5598a2b8d9db7}},
      {{0x986df64c51dc4e3c, 0x3f671ae80eef4378, 0x9ba697119494494,
        0xcd2b4de3cb05991}},
      {{0xc1c79547f19a33e3, 0xc2c09ca4f764c0b, 0x4417eb9bba9fd8cb,
        0x5f5f6fe8dedc60e0}},
      {{0xe2f19ed28b9abf39, 0xbc20fb396fceaf26, 0x53a3219f06f7a5cd,
        0x54bf60a29b670a27}},
      {{0x28cfb40ee98d103c, 0xf4f2efe8d69743ca, 0x1073b7c67aec8d84,
        0x733d3be97baa402c}},
      {{0xc2f437a3de81c2ac, 0x1d67afcad5501fd4, 0xda5a63f6c2bed3a9,
        0x7169d8456dea81a1}},
      {{0xe0b0bf5b61f19ccb, 0x11821f1d6a727b58, 0xa19642ef7480ce98,
        0xe58191b634bc43cf}},
      {{0x82d7773f2e1a19c8, 0xcf9957b9ee303f92, 0x94b3449b430a7638,
        0xcad2cadb5f8834f6}},
      {{0xc97f1c321f4dbb36, 0x37c5b0d0bbc2c612, 0x785fea513e10844d,
        0xe114b929f524aa53}},
      {{0x1f84f42727216ad2, 0x53fd69706fbc4363, 0x986ab481972a07e8,
        0x176bf87e6865b867}},
      {{0xee5debd6b4df6c61, 0x1e9d50b3c3b40b54, 0x1469a8ef28a89a34,
        0x7b008238cda10e2f}},
      {{0x47408a54e926dfa8, 0x4109e22078f42fdf, 0xbb4cffcd518fb630,
        0x6dfec5ad2a274fcd}},
      {{0x772f28b8900e6a60, 0x4f99558e713f10d, 0x449894a89573517c,
        0xa23b938015a3cde3}},
      {{0x4d2165bb60a77db1, 0xaa409f5ac63966d3, 0xdb5a590add28da44,
        0x83fc20d38333f179}},
      {{0x59d57cf796a3e66, 0x5d883de88b4a26b1, 0x3a99df32d3e58542,
        0xd587e87ceb0e7c78}},
      {{0xdd9b969da90f93b6, 0x85c2eec737d070d1, 0xf83393ab93720dd4,
        0xca46a6507d1c8580}},
      {{0x1de27605d6613908, 0x9aedc0b979de5e49, 0xa5bd97c278030f5c,
        0x3a14d7e7d94d6d24}},
      {{0x89c08da8f8bc28ca, 0x146bfecf6f4e0831, 0x9d0958507a9513cc,
        0x80fe5d20cc133fb1}},
      {{0xd4919453f5418d5f, 0x65c9f53b102c153d, 0x43beee0a3e1156e1,
        0x7b19d5b950d70111}},
      {{0x79ee3ad2aaa37979, 0x7bf29d7f9f2fea1d, 0x6ed52b27ef0d30d3,
        0x7df100900a865}},
      {{0x16521c765cb1a04d, 0x30e2ca80444559ce, 0xeddb6fe9030d1cb9,
        0xbb645bf6dde6e24f}},
      {{0xba5662a489e9b1fb, 0x12ed0b1818130853, 0x1f0b94b405af5576,
        0xd0887a76806131d1}},
      {{0x816ce6fd93c16e09, 0xa6bd9c50dd14077, 0xb4380476ee0bc1b6,
        0xfab88402c8a8617b}},
      {{0x4736456dcf6c177d, 0xf4db10be4dc6746e, 0xb1d67b0240b96c0,
        0x6b8c1bd79180c832}},
      {{0xb5fe1b2a1b0246a9, 0x48337a5ad9e5ce32, 0x97378cb1f3c5483b,
        0x391974572000ea3a}},
      {{0xd3f6dedcebfa1026, 0x6b1e5bf48a1dbd83, 0x20c347415af8edb0,
        0x8119e668894e58}},
      {{0x86a34812161bc75d, 0x620e474134a359cd, 0xe0bdf81871b4a60b,
        0xa8a7250762819d4a}},
      {{0xfaaa1032ba04f54a, 0x7a70834fe531b1d, 0x86d3fd2d9c9deb11,
        0x3c73f3c21efd60e9}},
      {{0xfdb2faa116a19adc, 0x8e037de6c0b16928, 0x2c3604c0a4a1e0f0,
        0xf20501be4041d237}},
      {{0x30f5daaefd7d8b7e, 0x71ca41330721450b, 0xec561fb5984e9dcb,
        0x4179fcad11afeb89}},
      {{0x6bc9d13cd898bcfc, 0x565d956df8566605, 0xbf309b7381df608f,
        0x6042401398c8e4cd}},
      {{0x6b966da4b4479410, 0x5664886b37809012, 0x9f7d55f867550174,
        0x9bbf59dbd5537c62}},
      {{0x93fe85e12ccf86a4, 0x7d1d30c133a1e124, 0x77c09a1175f13251,
        0xc7d97d2c96a4a984}},
      {{0xe6937a3de97221e6, 0x82b136e8113f99b0, 0x1c507b6c067dd1bb,
        0x32cad62acbd0c189}},
      {{0xfcd515db56eef974, 0x79fc479394c73e01, 0xe12600febabe5822,
        0xe1a146a86e943151}},
      {{0x462c54612ecbbfee, 0x7aa0d06fb7a86bbd, 0xbb15354cfa7a5939,
        0xb2bff8e5e37d8eff}},
      {{0x211a212e8b54df30, 0xb42ce4a10b643a06, 0x7b5df9fce8b0756e,
        0x959e06f809ddde99}},
      {{0xa4e9fb9a3ee78e32, 0xd5c42f54b182aafd, 0x9862e1beacf8307b,
        0x7ef8851185adb74b}},
      {{0xc318e711b9490d29, 0x59648e486d834fcb, 0x98ed556b017d4343,
        0x2a599bd277acebd0}},
      {{0xe50a67ebc6e27fbd, 0x8c21eab6bdb92541, 0x90c40cd4cea69b03,
        0x3d77ee604ab13c09}},
      {{0xa4912f544c0440fa, 0xa65b1f83f7546fd0, 0x1fd410542d112779,
        0xb2da06d1280a333d}},
      {{0x2bc8e6fa524177c7, 0x33027ea09444c75d, 0x65079a3c93c467c7,
        0xe649582e929362b1}},
      {{0x6218815644a47715, 0x1291df35a046e030, 0x11ac7d7f97985771,
        0xad2829317336de0e}},
      {{0xf13346807d822cc4, 0xea248ed4bea6514b, 0x3263ed7b26137f6e,
        0xc95991d17a38d0f7}},
      {{0xea22656d6088b920, 0x87786b6f88d57d45, 0xf11d96d200c721,
        0x718acb321562fde2}},
      {{0x97f1a0943d4fb02d, 0x6428511b3c1a2888, 0x1d5f57741d3b14a1,
        0x9d82fc2f5e8763a3}},
      {{0x7d423d46e7caf377, 0x4df7e284a2d3b93b, 0x72d454f605e1cbf9,
        0xf61aed0aea9c8925}},
      {{0xe5a0606d4aa8be9, 0xf37f5fb99679846b, 0xb0ef5bb0d81fa3fd,
        0x572f48009141caa9}},
      {{0x95fff39a938bb72d, 0x3d5b752a7a6aaa47, 0x196bb52d69e84bd1,
        0x544119b65428b1d8}},
      {{0xa5429b55c600b3d1, 0x29882dcb365f43ad, 0xc7a2d286b0dfc549,
        0x580a3a46e68ad2f6}},
      {{0x7e86f9753880d5fd, 0xbc1da70bec409792, 0x7227d6842f5aa4e5,
        0x5e16d8fe02950d2d}},
      {{0x1644fd6b4d8cea8a, 0x25cca380d981af15, 0xf6c4a9407b8080ce,
        0x9dadac5d954c575f}},
      {{0xcf2ca16521e8d2e4, 0xba2af999335f15e7, 0xbed8b9f5f6523dc7,
        0xa6f91a649eba4d4d}},
      {{0xeeb88eabf97956f1, 0x1cf13fd98d2a582b, 0x80c81ea7ff64d1c8,
        0x171bd5a099a40189}},
      {{0xd683cecadb86ca31, 0xf5ab6932bb3b2faa, 0x1e1786f10ad6ecb8,
        0x885ed0d2adbb6c50}},
      {{0x917c91c488799e4f, 0x36312c94e2ad559c, 0x3181c81f859c606d,
        0x59323e7487dd4895}},
      {{0x6650314158584ff0, 0x7f66980bdb41c93b, 0x9577f6dea7424157,
        0x2b40990890166e0}},
      {{0x6e666d0d0e8582a, 0x5a8b126f6793cd45, 0x5da17cda043d2985,
        0x9b4d63f9ec5bf57c}},
      {{0x151e95e800de7dff, 0xc6dd916894e04d09, 0x588cb3d0071d208f,
        0xb2b93c52022287de}},
      {{0x27268590acb8431d, 0x868c7ebd77d3418, 0x17dccf7768129482,
        0xb7b141b1d5915490}},
      {{0x387d085fc475116a, 0x6b3efbc652eaee5d, 0x90e01f90a32cd7d6,
        0x4ae9b7cc3f001d12}},
      {{0x2c1fc771da0a898e, 0xe428238457196972, 0x4bed690b565ff470,
        0xb5d901bd770356ad}},
      {{0xc14c6ccc8e085aad, 0xe8e14f1c5124a35f, 0xa1920670b4cf1de2,
        0x111951c1a24f856e}},
      {{0x52840896de5bb384, 0x9573b00792162556, 0x6007ba040a7c740d,
        0xfedee7204b9c8a52}},
      {{0xd377f8d5692112a0, 0x876ab5eeac42d4f8, 0xb4b7a8fb5468074a,
        0x4373ecda96ff46d}},
      {{0x6fe08c69beca8b43, 0x88c3a7ddb0f6c83f, 0xe0831025f78a852a,
        0x79c44150831b6cc9}},
      {{0x3ce8840467c8515a, 0xd1a2da699e0661b2, 0x8a69ac6bdc2f3db7,
        0xbbf167310659d9c7}},
      {{0xf93edacc12195378, 0xb88866a69649db89, 0xfe4636b504420a8e,
        0x651e35d7962025f9}},
      {{0x64f372211455c474, 0x5b641ba6617874fd, 0x28a727f2c5177355,
        0xacb0cf167fe28ac4}},
      {{0x592a9644982c0a49, 0x9e8da02737c4f562, 0x9d66b79b3583f866,
        0xc4d8bd8f2baeae44}},
      {{0x773b0b241c4ed815, 0xb021290f87fd3fde, 0x53a6c1ae901b9ad,
        0xe5dc5af609616db8}},
      {{0x977e347a2ff48115, 0xb1256ac3d49456e0, 0x87e57c146937f7f3,
        0x3c332fe7de3e7cf}},
      {{0x41e3233140d27ee0, 0x21a22e4006538931, 0x3ec7e8699072dd45,
        0x16e7d173266a3e52}},
      {{0xeba21d254f546a74, 0xa2d12e0d9e4537fd, 0x175f6d9e3f1374e1,
        0xb820311a13233e4a}},
      {{0xaf380caf71ead37f, 0xebfc83147d88b9ec, 0xdb875adf4653f3d7,
        0x68683a1c32efc739}},
      {{0x60eb320d5b3109d2, 0xb99ecf55ae2906f1, 0x64733bfed7d22bb9,
        0x801beb2d8aa5e55d}},
      {{0x962ce69b9df9b642, 0x3efbfff3138fe415, 0xe125ee75b6020550,
        0x3c8780fc6a616825}},
      {{0x38f240888a35f327, 0x8b3f1b85e3a7f5e2, 0xab14a60791bbe5d0,
        0xdc3f6e11f37093bc}},
      {{0xe9895379ab60ec74, 0x503365d818de244a, 0x7f4e88526b1e9285,
        0x6f25ef08162997c2}},
      {{0x231958c8bbef3be3, 0x2b0b08c64b66bfbc, 0x3195078a5e765fcd,
        0x225a1bb2de17eff1}},
      {{0x456008e5e288d25d, 0xf38817bbfdff2047, 0x5c2963d90a80b648,
        0xd29ccff24f2f4b83}},
      {{0x410d2a3287ef75cd, 0x83c07bccb9db11bd, 0xd9a3b8577bb23a6b,
        0xac576e6c0ff1e1ee}},
      {{0xb3cff713be5c7341, 0x624bafcae2040b0c, 0x3c8ca341f9515576,
        0x1aef704a0bee9c9e}},
      {{0xfcf5818e6528d5fe, 0x6fe20d68d13921d0, 0x4696c1cf70973da2,
        0x2d17226293f1c5c}},
      {{0x8de9534c81141b79, 0xf19be571fe9b1e09, 0x71f8b41d516d0268,
        0x1fd00059afe9efd5}},
      {{0x9ec4c5e2f0951c62, 0xa2f2e498d3484efd, 0x193201ba0641f831,
        0x7afe3636a550b111}},
      {{0xefb45d4819da742f, 0xd3a15303c0f19c44, 0x166a6d4a9f9edfed,
        0x6560aa6572c76079}},
      {{0x81fa716f58d30b40, 0x5a0b4038a5089c19, 0xc9f0d0ab8085fdc5,
        0x2c86ded73e6bd5e7}},
      {{0x6bc7bef3d1625930, 0xf98dcd54a3ebf734, 0x661013fe9f9bb346,
        0xa3a458725a858a07}},
      {{0x2e54469e74a52959, 0xed71f6f0c5c7b203, 0xce3becb06ab50aa5,
        0xd9f4b5878cf785e8}},
      {{0xccebea1367c817f, 0xcf2734aae6a3109c, 0x26e52e17918ec5ce,
        0xfd57ce487f15ba6d}},
      {{0x7bce8ce0c4ba17b8, 0x5da5240fcb06a94b, 0x90357360e53dc1ab,
        0xb7587673dc005c05}},
      {{0x3fd75d3bf52d7d16, 0x4a6994109c5d7d62, 0x9f2bae75ae517c0a,
        0xded05f1920e6ff45}},
      {{0x36ba9d27224c15d2, 0xd0a990ca6aac9deb, 0xa47d899f32dd539e,
        0xd9461cc41db918bf}},
      {{0x357521bbb4efd4af, 0x1ebb78a19a4a2878, 0x5d18a2dfd4c94b1e,
        0x7fb18508bb983a86}},
      {{0x374ac99be644bb97, 0xdc38fc4a57f880cc, 0x141a3dbe5fb98a3d,
        0x530ccb769bb5e4f9}},
      {{0x2151a793ff59d934, 0x1e496b9deb6917b1, 0xf897b4e0829853cb,
        0x13c6c48cb96e2b7b}},
      {{0xa507d0eba8a32ac1, 0x19180de13c1d9110, 0xe5b340b1e0056960,
        0x1be459dc3f7bd0f0}},
      {{0x93ce5fe6c56e7981, 0xf3c617014d846b79, 0xf79cd87aa9f1a4e,
        0x29da39738bd31fab}},
      {{0x37c3289605270c10, 0x448f4321a0de94e8, 0x5b4343024d09f449,
        0x5cc6c148968ede16}},
      {{0xfbf9c480d8081117, 0x55671cb3bbbc4426, 0x471754f3148f3ed7,
        0x703ff49d73d3d519}},
      {{0x56b885fc7c0a190f, 0xde208fddc49eb23f, 0xdf0fe34afe5d4058,
        0xbd51514e79b8846c}},
      {{0xad2f9d2160951d64, 0xf7a1679a63cf326f, 0xd556da7fa1c3452c,
        0x7cd052b368f1770b}},
      {{0xf82b44f8e00c2d50, 0xdc1a2b9353790648, 0xf10b48be4bb138ed,
        0x35565996ec9f60b}},
      {{0x6d7340566c2252f4, 0x242b59f408565a7f, 0xf5dc228eded7471a,
        0xa89995a6f101ec0}},
      {{0x470df0be267655eb, 0x17b41ec4e41aea0a, 0x5324487d0699abba,
        0xa1e8481ec99d9f26}},
      {{0x8a1cded873b3b21c, 0xc05965fac084e55e, 0xc4dcc20f8e5f1931,
        0xf74530e24553cfb5}},
      {{0x5b89a74625643404, 0x33ab6e838534bb93, 0x7395a80d682efcf7,
        0xe4cf78e41d8e61a0}},
      {{0x54e1e9f2ddd5bf9b, 0xf50203b5e450d59c, 0xa46416a1e5069360,
        0x8438fc3bd4795d2d}},
      {{0x423cb5de3abb1bb3, 0x14d6017750a1dbd1, 0xbc2e6b55ee5055d5,
        0xbd9dc79cb6d3b387}},
      {{0xc85ceaad1143044e, 0x827232a57af37dab, 0x36f0656c4f552aed,
        0xe1e17bb8d7946ada}},
      {{0x8b436fb1f77e6a28, 0xdf847d0aa5586d0e, 0xc9d70b1bfba60ad1,
        0xfb734e6d12b37ee5}},
      {{0xbf3e451d8b72d06d, 0xa1a19143a6a4f0fc, 0xbf1e9a98fe975c38,
        0xe451fbf896ac96b7}},
      {{0x84eac3d552a527d0, 0x972e0bd783f4ae5b, 0xe13747dc70e826f4,
        0xb4509860e54044}},
      {{0xe5b3cde4d447ae3e, 0xf62c27d02e8ac059, 0x8c8c55ed6c64fb8d,
        0x39fd59d8f0e38a7d}},
      {{0x5ca2226b51ebf9b2, 0x27aff5a1ab91c299, 0xab32dbd0c158f4c0,
        0xf43b2275507e6883}},
      {{0xb5daf97ef4035a9a, 0xa929ab44493b32dd, 0xf5b5eaea0e0279bd,
        0xce9091fdd15e268}},
      {{0xa05d90de7f476b4d, 0x3f131fc5cab3a1e8, 0xfe8e87e8dd8eacdb,
        0x33a10f0c70928567}},
      {{0xe042ae9688f16a80, 0xd9b81574858ace1f, 0x190c22ccfdcd4e44,
        0xba6c9ab3bf779ad4}},
      {{0xc30f2a318207786e, 0xc036e641f499eaec, 0x936fc2849cc491f6,
        0x4b30a93d1456f71a}},
      {{0x73e3526006ab4b48, 0x7e1c1f86e940c5aa, 0x748d9ac6addf7b94,
        0xb4acf308d63e7ba7}},
      {{0x3dfcbb06d0060d9a, 0x85bbca7614838afe, 0x88d636ffa109062b,
        0x653b5dd09e129c07}},
      {{0xf6aaf4aa242f283f, 0x461eef9e34dd3989, 0x287c6ce20ca20a9,
        0xe070e1965312cbc3}},
      {{0xbf2cae7c7c016f95, 0x9bd22d3689a5ce53, 0xd0681aeb2b2f8feb,
        0xc80e4aa84f394fd5}},
      {{0x6fecdda4b87beb9b, 0xc546336b8bc7ba4c, 0x8d1d3d33c1049cec,
        0xc8b82edcbccd7f6f}},
      {{0xee9edcdd0ef951ec, 0x54bb7d2cd290a52f, 0xfb6d8d72b0566f15,
        0xba88323dc4735a32}},
      {{0xd74a24250e786616, 0xed7df44c219eb09b, 0x9c53de3099d6079f,
        0xa7f065e72f5fa01c}},
      {{0xa5b64374eceff990, 0x55fc7a8ace3f2882, 0xf18d64a8748970ae,
        0x624576b5ddb4bf4}},
      {{0x3163c15690d4f416, 0x58181a811efc66ab, 0xc4eae38a3b5f3bf6,
        0x9a5b99419eecc933}},
      {{0xd08820bece19b4ba, 0x15284a64bac1d058, 0xc91c67867cbe3b65,
        0x6962ce9ac99b0c7e}},
      {{0xc1723b680325e236, 0xa2ec99abcac86354, 0x23268e3739f239a5,
        0x7bdfad2c5cf18915}},
      {{0x93411eda35d53e6e, 0x4e086ff3f0c6712, 0xc0f312067cf95691,
        0xac88a3ee96d5d190}},
      {{0x5764801467dd3cde, 0xc3ef6bf9b01ba11e, 0x5af0fdd06089de63,
        0x796e797d62d5268a}},
      {{0x3426d1b324d47896, 0x1fcc5a1ed5fb95b9, 0x60edbc5a27215012,
        0xb1b8b87b4a702377}},
      {{0xb3759f9d6a7270e6, 0x2c476be1483938be, 0x51adee7985c03e73,
        0xf6f3851a252909b}},
      {{0xbf0c0a2025ca0dbe, 0x5324f72f991aa266, 0x12ed5db1bc6b2f04,
        0x4ae4ed9632b7752f}},
      {{0xcda914afaacffcb0, 0xec4290e1289edfe4, 0x478aadb7267eee09,
        0x9345281259196300}},
      {{0xc871a87b9f0ef452, 0x43fb2d608058f0b5, 0x6069697d6dc4a022,
        0xaf4525c359896505}},
      {{0x329172938b7b4e92, 0x8e00ffc1193c4630, 0x8463b4810ae082f,
        0x3d07badb4e6d0097}},
      {{0xa479ceaaf2c82631, 0xe5f1608a7197716b, 0x19e7d00030026d03,
        0xeec1029a02575af3}},
      {{0x82a6a87a06847033, 0x62efc6f849539a3a, 0xd63e77bb860b5de8,
        0x9f9b4bd1be86ca17}},
      {{0x65257bb616080667, 0x858d390c046e7c5b, 0xdd9e58dd20e31ab2,
        0x7e3a835759fb872f}},
      {{0xcac8b6402a81189a, 0x26e8200c00251c7a, 0xedf4f5c86038f446,
        0xf61e8df0a6e74d1}},
      {{0xc921049869be0159, 0xdab78f2c5b83ede, 0x5eaee7a651f7f372,
        0x48d31b05010da3f6}},
      {{0xdd6ab7638dbd49c3, 0xe57e487a9b1d35f9, 0x61100a9b6257e894,
        0xaaab6dfe5f12aef3}},
      {{0xb54ba6abb6bfb38f, 0x11fa918fa5ed91c, 0xda1fb0a7ef55e26b,
        0xe77f782cae447967}},
      {{0x747eba151fafcaff, 0x9734d47bbde4ec06, 0xfb99e13c7775931b,
        0x2c485d34d3b630ea}},
      {{0xcd826dd94505fe16, 0x6baab590822b5869, 0x1a0f31a743395b41,
        0x8d88bd955fb5dede}},
      {{0xf316febc1bb6d32b, 0xb62198043775df75, 0x822a85d17477c908,
        0x2940123712548854}},
      {{0xdaa511feedcc9f91, 0xe052c8a28226d73c, 0x71ada787e31da6a4,
        0x839ad67defccb8b4}},
      {{0xfa72c967dcc8d513, 0x841dee043419bdb, 0x2f144583b50b2edf,
        0x965af20d9168feea}},
      {{0x84527a8dac55533b, 0xb2c7a58fd8a05948, 0x5ec06561d7bd5b8b,
        0x8e61a56aedd90864}},
      {{0x4e6e95ce21f178d2, 0x2417601c3b8b4c7e, 0xc20f158c837d40f,
        0xd4ccfa024e965af4}},
      {{0xf0f53836eb99f26e, 0x6c2a483c171a0e46, 0x119c576e818359e2,
        0x11b2c73984be7cfb}},
      {{0x344972cdb1fec9bc, 0x87cd0873ca0375bf, 0xf9b45c1403a75999,
        0x8da62a88e8b72809}},
      {{0x350276475ca6694f, 0x493bf923ceec3f30, 0x2753ac23a08e8bad,
        0x22b7d4ea1ed4b371}},
      {{0x30549036ecbb7210, 0x2ce18c7cf0f96392, 0xe35019c94651d80d,
        0x6db0c10a1f5af3c0}},
      {{0x3e59326c2be51097, 0x2b6e9f786b44fc01, 0xa4ea76faf754550b,
        0xfea5743abc62807d}},
      {{0x5a39aeb35d05bf82, 0xa4769985bf68f837, 0x2bd6116a5e14183e,
        0xab8a01c45f9b9952}},
      {{0xcbe68af55d9854cd, 0x8606e0c2cf10d886, 0x9a09c2396ce50f62,
        0x224ef12f7b599b00}},
      {{0x994be7d4a47a30b2, 0xdfbd8d67c6d0fd75, 0x2faa55748104f360,
        0x616d58352ab9b65}},
      {{0x45bdfeb48b9617f8, 0xb1185c2517a74f84, 0xbe7caa1c9de18c67,
        0x9941012c9c3f6b98}},
      {{0x4d4fe46f89866aef, 0x8688d2c62afdcf7c, 0xaa9ea672f260418,
        0x453716f4324ae141}},
      {{0x35ba88e3d2da4bc8, 0x6e06f378a82b90d, 0x713d1a2a7494284c,
        0x3a721a8e06cad0d}},
      {{0x9c53143cb707f377, 0x4ff46cfd3daebc31, 0xbc3fc5a9f7145c44,
        0xa0bb2802d56142e7}},
      {{0x16184e08e2be378d, 0x440d4ee7ae67b03d, 0xdeb2ec6edbbcb047,
        0xa7703f9a89268dcf}},
      {{0xac9832d86711b9bf, 0x701d11cdec522ad8, 0x34be590751206764,
        0x62061779f0a23cb4}},
      {{0x1eead8cc71f7adba, 0x3f61545256174d9f, 0xe0b39bd67ada6105,
        0x3033aad0d8c3214e}},
      {{0xa9645721d87ac96f, 0xf3500c745c02257d, 0xcfa9a7fe2a81d1a6,
        0x2b2d6d95d7985837}},
      {{0x427a05975639d707, 0xe2897c46986480dc, 0xaa4872633c50bb36,
        0xd9a9c6b259c0b6b8}},
      {{0x765654e84c0e2099, 0x725cfd1a37b859f3, 0xe028012e01cbd66d,
        0xe93b2e207c6c379e}},
      {{0x1c111d0fa4ac99d5, 0x869d9566f308a237, 0xa7b1a8fa6fd9f262,
        0x2bc4d3ab2e31d54a}},
      {{0x5895a2ac6a2386f3, 0x27355980bd616fe1, 0x8f8fe8af1915a93f,
        0x40fab6dcb651b739}},
      {{0x5220bd8b8ada4109, 0x586b5ecf75eeea57, 0x99497a5dfa6d13d3,
        0x6d6d7e3f0a9cab64}},
      {{0xb58a2cf1dbeba379, 0x11fe0302feb148f8, 0x2694a76f4f7ea202,
        0xe7cdd0f1db787da7}},
      {{0x7bf2d24c5055a14f, 0x704b447494ccbc85, 0x7856bd0ee710aa31,
        0xfdacff94d3d37484}},
      {{0x22a6da3db3b6a34a, 0xd0f0476fa3d46a97, 0x984d78d78c77476c,
        0x178a0e8bf0c84bf8}},
      {{0xb7a8840ca0e047a0, 0x5e70bfa68acc8498, 0xfb1249ecf2dba690,
        0xc8eb107472aca321}},
      {{0xaa60318cfea8aedc, 0x7789515945052dd7, 0xb90a375fce843b29,
        0x1dea04150c5992ab}},
      {{0x54e1ac183ba79e46, 0x5b349f163e907fd2, 0xc75ad15aba91652,
        0x35f63b8ce5e45a35}},
      {{0x3ff095cfb7c79e87, 0x72f46fda6e61608e, 0xba3302aa15f48600,
        0xefb2a0d291f5429f}},
      {{0xe87615245ec49ff4, 0x72235f81f9edd7c, 0x1a52ed88ee4e4646,
        0x7a91bd836042003f}},
      {{0x8236fc09113ee0cd, 0x1566aa2b11a37f90, 0x15c494cec26cd28f,
        0x22b65c688583eff2}},
      {{0xfda716167bc95fc0, 0xac62c5da6200f7b, 0xc9cfc3ea9fefb9be,
        0xb47eda2aa6d787af}},
      {{0xa9167352f91a3db2, 0x8721cbdb863b0da7, 0x538b2853e2accc4c,
        0x60a50f592c5f6e98}},
      {{0xcb0bd9a653ec5c54, 0x5e3cb022ec62e148, 0xc77b493b444c64bb,
        0xb49474c8a276d479}},
      {{0x5b89c1c78b91b65b, 0xbc3ea0aaf354fa00, 0x2dc603b97adb8f4,
        0x6ebeb98f7f6a497b}},
      {{0xc72ddb2f604ffe5f, 0x1d98b3d7cd0081bb, 0xd3d2e8044cd9fc98,
        0x27d16e7fd11d668}},
      {{0xf73cb49da8a004d0, 0x3dedf0143063e1ab, 0x12db3c09afde890c,
        0x43b93f65314b4d7}},
      {{0x45941e23f9233dad, 0x9b25ed7e1e1c13cb, 0x473b4ed9167d13a9,
        0xd11a0fd9e53e8817}},
      {{0xf6ee12e7d29e9524, 0x7ae94fdc4a59a43c, 0xa552f7e7ec24a0da,
        0xfbc1d27cd1d6095f}},
      {{0xe7aa0e9d2f5ed432, 0x556bb6a06cad92b5, 0x218558ee5400dbca,
        0xc9e3a99e7c285956}},
      {{0x13c4db49830341aa, 0x29c7c18cdf7048cc, 0x8e911dcb591d2f5e,
        0x67d3edd0d1f1bec0}},
      {{0x80b001644c77278a, 0x8791a2ce9fc97a5e, 0x1df4793838d59b51,
        0x60c7ca3ebfcabfad}},
      {{0x389c752a64e6cdba, 0x73466796a81005eb, 0x2135fc7408d3ce46,
        0x661759a471773ac9}},
      {{0xc24d487fee5e917, 0x2f31c6a8c35efcd4, 0x8af0b38301b82170,
        0x54ec4471ce511769}},
      {{0xc48ceeb6d6bfbb0d, 0xebefcda203487773, 0x401153fb866010ad,
        0x4fff1d385f56b7b2}},
      {{0xf5efa24bfe233af3, 0x3f807aa480cd6a8a, 0xd72d9a2f3b69249,
        0xd2c59776d5bad2c7}},
      {{0x371dec76565d0980, 0x19b9b0a12d317f3d, 0x23881c6ea297a542,
        0x99366a49fafcb381}},
      {{0xb9f28973116c5eda, 0x59bd577356542f2c, 0xb70a2eb9ef2a9ac1,
        0xb0c24a1854bebf2e}},
      {{0x1d4186771f103eb, 0x8031a0f11842f545, 0xc09bc7d6147ae4cf,
        0x9332573388425e79}},
      {{0xa9153df58594d23d, 0xb2086f00d88fb8b7, 0xfe586b656ba6ebfa,
        0x98cb34684f606ec7}},
      {{0x3146ead9fecaf116, 0xd4f71e362f961b54, 0xd463ba017d954a41,
        0xbe7da64b8f17de9a}},
      {{0x44cb6dcae215c9ff, 0x1b385db8ad46f48d, 0x83e9e467e7f6bac8,
        0xc0a9400eb959169a}},
      {{0x5c38655ab69568ac, 0x67043e68a3a0841a, 0xa6694494504a1592,
        0x71b4765dae87f10b}},
      {{0x25f6a1588a2324a7, 0x5b113c067b1c6db8, 0xbe4b79a7e620b4bd,
        0xce478a17143358c}},
      {{0x8ba7bbd8f3f46b60, 0x6f6911d5546d612c, 0xc2d8f5e061d1ed51,
        0xc7f5c81e90a1fd6d}},
      {{0xb1ef894ac9d5c6c8, 0x7badf60e7414d5dc, 0x1f4dfc406245c83c,
        0x670a4207bc1b23ff}},
      {{0x53ca74669d82e699, 0x30b096b78e24eac0, 0xd8f0c1477d35ced7,
        0x3b11155ef00fc0f9}},
      {{0xa0dfc3171b837d64, 0xc501528b1014501e, 0xd94c7971c8cea752,
        0x99831e4627ea4317}},
  };
  field::GF2_256 v(
      "0x0123456789abcdeffedcba98765432100123456789abcdeffedcba9876543210");
  field::GF2_256 result = v.multiply_with_GF2_matrix(m1);
  field::GF2_256 result_transposed =
      v.multiply_with_transposed_GF2_matrix(m1_transposed);
  REQUIRE(result == result_transposed);
}