#pragma once
#include "AddressingConcept.hpp"
#include <cstdint>
#include <concepts>

template <uint8_t opcode, typename AddressingPolicy, typename Instruction, typename CyclePolicy>
struct OpCode {
  inline static void execute(AddressingPolicy policy, Instruction instruction, uint16_t param) noexcept {
    auto addressed_memory = policy.get_mem(param);
    auto instruction_result = instruction.execute(std::get<0>(addressed_memory));
    CyclePolicy::compute_cycle(addressed_memory);
  }

  constexpr inline static uint8_t get_opcode() noexcept {
    return opcode;
  }
};

template <typename T, typename P>
concept Instruction = requires(T type, P param) {
  { type.run() } -> std::same_as<bool>;
};
