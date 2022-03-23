cmake_minimum_required (VERSION 3.12)
project (rain_signatures C CXX)

cmake_policy(SET CMP0069 NEW) # using CheckIPOSupported

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17) 

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT error)


if( ipo_supported )
    message(STATUS "IPO / LTO enabled")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION True)
else()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif()

set(BUILD_TESTS OFF CACHE BOOL "Build unit tests.")

add_compile_options("-Wall")
add_compile_options("-march=native")
#add_compile_options("-fsanitize=address")
#add_link_options("-fsanitize=address")

add_subdirectory(keccak)
add_subdirectory(field)

set(RAIN_SRCS
  instances.cpp
  rain.cpp
  randomness.c
  signature.cpp
  tape.cpp
  tree.cpp
  )


add_library(rain_static STATIC ${RAIN_SRCS})
target_link_libraries(rain_static PUBLIC keccak field) 
#also includes the non-transposed matrices, can be useful for debugging
#target_compile_definitions(rain_static PUBLIC INCLUDE_STANDARD_MATRICES)

add_library(bench_utils STATIC tools/bench_utils.cpp tools/bench_timing.cpp)
add_executable(bench tools/bench.cpp)
add_executable(bench_free tools/bench_free.cpp)
target_link_libraries(bench rain_static bench_utils)
target_link_libraries(bench_free rain_static bench_utils)

if(BUILD_TESTS)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.8)

FetchContent_MakeAvailable(Catch2)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Catch2_SOURCE_DIR}/contrib/")


include(CTest)
include(Catch)

function(add_test test_name)
  add_executable(${test_name} tests/${test_name}.cpp)
  target_link_libraries(${test_name} Catch2::Catch2 rain_static)
  catch_discover_tests(${test_name})
endfunction()

add_test(rain_test)
#add_test(signature_test)
#add_test(tree_test)
endif()
