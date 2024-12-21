#pragma once
#include <cstdint>
#include <limits>
#include "AddressingConcept.hpp"
#include "Types.hpp"

template <typename P, typename T>
inline bool overflowed_bit_7(T parameter) {
  if (parameter > std::numeric_limits<P>::max()) {
    return true;
  }
  return false;
}

template <typename P, typename T>
inline bool negative(T parameter) {
  if ((parameter & 0x0000001) == 0x0000001) {
    return true;
  }
  return false;
}

template <typename P, typename T>
inline bool invalid_2_complements(T parameter) {
  return false;
}

struct ADC {
  ADC(ProcessorStatus &status, Accumulator &acc, Memory &mem): acc{acc}, status{status}, mem{mem} {}

  void execute(int16_t parameter) {
    uint16_t result = static_cast<uint16_t>(mem[parameter]) + static_cast<uint16_t>(acc.get_register()) + static_cast<uint16_t>(status.get_register());
  }

private:
    Accumulator &acc;
    ProcessorStatus &status;
    Memory &mem;
};
