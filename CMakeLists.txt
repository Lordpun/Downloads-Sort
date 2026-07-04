cmake_minimum_required(VERSION 3.14)
project(Downloads-Sort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  efsw
  GIT_REPOSITORY https://github.com/SpartanJ/efsw.git
  GIT_TAG master
)
set(EFSW_BUILD_DEMO OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(efsw)

add_executable(Downloads-Sort 
  src/main.cpp
  src/config.cpp
  src/sort.cpp
)

target_include_directories(Downloads-Sort PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)
target_link_libraries(Downloads-Sort PRIVATE efsw)

if(WIN32)
  target_compile_definitions(Downloads-Sort PRIVATE NOMINMAX)
endif()

if(APPLE)
  find_library(CORE_SERVICES_FRAMEWORK CoreServices)
  if(CORE_SERVICES_FRAMEWORK)
    target_link_libraries(Downloads-Sort PRIVATE ${CORE_SERVICES_FRAMEWORK})
  endif()
endif()