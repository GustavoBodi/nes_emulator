#pragma once
#include <cstdint>

template <uint16_t Size, typename Old, typename New>
inline bool new_page(Old old, New new_parameter) {
  uint16_t old_page = static_cast<uint16_t>(old) / Size;
  uint16_t current_page = static_cast<uint16_t>(new_parameter) / Size;
  return old_page != current_page;
}
