cmake_minimum_required(VERSION 3.22)
project(Nes VERSION 0.0.1 LANGUAGES CXX)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include(${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake)

# Add these lines to use the new Conan CMake integration
find_package(SDL2 REQUIRED)

find_package(imgui REQUIRED)

# Find Catch2 for testing
find_package(Catch2 3 REQUIRED)

# Gather all source files for the main project
file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/include/*.h"
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

# Add the main executable
add_executable(Nes ${PROJECT_SOURCES})

# Link Boost libraries to the main executable
target_link_libraries(Nes PRIVATE SDL2::SDL2 imgui::imgui)

# Enable compiler features and warnings (optional but recommended)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(Nes PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-unused-variable -Wno-unused-function)
elseif (MSVC)
  target_compile_options(Nes PRIVATE /W4 /WX)
endif()

# Testing Configuration
file(GLOB_RECURSE TEST_SOURCES
    "${CMAKE_SOURCE_DIR}/tests/*.cpp"
)

add_executable(UnitTests ${TEST_SOURCES})

include_directories("${CMAKE_SOURCE_DIR}/include")
# Link Catch2 with tests and Boost libraries
target_link_libraries(UnitTests PRIVATE Catch2::Catch2WithMain SDL2::SDL2)

# Register tests with CTest
include(CTest)
include(Catch)
catch_discover_tests(UnitTests)

# Installation (Optional)
install(TARGETS Nes
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

