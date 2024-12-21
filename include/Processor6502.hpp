#pragma once
#include <cassert>
#include <memory>
#include <cstdint>
#include <array>
#include <stdexcept>
#include "Register.hpp"
#include "Types.hpp"

class Processor6502 {
public:
  Processor6502() {

  }

  template<uint8_t page>
  uint16_t get_address_from_page(uint16_t offset) {
    static_assert(page >= 0);
    static_assert(page <= 32);
    if (offset < 0) {
      throw std::invalid_argument("Offset lesser than zero");
    }
    if (offset > 0x00FF) {
      throw std::invalid_argument("Offset greater than page size");
    }
    return page * 0x0100 + offset;
  }

  uint8_t get_x_register() {
    return index_x.get_register();
  }

  uint16_t get_address_from_zero_page(uint16_t offset) {
    return get_address_from_page<0>(offset);
  }

  uint16_t get_address_from_stack(uint16_t offset) {
    return get_address_from_page<1>(offset);
  } 

  std::tuple<uint16_t, uint16_t> get_address_range_from_nmask_interrupt_handler() {
    return std::make_tuple(0xFFFA, 0xFFFB);
  }

  std::tuple<uint16_t, uint16_t> get_address_range_from_reset() {
    return std::make_tuple(0xFFFC, 0xFFFD);
  }

  std::tuple<uint16_t, uint16_t> get_address_range_from_brk_request_handler() {
    return std::make_tuple(0xFFFE, 0xFFFF);
  }


  ~Processor6502() = default;
private:
  Memory memory { 0 };

  // The program counter points to thenext instruction
  // Modifiable by jump, relative branch, subroutine, return from subroutine
  // or interrupt
  ProgramCounter program_counter { 0 };

  // The stack is the first page (different from zero). This holds the low 8 bits of the
  // next free location on the stack. Pushing bytes causes the stack to be decremented,
  // pulling bytes causes increment. There are no checks for stack overflow in this CPU.
  StackPointer stack_pointer { 0 };

  // Accumulator for arithmetical expressions (register)
  Accumulator accumulator { 0 };

  // The index x (register) is used for counter and offsets to memoty
  // Special: can get a copy of the stack pointer of change its value
  RegisterX index_x { 0 };

  // The index y (register) is used for the same as the index x but has
  // no special functions
  RegisterY index_y { 0 };

  // Register that describes the record results of operations.
  // Carry flag: if the operation caused overflow from bit 7 or underflow from bit 0.
  // Zero flag: if the last operation resulted in zero.
  // Interrupt Disable: If the program executed SEI, until CLI.
  // Decimal Mode: If set, the processor will follow BCD rules.
  // Break Command: BRK is executed and an interrupted generated to proccess it.
  // Overflow Flag: If the operationg yielded an invalid 2 complements result.
  // Negative Flag: If the last operation yielded a result with bit 7 set to one.
  ProcessorStatus processor_status { 0 };

};
