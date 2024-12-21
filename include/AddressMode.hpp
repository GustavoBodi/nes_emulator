#pragma once

enum class AddressMode {
  // Operations like Clear the Flag (CLC) and Return From Subroutine (RTS)
  Implicit,
  // Operates directly on the accumelators
  Accumulator,
  // Programmer specifies directly the 8 bit constant
  Immediate,
  // Has only 8 bit address operand
  ZeroPage,
  // Is calculated by taking the 8 bit zero page address from the
  // instruction and adding the current value of the x register to it.
  // If the address calculation surpasses FF, the sum wraps e.g. 80 + FF = 7F
  ZeroPageX,
  // Sums the 8bit zero page address from the instruction and the value from the
  // y register, only accespted by ldx and stx.
  ZeroPageY,
  // Used by branch instructions, the instruction is a signed 8 bit offset that
  // is added to the program counter.
  Relative,
  // Jump to a 16 bit address.
  Absolute,
  // 16 bit address of the instruction added the content of the x register.
  AbsoluteX,
  // 16 bit address of the instruction added the content of the y register.
  AbsoluteY,
  // JMP is the only instruction. The instruction contains a 16 bit address
  // which identifies the location of the least significant byte of another
  // address that has the real instruction. e.g.
  // For example if location $0120 contains $FC and location $0121 contains $BA
  // then the instruction JMP ($0120) will cause the next instruction execution
  // to occur at $BAFC (e.g. the contents of $0120 and $0121).
  Indirect,
  // The zero page address of the tbale is taken from the instructiona nd the x
  // register is added to it (with zero page wrap around) to give the location of
  // the least significant byte of the target address.
  IndexedIndirect,
  // An instruction contains the zero page location of the least significant byte of
  // the 16 bit address, the y register dynamically added to this value to generate 
  // the actual target address of the operation.
  IndirectIndexed,
};
