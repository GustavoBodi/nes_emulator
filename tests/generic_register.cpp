#include "AddressingBehaviour.hpp"
#include "AdressingModesImpl.hpp"
#include "Register.hpp"
#include "Instruction.hpp"
#include "Types.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <Processor6502.hpp>

TEST_CASE("Register constructor default construction", "[generic_register]") {
  Register<uint8_t> reg { 0 };
  REQUIRE(reg.get_register() == 0);
}

TEST_CASE("Register constructor with value", "[generic_register]") {
  Register<uint8_t> reg { 30 };
  REQUIRE(reg.get_register() == 30);
}

TEST_CASE("Register with set value", "[generic_register]") {
  Register<uint8_t> reg { 30 };
  reg.set_register(10);
  REQUIRE(reg.get_register() == 10);
}

TEST_CASE("Register with multiple set values", "[generic_register]") {
  Register<uint8_t> reg { 30 };
  reg.set_register(10);
  reg.set_register(20);
  reg.set_register(50);
  REQUIRE(reg.get_register() == 50);
}

