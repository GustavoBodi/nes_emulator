#include "AddressingBehaviour.hpp"
#include "AdressingModesImpl.hpp"
#include "Types.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <Processor6502.hpp>

int main(int argc, char **argv) {
  int result = Catch::Session().run(argc, argv);
}

TEST_CASE("Starting program status flags all zero", "[program_status_flags]") {
  ProgramStatusRegister registers {};
  REQUIRE(registers.get_flag<Carry>() == 0);
  REQUIRE(registers.get_flag<ZeroResult>() == 0);
  REQUIRE(registers.get_flag<InterruptDisable>() == 0);
  REQUIRE(registers.get_flag<DecimalMode>() == 0);
  REQUIRE(registers.get_flag<Break>() == 0);
  REQUIRE(registers.get_flag<Overflow>() == 0);
  REQUIRE(registers.get_flag<NegativeResult>() == 0);
}

TEST_CASE("Set value for carry flag and no interference", "[program_status_flags]") {
  ProgramStatusRegister registers {};
  registers.set_flag<Carry>();
  REQUIRE(registers.get_flag<Carry>() == 1);
  REQUIRE(registers.get_flag<ZeroResult>() == 0);
  REQUIRE(registers.get_flag<InterruptDisable>() == 0);
  REQUIRE(registers.get_flag<DecimalMode>() == 0);
  REQUIRE(registers.get_flag<Break>() == 0);
  REQUIRE(registers.get_flag<Overflow>() == 0);
  REQUIRE(registers.get_flag<NegativeResult>() == 0);
}

TEST_CASE("Set value for zero result flag and no interference", "[program_status_flags]") {
  ProgramStatusRegister registers {};
  registers.set_flag<ZeroResult>();
  REQUIRE(registers.get_flag<Carry>() == 0);
  REQUIRE(registers.get_flag<ZeroResult>() == 1);
  REQUIRE(registers.get_flag<InterruptDisable>() == 0);
  REQUIRE(registers.get_flag<DecimalMode>() == 0);
  REQUIRE(registers.get_flag<Break>() == 0);
  REQUIRE(registers.get_flag<Overflow>() == 0);
  REQUIRE(registers.get_flag<NegativeResult>() == 0);
}

TEST_CASE("Set value for interrupt disable flag and no interference", "[program_status_flags]") {
  ProgramStatusRegister registers {};
  registers.set_flag<InterruptDisable>();
  REQUIRE(registers.get_flag<Carry>() == 0);
  REQUIRE(registers.get_flag<ZeroResult>() == 0);
  REQUIRE(registers.get_flag<InterruptDisable>() == 1);
  REQUIRE(registers.get_flag<DecimalMode>() == 0);
  REQUIRE(registers.get_flag<Break>() == 0);
  REQUIRE(registers.get_flag<Overflow>() == 0);
  REQUIRE(registers.get_flag<NegativeResult>() == 0);
}

TEST_CASE("Set value for decimal mode flag and no interference", "[program_status_flags]") {
  ProgramStatusRegister registers {};
  registers.set_flag<DecimalMode>();
  REQUIRE(registers.get_flag<Carry>() == 0);
  REQUIRE(registers.get_flag<ZeroResult>() == 0);
  REQUIRE(registers.get_flag<InterruptDisable>() == 0);
  REQUIRE(registers.get_flag<DecimalMode>() == 1);
  REQUIRE(registers.get_flag<Break>() == 0);
  REQUIRE(registers.get_flag<Overflow>() == 0);
  REQUIRE(registers.get_flag<NegativeResult>() == 0);
}

TEST_CASE("Set value for break flag and no interference", "[program_status_flags]") {
  ProgramStatusRegister registers {};
  registers.set_flag<Break>();
  REQUIRE(registers.get_flag<Carry>() == 0);
  REQUIRE(registers.get_flag<ZeroResult>() == 0);
  REQUIRE(registers.get_flag<InterruptDisable>() == 0);
  REQUIRE(registers.get_flag<DecimalMode>() == 0);
  REQUIRE(registers.get_flag<Break>() == 1);
  REQUIRE(registers.get_flag<Overflow>() == 0);
  REQUIRE(registers.get_flag<NegativeResult>() == 0);
}

TEST_CASE("Set value for overflow and no interference", "[program_status_flags]") {
  ProgramStatusRegister registers {};
  registers.set_flag<Overflow>();
  REQUIRE(registers.get_flag<Carry>() == 0);
  REQUIRE(registers.get_flag<ZeroResult>() == 0);
  REQUIRE(registers.get_flag<InterruptDisable>() == 0);
  REQUIRE(registers.get_flag<DecimalMode>() == 0);
  REQUIRE(registers.get_flag<Break>() == 0);
  REQUIRE(registers.get_flag<Overflow>() == 1);
  REQUIRE(registers.get_flag<NegativeResult>() == 0);
}

