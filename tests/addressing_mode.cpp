#include "AddressingBehaviour.hpp"
#include "AdressingModesImpl.hpp"
#include "Register.hpp"
#include "Instruction.hpp"
#include "Types.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <Processor6502.hpp>

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

TEST_CASE("ZeroPageX wrapping test", "[addressing_mode]") {
  RegisterX register_x {0xF1};
  auto zero = ZeroPageX(register_x);
  uint8_t address = 0xFA;
  REQUIRE(std::get<0>(zero.get_mem(address)) == 0xEB);
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

TEST_CASE("ZeroPageY wrapping test", "[addressing_mode]") {
  RegisterY register_y {0xF1};
  auto zero = ZeroPageY(register_y);
  uint8_t address = 0xFA;
  REQUIRE(std::get<0>(zero.get_mem(address)) == 0xEB);
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

TEST_CASE("Indirect Addressing of memory", "[addressing_mode]") {
  Memory mem { };
  mem[0x120] = 0xFC;
  mem[0x121] = 0xBA;
  Indirect ind { mem };
  REQUIRE(std::get<0>(ind.get_mem(0x0120)) == 0xBAFC);
  REQUIRE(std::get<1>(ind.get_mem(0x0120)) == None);
}

TEST_CASE("Indexed Indirect Addressing of Memory", "[addressing_mode]") {
  Memory mem { };
  auto reg_x = RegisterX { 0x10 };
  mem[0xFA] = 0xAA;
  mem[0xFB] = 0xCD;
  IndexedIndirect ind {mem, reg_x};
  REQUIRE(std::get<0>(ind.get_mem(0xEA)) == 0xCDAA);
  REQUIRE(std::get<1>(ind.get_mem(0xEA)) == None);
}

TEST_CASE("Indirect Indexed Addressing of Memory with page crossing", "[addressing_mode]") {
  Memory mem { };
  auto reg_y = RegisterY { 0x10 };
  mem[0xFA] = 0xAA;
  mem[0xFB] = 0xCD;
  IndirectIndexed ind { mem, reg_y };
  REQUIRE(std::get<0>(ind.get_mem(0xFA)) == 0xCDBA);
  REQUIRE(std::get<1>(ind.get_mem(0xFA)) == PageCrossed);
}

TEST_CASE("Indirect Indexed Addressing of Memory without page crossing", "[addressing_mode]") {
  Memory mem { };
  auto reg_y = RegisterY { 0x10 };
  mem[0xFA] = 0xAA;
  mem[0xFB] = 0x00;
  IndirectIndexed ind { mem, reg_y };
  REQUIRE(std::get<0>(ind.get_mem(0xFA)) == 0x00BA);
  REQUIRE(std::get<1>(ind.get_mem(0xFA)) == None);
}

