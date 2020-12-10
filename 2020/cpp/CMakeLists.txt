cmake_minimum_required(VERSION 3.2)
project(adventofcode2020)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(day1 ./1/app.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/1/input1.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/2/input2.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/3/input3.txt  
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(day2 ./2/app.cpp)
add_executable(day3 ./3/app.cpp)
add_executable(day4 ./4/app.cpp)

