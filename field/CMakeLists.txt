cmake_minimum_required(VERSION 3.12)
project(field C CXX)

set(FIELD_SRCS
    field_GF2_128.cpp
    field_GF2_192.cpp
    field_GF2_256.cpp
  )

set(BUILD_TESTS OFF CACHE BOOL "Build unit tests.")
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(CheckCXXCompilerFlag)
add_library(field STATIC ${FIELD_SRCS})
CHECK_CXX_COMPILER_FLAG(-mpclmul COMPILER_HAS_M_PCLMUL)
CHECK_CXX_COMPILER_FLAG(-msse2 COMPILER_HAS_M_SSE2)
CHECK_CXX_COMPILER_FLAG(-msse4 COMPILER_HAS_M_SSE4)
CHECK_CXX_COMPILER_FLAG(-mpopcnt COMPILER_HAS_M_POPCNT)
CHECK_CXX_COMPILER_FLAG(-mavx2 COMPILER_HAS_M_AVX2)

if (COMPILER_HAS_M_PCLMUL AND COMPILER_HAS_M_SSE2 AND COMPILER_HAS_M_SSE4 AND COMPILER_HAS_M_POPCNT AND COMPILER_HAS_M_AVX2)
  target_compile_options(field PRIVATE -mpclmul -msse2 -msse4 -mpopcnt)
else()
  message(
    ERROR
    "compiler does not have at least one of flag (pclmul, sse2, sse4, popcnt, avx2) which are needed"  )
endif()

target_include_directories(field PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if(BUILD_TESTS)
FIND_PACKAGE(NTL REQUIRED)
FIND_PACKAGE(GMP REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.8)

FetchContent_MakeAvailable(Catch2)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Catch2_SOURCE_DIR}/contrib/")
add_library(test_utils STATIC tests/utils.cpp)
target_link_libraries(test_utils PUBLIC ${NTL_LIBRARY} ${GMP_LIBRARIES} Threads::Threads)

include(CTest)
include(Catch)

function(add_test test_name)
  add_executable(${test_name} tests/${test_name}.cpp)
  target_link_libraries(${test_name} Catch2::Catch2 test_utils field)
  catch_discover_tests(${test_name})
endfunction()

add_test(util_test)
add_test(field_GF2_128_test)
add_test(field_GF2_192_test)
add_test(field_GF2_256_test)
endif()
