#pragma once
#include "StatusFlags.hpp"
#include "Types.hpp"

class ProgramStatusRegister {
public:
  using StatusMask = uint8_t;
  using StatusRegister = uint8_t;

  ProgramStatusRegister() {}

  template <StatusFlags flag>
  inline StatusRegister get_flag() {
    return (statusRegister & calculate_mask<flag>()) >> flag;
  }

  template <StatusFlags flag>
  inline void set_flag() {
    statusRegister |= calculate_mask<flag>();
  }

  template <StatusFlags flag>
  inline void clear_flag() {
    statusRegister &= (calculate_mask<flag>() ^ 0xFF);
  }

private:
  template <StatusFlags flag>
  constexpr StatusMask calculate_mask() const {
    constexpr uint8_t mask = 0b01 << flag;
    return mask;
  }

  StatusRegister statusRegister { 0 };
};