TEST_CASE("Set value for negative result and no interference", "[program_status_flags]") {
  ProgramStatusRegister registers {};
  registers.set_flag<NegativeResult>();
  REQUIRE(registers.get_flag<Carry>() == 0);
  REQUIRE(registers.get_flag<ZeroResult>() == 0);
  REQUIRE(registers.get_flag<InterruptDisable>() == 0);
  REQUIRE(registers.get_flag<DecimalMode>() == 0);
  REQUIRE(registers.get_flag<Break>() == 0);
  REQUIRE(registers.get_flag<Overflow>() == 0);
  REQUIRE(registers.get_flag<NegativeResult>() == 1);
}

TEST_CASE("Set value for carry and overflow flags", "[program_status_flags]") {
  ProgramStatusRegister registers {};
  registers.set_flag<Carry>();
  registers.set_flag<Overflow>();
  REQUIRE(registers.get_flag<Carry>() == 1);
  REQUIRE(registers.get_flag<ZeroResult>() == 0);
  REQUIRE(registers.get_flag<InterruptDisable>() == 0);
  REQUIRE(registers.get_flag<DecimalMode>() == 0);
  REQUIRE(registers.get_flag<Break>() == 0);
  REQUIRE(registers.get_flag<Overflow>() == 1);
  REQUIRE(registers.get_flag<NegativeResult>() == 0);
}

TEST_CASE("Clear the value for decimal flag", "[program_status_flags]") {
  ProgramStatusRegister registers {};
  registers.set_flag<DecimalMode>();
  registers.clear_flag<DecimalMode>();
  REQUIRE(registers.get_flag<Carry>() == 0);
  REQUIRE(registers.get_flag<ZeroResult>() == 0);
  REQUIRE(registers.get_flag<InterruptDisable>() == 0);
  REQUIRE(registers.get_flag<DecimalMode>() == 0);
  REQUIRE(registers.get_flag<Break>() == 0);
  REQUIRE(registers.get_flag<Overflow>() == 0);
  REQUIRE(registers.get_flag<NegativeResult>() == 0);
}

TEST_CASE("Set the value for carry negative result, break and clear the value for overflow flag", "[program_status_flags]") {
  ProgramStatusRegister registers {};
  registers.set_flag<Break>();
  registers.set_flag<NegativeResult>();
  registers.set_flag<Overflow>();
  registers.clear_flag<Overflow>();
  REQUIRE(registers.get_flag<Carry>() == 0);
  REQUIRE(registers.get_flag<ZeroResult>() == 0);
  REQUIRE(registers.get_flag<InterruptDisable>() == 0);
  REQUIRE(registers.get_flag<DecimalMode>() == 0);
  REQUIRE(registers.get_flag<Break>() == 1);
  REQUIRE(registers.get_flag<Overflow>() == 0);
  REQUIRE(registers.get_flag<NegativeResult>() == 1);
}

TEST_CASE("Clear carry and zero result flags and set break", "[program_status_flags]") {
  ProgramStatusRegister registers {};
  registers.set_flag<Carry>();
  registers.set_flag<Break>();
  registers.set_flag<ZeroResult>();
  registers.clear_flag<Carry>();
  registers.clear_flag<ZeroResult>();
  REQUIRE(registers.get_flag<Carry>() == 0);
  REQUIRE(registers.get_flag<ZeroResult>() == 0);
  REQUIRE(registers.get_flag<InterruptDisable>() == 0);
  REQUIRE(registers.get_flag<DecimalMode>() == 0);
  REQUIRE(registers.get_flag<Break>() == 1);
  REQUIRE(registers.get_flag<Overflow>() == 0);
  REQUIRE(registers.get_flag<NegativeResult>() == 0);
}

TEST_CASE("Calculate Offset 0 in zero page", "[page_offset]") {
  Processor6502 cpu {};
  REQUIRE(cpu.get_address_from_page<0>(0) == 0);
}

TEST_CASE("Calculate Offsets in first page", "[page_offset]") {
  Processor6502 cpu {};
  REQUIRE(cpu.get_address_from_page<1>(0) == 0x0100);
  REQUIRE(cpu.get_address_from_page<1>(10) == 0x010A);
}

TEST_CASE("Calculate Final Offsets in the zero page", "[page_offset]") {
  Processor6502 cpu {};
  REQUIRE(cpu.get_address_from_page<0>(0xFF) == 0x0FF);
}

TEST_CASE("Calculate the offsets bounds in the first page", "[page_offset]") {
  Processor6502 cpu {};
  REQUIRE(cpu.get_address_from_page<1>(0xFF) == 0x01FF);
  REQUIRE_THROWS(cpu.get_address_from_page<1>(-1));
  REQUIRE_THROWS(cpu.get_address_from_page<1>(0x100));
}

TEST_CASE("Immediate Addressing mode", "[addressing_mode]") {
  auto imm = Immediate();
  uint8_t address = 0xFF;
  REQUIRE(std::get<0>(imm.get_mem(address)) == address);
  REQUIRE(std::get<1>(imm.get_mem(address)) == None);
}

