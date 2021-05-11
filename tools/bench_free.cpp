/*
 *  This file is part of the optimized implementation of the Picnic signature
 * scheme. See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../signature.h"
#include "bench_timing.h"
#include "bench_utils.h"

#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>

struct timing_and_size_t {
  uint64_t keygen, sign, verify, size;
};

static void print_timings(const std::vector<timing_and_size_t> &timings) {
  printf("keygen,sign,verify,size\n");
  for (const auto &timing : timings) {
    printf("%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64 "\n", timing.keygen,
           timing.sign, timing.verify, timing.size);
  }
}

static void bench_sign_and_verify_free(const bench_options_free_t *options) {
  static const uint8_t m[] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                              12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
                              23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

  std::vector<timing_and_size_t> timings(options->iter);

  timing_context_t ctx;
  if (!timing_init(&ctx)) {
    printf("Failed to initialize timing functionality.\n");
    return;
  }
  signature_instance_t instance;
  instance.digest_size = 2 * options->kappa;
  instance.seed_size = options->kappa;
  if (options->rounds != 3 && options->rounds != 4) {
    printf("invalid cipher rounds, choose 3 or 4\n");
  }
  switch (options->kappa) {
  case 16:
    instance.block_cipher_params = {16, 16, options->rounds};
    break;
  case 24:
    instance.block_cipher_params = {24, 24, options->rounds};
    break;
  case 32:
    instance.block_cipher_params = {32, 32, options->rounds};
    break;
  default:
    printf("invalid kappa, choose 16,24,32\n");
  }
  instance.num_MPC_parties = options->N;
  instance.num_repetitions = options->tau;
  printf("Instance: N=%d, tau=%d, Seclvl=%d\n", instance.num_MPC_parties,
         instance.num_repetitions, instance.block_cipher_params.key_size);

  for (unsigned int i = 0; i != options->iter; ++i) {
    timing_and_size_t &timing = timings[i];

    uint64_t start_time = timing_read(&ctx);
    keypair_t keypair = rainier_keygen(instance);

    uint64_t tmp_time = timing_read(&ctx);
    timing.keygen = tmp_time - start_time;
    start_time = timing_read(&ctx);

    std::vector<uint8_t> signature =
        rainier_sign(instance, keypair, m, sizeof(m));

    tmp_time = timing_read(&ctx);
    timing.sign = tmp_time - start_time;
    timing.size = signature.size();

    start_time = timing_read(&ctx);
    bool ok = rainier_verify(instance, keypair.second, signature, m, sizeof(m));
    tmp_time = timing_read(&ctx);
    timing.verify = tmp_time - start_time;
    if (!ok)
      std::cerr << "failed to verify signature" << std::endl;
  }

  timing_close(&ctx);
  print_timings(timings);
}

int main(int argc, char **argv) {
  bench_options_free_t opts = {0, 0, 0, 0};
  int ret = parse_args_free(&opts, argc, argv) ? 0 : -1;

  if (!ret) {
    bench_sign_and_verify_free(&opts);
  }

  return ret;
}
