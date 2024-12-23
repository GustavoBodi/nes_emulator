#include "AddressingBehaviour.hpp"
#include "AdressingModesImpl.hpp"
#include "Register.hpp"
#include "Instruction.hpp"
#include "Types.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <Processor6502.hpp>

TEST_CASE("New offset in the same zero page", "[new_page_calculation]") {
  REQUIRE(new_page<0x100>(0x00, 0xFF) == false);
  REQUIRE(new_page<0x100>(0x00, 0xAA) == false);
  REQUIRE(new_page<0x100>(0xFF, 0xFF) == false);
}

TEST_CASE("New offset in different page compared to zero page", "[new_page_calculation]") {
  REQUIRE(new_page<0x100>(0x00, 0x100) == true);
  REQUIRE(new_page<0x100>(0x00, 0x10A) == true);
  REQUIRE(new_page<0x100>(0xFF, 0x1FF) == true);
}

TEST_CASE("New offset in the same first page", "[new_page_calculation]") {
  REQUIRE(new_page<0x100>(0x100, 0x1FF) == false);
  REQUIRE(new_page<0x100>(0x110, 0x1AA) == false);
  REQUIRE(new_page<0x100>(0x1F0, 0x1FF) == false);
}

TEST_CASE("New offset in different page than second page", "[new_page_calculation]") {
  REQUIRE(new_page<0x100>(0x100, 0xFF) == true);
  REQUIRE(new_page<0x100>(0x110, 0xEAA) == true);
  REQUIRE(new_page<0x100>(0x1F0, 0x2FF) == true);
}


