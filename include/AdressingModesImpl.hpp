#pragma once
#include "AddressMode.hpp"
#include "AddressingConcept.hpp"
#include "Pages.hpp"
#include "Types.hpp"
#include <cstdint>

struct Immediate {
  AddressMode mode = AddressMode::Immediate;

  inline std::tuple<uint16_t, AddressingBehaviour> get_mem(uint8_t parameter) {
    return std::tuple(parameter, None);
  }
};

struct ZeroPage {
  AddressMode mode = AddressMode::ZeroPage;

  inline std::tuple<uint16_t, AddressingBehaviour> get_mem(uint8_t parameter) {
    return std::tuple(parameter, None);
  }
};

struct ZeroPageX {
  AddressMode mode = AddressMode::ZeroPageX;

  inline ZeroPageX(RegisterX &reg): reg_x{reg} {}

  inline std::tuple<uint16_t, AddressingBehaviour> get_mem(uint8_t parameter) {
    return std::tuple((parameter + reg_x.get_register()) % 0x100, None);
  }

private:
  RegisterX &reg_x;
};

struct ZeroPageY {
  AddressMode mode = AddressMode::ZeroPageY;

  inline ZeroPageY(RegisterY &reg): reg_y{reg} {}

  inline std::tuple<uint16_t, AddressingBehaviour> get_mem(uint8_t parameter) {
    return std::tuple((parameter + reg_y.get_register()) % 0x100, None);
  }

private:
  RegisterY &reg_y;
};

struct Relative {
  AddressMode mode = AddressMode::Relative;

  inline Relative(ProgramCounter &pc): pc{pc} {}

  inline std::tuple<uint16_t, AddressingBehaviour> get_mem(int8_t parameter) {
    uint16_t result = pc.get_register() + parameter;
    AddressingBehaviour behaviour { None };
    if (new_page<0x100>(pc.get_register(), result)) {
      behaviour = PageCrossed;
    }
    return std::tuple(result, behaviour);
  }

private:
  ProgramCounter &pc;
};


struct Absolute {
  AddressMode mode = AddressMode::Absolute;

  inline std::tuple<uint16_t, AddressingBehaviour> get_mem(uint16_t parameter) {
    return std::tuple(parameter, None);
  }
};

struct AbsoluteX {
  AddressMode mode = AddressMode::AbsoluteX;

  inline AbsoluteX(RegisterX &reg): reg{reg} {}

  inline std::tuple<uint16_t, AddressingBehaviour> get_mem(uint16_t parameter) {
    uint16_t result = parameter + reg.get_register();
    AddressingBehaviour behaviour { None };
    if (new_page<0x100>(parameter, result)) {
      behaviour = PageCrossed;
    }
    return std::tuple(result, behaviour);
  }

private:
  RegisterX &reg;
};

struct AbsoluteY {
  AddressMode mode = AddressMode::AbsoluteY;

  inline AbsoluteY(RegisterY &reg): reg{reg} {}

  inline std::tuple<uint16_t, AddressingBehaviour> get_mem(uint16_t parameter) {
    uint16_t result = parameter + reg.get_register();
    AddressingBehaviour behaviour { None };
    if (new_page<0x100>(parameter, result)) {
      behaviour = PageCrossed;
    }
    return std::tuple(result, behaviour);
  }

private:
  RegisterY &reg;
};

struct Indirect {
  AddressMode mode = AddressMode::Indirect;

  inline Indirect(Memory &mem): mem{mem} {}

  inline std::tuple<uint16_t, AddressingBehaviour> get_mem(uint16_t parameter) {
    uint16_t address = static_cast<uint16_t>(mem[parameter]) + (static_cast<uint16_t>(mem[parameter + 1]) << 8);
    return std::tuple(address, None);
  }

private:
  Memory &mem;
};

struct IndexedIndirect {
  AddressMode mode = AddressMode::IndexedIndirect;

  inline IndexedIndirect(Memory &mem, RegisterX &reg): mem{mem}, reg{reg} {}

  inline std::tuple<uint16_t, AddressingBehaviour> get_mem(uint16_t parameter) {
    uint8_t page_address_first_byte = static_cast<uint8_t>((static_cast<uint16_t>(parameter) + static_cast<uint16_t>(reg.get_register())) % 0x100);
    uint8_t page_address_second_byte = static_cast<uint8_t>((static_cast<uint16_t>(parameter) + static_cast<uint16_t>(reg.get_register()) + 1) % 0x100);
    uint16_t address = (mem[page_address_first_byte] + (mem[page_address_second_byte] << 8));
    return std::tuple(address, None);
  }

private:
  Memory &mem;
  RegisterX &reg;
};

struct IndirectIndexed {
  AddressMode mode = AddressMode::IndirectIndexed;

  inline IndirectIndexed(Memory &mem, RegisterY &reg): mem{mem}, reg{reg} {}

  inline std::tuple<uint16_t, AddressingBehaviour> get_mem(uint8_t parameter) {
    AddressingBehaviour behaviour = None;
    uint8_t page_address_first_byte = mem[parameter];
    uint8_t page_address_second_byte = mem[(parameter + 1) % 0x100];
    uint16_t address = static_cast<uint16_t>(page_address_first_byte) + static_cast<uint16_t>(page_address_second_byte << 8) + static_cast<uint16_t>(reg.get_register());
    if (new_page<0x100>(parameter, address)) {
      behaviour = PageCrossed;
    }
    return std::tuple(address, behaviour);
  }

private:
  Memory &mem;
  RegisterY &reg;
};
