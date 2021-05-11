#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../rain.h"

TEST_CASE("RAIN-128-3-KAT", "[cipher]") {

  // key, pt, ct
  std::array<std::string, 3> testvectors[] = {
      {
          "0x4cd8ceac27957eb5b61eb19e0ee2444d",
          "0xc3bf252ca498404d9cd4e2162a46ec55",
          "0xc824f3cfaba5cfb12d77b831e6dea75e",
      },
      {
          "0x8c4bfcd5636b317c7069143b78cc1f71",
          "0x420bc1c86d31ea6c4b667c96d7d9d5c5",
          "0xe89d3cd9328229059fe1e6b53a4f53d9",
      },
      {
          "0x6dd61e40269c10c10c093ae2b9386615",
          "0x1d6b3ab42a5bcbac299142f7174e672c",
          "0x16dd1b697181e01999b29c8b19f8af96",
      },
      {
          "0xea69cbdbda1e88069c025591a7329f7f",
          "0xc00e0ae66f6f531d62aada5e0a8b5281",
          "0xa4ca13813d53dabe3aa7dc27452e3db1",
      },
      {
          "0x5cfa3f00042571041293f91c26fe2749",
          "0x37eb48d8a8206e70cc3419655f947f4d",
          "0x420ae0d1960c64799dee673e50468536",
      },
  };
  for (auto testcase : testvectors) {
    const field::GF2_128 key_gf(testcase[0]);
    const field::GF2_128 pt_gf(testcase[1]);
    const field::GF2_128 ct_gf(testcase[2]);

    std::vector<uint8_t> key(key_gf.BYTE_SIZE);
    std::vector<uint8_t> plaintext(pt_gf.BYTE_SIZE);
    std::vector<uint8_t> ciphertext_expected(ct_gf.BYTE_SIZE);

    key_gf.to_bytes(key.data());
    pt_gf.to_bytes(plaintext.data());
    ct_gf.to_bytes(ciphertext_expected.data());

    std::vector<uint8_t> ciphertext;

    RAIN_128_3::rain(key, plaintext, ciphertext);

    REQUIRE(ciphertext_expected == ciphertext);
  };
}

TEST_CASE("RAIN-192-3-KAT", "[cipher]") {

  // key, pt, ct
  std::array<std::string, 3> testvectors[] = {
      {
          "0x986b6c0be0a5a8a6326075218a8f65ffc0a485785b52c047",
          "0x9366682858b4579b815d1101f659285a94d3b85ab94c4b29",
          "0x8c03b12fd56d873fb85e532a2323783fb0d7333cf0c5863b",
      },
      {
          "0x670286e8caa0d4b09ee3f90560e494bdee4d747b66bb56d1",
          "0x82ac69fa3b3ecd429087c97569f4d805583902f274cf31fd",
          "0x9abad8b1ba5ecc18ec422ea0acbd11af5518403bada357bf",
      },
      {
          "0x30014fbafd04941fffa52d8a4c03942b06ae14a3532e9972",
          "0x9bab4bde04714ff70c0a6b897b97285f6f24376a13ba1641",
          "0xaa8ab625d5f67d62762b0ed3a11b35f9dede3f825e1e032f",
      },
      {
          "0xda2b65584ab54d5e5bd3442fbab5605743eabe0399ab7dd4",
          "0x62894b7e66b3d4bbe6eedcb649ed2f5c1fcbb25cbaadfe28",
          "0x8c3990853503da3e5ecf175e3d8218653cccdade99ba5bae",
      },
      {
          "0x56023b2ba5b5a8363387d17efdda6cc11147ad1b042788d6",
          "0x91d6f5f37cb3bdad4f12a19b04727353a032556351c3bb24",
          "0x9b8f3e15f57401b11ebeea39e30284f35f08023424481c16",
      },
  };
  for (auto testcase : testvectors) {
    const field::GF2_192 key_gf(testcase[0]);
    const field::GF2_192 pt_gf(testcase[1]);
    const field::GF2_192 ct_gf(testcase[2]);

    std::vector<uint8_t> key(key_gf.BYTE_SIZE);
    std::vector<uint8_t> plaintext(pt_gf.BYTE_SIZE);
    std::vector<uint8_t> ciphertext_expected(ct_gf.BYTE_SIZE);

    key_gf.to_bytes(key.data());
    pt_gf.to_bytes(plaintext.data());
    ct_gf.to_bytes(ciphertext_expected.data());

    std::vector<uint8_t> ciphertext;

    RAIN_192_3::rain(key, plaintext, ciphertext);

    REQUIRE(ciphertext_expected == ciphertext);
  };
}

