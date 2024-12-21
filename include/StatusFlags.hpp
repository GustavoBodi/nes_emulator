#pragma once

enum StatusFlags {
  Carry = 0,
  ZeroResult = 1,
  InterruptDisable = 2,
  DecimalMode = 3,
  Break = 4,
  Overflow = 6,
  NegativeResult = 7,
};