TEST_CASE("ZeroPage Addressing mode", "[addressing_mode]") {
  auto zero = ZeroPage();
  uint8_t address = 0xFF;
  REQUIRE(std::get<0>(zero.get_mem(address)) == address);
  REQUIRE(std::get<1>(zero.get_mem(address)) == None);
}

TEST_CASE("ZeroPageX Addressing mode with 0 in registerX", "[addressing_mode]") {
  RegisterX register_x { 0 };
  auto zero = ZeroPageX(register_x);
  uint8_t address = 0xFF;
  REQUIRE(std::get<0>(zero.get_mem(address)) == address);
  REQUIRE(std::get<1>(zero.get_mem(address)) == None);
}

TEST_CASE("ZeroPageX Addressing mode with 0x10 in registerX", "[addressing_mode]") {
  RegisterX register_x { 0x10 };
  auto zero = ZeroPageX(register_x);
  uint8_t address = 0xAA;
  REQUIRE(std::get<0>(zero.get_mem(address)) == 0xBA);
  REQUIRE(std::get<1>(zero.get_mem(address)) == None);
}

TEST_CASE("ZeroPageY Addressing mode with 0 in registerY", "[addressing_mode]") {
  RegisterX register_y { 0 };
  auto zero = ZeroPageY(register_y);
  uint8_t address = 0xFF;
  REQUIRE(std::get<0>(zero.get_mem(address)) == address);
  REQUIRE(std::get<1>(zero.get_mem(address)) == None);
}

TEST_CASE("ZeroPageY Addressing mode with 0x10 in registerY", "[addressing_mode]") {
  RegisterY register_y { 0x10 };
  auto zero = ZeroPageY(register_y);
  uint8_t address = 0xBA;
  REQUIRE(std::get<0>(zero.get_mem(address)) == 0xCA);
  REQUIRE(std::get<1>(zero.get_mem(address)) == None);
}

TEST_CASE("Relative Addressing Mode with 120 as offset and pc 0", "[addressing_mode]") {
  ProgramCounter pc { 0 };
  auto rel = Relative(pc);
  uint8_t offset = 120;
  REQUIRE(std::get<0>(rel.get_mem(offset)) == 120);
  REQUIRE(std::get<1>(rel.get_mem(offset)) == None);
}

TEST_CASE("Relative Addressing Mode with 0 as offset and pc 0", "[addressing_mode]") {
  ProgramCounter pc { 0 };
  auto rel = Relative(pc);
  uint8_t offset = 0;
  REQUIRE(std::get<0>(rel.get_mem(offset)) == 0);
  REQUIRE(std::get<1>(rel.get_mem(offset)) == None);
}

TEST_CASE("Relative Addressing Mode with 100 as offset and pc 1000", "[addressing_mode]") {
  ProgramCounter pc { 1000 };
  auto rel = Relative(pc);
  uint8_t offset = 100;
  REQUIRE(std::get<0>(rel.get_mem(offset)) == 1100);
  REQUIRE(std::get<1>(rel.get_mem(offset)) == PageCrossed);
}

TEST_CASE("Absolute Addressing Mode with 0x300 parameter", "[addressing_mode]") {
  auto abs = Absolute();
  uint16_t offset = 0x0300;
  REQUIRE(std::get<0>(abs.get_mem(offset)) == 0x0300);
  REQUIRE(std::get<1>(abs.get_mem(offset)) == None);
}

TEST_CASE("AbsoluteX addressing_mode in the same page", "[addressing_mode]") {
  RegisterX reg_x { 0x0F };
  auto abs_x = AbsoluteX(reg_x);
  REQUIRE(std::get<0>(abs_x.get_mem(0xF0)) == 0x0FF);
  REQUIRE(std::get<1>(abs_x.get_mem(0xF0)) == None);
}

TEST_CASE("AbsoluteX addressing_mode in different pages", "[addressing_mode]") {
  RegisterX reg_x { 0x1F };
  auto abs_x = AbsoluteX(reg_x);
  REQUIRE(std::get<0>(abs_x.get_mem(0xF0)) == 0x10F);
  REQUIRE(std::get<1>(abs_x.get_mem(0xF0)) == PageCrossed);
}

TEST_CASE("AbsoluteY addressing_mode in the same page", "[addressing_mode]") {
  RegisterY reg_y { 0x0F };
  auto abs_y = AbsoluteY(reg_y);
  REQUIRE(std::get<0>(abs_y.get_mem(0xF0)) == 0x0FF);
  REQUIRE(std::get<1>(abs_y.get_mem(0xF0)) == None);
}

TEST_CASE("AbsoluteY addressing_mode in different pages", "[addressing_mode]") {
  RegisterY reg_y { 0x1F };
  auto abs_y = AbsoluteY(reg_y);
  REQUIRE(std::get<0>(abs_y.get_mem(0xF0)) == 0x10F);
  REQUIRE(std::get<1>(abs_y.get_mem(0xF0)) == PageCrossed);
}
