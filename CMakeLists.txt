cmake_minimum_required(VERSION 3.10)
project(Downloads-Sort)
add_executable(Downloads-Sort 
  src/main.cpp
  src/config.cpp
  src/sort.cpp
)

target_include_directories(Downloads-Sort PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)