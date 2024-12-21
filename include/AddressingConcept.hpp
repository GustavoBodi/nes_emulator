#pragma once
#include <concepts>
#include <cstdint>
#include <tuple>
#include "AddressingBehaviour.hpp"

template <typename T, typename P>
concept AddressingConcept = requires(T addr, P parameter) {
  { addr.get_mem(parameter) } -> std::same_as<std::tuple<uint16_t, AddressingBehaviour>>;
};

