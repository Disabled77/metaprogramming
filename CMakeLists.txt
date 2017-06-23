cmake_minimum_required(VERSION 2.8)

project(metaprogramming)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -march='native' -Wnarrowing -std=c++14")# -march='nehalem'
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sources")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
#message("SOURCE_DIR = ${SOURCE_DIR}")
add_executable(${PROJECT_NAME} "${SOURCE_DIR}/main.cpp" "${SOURCE_DIR}/class_provide_strategy.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC -lgtest -lgtest_main -lpthread)
