#pragma once
#include <cstdint>
#include <limits>
#include <type_traits>
#include "AddressingConcept.hpp"
#include "StatusFlags.hpp"
#include "Types.hpp"
#include "FlagsFunctions.hpp"


struct ADC {
  inline ADC(ProcessorStatus &status, Accumulator &acc, Memory &mem): acc{acc}, status{status}, mem{mem} {}

  void execute(int16_t parameter) {
    uint16_t result = static_cast<uint16_t>(mem[parameter]) +
                      static_cast<uint16_t>(acc.get_register()) + static_cast<uint16_t>(status.get_flag<Carry>());
    acc = result;
  }

private:
    Accumulator &acc;
    ProcessorStatus &status;
    Memory &mem;
};

struct AND {
  inline AND(ProcessorStatus &status, Accumulator &acc, Memory &mem): status {status}, acc {acc}, mem{mem} {}

  void execute(uint8_t param) {
    acc = acc.get_register() & mem[param];
    if (zero(acc.get_register())) status.set_flag<ZeroResult>();
    if (negative<int8_t>(acc.get_register())) status.set_flag<NegativeResult>();
  }

private:
  ProcessorStatus &status;
  Accumulator &acc;
  Memory &mem;
};

struct ASLACC {
  inline ASLACC(ProcessorStatus &status, Accumulator &acc): status {status}, acc {acc} {}

  void execute() {
    acc = acc.get_register() << 1;
  }

private:
  ProcessorStatus &status;
  Accumulator &acc;
};

struct ASL {
  inline ASL(ProcessorStatus &status, Memory &mem): status {status}, mem{mem} {}

  void execute(uint16_t param) {
    mem[param] <<= 1;
  }

private:
  ProcessorStatus &status;
  Memory &mem;
};

struct LDA {
  inline LDA(ProcessorStatus &status, Accumulator &acc): status{status}, acc{acc} {}

  void execute(uint8_t param) {
    acc = param;
    if (zero(acc)) status.set_flag<ZeroResult>();
    if (negative(acc)) status.set_flag<NegativeResult>();
  }

private:
  ProcessorStatus &status;
  Accumulator &acc;
};

struct LDX {
  inline LDX(ProcessorStatus &status, RegisterX &reg_x): status{status}, reg_x{reg_x} {}

  void execute(uint8_t param) {
    reg_x = param;
    if (zero(reg_x)) status.set_flag<ZeroResult>();
    if (negative(reg_x)) status.set_flag<NegativeResult>();
  }

private:
  ProcessorStatus &status;
  RegisterX &reg_x;
};

struct LDY {
  inline LDY(ProcessorStatus &status, RegisterY &reg_y): status{status}, reg_y{reg_y} {}

  void execute(uint8_t param) {
    reg_y = param;
    if (zero(reg_y)) status.set_flag<ZeroResult>();
    if (negative(reg_y)) status.set_flag<NegativeResult>();
  }

private:
  ProcessorStatus &status;
  RegisterY &reg_y;
};
