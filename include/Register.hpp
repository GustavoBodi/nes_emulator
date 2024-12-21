#pragma once
#include <concepts>


template <typename T>
class Register {
public:
  inline Register(T initial_value): register_value{initial_value} {};

  inline void set_register(T param) {
    register_value = param;
  }

  inline T get_register() {
    return register_value;
  }

  ~Register() = default;
private:
    T register_value { 0 };
};
