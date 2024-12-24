#pragma once
#include <cstdint>
#include <array>
#include "ProgramStatusRegister.hpp"
#include "Memory.hpp"
#include "Register.hpp"

using RegisterX = Register<uint8_t>;
using RegisterY = Register<uint8_t>;
using ProcessorStatus = ProgramStatusRegister;
using Accumulator = Register<uint8_t>;
using StackPointer = Register<uint8_t>;
using ProgramCounter = Register<uint16_t>;
using Memory = MemoryInterface<uint8_t, 0xFFFF>;

template <typename, template <typename...> class>
struct is_specialization_of : std::false_type {};

template <typename... Args, template <typename...> class Template>
struct is_specialization_of<Template<Args...>, Template> : std::true_type {};

template <typename T, template <typename...> class Template>
constexpr bool is_specialization_of_v = is_specialization_of<T, Template>::value;

template <typename T>
concept Integral = std::is_integral_v<T>;

