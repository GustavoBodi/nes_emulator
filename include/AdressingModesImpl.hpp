#pragma once
#include "AddressMode.hpp"
#include "Types.hpp"
#include <cstdint>

struct Immediate {
  AddressMode mode = AddressMode::Immediate;

  inline uint8_t get_mem(uint8_t parameter) {
    return parameter;
  }
};

struct ZeroPage {
  AddressMode mode = AddressMode::ZeroPage;

  inline uint8_t get_mem(uint8_t parameter) {
    return parameter;
  }
};

struct ZeroPageX {
  AddressMode mode = AddressMode::ZeroPageX;

  inline ZeroPageX(RegisterX &reg): reg_x{reg} {}

  inline uint8_t get_mem(uint8_t parameter) {
    return parameter + reg_x.get_register();
  }

private:
  RegisterX &reg_x;
};

struct ZeroPageY {
  AddressMode mode = AddressMode::ZeroPageY;

  inline ZeroPageY(RegisterY &reg): reg_y{reg} {}

  inline uint8_t get_mem(uint8_t parameter) {
    return parameter + reg_y.get_register();
  }

private:
  RegisterY &reg_y;
};

struct Relative {
  AddressMode mode = AddressMode::Relative;

  inline Relative(ProgramCounter &pc): pc{pc} {}

  inline uint8_t get_mem(int8_t parameter) {
    return pc.get_register() + parameter;
  }

private:
  ProgramCounter &pc;
};


struct Absolute {
  AddressMode mode = AddressMode::Absolute;

  inline uint16_t get_mem(uint16_t parameter) {
    return parameter;
  }
};

struct AbsoluteX {
  AddressMode mode = AddressMode::AbsoluteX;

  inline AbsoluteX(RegisterX &reg): reg{reg} {}

  inline uint16_t get_mem(uint16_t parameter) {
    return parameter + reg.get_register();
  }

private:
  RegisterX &reg;
};

struct AbsoluteY {
  AddressMode mode = AddressMode::AbsoluteY;

  inline AbsoluteY(RegisterY &reg): reg{reg} {}

  inline uint16_t get_mem(uint16_t parameter) {
    return parameter + reg.get_register();
  }

private:
  RegisterY &reg;
};

struct Indirect {
  AddressMode mode = AddressMode::Indirect;

  inline Indirect(Memory &mem): mem{mem} {}

  inline uint16_t get_mem(uint16_t parameter) {
    uint16_t address = mem[parameter];
    return address;
  }

private:
  Memory &mem;
};

struct IndexedIndirect {
  AddressMode mode = AddressMode::IndexedIndirect;

  inline IndexedIndirect(Memory &mem, RegisterX &reg): mem{mem}, reg{reg} {}

  inline uint16_t get_mem(uint16_t parameter) {
    uint16_t address = mem[parameter + reg.get_register()] % 0x100;
    return address;
  }

private:
  Memory &mem;
  RegisterX &reg;
};

struct IndirectIndexed {
  AddressMode mode = AddressMode::IndirectIndexed;

  inline IndirectIndexed(Memory &mem, RegisterY &reg): mem{mem}, reg{reg} {}

  inline uint16_t get_mem(uint16_t parameter) {
    uint16_t address = mem[parameter] + reg.get_register();
    return address;
  }

private:
  Memory &mem;
  RegisterY &reg;
};
