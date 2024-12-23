#include "AddressingBehaviour.hpp"
#include "AdressingModesImpl.hpp"
#include "Register.hpp"
#include "Instruction.hpp"
#include "Types.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <Processor6502.hpp>

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
