CMAKE_MINIMUM_REQUIRED(VERSION 3.18.4)

# Single executable file
ADD_EXECUTABLE(example src/main.cpp)
# Use C++17
TARGET_COMPILE_FEATURES(example PRIVATE cxx_std_17)

# Strict checking on Clang
IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Show every warning, treat warnings as errors
    TARGET_COMPILE_OPTIONS(example PRIVATE -Weverything -Werror)
ENDIF()
