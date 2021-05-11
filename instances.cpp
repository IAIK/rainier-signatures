/*
 *  This file is part of the optimized implementation of the Picnic signature
 * scheme. See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */

#include "instances.h"

#include <stdexcept>

/* key_size, block_size, num_blocks, num_sboxes */
constexpr rain_params_t RAIN_128_3_PARAMS = {16, 16, 3};
constexpr rain_params_t RAIN_128_4_PARAMS = {16, 16, 4};
constexpr rain_params_t RAIN_192_3_PARAMS = {24, 24, 3};
constexpr rain_params_t RAIN_192_4_PARAMS = {24, 24, 4};
constexpr rain_params_t RAIN_256_3_PARAMS = {32, 32, 3};
constexpr rain_params_t RAIN_256_4_PARAMS = {32, 32, 4};

static const signature_instance_t instances[PARAMETER_SET_MAX_INDEX] = {
    {
        {0, 0, 0},
        0,
        0,
        0,
        0,
        PARAMETER_SET_INVALID,
    },
    /* some sample instances for ~64 parties */
    /* Rain_params, digest size, seed size, T, N, */
    {RAIN_128_3_PARAMS, 32, 16, 23, 57, Rainier_3_L1_Param1},
    {RAIN_192_3_PARAMS, 48, 24, 33, 64, Rainier_3_L3_Param1},
    {RAIN_256_3_PARAMS, 64, 32, 44, 64, Rainier_3_L5_Param1},
    {RAIN_128_4_PARAMS, 32, 16, 23, 57, Rainier_4_L1_Param1},
    {RAIN_192_4_PARAMS, 48, 24, 33, 64, Rainier_4_L3_Param1},
    {RAIN_256_4_PARAMS, 64, 32, 44, 64, Rainier_4_L5_Param1},
};

const signature_instance_t &instance_get(params_t param) {
  if (param <= PARAMETER_SET_INVALID || param >= PARAMETER_SET_MAX_INDEX) {
    throw std::runtime_error("invalid parameter set");
  }

  return instances[param];
}
