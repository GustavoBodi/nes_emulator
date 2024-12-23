#pragma once
#include <cstdint>
#include <limits>
#include "AddressingConcept.hpp"
#include "StatusFlags.hpp"
#include "Types.hpp"

template <typename T>
inline bool zero(T parameter) {
  return parameter == 0;
}

inline bool carry(uint16_t parameter) {
  return parameter > std::numeric_limits<uint8_t>::max();
}

template <typename P, typename T>
inline bool negative(T parameter) {
  return (static_cast<int8_t>(parameter) & 0b10000000) == 0b10000000;
}

inline bool overflow(uint8_t acc, uint8_t mem, int8_t result) {
  return ((result ^ (acc)) &
      (result ^ (mem))) & 0x80;
}

struct ADC {
  ADC(ProcessorStatus &status, Accumulator &acc, Memory &mem): acc{acc}, status{status}, mem{mem} {}

  void execute(int16_t parameter) {
    uint16_t result = static_cast<uint16_t>(mem[parameter]) +
                      static_cast<uint16_t>(acc.get_register()) + static_cast<uint16_t>(status.get_flag<Carry>());
  }

private:
    Accumulator &acc;
    ProcessorStatus &status;
    Memory &mem;
};
