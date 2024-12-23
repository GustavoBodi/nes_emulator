#pragma once
#include <cstdint>
#include <array>

template <typename T, std::size_t size>
class MemoryInterface {
public:
  MemoryInterface() {}

  inline T &operator[] (std::size_t param) {
    return internal_mem[param];
  }

  ~MemoryInterface() = default;

private:
  std::array<T, size> internal_mem { 0 };
};
