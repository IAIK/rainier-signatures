#include "rain.h"
#include <cassert>

namespace {

// generic template implementation, concrete instances below
template <typename Params, typename GF>
inline bool rain(const std::vector<uint8_t> &key_in,
                 const std::vector<uint8_t> &plaintext_in,
                 std::vector<uint8_t> &ciphertext_out) {

  assert(key_in.size() == Params::KEY_SIZE);
  assert(plaintext_in.size() == Params::BLOCK_SIZE);
  ciphertext_out.resize(Params::BLOCK_SIZE);

  GF key, state;
  key.from_bytes(key_in.data());
  state.from_bytes(plaintext_in.data());

  // first r-1 rounds
  for (size_t r = 0; r < Params::NUM_SBOXES - 1; r++) {
    state += key;
    state += Params::roundconst[r];
    if (state.is_zero())
      return false;
    state = state.inverse();
    // transposed matrix multiplication is faster, so we use that instead
    // standard multiplication can be useful for debugging, set
    // INCLUDE_STANDARD_MATRICES to include them
    //
    // state = state.multiply_with_GF2_matrix(Params::matrix[r]);
    state =
        state.multiply_with_transposed_GF2_matrix(Params::matrix_transposed[r]);
  }
  // last round
  state += key;
  state += Params::roundconst[Params::NUM_SBOXES - 1];
  if (state.is_zero())
    return false;
  state = state.inverse();
  state += key;
  state.to_bytes(ciphertext_out.data());

  return true;
}

template <typename Params, typename GF>
std::pair<std::vector<GF>, std::vector<GF>>
rain_with_sbox_output(const std::vector<uint8_t> &key_in,
                      const std::vector<uint8_t> &plaintext_in,
                      std::vector<uint8_t> &ciphertext_out) {
  assert(key_in.size() == Params::KEY_SIZE);
  assert(plaintext_in.size() == Params::BLOCK_SIZE);
  std::pair<std::vector<GF>, std::vector<GF>> result;
  result.first.reserve(Params::NUM_SBOXES);
  result.second.reserve(Params::NUM_SBOXES);
  ciphertext_out.resize(Params::BLOCK_SIZE);

  GF key, state;
  key.from_bytes(key_in.data());
  state.from_bytes(plaintext_in.data());

  // first r-1 rounds
  for (size_t r = 0; r < Params::NUM_SBOXES - 1; r++) {
    state += key;
    state += Params::roundconst[r];
    assert(!state.is_zero());
    result.first.push_back(state);
    state = state.inverse();
    result.second.push_back(state);
    // transposed matrix multiplication is faster, so we use that instead
    // standard multiplication can be useful for debugging, set
    // INCLUDE_STANDARD_MATRICES to include them
    //
    // state = state.multiply_with_GF2_matrix(Params::matrix[r]);
    state =
        state.multiply_with_transposed_GF2_matrix(Params::matrix_transposed[r]);
  }
  // last round
  state += key;
  state += Params::roundconst[Params::NUM_SBOXES - 1];
  assert(!state.is_zero());
  result.first.push_back(state);
  state = state.inverse();
  result.second.push_back(state);
  state += key;
  state.to_bytes(ciphertext_out.data());

  return result;
}

template <typename Params, typename GF>
void rain_mpc(const std::vector<gsl::span<uint8_t>> &key_in,
              const std::vector<gsl::span<GF>> &t_shares,
              const std::vector<uint8_t> &plaintext_in,
              std::vector<gsl::span<uint8_t>> &ciphertext_out,
              std::vector<gsl::span<GF>> &s_shares) {
  const size_t num_parties = key_in.size();

  for (size_t party = 0; party < num_parties; party++) {
    size_t sbox_index = 0;
    GF key, state;
    key.from_bytes(key_in[party].data());
    if (party == 0) {
      GF pt;
      pt.from_bytes(plaintext_in.data());
      state += pt;
    }
    // first r-1 rounds
    for (size_t r = 0; r < Params::NUM_SBOXES - 1; r++) {
      // round 1
      state += key;
      if (party == 0) {
        state += Params::roundconst[r];
      }
      s_shares[party][sbox_index] = state;
      state = t_shares[party][sbox_index++];
      // transposed matrix multiplication is faster, so we use that instead
      // standard multiplication can be useful for debugging, set
      // INCLUDE_STANDARD_MATRICES to include them
      //
      // state = state.multiply_with_GF2_matrix(Params::matrix[r]);
      state = state.multiply_with_transposed_GF2_matrix(
          Params::matrix_transposed[r]);
    }
    // last round
    state += key;
    if (party == 0) {
      state += Params::roundconst[Params::NUM_SBOXES - 1];
    }
    s_shares[party][sbox_index] = state;
    state = t_shares[party][sbox_index++];
    state += key;
    state.to_bytes(ciphertext_out[party].data());
  }
}

} // namespace

#define IMPL_RAIN_FOR(PARAMS, FIELD)                                           \
  namespace PARAMS {                                                           \
  bool rain(const std::vector<uint8_t> &key_in,                                \
            const std::vector<uint8_t> &plaintext_in,                          \
            std::vector<uint8_t> &ciphertext_out) {                            \
    return ::rain<PARAMS::Params, FIELD>(key_in, plaintext_in,                 \
                                         ciphertext_out);                      \
  }                                                                            \
                                                                               \
  std::pair<std::vector<FIELD>, std::vector<FIELD>>                            \
  rain_with_sbox_output(const std::vector<uint8_t> &key_in,                    \
                        const std::vector<uint8_t> &plaintext_in,              \
                        std::vector<uint8_t> &ciphertext_out) {                \
    return ::rain_with_sbox_output<PARAMS::Params, FIELD>(                     \
        key_in, plaintext_in, ciphertext_out);                                 \
  }                                                                            \
                                                                               \
  void rain_mpc(const std::vector<gsl::span<uint8_t>> &key_in,                 \
                const std::vector<gsl::span<FIELD>> &t_shares,                 \
                const std::vector<uint8_t> &plaintext_in,                      \
                std::vector<gsl::span<uint8_t>> &ciphertext_out,               \
                std::vector<gsl::span<FIELD>> &s_shares) {                     \
    ::rain_mpc<PARAMS::Params, FIELD>(key_in, t_shares, plaintext_in,          \
                                      ciphertext_out, s_shares);               \
  }                                                                            \
  }

IMPL_RAIN_FOR(RAIN_128_3, field::GF2_128)
IMPL_RAIN_FOR(RAIN_192_3, field::GF2_192)
IMPL_RAIN_FOR(RAIN_256_3, field::GF2_256)

IMPL_RAIN_FOR(RAIN_128_4, field::GF2_128)
IMPL_RAIN_FOR(RAIN_192_4, field::GF2_192)
IMPL_RAIN_FOR(RAIN_256_4, field::GF2_256)