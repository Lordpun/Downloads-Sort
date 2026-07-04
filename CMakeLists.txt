cmake_minimum_required(VERSION 3.14)
project(Downloads-Sort)

include(FetchContent)

FetchContent_Declare(
  efsw
  GIT_REPOSITORY https://github.com/SpartanJ/efsw.git
  GIT_TAG master
)
FetchContent_MakeAvailable(efsw)

add_executable(Downloads-Sort 
  src/main.cpp
  src/config.cpp
  src/sort.cpp
)

target_include_directories(Downloads-Sort PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)
target_link_libraries(Downloads-Sort PRIVATE efsw)