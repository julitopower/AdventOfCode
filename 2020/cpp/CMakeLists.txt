cmake_minimum_required(VERSION 3.2)
project(adventofcode2020)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(day1 ./1/app.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/1/input1.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/2/input2.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/3/input3.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/4/input4.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/5/input5.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/6/input6.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/7/input7.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/8/input8.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/9/input9.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/10/input10.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/11/input11.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/12/input12.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/13/input13.txt
  ${CMAKE_CURRENT_SOURCE_DIR}/14/input14.txt    
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(day2 ./2/app.cpp)
add_executable(day3 ./3/app.cpp)
add_executable(day4 ./4/app.cpp)
add_executable(day5 ./5/app.cpp)
add_executable(day6 ./6/app.cpp)
add_executable(day7 ./7/app.cpp)
add_executable(day8 ./8/app.cpp)
add_executable(day9 ./9/app.cpp)
add_executable(day10 ./10/app.cpp)
add_executable(day11 ./11/app.cpp)
add_executable(day12 ./12/app.cpp)
add_executable(day13 ./13/app.cpp)
add_executable(day14 ./14/app.cpp)
