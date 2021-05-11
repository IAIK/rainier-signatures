/*
 *  This file is part of the optimized implementation of the Picnic signature
 * scheme. See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */

#ifndef BENCH_UTILS_H
#define BENCH_UTILS_H

#include <stdbool.h>
#include <stdint.h>

#include "../instances.h"

typedef struct {
  params_t params;
  uint32_t iter;
} bench_options_t;

typedef struct {
  uint32_t iter;
  uint32_t kappa;
  uint32_t rounds;
  uint32_t tau;
  uint32_t N;
} bench_options_free_t;

bool parse_args(bench_options_t *options, int argc, char **argv);

bool parse_args_free(bench_options_free_t *options, int argc, char **argv);

#endif
