#pragma once
#include <concepts>
#include <cstdint>

template <typename T, typename P>
concept AddressingConcept = requires(T addr, P parameter) {
  { get_mem(parameter) } -> std::convertible_to<uint16_t>;
};
