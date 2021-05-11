#pragma once

#include <array>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "instances.h"
#include "types.h"

// crypto api
keypair_t rainier_keygen(const signature_instance_t &instance);

std::vector<uint8_t> rainier_sign(const signature_instance_t &instance,
                                  const keypair_t &keypair,
                                  const uint8_t *message, size_t message_len);

bool rainier_verify(const signature_instance_t &instance,
                    const std::vector<uint8_t> &pk,
                    const std::vector<uint8_t> &signature,
                    const uint8_t *message, size_t message_len);
