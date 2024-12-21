#pragma once
#include <cstdint>
#include <array>
#include "ProgramStatusRegister.hpp"
#include "Register.hpp"

using RegisterX = Register<uint8_t>;
using RegisterY = Register<uint8_t>;
using ProcessorStatus = ProgramStatusRegister;
using Accumulator = Register<uint8_t>;
using StackPointer = Register<uint8_t>;
using ProgramCounter = Register<uint16_t>;
using Memory = std::array<uint8_t, 0xFFFF>;