TEST_CASE("RAIN-256-3-KAT", "[cipher]") {

  // key, pt, ct
  std::array<std::string, 3> testvectors[] = {
      {
          "0x3529e1644e8e0a137b7b3cdf2a5d51b5c23e077b8b215eda452dc739a033b5fc",
          "0xc36d5b4a51e1f4fafb6450a5cf219109644f96cda5055d0196c5eb2777176599",
          "0x81dae3155b6c2143b24023925bbdafe84f347bd0050e8fdfdfa4de29f7cb7302",
      },
      {
          "0xbbfde480e3d18cbd0e035eea1a647e6220f4d5f83b79e04778199ad0bcae24c1",
          "0x95185f799efa8dde010dffaf2ab9f70cd2a60b75b686a09b18e7fddb9b4161b7",
          "0x4b55990b7643dcdf5f90ef7bd1594498e010a4f6b26da3602882bdd312689061",
      },
      {
          "0x65340bc3027b225ed6af62939ea79f590f2139a427242913699b48cb22c3dd46",
          "0xca13f063ec9ab94fb28f3ef6203f0df18b9e152f4cc8f461977958b6b87e1905",
          "0x7b4c4d0858a042d409643b3ec8a772e10e3e5c0d81bbd2c1a813a2433b2ee405",
      },
      {
          "0x2cc0acfc1ddf988c5c3978a1ffdb1adc958b207875b81327f334ad9193bd8fe2",
          "0xc1877b18025d824dd83e5f2993334e6c073dd38a4e1f044bde53889818455a4d",
          "0x3b0b283aa90e9c33ae509dd0ff7abfef426ae7911156c3c3a25f18f0759933dc",
      },
      {
          "0x460ace14742d5513665944b6d074eafcd925e0cee8e8d18593e2fa0da519c6c6",
          "0xda4a9660bb965c7b90b3414243898bb13db1702cd645854d270264117fda42ad",
          "0x761712fcc20d0ea2a6bda24b988a88d26d342f9c4b534cd2dcd5228e0e3a291d",
      },
  };
  for (auto testcase : testvectors) {
    const field::GF2_256 key_gf(testcase[0]);
    const field::GF2_256 pt_gf(testcase[1]);
    const field::GF2_256 ct_gf(testcase[2]);

    std::vector<uint8_t> key(key_gf.BYTE_SIZE);
    std::vector<uint8_t> plaintext(pt_gf.BYTE_SIZE);
    std::vector<uint8_t> ciphertext_expected(ct_gf.BYTE_SIZE);

    key_gf.to_bytes(key.data());
    pt_gf.to_bytes(plaintext.data());
    ct_gf.to_bytes(ciphertext_expected.data());

    std::vector<uint8_t> ciphertext;

    RAIN_256_3::rain(key, plaintext, ciphertext);

    REQUIRE(ciphertext_expected == ciphertext);
  };
}

TEST_CASE("RAIN-128-4-KAT", "[cipher]") {

  // key, pt, ct
  std::array<std::string, 3> testvectors[] = {
      {
          "0xcfa39657231c95b780cecbca81c371e7",
          "0xaedeea13a6de87c283616230e8fd9173",
          "0x376685590793c69addf8df897b9cadfd",
      },
      {
          "0xb24ee0449842dcb6bc93d77721784c71",
          "0xe0c46f1b3dbe3c49c44012a6f787ee0",
          "0x4781e5974eacd5366aa446975be1e8c0",
      },
      {
          "0x7f7dcc2851629a13704a6154ad0b1efd",
          "0xd96332664637d5f93b6c7ae34ba4fd9b",
          "0xd52953b4e2c2a83fe401174521c8697d",
      },
      {
          "0x588e1818447ffe2ae18727122183ff2",
          "0x7b5a8f47577de1956b8484207b20cf7",
          "0x24d0dc8fca6f40a1177fc6a3e6d7cddc",
      },
      {
          "0x595f084e7c2b92f6f624572d9004a461",
          "0xe93d5ce1df4127a81bed0186ee7f9fa5",
          "0x33202998167ea11dc6210c306ad362a1",
      },
  };
  for (auto testcase : testvectors) {
    const field::GF2_128 key_gf(testcase[0]);
    const field::GF2_128 pt_gf(testcase[1]);
    const field::GF2_128 ct_gf(testcase[2]);

    std::vector<uint8_t> key(key_gf.BYTE_SIZE);
    std::vector<uint8_t> plaintext(pt_gf.BYTE_SIZE);
    std::vector<uint8_t> ciphertext_expected(ct_gf.BYTE_SIZE);

    key_gf.to_bytes(key.data());
    pt_gf.to_bytes(plaintext.data());
    ct_gf.to_bytes(ciphertext_expected.data());

    std::vector<uint8_t> ciphertext;

    RAIN_128_4::rain(key, plaintext, ciphertext);

    REQUIRE(ciphertext_expected == ciphertext);
  };
}

