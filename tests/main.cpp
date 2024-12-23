#include "AddressingBehaviour.hpp"
#include "AdressingModesImpl.hpp"
#include "Instruction.hpp"
#include "Types.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <Processor6502.hpp>

int main(int argc, char **argv) {
  int result = Catch::Session().run(argc, argv);
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

