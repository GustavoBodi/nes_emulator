#pragma once
#include <type_traits>
#include <limits>
#include "Types.hpp"

// Define a Concept using the trait
template <typename T>
concept RegisterSpecialization = is_specialization_of_v<T, Register>;

inline bool zero(Integral auto parameter) {
  return parameter == 0;
}

template <typename T>
inline bool zero(Register<T> register_repr) {
  return register_repr.get_register() == 0;
}

inline bool carry(uint16_t parameter) {
  return parameter > std::numeric_limits<uint8_t>::max();
}

inline bool negative(RegisterSpecialization auto parameter) {
  return (static_cast<int8_t>(parameter.get_register()) & 0b10000000) == 0b10000000;
}

template <typename T>
inline bool negative(T parameter) {
  return (static_cast<int8_t>(parameter) & 0b10000000) == 0b10000000;
}

inline bool overflow(uint8_t acc, uint8_t mem, int8_t result) {
  return ((result ^ (acc)) &
      (result ^ (mem))) & 0x80;
}