TEST_CASE("RAIN-192-4-KAT", "[cipher]") {

  // key, pt, ct
  std::array<std::string, 3> testvectors[] = {
      {
          "0xebd668e6628903d0bffb10eacab284a015b6f6175caf3f8e",
          "0xf5b8f7fd595ee0fa2bf78dbc0a0cee9c300948af60cfb4e6",
          "0xe46387f07184154d8f59a85c114b6fb79b0f7cccc954f413",
      },
      {
          "0x5c9c103dcbb3ef58440efe49ed1e188895d8d775fd9e888c",
          "0xe71236f1aee0a512463fe18f94245181188ad699e934f13",
          "0x18c0904e178d0f7c8b696f32a9385dda091f2cac04645d0a",
      },
      {
          "0x970a4b9cf0106fc4fd50ea0b9cfeb8c3d13abd000c3143c3",
          "0xbd330faf0d0cd1ce98f9aa81781b9e757db4ed5d9bd5687e",
          "0x1cbc25fa436e7c375592b57fe0c6c57f09ce33ea5ff84d4",
      },
      {
          "0xe5b10de2dd4a3ab54da9ade6fe972477af3a0710409617b8",
          "0xfe474e2189d247bb8c40582eb1f376466c6f5c5f59b9e3a6",
          "0xa8476b8d8fdff40723f076147e5b48b411d73ffb22a7b174",
      },
      {
          "0x9e930f995da548cddf342768482bb36670575eab87b63247",
          "0x453ebd1b1a525247d8d963553c0e4edf4f9848ad774b2803",
          "0x97ffb62b208f6fd8cd1f91e310df7cda67e7ab9fe4ee4d4d",
      },
  };
  for (auto testcase : testvectors) {
    const field::GF2_192 key_gf(testcase[0]);
    const field::GF2_192 pt_gf(testcase[1]);
    const field::GF2_192 ct_gf(testcase[2]);

    std::vector<uint8_t> key(key_gf.BYTE_SIZE);
    std::vector<uint8_t> plaintext(pt_gf.BYTE_SIZE);
    std::vector<uint8_t> ciphertext_expected(ct_gf.BYTE_SIZE);

    key_gf.to_bytes(key.data());
    pt_gf.to_bytes(plaintext.data());
    ct_gf.to_bytes(ciphertext_expected.data());

    std::vector<uint8_t> ciphertext;

    RAIN_192_4::rain(key, plaintext, ciphertext);

    REQUIRE(ciphertext_expected == ciphertext);
  };
}

TEST_CASE("RAIN-256-4-KAT", "[cipher]") {

  // key, pt, ct
  std::array<std::string, 3> testvectors[] = {
      {
          "0xfab12d982e449e03b4f8cb57a24f38571b30591a3e559195f70ea236bad9da61",
          "0x2079cf036637a3818a7b3cf84223e25c83385dc6e28b9ee0dcfed28723e69e8d",
          "0xc694dafd0527f425ac8cd552060b3faa6bd545dd9fae557cb15932a22ee085a6",
      },
      {
          "0x9bf9136bb982b3f0ecf0b79e88250c6e58f0004a6445cc1a0a6c0bc242f353c4",
          "0xfcdb7f70737df5aa15eaf600678c841c23ee43e00346709939308a0eccf43f99",
          "0x8abca47a7cf2ce4d4c91fc21b7c5e23c90e81900f5c72af1202118a163dc7d99",
      },
      {
          "0x79f65050105cf6306ab60ef32ff249e3da3600aa121cad99a28d8a4a0749962e",
          "0x2ce45cc42d30433b5940c4056ad12274cb3a547b8db78d8a61932067800f2304",
          "0x7fdee4e0f01c149ce1f06768338d8ca8315939b6c3427425010b07efe1786f04",
      },
      {
          "0x9ae0091fe0ae060396858ca83dcc6baeaaf05e73550a70ee611ae627599c110f",
          "0xb057158d779ef70d3feba462e6f1eed13c867f8617215344afa071c904bd13e9",
          "0xf32114f0409b1f78be5c2277afc1559bb3c954270b5533fef3210a4f6ffc350d",
      },
      {
          "0xff6570a8b2c9170ec29041aa3e71898c7d3073d21943df53754d77f44038422a",
          "0xe5e29ea9ff9ad4691f8d520b89c36df5bb466b1530db295bc61c1083dcf33043",
          "0x9d05d180c2572007b99468109f8df08efea8083bd50d9d46d5937bc98ecd3bbb",
      },
  };
  for (auto testcase : testvectors) {
    const field::GF2_256 key_gf(testcase[0]);
    const field::GF2_256 pt_gf(testcase[1]);
    const field::GF2_256 ct_gf(testcase[2]);

    std::vector<uint8_t> key(key_gf.BYTE_SIZE);
    std::vector<uint8_t> plaintext(pt_gf.BYTE_SIZE);
    std::vector<uint8_t> ciphertext_expected(ct_gf.BYTE_SIZE);

    key_gf.to_bytes(key.data());
    pt_gf.to_bytes(plaintext.data());
    ct_gf.to_bytes(ciphertext_expected.data());

    std::vector<uint8_t> ciphertext;

    RAIN_256_4::rain(key, plaintext, ciphertext);

    REQUIRE(ciphertext_expected == ciphertext);
  };
}