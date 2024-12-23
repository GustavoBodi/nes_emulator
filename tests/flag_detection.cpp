#include "AddressingBehaviour.hpp"
#include "AdressingModesImpl.hpp"
#include "Instruction.hpp"
#include "Types.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <Processor6502.hpp>

TEST_CASE("Negative Flag detection", "[flag_detection]") {
  REQUIRE(negative<uint8_t>(0b10000000) == true);
  REQUIRE(negative<uint8_t>(0b01010010) == false);
}

TEST_CASE("Carry flag detection", "[flag_detection]") {
  uint8_t value1 = 0x20;
  uint8_t value2 = 0xF0;
  REQUIRE(carry(value1 + value2) == true);
  REQUIRE(carry(0x100) == true);
  REQUIRE(carry(value1) == false);
  REQUIRE(carry(value2) == false);
  REQUIRE(carry(0xFF) == false);
}

TEST_CASE("Zero flag detection", "[flag_detection]") {
  uint8_t value1 = 0x10;
  uint8_t value2 = 0x20;
  REQUIRE(zero(value1) == false);
  REQUIRE(zero(static_cast<uint16_t>(value1)) == false);
  REQUIRE(zero(0x0) == true);
  REQUIRE(zero(value2 - 2 * value1) == true);
}

TEST_CASE("Overflow flag detection", "[flag_detection]") {
  uint8_t value1 = 100;
  uint8_t value2 = 30;
  REQUIRE(overflow(value1, value2, static_cast<int8_t>(value1) + static_cast<int8_t>(value2)) == true);
}

