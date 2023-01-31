cmake_minimum_required(VERSION 3.20)

project(POCKET_CSV_TEST)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# The general idea is to use the default values and overwrite them only for
# specific, well experimented environments.
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU"
    OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")

  set(NO_WARN_FLAGS "-w")

  set(WARN_FLAGS "-Wpedantic" "-Wall" "-Wextra" "-Winvalid-pch" "-Wpedantic"
                 "-Wformat=2" "-Wfloat-equal" "-Wshadow" "-Wdouble-promotion"
                 "-Wzero-as-null-pointer-constant")
  # `-Wconversion`, `-Wsign-conversion`, `-Weffc++` are other interesting
  # switches to try from time to time (they give many false positives).

elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

  set(NO_WARN_FLAGS "/w")
  set(WARN_FLAGS "/W3")

endif()

enable_testing()

add_compile_options(${OTHER_FLAGS} ${WARN_FLAGS})

# Compiler must support the C++17 standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${POCKET_CSV_TEST_SOURCE_DIR})
include_directories(../${POCKET_CSV_TEST_SOURCE_DIR})

add_executable(test_parser test_parser.cc)
add_test(NAME test_parser COMMAND test_parser)
