CMAKE_MINIMUM_REQUIRED(VERSION 3.18.4)

# Single executable file
ADD_EXECUTABLE(example src/main.cpp)
# Use C++17
TARGET_COMPILE_FEATURES(example PRIVATE cxx_std_17)

# Strict checking on Clang
IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Show every warning, treat warnings as errors
    # Disabling default function with delete is not accepted by c++98, silence those warnings
    TARGET_COMPILE_OPTIONS(example PRIVATE -Weverything -Werror -Wno-c++98-compat)

    # Add clang-tidy to check format
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,clang-analyzer-*,-clang-analyzer-cplusplus*")
ENDIF()
